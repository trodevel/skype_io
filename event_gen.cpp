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

// $Id: event_gen.cpp 1103 2014-10-07 18:12:21Z serge $

#include "event_gen.h"       // self

#include <iostream>             // cout
#include <sstream>              // std::ostringstream
#include <algorithm>            // std::find
#include <boost/bind.hpp>       // boost::bind
#include <boost/assert.hpp>     // BOOST_ASSERT

#include "event_parser.h"       // EventParser
#include "../utils/wrap_mutex.h"    // SCOPE_LOCK

NAMESPACE_SKYPE_WRAP_START

EventGen::EventGen()
{
}

/**
 * @return true - success, false - error
 */
bool EventGen::register_handler( ISkypeCallback * eh )
{
    if( !eh )
        return false;

    SCOPE_LOCK( mutex_ );

    if( std::find( ev_.begin(), ev_.end(), eh ) != ev_.end() )
        return false;

    ev_.push_back( eh );

    return true;
}

void EventGen::handle( const std::string & s )
{
    Event ev = EventParser::to_event( s );

    Event::type_e id = ev.get_id();

    SCOPE_LOCK( mutex_ );

    switch( id )
    {
    case Event::CONNSTATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_conn_status, _1, ev.get_conn_s() ));
        break;

    case Event::USERSTATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_user_status, _1, ev.get_user_s() ));
        break;

    case Event::CURRENTUSERHANDLE:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_current_user_handle, _1, ev.get_par_str() ));
        break;

    case Event::USER_ONLINE_STATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_user_online_status, _1, ev.get_par_str(), ev.get_user_s() ));
        break;

    case Event::CALL:
        break;
    case Event::CALL_DURATION:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_duration, _1, ev.get_call_id(), ev.get_par_int() ));
        break;

    case Event::CALL_STATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_status, _1, ev.get_call_id(), ev.get_call_s() ));
        break;

    case Event::CALL_FAILUREREASON:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_failure_reason, _1, ev.get_call_id(), ev.get_par_int() ));
        break;

    case Event::CALL_VAA_INPUT_STATUS:
        std::for_each( ev_.begin(), ev_.end(), boost::bind( &ISkypeCallback::on_call_vaa_input_status, _1, ev.get_call_id(), ev.get_par_int() ));
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
}


NAMESPACE_SKYPE_WRAP_END
