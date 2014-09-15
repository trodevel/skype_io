/*

C++ wrapper for GDK.

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

// $Id: gdk_wrap.cpp 397 2014-04-18 23:49:09Z serge $

#include "gdk_wrap.h"       // self

#include <gtk/gtk.h>        // gtk_init, gtk_main, gtk_main_quit
#include <dbus/dbus-glib.h>         // dbus_g_thread_init

#include <stdexcept>                // std::runtime_error
#include <iostream>         // cout

#include "../utils/dummy_logger.h"      // dummy_log

#define MODULENAME      "GdkWrap"


NAMESPACE_SKYPE_WRAP_START

GdkWrap::GdkWrap():
    is_inited_( false ), is_running_( false )
{
}

GdkWrap::~GdkWrap()
{
    dummy_log( 0, MODULENAME, "~GdkWrap()" );

    if( is_inited_ )
        shutdown();
}

GdkWrap& GdkWrap::get()
{
    static GdkWrap r;

    return r;
}

bool GdkWrap::init()
{
    dummy_log( 0, MODULENAME, "init()" );

    char *dummy_args[] = { 0L };
    char **argv = dummy_args;
    int argc    =   0;

    gtk_init( &argc, &argv );
    gdk_init( &argc, &argv );

    g_thread_init( NULL );
    gdk_threads_init();
    gdk_threads_enter();

    // Important: call g_type_init()
    g_type_init();
    dbus_g_thread_init(); // ???

    is_inited_  = true;

    return true;
}

bool GdkWrap::start()
{
    if( !is_inited_ )
    {
        dummy_log( 0, MODULENAME, "start() - not initialized" );
        return false;
    }

    std::cout << "main_thread: started" << std::endl;

    is_running_ = true;

    gtk_main();

    is_running_ = false;

    std::cout << "main_thread: exit" << std::endl;

    return true;
}

bool GdkWrap::shutdown()
{
    dummy_log( 0, MODULENAME, "shutdown()" );

    if( !is_inited_ )
    {
        dummy_log( 0, MODULENAME, "shutdown() - not initialized or already down" );
        return false;
    }

    if( is_running_ )
    {
        gtk_main_quit();
        is_running_ = false;
    }

    gdk_threads_leave();

    is_inited_  = false;

    return true;
}

bool GdkWrap::is_inited() const
{
    return is_inited_;
}

bool GdkWrap::is_running() const
{
    return is_running_;
}


NAMESPACE_SKYPE_WRAP_END
