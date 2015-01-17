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

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#include "dbus.h"     // self

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>         // cout

#include "gdk_wrap.h"       // GdkWrap

extern "C" {
//#include "skype-service.h"
#include "skype-service-object-glue.h"
}

#include "../utils/dummy_logger.h"      // dummy_log

#define MODULENAME      "DBus"


NAMESPACE_SKYPE_WRAP_START

#define DBUS_MPRIS_TIMEOUT 300 // Milliseconds

DBus::DBus():
    g_dbus_conn_( 0L )
{
}

DBus::~DBus()
{
    dummy_log( 0, MODULENAME, "~DBus()" );

    if( is_inited() )
        shutdown();
}

bool DBus::init_gtk_gdk()
{
    GdkWrap & g = GdkWrap::get();

    if( g.is_inited() )
        return false;

    return g.init();
}

bool DBus::init()
{
    dummy_log( 0, MODULENAME, "init()" );

    if( g_dbus_conn_ )
    {
        dummy_log( 0, MODULENAME, "init: already initialized" );
        return false;
    }

    {
        bool b = init_gtk_gdk();
        if( !b )
        {
            dummy_log( 0, MODULENAME, "init: Cannot init GTK, GDK" );
        }

    }

    // Connect to GLib/DBus
    GError *error = NULL;


    g_dbus_conn_ = dbus_g_bus_get( DBUS_BUS_SESSION, &error );

    if( !g_dbus_conn_ )
    {
        dummy_log( 0, MODULENAME, "dbus_player_connect_to_dbus: Cannot connect to DBus: %s\n", error ? error->message : "" );

        if( error )
            g_error_free( error );

        return false ;
    }

    return true;
}

bool DBus::is_inited() const
{
    return g_dbus_conn_ != 0L;
}

DBusGConnection *DBus::get()
{
    if( !g_dbus_conn_ )
    {
        throw DBusInitError( "get(): not initialized" );
    }

    return g_dbus_conn_;
}

bool DBus::shutdown()
{
    dummy_log( 0, MODULENAME, "shutdown()" );

    if( !g_dbus_conn_ )
    {
        dummy_log( 0, MODULENAME, "shutdown() - already down" );
        return false;
    }

    dbus_g_connection_unref( g_dbus_conn_ );

    g_dbus_conn_    = 0L;

    GdkWrap & g = GdkWrap::get();

    if( g.is_inited() )
        g.shutdown();

    return true;
}

const DBusGObjectInfo* DBus::get_object_info()
{
    return &dbus_glib_server_object_object_info;
}

NAMESPACE_SKYPE_WRAP_END
