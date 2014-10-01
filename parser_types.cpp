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

// $Id: parser_types.cpp 1097 2014-10-01 18:59:43Z serge $

#include "parser_types.h"     // self

#include <map>

NAMESPACE_SKYPE_WRAP_START

#define GLUE( _a, _b )  _a ## _b

#define TUPLE_VAL_STR(_x_)  _x_,#_x_
#define TUPLE_STR_VAL(_x_)  #_x_,_x_

#define TUPLE_STR_VAL_PREF(_pref,_x_)  #_x_,GLUE( _pref, _x_)

#define MAP_INSERT( _m, _val )              _m.insert( Map::value_type( TUPLE_STR_VAL( _val ) ) )
#define MAP_INSERT_PREF( _m, _pref, _val )  _m.insert( Map::value_type( TUPLE_STR_VAL_PREF( _pref, _val ) ) )

template< typename _M, typename _E, typename _S >
_M inv_value_type( _E i, _S s )
{
    return _M( s, i );
}

#define INV_SPEC(_x)     inv_value_type<Map::value_type,_x,std::string>

conn_status_e to_conn_status( const std::string & s )
{
    typedef std::map< std::string, conn_status_e > Map;
    static Map m;
    if( m.empty() )
    {
        m.insert( INV_SPEC( conn_status_e )( conn_status_e:: TUPLE_VAL_STR( NONE ) ) );
        m.insert( INV_SPEC( conn_status_e )( conn_status_e:: TUPLE_VAL_STR( OFFLINE ) ) );
        m.insert( INV_SPEC( conn_status_e )( conn_status_e:: TUPLE_VAL_STR( CONNECTING ) ) );
        m.insert( INV_SPEC( conn_status_e )( conn_status_e:: TUPLE_VAL_STR( ONLINE ) ) );
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
        m.insert( INV_SPEC( user_status_e )( user_status_e:: TUPLE_VAL_STR( NONE ) ) );
        m.insert( INV_SPEC( user_status_e )( user_status_e:: TUPLE_VAL_STR( OFFLINE ) ) );
        m.insert( INV_SPEC( user_status_e )( user_status_e:: TUPLE_VAL_STR( ONLINE ) ) );
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
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( UNPLACED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( ROUTING ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( EARLYMEDIA ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( FAILED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( RINGING ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( INPROGRESS ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( ONHOLD ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( FINISHED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( MISSED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( REFUSED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( BUSY ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( CANCELLED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( TRANSFERRING ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( TRANSFERRED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( VM_BUFFERING_GREETING ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( VM_PLAYING_GREETING ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( VM_RECORDING ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( VM_UPLOADING ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( VM_SENT ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( VM_CANCELLED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( VM_FAILED ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( WAITING_REDIAL_COMMAND ) ) );
        m.insert( INV_SPEC( call_status_e )( call_status_e:: TUPLE_VAL_STR( REDIAL_PENDING ) ) );
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

