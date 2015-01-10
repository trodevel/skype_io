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

// $Id: event.h 1359 2015-01-09 18:17:09Z serge $

#ifndef EVENT_H
#define EVENT_H

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

class Event
{
public:
    enum type_e
    {
        UNDEF = 0,
        UNKNOWN,
        ERROR,
        CONNSTATUS,
        USERSTATUS,
        CURRENTUSERHANDLE,
        USER_ONLINE_STATUS,
        CALL,
        CALL_DURATION,
        CALL_STATUS,
        CALL_PSTN_STATUS,
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
    Event(
        Event::type_e       type );

    type_e get_type() const;

private:

    type_e          type_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // EVENT_H
