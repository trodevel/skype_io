/*

Skype Low level I/O.

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

// $Revision: 1802 $ $Date:: 2015-06-01 #$ $Author: serge $

#ifndef SKYPE_LOW_IO_H
#define SKYPE_LOW_IO_H

#include <string>                   // std::string
#include <mutex>                    // std::mutex
#include <thread>                   // std::thread
#include <atomic>                   // std::atomic

#include "namespace_lib.h"          // NAMESPACE_SKYPE_IO_START
#include "i_callback.h"             // ICallback

NAMESPACE_SKYPE_IO_START

class SkypeLowIoImpl;

class SkypeLowIo
{

public:
    SkypeLowIo();
    ~SkypeLowIo();

    bool init();

    bool shutdown();

    bool is_inited() const;

    bool register_callback( ICallback * callback );

    bool send( const std::string & s );

    std::string get_error_msg() const;

private:

    SkypeLowIoImpl       & impl_;
};

NAMESPACE_SKYPE_IO_END

#endif  // SKYPE_LOW_IO_H
