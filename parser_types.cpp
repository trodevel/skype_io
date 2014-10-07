/*

Auxiliary parsing functions.

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

// $Id: parser_types.cpp 1100 2014-10-06 17:21:16Z serge $

#include "parser_types.h"     // self

#include <map>

NAMESPACE_SKYPE_WRAP_START

#define TUPLE_VAL_STR(_x_)  _x_,#_x_
#define TUPLE_STR_VAL(_x_)  #_x_,_x_

template< typename _M, typename _U, typename _V >
void insert_inverse_pair( _M & map, _U first, _V second )
{
    map.insert( typename _M::value_type( second, first ) );
}

conn_status_e to_conn_status( const std::string & s )
{
    typedef std::map< std::string, conn_status_e > Map;
    static Map m;
    if( m.empty() )
    {
        insert_inverse_pair( m, conn_status_e:: TUPLE_VAL_STR( NONE ) );
        insert_inverse_pair( m, conn_status_e:: TUPLE_VAL_STR( OFFLINE ) );
        insert_inverse_pair( m, conn_status_e:: TUPLE_VAL_STR( CONNECTING ) );
        insert_inverse_pair( m, conn_status_e:: TUPLE_VAL_STR( ONLINE ) );
    }

    if( 0 == m.count( s ) )
        return conn_status_e::NONE;

    return m[s];
}

user_status_e to_user_status( const std::string & s )
{
    typedef std::map< std::string, user_status_e > Map;
    static Map m;
    if( m.empty() )
    {
        insert_inverse_pair( m, user_status_e:: TUPLE_VAL_STR( NONE ) );
        insert_inverse_pair( m, user_status_e:: TUPLE_VAL_STR( OFFLINE ) );
        insert_inverse_pair( m, user_status_e:: TUPLE_VAL_STR( ONLINE ) );
    }

    if( 0 == m.count( s ) )
        return user_status_e::NONE;

    return m[s];
}

call_status_e to_call_status( const std::string & s )
{
    typedef std::map< std::string, call_status_e > Map;
    static Map m;
    if( m.empty() )
    {
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( UNPLACED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( ROUTING ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( EARLYMEDIA ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( FAILED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( RINGING ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( INPROGRESS ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( ONHOLD ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( FINISHED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( MISSED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( REFUSED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( BUSY ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( CANCELLED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( TRANSFERRING ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( TRANSFERRED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( VM_BUFFERING_GREETING ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( VM_PLAYING_GREETING ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( VM_RECORDING ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( VM_UPLOADING ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( VM_SENT ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( VM_CANCELLED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( VM_FAILED ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( WAITING_REDIAL_COMMAND ) );
        insert_inverse_pair( m, call_status_e:: TUPLE_VAL_STR( REDIAL_PENDING ) );
    }

    if( 0 == m.count( s ) )
        return call_status_e::NONE;

    return m[s];
}


bool to_bool( const std::string & s )
{
    if( s == "true" || s == "TRUE" || s == "True" )
        return true;
    return false;
}

NAMESPACE_SKYPE_WRAP_END

