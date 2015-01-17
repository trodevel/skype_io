/*

C++ wrapper for skype_service.

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

#include "skype_service_c.h"    // self

#include <iostream>             // cout
#include <stdexcept>            // std::runtime_error

extern "C" {
#include "skype-service.h"      // SkypeService
}

#include "../utils/dummy_logger.h"      // dummy_log

#define MODULENAME      "SkypeServiceC"

NAMESPACE_SKYPE_WRAP_START

SkypeServiceC::SkypeServiceC():
    service_object_( 0L )
{
}

SkypeServiceC::~SkypeServiceC()
{
    dummy_log( 0, MODULENAME, "~SkypeServiceC()" );

    if( is_inited() )
        shutdown();
}

bool SkypeServiceC::init( const std::string & service_path, IObserver * observer )
{
    dummy_log( 0, MODULENAME, "init()" );

    if( service_object_ )
    {
        dummy_log( 0, MODULENAME, "init: already inited" );
        return false;
    }

    service_object_ = skype_service_new( observer );

    service_path_   = service_path;

    return true;
}

SkypeService *SkypeServiceC::get()
{
    if( !service_object_ )
    {
        throw std::runtime_error( "SkypeServiceC: not initialized" );
    }

    return service_object_;
}

const std::string & SkypeServiceC::get_service_path() const
{
    if( !service_object_ )
    {
        throw std::runtime_error( "SkypeServiceC: not initialized" );
    }

    return service_path_;
}

bool SkypeServiceC::shutdown()
{
    dummy_log( 0, MODULENAME, "shutdown()" );

    if( !service_object_ )
    {
        dummy_log( 0, MODULENAME, "shutdown() - already down" );
        return false;
    }

    service_object_    = 0L;

    return true;
}

bool SkypeServiceC::is_inited() const
{
    return service_object_ != 0L;
}

NAMESPACE_SKYPE_WRAP_END
