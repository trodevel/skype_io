/*

Skype wrapper.

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

// $Id: skype_wrap.cpp 412 2014-04-22 22:02:15Z serge $

#include "skype_wrap.h"     // self

#include "dbus.h"         // DBus
#include "dbus_proxy.h"         // DBusProxy
#include "skype_service_c.h"    // SkypeServiceC
#include "gdk_wrap.h"           // GdkWrap

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/assert.hpp>     // BOOST_ASSERT
#include <iostream>         // cout

#include "../utils/wrap_mutex.h"    // SCOPE_LOCK
#include "../utils/dummy_logger.h"  // dummy_log

#define MODULENAME      "SkypeWrap"


NAMESPACE_SKYPE_WRAP_START

SkypeWrap::SkypeWrap():
    dbus_( 0L ), proxy_( 0L ), service_( 0L ), is_inited_( false )
{
}

SkypeWrap::~SkypeWrap()
{
    dummy_log( 0, MODULENAME, "~SkypeWrap()" );

    SCOPE_LOCK( mutex_ );

    if( is_inited_ )
        shutdown__();

    if( service_ )
    {
        delete service_;
        service_    = 0L;
    }

    if( proxy_ )
    {
        delete proxy_;
        proxy_      = 0L;
    }

    if( dbus_ )
    {
        delete dbus_;
        dbus_       = 0L;
    }
}

bool SkypeWrap::init( IObserver * observer )
{
    dummy_log( 0, MODULENAME, "init()" );

    SCOPE_LOCK( mutex_ );

    if( is_inited_ )
    {
        dummy_log( 0, MODULENAME, "init: already inited" );
        return false;
    }

    try
    {
        bool b = init__throwing( observer );
        if( b )
        {
            is_inited_  = true;
        }
        return b;
    }
    catch( std::exception &e )
    {
        set_error_msg( std::string( "exception - " ) + e.what() );
    }

    return false;
}

bool SkypeWrap::init__throwing( IObserver * observer )
{
    if( dbus_ )
    {
        set_error_msg( "dbus is already initialized" );
        return false;
    }

    dbus_   = new DBus();

    {
        bool b = dbus_->init();

        if( !b )
        {
            set_error_msg( "cannon initialize DBus" );
            return false;
        }
    }

    proxy_  = new DBusProxy();

    {
        bool b = proxy_->init( dbus_, "com.Skype.API", "/com/Skype" );

        if( !b )
        {
            set_error_msg( "cannon initialize DBusProxy" );
            return false;
        }
    }

    service_    = new SkypeServiceC();

    {
        bool b = service_->init( SKYPE_SERVICE_PATH, observer );

        if( !b )
        {
            set_error_msg( "cannon initialize SkypeServiceC" );
            return false;
        }
    }

    {
        bool b = connect_to_skype();
        if( !b )
        {
            set_error_msg( "cannon connect to Skype" );
            return false;
        }
    }

    return true;
}

bool SkypeWrap::is_inited() const
{
    SCOPE_LOCK( mutex_ );

    return is_inited_;
}

bool SkypeWrap::is_inited__() const
{
    return is_inited_;
}

bool SkypeWrap::send( const std::string & s, std::string & response )
{
    SCOPE_LOCK( mutex_ );

    if( !is_inited__() )
    {
        set_error_msg( "SkypeWrap: not initialized" );
        throw std::runtime_error( "SkypeWrap: not initialized" );
    }

    response = send__p( s );

    return true;
}

void SkypeWrap::set_error_msg( const std::string & s )
{
    error_msg_  = s;
}

std::string SkypeWrap::get_error_msg() const
{
    SCOPE_LOCK( mutex_ );

    return error_msg_;
}

bool SkypeWrap::shutdown()
{
    dummy_log( 0, MODULENAME, "shutdown()" );

    SCOPE_LOCK( mutex_ );

    return shutdown__();
}

bool SkypeWrap::shutdown__()
{
    if( !is_inited_ )
    {
        dummy_log( 0, MODULENAME, "shutdown() - not initialized or already down" );
        return false;
    }


    if( dbus_ )
        dbus_->unregister_service( service_ );

    if( service_ )
        service_->shutdown();

    if( proxy_ )
        proxy_->shutdown();

    if( dbus_ )
        dbus_->shutdown();

    is_inited_  = false;

    return true;
}

std::string SkypeWrap::send__p( const std::string & command )
{
    return proxy_->send( command );
}

bool SkypeWrap::connect_to_skype()
{

    // Send name
    std::string ret = send__p( "NAME TestApplication" );
    // OK or
    // ERROR 68 = Access denied.

    if( !ret.empty() )
    {
        printf( "Got=<%s>\n", ret.c_str() );
    }

    // Settle protocol
    ret = send__p( "PROTOCOL 7" ); // Try also "PROTOCOL 2" etc.
    if( !ret.empty() )
    {
        printf( "Got=<%s>\n", ret.c_str() );
    }

    // Connect notify methods
    {
        bool b = dbus_->register_service( service_ );
        if( !b )
        {
            std::cout << "failed to register service" << std::endl;
            return false;
        }
    }

    return true;
}

void SkypeWrap::control_thread()
{
    std::cout << "type exit or quit to quit: " << std::endl;

    std::string input;

    while( true )
    {
        std::cout << "your command: ";

        std::getline( std::cin, input );

        std::cout << "command: " << input << std::endl;

        if( input == "exit" || input == "quit" )
            break;

        std::string response;
        bool b = send( input, response );

        if( b == false )
        {
            std::cout << "ERROR: cannot process command '" << input << "'" << std::endl;
        }

    };

    std::cout << "exiting ..." << std::endl;

    shutdown();
}

void SkypeWrap::main_thread()
{
    GdkWrap & g = GdkWrap::get();

    if( !g.is_inited() )
    {
        set_error_msg( "GdkWrap is not initialized" );
        throw std::runtime_error( "GdkWrap is not initialized" );
    }

    if( g.is_running() )
    {
        set_error_msg( "GdkWrap is already running" );
        throw std::runtime_error( "GdkWrap is already running" );
    }

    std::cout << "SkypeWrap::main_thread: started" << std::endl;

    g.start();

    std::cout << "SkypeWrap::main_thread: exit" << std::endl;
}

NAMESPACE_SKYPE_WRAP_END
