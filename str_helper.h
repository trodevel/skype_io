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

// $Id: str_helper.h 1359 2015-01-09 18:17:09Z serge $

#include "parser_types.h"           // conn_status_e, user_status_e, call_status_e

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

class StrHelper
{
public:
    static std::string to_string( conn_status_e l );
    static std::string to_string( user_status_e l );
};

std::string to_string( call_status_e l );

NAMESPACE_SKYPE_WRAP_END
