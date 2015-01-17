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

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#ifndef _SKYPE_SERVICE_H_
#define _SKYPE_SERVICE_H_

// Ref:http://library.gnome.org/devel/gobject/unstable/chapter-gobject.html
//     http://live.gnome.org/DBusGlibBindings

#include <glib.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-bindings.h>
#include <dbus/dbus-glib-lowlevel.h>

// DBus path and interface
#define SKYPE_SERVICE_PATH       "/com/Skype/Client"
#define SKYPE_SERVICE_INTERFACE  "com.Skype.API.Client"

// Service Object
#define TYPE_SKYPE_SERVICE            (skype_service_get_type ())
#define SKYPE_SERVICE(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), TYPE_SKYPE_SERVICE, SkypeService))
#define SKYPE_SERVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SKYPE_SERVICE, SkypeServiceClass))
#define IS_SKYPE_SERVICE(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), TYPE_SKYPE_SERVICE))
#define IS_SKYPE_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SKYPE_SERVICE))
#define SKYPE_SERVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SKYPE_SERVICE, SkypeServiceClass))

G_BEGIN_DECLS

typedef struct _SkypeService SkypeService;
typedef struct _SkypeServiceClass SkypeServiceClass;

struct _SkypeService
{
    GObject parent;
    void    * handler;
};

struct _SkypeServiceClass
{
    GObjectClass parent;
};

gboolean skype_service_notify_callback( SkypeService *object, gchar *message, GError **error );

//SkypeService *skype_service_new( void );
SkypeService *skype_service_new( void * handler );
GType skype_service_get_type( void );

G_END_DECLS

#endif
