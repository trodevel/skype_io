/*

Skype wrapper.

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

// $Revision: 1695 $ $Date:: 2015-04-01 #$ $Author: serge $

#ifndef SKYPE_WRAP_H
#define SKYPE_WRAP_H

#include <string>                   // std::string
#include <mutex>                    // std::mutex
#include <thread>                   // std::thread
#include <atomic>                   // std::atomic

#include "namespace_lib.h"          // NAMESPACE_SKYPE_WRAP_START
#include "i_observer.h"             // IObserver

NAMESPACE_SKYPE_WRAP_START

class SkypeWrapImpl;

class SkypeWrap
{

public:
    SkypeWrap();
    ~SkypeWrap();

    bool init( IObserver * observer );

    bool shutdown();

    bool is_inited() const;

    bool send( const std::string & s );

    void control_thread();

    std::string get_error_msg() const;

private:

    SkypeWrapImpl       & impl_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_WRAP_H
