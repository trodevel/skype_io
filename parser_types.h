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

// $Id: parser_types.h 474 2014-04-29 17:49:24Z serge $

#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START

#include "../utils/types.h"         // uint32

#include <string>

NAMESPACE_SKYPE_WRAP_START

enum conn_status_e
{
    CS_NONE         = 0,
    CS_OFFLINE,
    CS_CONNECTING,
    CS_ONLINE,
};

enum user_status_e
{
    US_NONE     = 0,
    US_OFFLINE,
    US_ONLINE,
};

enum call_status_e
{
    CLS_NONE     = 0,
    CLS_UNPLACED,
    CLS_ROUTING,
    CLS_RINGING,
    CLS_INPROGRESS,
    CLS_FINISHED
};

conn_status_e to_conn_status( const std::string & s );
user_status_e to_user_status( const std::string & s );
call_status_e to_call_status( const std::string & s );

NAMESPACE_SKYPE_WRAP_END

#endif  // PARSER_TYPES_H
