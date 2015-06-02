/*

Skype Low level I/O.

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 1802 $ $Date:: 2015-06-01 #$ $Author: serge $

#include "skype_low_io.h"       // self

#include <sstream>              // std::stringstream
#include <cstring>              // strchr
#include <iostream>             // cout
#include <functional>           // std::bind

#include "dbus.h"                   // dbus::Connection

#include "../utils/mutex_helper.h"  // MUTEX_SCOPE_LOCK
#include "../utils/dummy_logger.h"  // dummy_log
#include "../utils/assert.h"        // ASSERT

#define MODULENAME      "SkypeLowIo"


NAMESPACE_SKYPE_IO_START

class SkypeLowIoImpl
{

public:
    SkypeLowIoImpl();
    ~SkypeLowIoImpl();

    bool init();

    bool shutdown();

    bool is_inited() const;

    bool register_callback( ICallback * callback );

    bool send( const std::string & s );

    std::string get_error_msg() const;


private:

    //static void* thread_func_wrap( void* arg );

    void thread_func();

    static DBusHandlerResult signal_filter( DBusConnection *connection, DBusMessage *message, void *user_data );

    bool send__( const std::string & s );

    bool shutdown__();

    bool is_inited__() const;

    void set_error_msg( const std::string & s );

    bool connect_to_skype();

private:
    mutable std::mutex    mutex_;

    std::thread         thread_;

    std::atomic<bool>   must_stop_;

    dbus::Connection    dbus_;

    ICallback           * callback_;

    unsigned int    sequence_;

    bool            is_running_;

    std::string     response_;

    std::string     error_msg_;
};

SkypeLowIoImpl::SkypeLowIoImpl():
    must_stop_( true ), dbus_( nullptr ), callback_( nullptr ), sequence_( 0 ), is_running_( false )
{
}

SkypeLowIoImpl::~SkypeLowIoImpl()
{
    dummy_log_debug( MODULENAME, "~SkypeLowIoImpl()" );

    MUTEX_SCOPE_LOCK( mutex_ );

    if( is_running_ )
    {
        shutdown__();
    }
}

bool SkypeLowIoImpl::init()
{
    dummy_log_debug( MODULENAME, "init()" );

    MUTEX_SCOPE_LOCK( mutex_ );

    if( is_running_ )
    {
        dummy_log_error( MODULENAME, "init: already inited" );
        return false;
    }


    dbus::Threads::init_default();
    dbus::Error error;
    dbus_ = dbus::Bus::get( DBUS_BUS_SESSION, error );

    if( !dbus_.get_raw() )
    {
        dummy_log_error( MODULENAME, "%s: %s", error.get_raw().name, error.get_raw().message );
        return false;
    }

//  printf("unique name: %s\n", dbus_bus_get_unique_name(dbus_));
    dbus::Bus::add_match( dbus_, "path='/com/Skype/Client'", error );
    dbus_.add_filter( signal_filter, this, NULL );

    connect_to_skype();

    must_stop_  = false;

    thread_ = std::thread( std::bind( &SkypeLowIoImpl::thread_func, this ) );

    return true;
}

bool SkypeLowIoImpl::is_inited() const
{
    MUTEX_SCOPE_LOCK( mutex_ );

    return is_running_;
}

bool SkypeLowIoImpl::is_inited__() const
{
    return is_running_;
}

bool SkypeLowIoImpl::register_callback( ICallback * callback )
{
    if( callback == nullptr )
        return false;

    MUTEX_SCOPE_LOCK( mutex_ );

    if( callback_ != nullptr )
        return false;

    callback_ = callback;

    return true;
}

bool SkypeLowIoImpl::send( const std::string & s )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    if( !is_inited__() )
    {
        set_error_msg( "SkypeLowIoImpl: not initialized" );
        throw std::runtime_error( "SkypeLowIoImpl: not initialized" );
    }

    return send__( s );
}

bool SkypeLowIoImpl::send__( const std::string & s )
{
    const char* command = s.c_str();
//  std::cout << "Command: " << ss.str() << endl;
    dbus::Message message( "com.Skype.API", "/com/Skype", "com.Skype.API", "Invoke" );
    message.append_args( DBUS_TYPE_STRING, &command, DBUS_TYPE_INVALID );
    return dbus_.send( message, NULL );
}

void SkypeLowIoImpl::set_error_msg( const std::string & s )
{
    error_msg_  = s;
}

std::string SkypeLowIoImpl::get_error_msg() const
{
    MUTEX_SCOPE_LOCK( mutex_ );

    return error_msg_;
}

bool SkypeLowIoImpl::shutdown()
{
    dummy_log_debug( MODULENAME, "shutdown()" );

    return shutdown__();
}

bool SkypeLowIoImpl::shutdown__()
{
    dummy_log_trace( MODULENAME, "shutdown__()" );

    ASSERT( is_running_ );

    must_stop_  = true;

    thread_.join();

    dbus_.flush();

    return true;
}


bool SkypeLowIoImpl::connect_to_skype()
{
    send__( "NAME TestApplication" );

    send__( "PROTOCOL 5" );

    return true;
}

void SkypeLowIoImpl::thread_func()
{
    dummy_log_trace( MODULENAME, "SkypeLowIoImpl::thread_func: started" );

    is_running_ = true;

    while( true )
    {
        if( must_stop_ )
            break;

        {
            MUTEX_SCOPE_LOCK( mutex_ );

            unsigned int seq = sequence_;

            dbus_.read_write_dispatch( 100 );

            if( seq != sequence_ )
            {
                if( sequence_ - seq > 1 )
                {
                    dummy_log_fatal( MODULENAME, "SkypeLowIoImpl::thread_func: missed messages" );
                    ::exit( 42 );
                }
                if( callback_ )
                    callback_->handle( response_ );
                seq = sequence_;
            }
        }

        THIS_THREAD_SLEEP_MS( 1 );
    }

    is_running_ = false;

    dummy_log_trace( MODULENAME, "SkypeLowIoImpl::thread_func: exit" );
}

DBusHandlerResult SkypeLowIoImpl::signal_filter( DBusConnection */*connection*/, DBusMessage *message, void *user_data )
{
    SkypeLowIoImpl* priv = (SkypeLowIoImpl*)user_data;
    char *s;
    dbus::Error error;
    if( dbus::Message( message ).get_args( error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID ) )
    {
        std::stringstream ss;
        ss << "#" << priv->sequence_ << " ";
        std::string prefix = ss.str();

//      printf("Sequence is %d\n", priv->_sequence);
//      printf("Prefix is \"%s\"\n", prefix.c_str());
//      printf("Signal: Response : %s\n", s);

        // Skip sequence number for global message handler;
//        const char* ptr = s;
//        if( s[0] == '#' )
//            ptr = strchr( s, ' ' ) + 1;
        //priv->message_handler(ptr);

        priv->response_ = s;
        priv->sequence_++;

//      if (strstr(s, prefix.c_str()) == s) {
//          pthread_mutex_lock(&priv->_lock);
//          priv->_response = s + prefix.size();
//          pthread_cond_broadcast(&priv->_cond);
//          pthread_mutex_unlock(&priv->_lock);
//      }

        return DBUS_HANDLER_RESULT_HANDLED;
    }
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

}


SkypeLowIo::SkypeLowIo():
        impl_( * new SkypeLowIoImpl )
{
}

SkypeLowIo::~SkypeLowIo()
{
    delete & impl_;
}

bool SkypeLowIo::init()
{
    return impl_.init();
}

bool SkypeLowIo::shutdown()
{
    return impl_.shutdown();
}

bool SkypeLowIo::is_inited() const
{
    return impl_.is_inited();
}

bool SkypeLowIo::register_callback( ICallback * callback )
{
    return impl_.register_callback( callback );
}

bool SkypeLowIo::send( const std::string & s )
{
    return impl_.send( s );
}

std::string SkypeLowIo::get_error_msg() const
{
    return impl_.get_error_msg();
}

NAMESPACE_SKYPE_IO_END
