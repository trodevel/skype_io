/*

Event parser.

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

// $Id: event_parser.cpp 414 2014-04-18 22:51:52Z serge $

#include "event_parser.h"       // self

#include <boost/assert.hpp>     // BOOST_ASSERT
#include <iostream>             // cout
#include <sstream>              // std::ostringstream
#include <boost/lexical_cast.hpp>   // lexical_cast

#include "../utils/tokenizer.h"     //

NAMESPACE_SKYPE_WRAP_START

#define KEYW_CONNSTATUS             "CONNSTATUS"
#define KEYW_CURRENTUSERHANDLE      "CURRENTUSERHANDLE"
#define KEYW_USERSTATUS             "USERSTATUS"
#define KEYW_CALL                   "CALL"
#define KEYW_DURATION               "DURATION"
#define KEYW_STATUS                 "STATUS"
#define KEYW_FAILUREREASON          "FAILUREREASON"
#define KEYW_ALTER                  "ALTER"
#define KEYW_SET_INPUT              "SET_INPUT"
#define KEYW_SET_OUTPUT             "SET_OUTPUT"
#define KEYW_FILE                   "file"
#define KEYW_VAA_INPUT_STATUS       "VAA_INPUT_STATUS"
#define KEYW_TRUE                   "TRUE"
#define KEYW_FALSE                  "FALSE"

Event EventParser::to_event( const std::string & s )
{
    std::vector< std::string > toks;

    tokenize_to_vector( toks, s, " " );

    return handle_tokens( toks, s );
}


/**
 * @param s original string
 */
Event EventParser::handle_tokens( const std::vector< std::string > & toks, const std::string & s )
{
    try
    {
        return handle_tokens__throwing( toks, s );
    }
    catch( std::exception &e )
    {
        std::cerr << "exception - " << e.what() << std::endl;
    }

    return Event();
}

Event EventParser::create_unknown( const std::string & s )
{
    static std::string  dummy_s;
    return Event( Event::UNKNOWN, s, dummy_s, 0, 0, CS_NONE, US_NONE, CLS_NONE );
}

Event EventParser::handle_tokens__throwing( const std::vector< std::string > & toks, const std::string & s )
{
    static Event        ev_dummy;

    if( toks.empty() )
        return ev_dummy;

    const std::string & keyw = toks[0];

    if( keyw == KEYW_CONNSTATUS )
    {
        return handle_connstatus( toks );
    }
    else if( keyw == KEYW_USERSTATUS )
    {
        return handle_userstatus( toks );
    }
    else if( keyw == KEYW_CURRENTUSERHANDLE )
    {
        return handle_currentuserhandle( toks );
    }
    else if( keyw == KEYW_CALL )
    {
        return handle_call( toks );
    }
    else if( keyw == KEYW_ALTER )
    {
        if( toks.size() < 2 )
            return create_unknown( s );

        if( toks[1] != KEYW_CALL )
            return create_unknown( s );

        return handle_alter_call( toks );
    }

    return create_unknown( s );

}

