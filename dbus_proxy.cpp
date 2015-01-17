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

#include "dbus_proxy.h"     // self

#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <dbus/dbus.h>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>         // cout

#include "dbus.h"                   // DBus

#include "../utils/dummy_logger.h"      // dummy_log

#define MODULENAME      "DBusProxy"


NAMESPACE_SKYPE_WRAP_START


DBusProxy::DBusProxy():
        proxy_send_( 0L )
{
}

DBusProxy::~DBusProxy()
{
    dummy_log( 0, MODULENAME, "~DBusProxy()" );

    if( is_inited() )
        shutdown();
}

bool DBusProxy::init( DBus * dbus, const std::string & api, const std::string & api_path )
{
    dummy_log( 0, MODULENAME, "init()" );

    if( proxy_send_ )
    {
        dummy_log( 0, MODULENAME, "ERROR: already initialized" );
        return false;
    }

    DBusGConnection *dbus_conn = dbus->get();

    const char  * api_s         = api.c_str();
    const char  * api_path_s    = api_path.c_str();

    proxy_send_ = dbus_g_proxy_new_for_name( dbus_conn, api_s, api_path_s, api_s );

    if( !proxy_send_ )
    {
        dummy_log( 0, MODULENAME, "ERROR: Cannot create proxy_send_." );
        return false ;
    }

    return true;
}

bool DBusProxy::shutdown()
{
    dummy_log( 0, MODULENAME, "shutdown()" );

    if( !proxy_send_ )
    {
        dummy_log( 0, MODULENAME, "shutdown() - already down" );
        return false;
    }

    g_object_unref( proxy_send_ );
    proxy_send_ = 0L;

    return true;

}

bool DBusProxy::is_inited() const
{
    return proxy_send_ != 0L;
}

std::string DBusProxy::send( const std::string & s )
{
    boost::mutex::scoped_lock  _( mutex_ );

    if( !proxy_send_ )
    {
        throw DBusInitError( "proxy_send_ is not initialized" );
    }

    gchar *str = NULL;
    GError *error = NULL;

    const gchar* command = s.c_str();

    if( !dbus_g_proxy_call( proxy_send_, "Invoke", &error, G_TYPE_STRING, command, G_TYPE_INVALID, G_TYPE_STRING, &str, G_TYPE_INVALID ) )
    {

        if( error )
        {
            error_msg_  = error->message;
            dummy_log( 0, MODULENAME, "ERROR: Failed to make DBus call: %s.\n", error->message );
            g_error_free( error );

            throw DBusSendError( "Failed to make DBus call: " + error_msg_ );
        }
        else
        {
            dummy_log( 0, MODULENAME, "ERROR: Failed to make DBus call." );

            throw DBusSendError( "Failed to make DBus call - unknown error" );
        }
    }

    // The caller should g_free() this value
    std::string res = str;

    g_free( str );

    return res;
}

const std::string & DBusProxy::get_error_msg() const
{
    return error_msg_;
}


NAMESPACE_SKYPE_WRAP_END
