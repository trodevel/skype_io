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

// $Id: event.h 1103 2014-10-07 18:12:21Z serge $

#ifndef EVENT_H
#define EVENT_H

#include <string>                   // std::string

#include "parser_types.h"           // user_status_e, conn_status_e, call_status_e

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

class Event
{
public:
    enum type_e
    {
        UNDEF = 0,
        UNKNOWN,
        CONNSTATUS,
        USERSTATUS,
        CURRENTUSERHANDLE,
        USER_ONLINE_STATUS,
        CALL,
        CALL_DURATION,
        CALL_STATUS,
        CALL_FAILUREREASON,
        CHAT,
        CHATMEMBER,
        ALTER_CALL_SET_INPUT_SOUNDCARD,
        ALTER_CALL_SET_INPUT_PORT,
        ALTER_CALL_SET_INPUT_FILE,
        ALTER_CALL_SET_OUTPUT_SOUNDCARD,
        ALTER_CALL_SET_OUTPUT_PORT,
        ALTER_CALL_SET_OUTPUT_FILE,
        CALL_VAA_INPUT_STATUS,
    };

public:
    Event();

    Event(
        Event::type_e       id,
        const std::string   & unk,
        const std::string   & par_str,
        uint32              par_int,
        uint32              call_id,
        conn_status_e       conn_s,
        user_status_e       user_s,
        call_status_e       call_s );

    type_e get_id() const;
    uint32 get_call_id() const;
    call_status_e get_call_s() const;
    conn_status_e get_conn_s() const;
    uint32 get_par_int() const;
    const std::string& get_par_str() const;
    const std::string& get_unk() const;
    user_status_e get_user_s() const;

private:

private:

    type_e          id_;

    std::string     unk_;
    std::string     par_str_;
    uint32          par_int_;
    uint32          call_id_;
    conn_status_e   conn_s_;
    user_status_e   user_s_;
    call_status_e   call_s_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // EVENT_H
