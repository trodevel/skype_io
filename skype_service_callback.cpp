/*

Callback function.

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

// $Id: skype_service_callback.cpp 414 2014-04-18 22:51:52Z serge $

#include "skype_service_callback.h"     // self

#include "i_observer.h"                 // IObserver

inline skype_wrap::IObserver * to_observer( void * p )
{
    return static_cast<skype_wrap::IObserver*>( p );
}

int skype_service_callback( void * handler, const char * message )
{
    if( !handler )
        return 0L;

    skype_wrap::IObserver *observer = to_observer( handler );

    std::string s( message );

    observer->handle( s );

    return 1;
}

