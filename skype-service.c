/*

Low-level Skype connection.

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

// $Id: skype-service.c 421 2014-04-18 23:51:59Z serge $

#include "skype-service.h"      // self

#include "skype_service_callback.h" // skype_service_callback

G_DEFINE_TYPE( SkypeService, skype_service, G_TYPE_OBJECT )

static void skype_service_finalize( GObject *object )
{
    G_OBJECT_CLASS( skype_service_parent_class )->finalize( object );
}

static void skype_service_class_init( SkypeServiceClass *klass )
{
    GObjectClass *object_class;
    object_class = G_OBJECT_CLASS( klass );
    object_class->finalize = skype_service_finalize;
}

static void skype_service_init( SkypeService *object )
{
    ;
}

SkypeService *skype_service_new( void * handler )
{
    SkypeService * res = g_object_new( TYPE_SKYPE_SERVICE, NULL );

    res->handler    = handler;

    return res;
}

gboolean skype_service_notify_callback( SkypeService *object, gchar *message, GError **error )
{
    // Notification messages. Called by Skype to notify its clients.

    skype_service_callback( object->handler, message );

    return TRUE;
}

