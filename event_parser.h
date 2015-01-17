/*

Event* parser.

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

#ifndef EVENT_PARSER_H
#define EVENT_PARSER_H

#include <string>                   // std::string
#include <vector>                   // std::vector
#include <stdexcept>                // std::runtime_error

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

class Event;

class EventParser
{
public:
    struct WrongFormat: public std::runtime_error
    {
        WrongFormat( const std::string & str ):
            std::runtime_error( str )
        {}
    };

public:
    static Event* to_event( const std::string & s );

private:

    static Event* create_unknown( const std::string & s );

    static Event* handle_tokens( std::vector< std::string > & toks, const std::string & s );

    static Event* handle_tokens__throwing( std::vector< std::string > & toks, const std::string & s );
    static void get_keyw_and_command_id( std::vector< std::string > & toks, std::string & keyw, std::string & id );

    static Event* handle_connstatus( const std::vector< std::string > & toks );
    static Event* handle_userstatus( const std::vector< std::string > & toks );
    static Event* handle_currentuserhandle( const std::vector< std::string > & toks );
    static Event* handle_error( const std::vector< std::string > & toks );
    static Event* handle_call( const std::vector< std::string > & toks );
    static Event* handle_alter_call( const std::vector< std::string > & toks );
    static Event* handle_chat( const std::vector< std::string > & toks );
    static Event* handle_chatmember( const std::vector< std::string > & toks );
};

NAMESPACE_SKYPE_WRAP_END

#endif  // EVENT_PARSER_H
