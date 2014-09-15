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

// $Id: dbus.h 396 2014-04-18 23:45:14Z serge $

#ifndef SKYPE_DBUS_H
#define SKYPE_DBUS_H

#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>

#include <string>                   // std::string
#include <stdexcept>                // std::runtime_error
#include <boost/thread.hpp>         // boost::mutex

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START

extern "C" {
#include "skype-service.h"
}

NAMESPACE_SKYPE_WRAP_START

class DBus
{

public:
    DBus();
    ~DBus();

    bool init();
    bool shutdown();

    bool is_inited() const;

    //DBusGConnection *dbus_player_connect_to_dbus();
    DBusGConnection *get();

    template<typename _T>
    bool register_service( _T * service_object )
    {
        // Create a receiver object
        if( !service_object )
        {
            return false;
            // Same as: g_object_new(TYPE_SKYPE_SERVICE, NULL);
        }

        // Connect to DBus
        DBusGConnection *dbus_conn = get();


        const char * service_path_s = service_object->get_service_path().c_str();

        dbus_g_object_type_install_info( G_TYPE_FROM_INSTANCE( service_object->get() ), get_object_info() );
        dbus_g_connection_register_g_object( dbus_conn, service_path_s/*/com/Skype/Client*/, (GObject*)service_object->get() );

        g_print( "Setup of service object and notify calls done and OK.\n" );

        return true;
    }

    template<typename _T>
    bool unregister_service( _T * service_object )
    {
        // Create a receiver object
        if( !service_object )
        {
            return false;
            // Same as: g_object_new(TYPE_SKYPE_SERVICE, NULL);
        }

        g_object_unref( service_object->get() );

        return true;
    }

private:

    bool init_gtk_gdk();

    static const DBusGObjectInfo* get_object_info();


private:
    DBusGConnection     * g_dbus_conn_;
};

class DBusSendError: public std::runtime_error
{
public:
    DBusSendError( const std::string& s ) :
        std::runtime_error( "DbSe-" + s )
    {
    }
};

class DBusInitError: public std::runtime_error
{
public:
    DBusInitError( const std::string& s ) :
        std::runtime_error( "DbIe-" + s )
    {
    }
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_DBUS_H
