/*

Event generator.

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

// $Id: event_proxy.h 1357 2015-01-09 18:08:15Z serge $

#ifndef EVENT_PROXY_H
#define EVENT_PROXY_H

#include <boost/thread.hpp>         // boost::mutex

#include "i_observer.h"             // IObserver
#include "i_skype_callback.h"       // ISkypeCallback

NAMESPACE_SKYPE_WRAP_START

class EventProxy: public IObserver
{
public:
    EventProxy();

    virtual void handle( const std::string & s );

    bool register_callback( ISkypeCallback * callback );

private:
    mutable boost::mutex        mutex_;

    ISkypeCallback              * callback_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // EVENT_PROXY_H
