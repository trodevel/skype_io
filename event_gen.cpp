/*

Event generator.

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

// $Revision: 1691 $ $Date:: 2015-04-01 #$ $Author: serge $

#include "event_gen.h"              // self

#include "event_parser.h"           // EventParser

#include "../utils/wrap_mutex.h"    // SCOPE_LOCK
#include "../utils/assert.h"        // ASSERT

NAMESPACE_SKYPE_WRAP_START

EventGen::EventGen():
    callback_( nullptr )
{
}

/**
 * @return true - success, false - error
 */
bool EventGen::register_callback( ISkypeCallback * callback )
{
    if( callback == nullptr )
        return false;

    SCOPE_LOCK( mutex_ );

    ASSERT( callback_ == nullptr );

    callback_ = callback;

    return true;
}

void EventGen::handle( const std::string & s )
{
    std::cout << "EventGen::handle: " << s << std::endl;

    Event *ev = EventParser::to_event( s );

    SCOPE_LOCK( mutex_ );

    callback_->consume( ev );
}


NAMESPACE_SKYPE_WRAP_END
