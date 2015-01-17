/*

DBus Proxy wrapper.

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

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#ifndef DBUS_PROXY_H
#define DBUS_PROXY_H

#include <dbus/dbus-glib.h>         // DBusGProxy

#include <string>                   // std::string
#include <stdexcept>                // std::runtime_error
#include <boost/thread.hpp>         // boost::mutex

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

class DBus;

class DBusProxy
{
public:
    DBusProxy();
    ~DBusProxy();

    bool init( DBus * dbus, const std::string & api, const std::string & api_path );

    bool shutdown();

    bool is_inited() const;

    std::string send( const std::string & s );

    const std::string & get_error_msg() const;

private:
    boost::mutex        mutex_;

    DBusGProxy          * proxy_send_;

    std::string         error_msg_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // DBUS_PROXY_H
