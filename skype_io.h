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

// $Revision: 1693 $ $Date:: 2015-04-01 #$ $Author: serge $

#ifndef SKYPE_IO_H
#define SKYPE_IO_H

#include <string>                   // std::string
#include <mutex>                    // std::mutex

#include "../threcon/i_controllable.h"      // IControllable
#include "../utils/types.h"         // uint32

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START
#include "skype_wrap.h"             // SkypeWrap
#include "event_gen.h"              // EventGen
#include "parser_types.h"           // call_status_e

NAMESPACE_SKYPE_WRAP_START

class SkypeIo: public virtual threcon::IControllable
{

public:
    SkypeIo();
    ~SkypeIo();

    bool init();

    // interface threcon::IControllable
    bool shutdown();

    bool is_inited() const;

    bool register_callback( ISkypeCallback * eh );

    bool send_raw( const std::string & s );

    // Skype interface
    bool call( const std::string & s );
    bool get_call_property( uint32 id, const std::string & s );
    bool set_call_status( uint32 id, call_status_e s );
    bool alter_call_hangup( uint32 id );
    bool alter_call_set_input_soundcard( uint32 id );
    bool alter_call_set_input_port( uint32 id, uint32 p );
    bool alter_call_set_input_file( uint32 id, const std::string & s );
    bool alter_call_set_output_soundcard( uint32 id );
    bool alter_call_set_output_port( uint32 id, uint32 p );
    bool alter_call_set_output_file( uint32 id, const std::string & s );
    bool alter_call_set_capture_mic_port( uint32 id, uint32 p );
    bool alter_call_set_capture_mic_file( uint32 id, const std::string & s );

    void control_thread();

    std::string get_error_msg() const;

private:

private:

    mutable std::mutex      mutex_;

    SkypeWrap               sw_;

    EventGen                event_gen_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_IO_H
