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

// $Id: parser_types.h 1359 2015-01-09 18:17:09Z serge $

#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START

#include "../utils/types.h"         // uint32

#include <string>

NAMESPACE_SKYPE_WRAP_START

enum class conn_status_e
{
    NONE         = 0,
    OFFLINE,
    CONNECTING,
    ONLINE,
};

enum class user_status_e
{
    NONE     = 0,
    OFFLINE,
    ONLINE,
};

enum class call_status_e
{
    NONE     = 0,
    UNPLACED,
    ROUTING,
    EARLYMEDIA,
    FAILED,
    RINGING,
    INPROGRESS,
    ONHOLD,
    FINISHED,
    MISSED,
    REFUSED,
    BUSY,
    CANCELLED,
    TRANSFERRING,
    TRANSFERRED,
    VM_BUFFERING_GREETING,
    VM_PLAYING_GREETING,
    VM_RECORDING,
    VM_UPLOADING,
    VM_SENT,
    VM_CANCELLED,
    VM_FAILED,
    WAITING_REDIAL_COMMAND,
    REDIAL_PENDING
};

conn_status_e to_conn_status( const std::string & s );
user_status_e to_user_status( const std::string & s );
call_status_e to_call_status( const std::string & s );

NAMESPACE_SKYPE_WRAP_END

#endif  // PARSER_TYPES_H
