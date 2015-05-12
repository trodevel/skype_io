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

// $Revision: 1744 $ $Date:: 2015-05-13 #$ $Author: elena $

#include "event.h"                  // self

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

Event::Event(
    Event::type_e       type,
    const std::string   & hash_id ):
    type_( type ),
    hash_id_( hash_id )
{
}

Event::type_e Event::get_type() const
{
    return type_;
}

const std::string & Event::get_hash_id() const
{
    return hash_id_;
}

bool Event::has_hash_id() const
{
    return hash_id_.empty() == false;
}

NAMESPACE_SKYPE_WRAP_END

