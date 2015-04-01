/*

DBus wrapper.

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

// $Revision: 1685 $ $Date:: 2015-03-31 #$ $Author: serge $

#include "dbus.h"     // self

#include <iostream>         // cout

#include "../utils/dummy_logger.h"      // dummy_log

#define MODULENAME      "DBus"

using namespace dbus;

Error::Error()
{
    dbus_error_init( & m_ );
}

Error::Error( DBusError e )
{
    m_  = e;
}

Error::~Error()
{
}

//void Error::init()
//{
//    dbus_error_init( & m_ );
//}

DBusError & Error::get_raw()
{
    return m_;
}

Connection Bus::get( DBusBusType type, Error &error )
{
    return Connection( dbus_bus_get( type, & error.get_raw() ) );
}

void Bus::add_match(
        Connection  & connection,
        const char  * rule,
        Error       & error )
{
    dbus_bus_add_match( connection.get_raw(), rule, & error.get_raw() );
}

Connection::Connection( DBusConnection  * m ):
    is_owner_( false ),
    m_( m )
{
}

Connection::~Connection()
{
    if( is_owner_ )
    {
    }
}

DBusConnection  *Connection::get_raw()
{
    return m_;
}

bool Connection::add_filter(
        DBusHandleMessageFunction  function,
        void                      *user_data,
        DBusFreeFunction           free_data_function )
{
    return dbus_connection_add_filter( m_, function, user_data, free_data_function );
}

bool Connection::send(
        Message               & message,
        dbus_uint32_t         * client_serial )
{
    return dbus_connection_send( m_, message.get(), client_serial );
}

bool Connection::read_write_dispatch( int timeout_milliseconds )
{
    return dbus_connection_read_write_dispatch( m_, timeout_milliseconds );
}

void Connection::flush()
{
    dbus_connection_flush( m_ );
}

Message::Message(
    const char  *bus_name,
    const char  *path,
    const char  *interface,
    const char  *method ):
        is_owner_( true )
{
    m_  = dbus_message_new_method_call( bus_name, path, interface, method );
}

Message::Message( DBusMessage *message ):
        is_owner_( false ),
        m_( message )
{
}

Message::~Message()
{
    if( is_owner_ )
    {
        dbus_message_unref( m_ );
        m_  = nullptr;
    }
}

bool Message::append_args( int first_arg_type, ... )
{
    va_list var_args;

    va_start( var_args, first_arg_type );

    bool res = append_args_valist( first_arg_type, var_args );

    va_end( var_args );

    return res;
}

bool Message::append_args_valist( int first_arg_type, va_list var_args )
{
    return dbus_message_append_args_valist( m_, first_arg_type, var_args );
}

bool Message::get_args( Error &error, int first_arg_type, ... )
{
    va_list var_args;

    va_start( var_args, first_arg_type );

    bool res = get_args_args_valist( error, first_arg_type, var_args );

    va_end( var_args );

    return res;
}

bool Message::get_args_args_valist( Error &error, int first_arg_type, va_list var_args )
{
    return dbus_message_get_args_valist( m_, & error.get_raw(), first_arg_type, var_args );
}

DBusMessage *Message::get()
{
    return m_;
}

void Threads::init_default()
{
    dbus_threads_init_default();
}

