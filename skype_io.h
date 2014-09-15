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

// $Id: skype_io.h 1009 2014-09-15 16:37:09Z serge $

#ifndef SKYPE_IO_H
#define SKYPE_IO_H

#include <string>                   // std::string
#include <boost/thread.hpp>         // boost::mutex

#include "../threcon/i_controllable.h"      // IControllable

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START
#include "skype_wrap.h"             // SkypeWrap
#include "event_gen.h"              // EventGen

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

    bool register_handler( ISkypeCallback * eh );

    bool send_raw( const std::string & s, std::string & response );

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

    // should be called after each Skype command
    std::string get_response() const;

    void control_thread();
    void main_thread();

    std::string get_error_msg() const;


private:

private:

    mutable boost::mutex    mutex_;

    SkypeWrap               sw_;

    EventGen                event_gen_;

    std::string             response_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_IO_H
