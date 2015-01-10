/*

Event.

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

// $Id: event.cpp 1359 2015-01-09 18:17:09Z serge $

#include "event.h"                  // self

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START
#include "../utils/init_member.h"   // INIT_MEMBER

NAMESPACE_SKYPE_WRAP_START

Event::Event(
    Event::type_e       type ):
    INIT_MEMBER( type )
{
}

Event::type_e Event::get_type() const
{
    return type_;
}

NAMESPACE_SKYPE_WRAP_END

