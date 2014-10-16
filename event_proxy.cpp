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

// $Id: event_proxy.cpp 1152 2014-10-16 18:18:55Z serge $

#include "event_proxy.h"        // self

#include <iostream>             // cout
#include <sstream>              // std::ostringstream
#include <algorithm>            // std::find
#include <boost/bind.hpp>       // boost::bind
#include <boost/assert.hpp>     // BOOST_ASSERT

#include "event_parser.h"       // EventParser
#include "events.h"             // CallEvent, etc.

#include "../utils/wrap_mutex.h"    // SCOPE_LOCK

NAMESPACE_SKYPE_WRAP_START

EventProxy::EventProxy()
{
}

/**
 * @return true - success, false - error
 */
bool EventProxy::register_handler( ISkypeCallback * eh )
{
    if( !eh )
        return false;

    SCOPE_LOCK( mutex_ );

    if( std::find( ev_.begin(), ev_.end(), eh ) != ev_.end() )
        return false;

    ev_.push_back( eh );

    return true;
}

void EventProxy::handle( const std::string & s )
{
    Event *ev = EventParser::to_event( s );

    Event::type_e id = ev->get_type();

    SCOPE_LOCK( mutex_ );

    switch( id )
    {
    case Event::CONNSTATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_conn_status, _1, static_cast<ConnStatusEvent*>( ev )->get_conn_s() ));
        break;

    case Event::USERSTATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_user_status, _1, static_cast<UserStatusEvent*>( ev )->get_user_s() ));
        break;

    case Event::CURRENTUSERHANDLE:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_current_user_handle, _1, static_cast<CurrentUserHandleEvent*>( ev )->get_par_str() ));
        break;

    case Event::USER_ONLINE_STATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_user_online_status, _1, static_cast<UserOnlineStatusEvent*>( ev )->get_par_str(), static_cast<UserOnlineStatusEvent*>( ev )->get_user_s() ));
        break;

    case Event::CALL:
        break;
    case Event::CALL_DURATION:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_duration, _1, static_cast<CallDurationEvent*>( ev )->get_call_id(), static_cast<CallDurationEvent*>( ev )->get_par_int() ));
        break;

    case Event::CALL_STATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_status, _1, static_cast<CallStatusEvent*>( ev )->get_call_id(), static_cast<CallStatusEvent*>( ev )->get_call_s() ));
        break;

    case Event::CALL_PSTN_STATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_pstn_status, _1, static_cast<CallPstnStatusEvent*>( ev )->get_call_id(), static_cast<CallPstnStatusEvent*>( ev )->get_par_int(), static_cast<CallPstnStatusEvent*>( ev )->get_par_str() ));
        break;

    case Event::CALL_FAILUREREASON:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_failure_reason, _1, static_cast<CallFailureReasonEvent*>( ev )->get_call_id(), static_cast<CallFailureReasonEvent*>( ev )->get_par_int() ));
        break;

    case Event::CALL_VAA_INPUT_STATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_vaa_input_status, _1, static_cast<CallVaaInputStatusEvent*>( ev )->get_call_id(), static_cast<CallVaaInputStatusEvent*>( ev )->get_par_int() ));
        break;

    case Event::ERROR:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_error, _1, static_cast<ErrorEvent*>( ev )->get_par_int(), static_cast<ErrorEvent*>( ev )->get_par_str() ));
        break;

    case Event::UNDEF:
        break;

    case Event::CHAT:
    case Event::CHATMEMBER:
        // simply ignore
        break;

    case Event::UNKNOWN:
    default:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_unknown, _1, s ));
        break;
    }

    delete ev;
}


NAMESPACE_SKYPE_WRAP_END
