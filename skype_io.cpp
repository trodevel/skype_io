/*

Skype I/O.

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

// $Id: skype_io.cpp 438 2014-04-23 16:45:36Z serge $

#include "skype_io.h"       // self

#include "../utils/wrap_mutex.h"    // SCOPE_LOCK
#include "../utils/dummy_logger.h"  // dummy_log
#include "command_gen.h"            // CommandGen

#define MODULENAME      "SkypeIo"


NAMESPACE_SKYPE_WRAP_START

SkypeIo::SkypeIo()
{
}

SkypeIo::~SkypeIo()
{
    dummy_log( 0, MODULENAME, "~SkypeIo()" );

    SCOPE_LOCK( mutex_ );

    sw_.shutdown();
}

bool SkypeIo::init()
{
    dummy_log( 0, MODULENAME, "init()" );

    SCOPE_LOCK( mutex_ );

    if( sw_.is_inited() )
    {
        dummy_log( 0, MODULENAME, "init: already inited" );
        return false;
    }

    bool b = sw_.init( &event_gen_ );

    if( b == false )
    {
        return false;
    }

    return true;
}

bool SkypeIo::is_inited() const
{
    SCOPE_LOCK( mutex_ );

    return sw_.is_inited();
}

bool SkypeIo::send_raw( const std::string & s, std::string & response )
{
    SCOPE_LOCK( mutex_ );

    return sw_.send( s, response );
}

std::string SkypeIo::get_error_msg() const
{
    SCOPE_LOCK( mutex_ );

    return sw_.get_error_msg();
}

bool SkypeIo::shutdown()
{
    dummy_log( 0, MODULENAME, "shutdown()" );

    SCOPE_LOCK( mutex_ );

    return sw_.shutdown();
}

bool SkypeIo::register_handler( ISkypeCallback * eh )
{
    SCOPE_LOCK( mutex_ );

    return event_gen_.register_handler( eh );
}

void SkypeIo::control_thread()
{
    sw_.control_thread();
}

void SkypeIo::main_thread()
{
    sw_.main_thread();
}

// Skype interface
bool SkypeIo::call( const std::string & s )
{
    std::string cmd = CommandGen::call( s );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::get_call_property( uint32 id, const std::string & s )
{
    std::string cmd = CommandGen::get_call_property( id, s );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::set_call_status( uint32 id, call_status_e s )
{
    std::string cmd = CommandGen::set_call_status( id, s );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_hangup( uint32 id )
{
    std::string cmd = CommandGen::alter_call_hangup( id );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_input_soundcard( uint32 id )
{
    std::string cmd = CommandGen::alter_call_set_input_soundcard( id );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_input_port( uint32 id, uint32 p )
{
    std::string cmd = CommandGen::alter_call_set_input_port( id, p );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_input_file( uint32 id, const std::string & s )
{
    std::string cmd = CommandGen::alter_call_set_input_file( id, s );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_output_soundcard( uint32 id )
{
    std::string cmd = CommandGen::alter_call_set_output_soundcard( id );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_output_port( uint32 id, uint32 p )
{
    std::string cmd = CommandGen::alter_call_set_output_port( id, p );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_output_file( uint32 id, const std::string & s )
{
    std::string cmd = CommandGen::alter_call_set_output_file( id, s );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_capture_mic_port( uint32 id, uint32 p )
{
    std::string cmd = CommandGen::alter_call_set_capture_mic_port( id, p );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}
bool SkypeIo::alter_call_set_capture_mic_file( uint32 id, const std::string & s )
{
    std::string cmd = CommandGen::alter_call_set_capture_mic_file( id, s );

    SCOPE_LOCK( mutex_ );

    return sw_.send( cmd, response_ );
}

// should be called after each Skype command
std::string SkypeIo::get_response() const
{
    SCOPE_LOCK( mutex_ );

    return response_;
}


NAMESPACE_SKYPE_WRAP_END
