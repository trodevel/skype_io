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

// $Id: events.h 1129 2014-10-10 17:32:51Z serge $

#ifndef EVENTS_H
#define EVENTS_H

#include <string>                   // std::string

#include "event.h"                  // Event
#include "parser_types.h"           // user_status_e, conn_status_e, call_status_e
#include "../utils/init_member.h"   // INIT_MEMBER

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

class EventDataStr
{
public:
    EventDataStr(
        const std::string   & par_str ):
            INIT_MEMBER( par_str )
    {
    }

    const std::string& get_par_str() const
    {
        return par_str_;
    }

private:
    std::string     par_str_;
};

class EventDataInt
{
public:
    EventDataInt(
        uint32              par_int ):
            INIT_MEMBER( par_int )
    {
    }

    uint32 get_par_int() const
    {
        return par_int_;
    }

private:
    uint32          par_int_;
};




class BasicCallEvent: public Event
{
public:
    BasicCallEvent();

    BasicCallEvent(
        Event::type_e       type,
        uint32              call_id ):
            Event( type ),
            call_id_( call_id )
    {
    }

    uint32 get_call_id() const
    {
        return call_id_;
    }

private:

    uint32          call_id_;
};

class BasicCallParamEvent: public BasicCallEvent, public EventDataInt
{
public:
    BasicCallParamEvent(
        Event::type_e       type,
        uint32              call_id,
        uint32              par_int ):
            BasicCallEvent( type, call_id ),
            EventDataInt( par_int )
    {
    }
};

class BasicCallParamStrEvent: public BasicCallEvent, public EventDataStr
{
public:
    BasicCallParamStrEvent(
        Event::type_e       type,
        uint32              call_id,
        const std::string   & par_str ):
            BasicCallEvent( type, call_id ),
            EventDataStr( par_str )
    {
    }
};



class BasicParamEvent: public Event, public EventDataStr
{
public:
    BasicParamEvent(
        Event::type_e       type,
        const std::string   & par_str ):
            Event( type ),
            EventDataStr( par_str )
    {
    }
};



class ConnStatusEvent: public Event
{
public:
    ConnStatusEvent(
        conn_status_e       conn_s ):
        Event( Event::CONNSTATUS ),
        INIT_MEMBER( conn_s )
    {
    }

    conn_status_e get_conn_s() const
    {
        return conn_s_;
    }

private:

    conn_status_e   conn_s_;
};

class UserStatusEvent: public Event
{
public:
    UserStatusEvent(
        user_status_e       user_s ):
        Event( Event::USERSTATUS ),
        INIT_MEMBER( user_s )
    {
    }

    user_status_e get_user_s() const
    {
        return user_s_;
    }

private:

private:
    user_status_e   user_s_;
};

class CurrentUserHandleEvent: public BasicParamEvent
{
public:
    CurrentUserHandleEvent(
        const std::string   & par_str ):
            BasicParamEvent( Event::CURRENTUSERHANDLE, par_str )
    {
    }

};

class UserOnlineStatusEvent: public BasicParamEvent
{
public:
    UserOnlineStatusEvent(
        const std::string   & par_str,
        user_status_e       user_s):
            BasicParamEvent( Event::USER_ONLINE_STATUS, par_str ),
            INIT_MEMBER( user_s )
    {
    }

    user_status_e get_user_s() const
    {
        return user_s_;
    }
private:
    user_status_e   user_s_;
};

class CallEvent: public BasicCallEvent
{
public:

    CallEvent(
        uint32              call_id ):
            BasicCallEvent( Event::CALL, call_id )
    {
    }
};

class CallDurationEvent: public BasicCallParamEvent
{
public:
    CallDurationEvent(
        uint32              call_id,
        uint32              par_int ):
            BasicCallParamEvent( Event::CALL_DURATION, call_id, par_int )
    {
    }
};

class CallStatusEvent: public BasicCallEvent
{
public:
    CallStatusEvent(
        uint32              call_id,
        call_status_e       call_s ):
            BasicCallEvent( Event::CALL_STATUS, call_id ),
            INIT_MEMBER( call_s )
    {
    }

    call_status_e get_call_s() const
    {
        return call_s_;
    }


private:
    call_status_e   call_s_;
};

class CallPstnStatusEvent: public BasicCallParamEvent, public EventDataStr
{
public:
    CallPstnStatusEvent(
        uint32              call_id,
        uint32              errorcode,
        const std::string   & descr ):
            BasicCallParamEvent( Event::CALL_PSTN_STATUS, call_id, errorcode ),
            EventDataStr( descr )
    {
    }
};

class CallFailureReasonEvent: public BasicCallParamEvent
{
public:
    CallFailureReasonEvent(
            uint32              call_id,
            uint32              par_int ):
                BasicCallParamEvent( Event::CALL_FAILUREREASON, call_id, par_int )
    {
    }
};

class CallVaaInputStatusEvent: public BasicCallParamEvent
{
public:
    CallVaaInputStatusEvent(
            uint32              call_id,
            uint32              par_int ):
                BasicCallParamEvent( Event::CALL_VAA_INPUT_STATUS, call_id, par_int )
    {
    }
};

NAMESPACE_SKYPE_WRAP_END

#endif  // EVENTS_H
