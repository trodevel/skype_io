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

// $Id: parser_types.cpp 391 2014-04-18 22:51:52Z serge $

#include "parser_types.h"     // self

#include <map>

NAMESPACE_SKYPE_WRAP_START

#define GLUE( _a, _b )  _a ## _b

#define TUPLE_VAL_STR(_x_)  _x_,#_x_
#define TUPLE_STR_VAL(_x_)  #_x_,_x_

#define TUPLE_STR_VAL_PREF(_pref,_x_)  #_x_,GLUE(_pref,_x_)

#define MAP_INSERT( _m, _val )              _m.insert( Map::value_type( TUPLE_STR_VAL( _val ) ) )
#define MAP_INSERT_PREF( _m, _pref, _val )  _m.insert( Map::value_type( TUPLE_STR_VAL_PREF( _pref, _val ) ) )

conn_status_e to_conn_status( const std::string & s )
{
    typedef std::map< std::string, conn_status_e > Map;
    static Map m;
    if( m.empty() )
    {
        MAP_INSERT_PREF( m, CS_, NONE );
        MAP_INSERT_PREF( m, CS_, OFFLINE );
        MAP_INSERT_PREF( m, CS_, CONNECTING );
        MAP_INSERT_PREF( m, CS_, ONLINE );
    }

    if( 0 == m.count( s ) )
        return CS_NONE;

    return m[s];
}

user_status_e to_user_status( const std::string & s )
{
    typedef std::map< std::string, user_status_e > Map;
    static Map m;
    if( m.empty() )
    {
        MAP_INSERT_PREF( m, US_, NONE );
        MAP_INSERT_PREF( m, US_, OFFLINE );
        MAP_INSERT_PREF( m, US_, ONLINE );
    }

    if( 0 == m.count( s ) )
        return US_NONE;

    return m[s];
}

call_status_e to_call_status( const std::string & s )
{
    typedef std::map< std::string, call_status_e > Map;
    static Map m;
    if( m.empty() )
    {
        MAP_INSERT_PREF( m, CLS_, NONE );
        MAP_INSERT_PREF( m, CLS_, UNPLACED );
        MAP_INSERT_PREF( m, CLS_, ROUTING );
        MAP_INSERT_PREF( m, CLS_, RINGING );
        MAP_INSERT_PREF( m, CLS_, INPROGRESS );
        MAP_INSERT_PREF( m, CLS_, FINISHED );
    }

    if( 0 == m.count( s ) )
        return CLS_NONE;

    return m[s];
}


bool to_bool( const std::string & s )
{
    if( s == "true" || s == "TRUE" || s == "True" )
        return true;
    return false;
}

NAMESPACE_SKYPE_WRAP_END

