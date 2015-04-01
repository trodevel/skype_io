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

// $Revision: 1679 $ $Date:: 2015-03-31 #$ $Author: serge $

#ifndef SKYPE_WRAP_H
#define SKYPE_WRAP_H

#include <string>                   // std::string
#include <mutex>                    // std::mutex
#include <thread>                   // std::thread
#include <atomic>                   // std::atomic

#include <dbus/dbus.h>              // DBusConnection
#include "dbus.h"                   // dbus::Connection

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START
#include "i_observer.h"             // IObserver

NAMESPACE_SKYPE_WRAP_START

class DBus;
class DBusProxy;
class SkypeServiceC;

class SkypeWrap
{

public:
    SkypeWrap();
    ~SkypeWrap();

    bool init( IObserver * observer );

    bool start();
    bool shutdown();

    bool is_inited() const;

    bool send( const std::string & s );

    void control_thread();

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

    IObserver       * callback_;

    unsigned int    sequence_;

    bool            is_running_;

    std::string     response_;

    std::string     error_msg_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_WRAP_H
