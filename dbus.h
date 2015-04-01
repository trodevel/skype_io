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

// $Revision: 1684 $ $Date:: 2015-03-31 #$ $Author: serge $

#ifndef DBUS_CPP_DBUS_H
#define DBUS_CPP_DBUS_H

#include <dbus/dbus.h>

#include <string>           // std::string
#include <stdarg.h>         // va_list stuff

namespace dbus
{

class Connection;
class Message;

class Error
{
public:

    Error();
    Error( DBusError e );
    ~Error();

//    void init();

    DBusError & get_raw();

private:
    DBusError m_;
};

class Bus
{
public:

    static Connection get( DBusBusType type, Error &error );

    static void add_match(
            Connection  & connection,
            const char  * rule,
            Error       & error );
};

class Connection
{
public:

    Connection( DBusConnection  * m );
    ~Connection();

    DBusConnection  *get_raw();

    bool add_filter(
            DBusHandleMessageFunction  function,
            void                      *user_data,
            DBusFreeFunction           free_data_function );

    bool send(
            Message               & message,
            dbus_uint32_t         * client_serial );

    bool read_write_dispatch( int timeout_milliseconds );

    void flush();

private:

    bool            is_owner_;

    DBusConnection  * m_;
};

class Message
{
public:

    Message(
        const char  *bus_name,
        const char  *path,
        const char  *interface,
        const char  *method );

    Message( DBusMessage *message );

    ~Message();

     bool append_args( int first_arg_type, ... );
     bool append_args_valist( int first_arg_type, va_list var_args );

     bool get_args( Error &error, int first_arg_type, ... );
     bool get_args_args_valist( Error &error, int first_arg_type, va_list var_args );

     DBusMessage *get();

private:

     bool           is_owner_;

     DBusMessage    * m_;

};

class Threads
{
public:
    static void init_default();
};

} // namespace dbus

#endif  // DBUS_CPP_DBUS_H
