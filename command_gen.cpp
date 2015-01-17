/*

Skype command generator.

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

#include "command_gen.h"        // self

#include <sstream>              // std::ostringstream
#include <map>                  // std::map

#include "str_helper.h"         // to_string

NAMESPACE_SKYPE_WRAP_START

std::string CommandGen::protocol( uint32 n )
{
    std::ostringstream os;

    os << "PROTOCOL " << n;

    return os.str();
}
std::string CommandGen::call( const std::string & s )
{
    std::ostringstream os;

    os << "CALL " << s;

    return os.str();
}
std::string CommandGen::get_call_property( uint32 id, const std::string & s )
{
    std::ostringstream os;

    os << "GET CALL " << id << " " << s;

    return os.str();
}

std::string CommandGen::set_call_status( uint32 id, call_status_e s )
{
    std::ostringstream os;

    os << "SET CALL " << id << " STATUS " << to_string( s );

    return os.str();
}
std::string CommandGen::alter_call_hangup( uint32 id )
{
    std::ostringstream os;

    os << "ALTER CALL " << id << " HANGUP";

    return os.str();
}


std::string alter_call_set_io_val( uint32 id, const std::string & inp_outp,
        const std::string & what, const std::string & val )
{
    std::ostringstream os;

    os << "ALTER CALL " << id << " " << inp_outp << " " << what << "=\"" << val << "\"";

    return os.str();
}


std::string CommandGen::alter_call_set_input_soundcard( uint32 id )
{
    return alter_call_set_io_val( id, "SET_INPUT", "soundcard", "default" );
}
std::string CommandGen::alter_call_set_input_port( uint32 id, uint32 p )
{
    std::ostringstream os;

    os << p;

    return alter_call_set_io_val( id, "SET_INPUT", "port", os.str() );
}
std::string CommandGen::alter_call_set_input_file( uint32 id, const std::string & s )
{
    return alter_call_set_io_val( id, "SET_INPUT", "file", s );
}

std::string CommandGen::alter_call_set_output_soundcard( uint32 id )
{
    return alter_call_set_io_val( id, "SET_OUTPUT", "soundcard", "default" );
}
std::string CommandGen::alter_call_set_output_port( uint32 id, uint32 p )
{
    std::ostringstream os;

    os << p;

    return alter_call_set_io_val( id, "SET_OUTPUT", "port", os.str() );
}
std::string CommandGen::alter_call_set_output_file( uint32 id, const std::string & s )
{
    return alter_call_set_io_val( id, "SET_OUTPUT", "file", s );
}
std::string CommandGen::alter_call_set_capture_mic_port( uint32 id, uint32 p )
{
    std::ostringstream os;

    os << p;

    return alter_call_set_io_val( id, "SET_CAPTURE_MIC", "port", os.str() );
}

std::string CommandGen::alter_call_set_capture_mic_file( uint32 id, const std::string & s )
{
    return alter_call_set_io_val( id, "SET_CAPTURE_MIC", "file", s );
}


NAMESPACE_SKYPE_WRAP_END
