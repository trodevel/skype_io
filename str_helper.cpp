/*

String helper.

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

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#include "str_helper.h"             // self

#include <map>                      // std::map

NAMESPACE_SKYPE_WRAP_START

#define TUPLE_VAL_STR(_x_)  _x_,#_x_
#define TUPLE_STR_VAL(_x_)  #_x_,_x_

#define MAP_INSERT_VAL( _m, _val )      _m.insert( Map::value_type( _val ) )

std::string StrHelper::to_string( conn_status_e l )
{
    typedef std::map< conn_status_e, std::string > Map;
    static Map m;
    if( m.empty() )
    {
        MAP_INSERT_VAL( m, conn_status_e:: TUPLE_VAL_STR( NONE ) );
        MAP_INSERT_VAL( m, conn_status_e:: TUPLE_VAL_STR( OFFLINE ) );
        MAP_INSERT_VAL( m, conn_status_e:: TUPLE_VAL_STR( CONNECTING ) );
        MAP_INSERT_VAL( m, conn_status_e:: TUPLE_VAL_STR( ONLINE ) );
    }

    if( 0 == m.count( l ) )
        return "UNDEF";

    return m[l];
}

std::string StrHelper::to_string( user_status_e l )
{
    typedef std::map< user_status_e, std::string > Map;
    static Map m;
    if( m.empty() )
    {
        MAP_INSERT_VAL( m, user_status_e:: TUPLE_VAL_STR( NONE ) );
        MAP_INSERT_VAL( m, user_status_e:: TUPLE_VAL_STR( OFFLINE ) );
        MAP_INSERT_VAL( m, user_status_e:: TUPLE_VAL_STR( ONLINE ) );
    }

    if( 0 == m.count( l ) )
        return "UNDEF";

    return m[l];
}

std::string to_string( call_status_e l )
{
    typedef std::map< call_status_e, std::string > Map;
    static Map m;
    if( m.empty() )
    {
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( UNPLACED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( ROUTING ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( EARLYMEDIA ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( FAILED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( RINGING ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( INPROGRESS ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( ONHOLD ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( FINISHED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( MISSED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( REFUSED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( BUSY ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( CANCELLED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( TRANSFERRING ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( TRANSFERRED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( VM_BUFFERING_GREETING ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( VM_PLAYING_GREETING ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( VM_RECORDING ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( VM_UPLOADING ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( VM_SENT ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( VM_CANCELLED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( VM_FAILED ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( WAITING_REDIAL_COMMAND ) );
        MAP_INSERT_VAL( m, call_status_e:: TUPLE_VAL_STR( REDIAL_PENDING ) );
    }

    if( 0 == m.count( l ) )
        return "UNDEF";

    return m[l];
}

NAMESPACE_SKYPE_WRAP_END

