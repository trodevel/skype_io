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

// $Id: skype_io.h 427 2014-04-22 17:01:05Z serge $

#ifndef SKYPE_IO_H
#define SKYPE_IO_H

#include <string>                   // std::string
#include <boost/thread.hpp>         // boost::mutex

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START
#include "skype_wrap.h"             // SkypeWrap
#include "event_gen.h"              // EventGen

NAMESPACE_SKYPE_WRAP_START

class SkypeIo
{

public:
    SkypeIo();
    ~SkypeIo();

    bool init();

    bool shutdown();

    bool is_inited() const;

    bool register_handler( ISkypeCallback * eh );

    bool send( const std::string & s, std::string & response );

    void control_thread();
    void main_thread();

    std::string get_error_msg() const;

private:

private:

    mutable boost::mutex    mutex_;

    SkypeWrap               sw_;

    EventGen                event_gen_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_IO_H