Event EventParser::handle_connstatus( const std::vector< std::string > & toks )
{
    if( toks.size() != 2 )
        throw WrongFormat( "expected 2 token(s)" );

    conn_status_e c = to_conn_status( toks[1] );

    std::string dummy_s;

    return Event( Event::CONNSTATUS, dummy_s, dummy_s, 0, 0, c, US_NONE, CLS_NONE );
}
Event EventParser::handle_userstatus( const std::vector< std::string > & toks )
{
    if( toks.size() != 2 )
        throw WrongFormat( "expected 2 token(s)" );

    user_status_e c = to_user_status( toks[1] );

    std::string dummy_s;

    return Event( Event::USERSTATUS, dummy_s, dummy_s, 0, 0, CS_NONE, c, CLS_NONE );
}
Event EventParser::handle_currentuserhandle( const std::vector< std::string > & toks )
{
    if( toks.size() != 2 )
        throw WrongFormat( "expected 2 token(s)" );

    const std::string & s = toks[1];

    std::string dummy_s;

    return Event( Event::CURRENTUSERHANDLE, dummy_s, s, 0, 0, CS_NONE, US_NONE, CLS_NONE );
}
Event EventParser::handle_call( const std::vector< std::string > & toks )
{
    if( toks.size() < 4 )
        throw WrongFormat( "expected at least 4 token(s)" );

    if( toks[1].empty() )
        throw WrongFormat( "CALL_ID is not defined" );

    uint32 call_id = boost::lexical_cast< uint32 >( toks[1] );

    const std::string keyw2 = toks[2];

    if( keyw2 == KEYW_DURATION )
    {
        if( toks[3].empty() )
            throw WrongFormat( "DURATION is empty" );

        uint32 dur = boost::lexical_cast< uint32 >( toks[3] );

        std::string dummy_s;

        return Event( Event::CALL_DURATION, dummy_s, dummy_s, dur, call_id, CS_NONE, US_NONE, CLS_NONE );
    }
    else if( keyw2 == KEYW_STATUS )
    {
        if( toks[3].empty() )
            throw WrongFormat( "STATUS is empty" );

        call_status_e s = to_call_status( toks[3] );

        std::string dummy_s;

        return Event( Event::CALL_STATUS, dummy_s, dummy_s, 0, call_id, CS_NONE, US_NONE, s );
    }
    else if( keyw2 == KEYW_VAA_INPUT_STATUS )
    {
        if( toks[3].empty() )
            throw WrongFormat( "VAA_INPUT_STATUS is empty" );


        if( toks[3] != KEYW_TRUE && toks[3] != KEYW_FALSE )
            throw WrongFormat( "VAA_INPUT_STATUS should be TRUE or FALSE" );

        uint32 s = ( toks[3] == KEYW_TRUE ) ? 1 : 0;

        std::string dummy_s;

        return Event( Event::CALL_VAA_INPUT_STATUS, dummy_s, dummy_s, s, call_id, CS_NONE, US_NONE, CLS_NONE );
    }
    else if( keyw2 == KEYW_FAILUREREASON )
    {
        if( toks[3].empty() )
            throw WrongFormat( "FAILUREREASON is empty" );

        uint32 c = boost::lexical_cast< uint32 >( toks[3] );

        std::string dummy_s;

        return Event( Event::CALL_FAILUREREASON, dummy_s, dummy_s, c, call_id, CS_NONE, US_NONE, CLS_NONE );
    }

    std::string dummy_s;

    return Event( Event::UNKNOWN, keyw2, dummy_s, 0, 0, CS_NONE, US_NONE, CLS_NONE );
}

Event EventParser::handle_alter_call( const std::vector< std::string > & toks )
{
    // ALTER CALL 846 SET_INPUT file="c:\test.wav"

    if( toks.size() < 5 )
        throw WrongFormat( "expected at least 5 token(s)" );

    if( toks[2].empty() )
        throw WrongFormat( "CALL_ID is not defined" );

    uint32 call_id = boost::lexical_cast< uint32 >( toks[2] );

    std::vector< std::string > pars;
    tokenize_to_vector( pars, toks[4], "=" );

    if( toks[3] == KEYW_SET_INPUT || toks[3] == KEYW_SET_OUTPUT )
    {
        bool is_input = ( toks[3] == KEYW_SET_INPUT );

        if( pars.size() != 2 )
            throw WrongFormat( "badly formed parameters - " + toks[4] );

        if( pars[0] == KEYW_FILE )
            return Event( is_input?
                    Event::ALTER_CALL_SET_INPUT_FILE :
                    Event::ALTER_CALL_SET_OUTPUT_FILE,
                    pars[1], "", 0, call_id, CS_NONE, US_NONE, CLS_NONE );
    }

    return create_unknown( toks[3] );
}


NAMESPACE_SKYPE_WRAP_END
