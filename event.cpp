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

// $Id: event.cpp 391 2014-04-18 22:51:52Z serge $

#include "event.h"                  // user_status_e, conn_status_e, call_status_e

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START
#include "../utils/init_member.h"   // INIT_MEMBER

NAMESPACE_SKYPE_WRAP_START


Event::Event():
    id_( UNDEF ),
    par_int_( 0 ),
    call_id_( 0 ),
    conn_s_( CS_NONE ),
    user_s_( US_NONE ),
    call_s_( CLS_NONE )
{
}

Event::Event(
    Event::type_e       id,
    const std::string   & unk,
    const std::string   & par_str,
    uint32              par_int,
    uint32              call_id,
    conn_status_e       conn_s,
    user_status_e       user_s,
    call_status_e       call_s ):
    INIT_MEMBER( id ),
    INIT_MEMBER( unk ),
    INIT_MEMBER( par_str ),
    INIT_MEMBER( par_int ),
    INIT_MEMBER( call_id ),
    INIT_MEMBER( conn_s ),
    INIT_MEMBER( user_s ),
    INIT_MEMBER( call_s )
{
}


Event::type_e Event::get_id() const
{
    return id_;
}

uint32 Event::get_call_id() const
{
    return call_id_;
}

call_status_e Event::get_call_s() const
{
    return call_s_;
}

conn_status_e Event::get_conn_s() const
{
    return conn_s_;
}

uint32 Event::get_par_int() const
{
    return par_int_;
}

const std::string& Event::get_par_str() const
{
    return par_str_;
}

const std::string& Event::get_unk() const
{
    return unk_;
}

user_status_e Event::get_user_s() const
{
    return user_s_;
}

NAMESPACE_SKYPE_WRAP_END

