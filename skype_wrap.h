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

// $Id: skype_wrap.h 391 2014-04-18 22:51:52Z serge $

#ifndef SKYPE_WRAP_H
#define SKYPE_WRAP_H

#include <string>                   // std::string
#include <boost/thread.hpp>         // boost::mutex

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START
#include "i_observer.h"             // IObserver

NAMESPACE_SKYPE_WRAP_START

class DBus;
class DBusProxy;
class SkypeServiceC;

class SkypeWrap
{

public:
    SkypeWrap();
    ~SkypeWrap();

    bool init( IObserver * observer );
    bool shutdown();

    bool is_inited() const;

    bool send( const std::string & s, std::string & response );

    void main_thread();
    void control_thread();

    std::string get_error_msg() const;


private:

    bool shutdown__();

    bool is_inited__() const;

    void set_error_msg( const std::string & s );

    bool init__throwing( IObserver * observer );

    std::string send__p( const std::string & command );

    bool connect_to_skype();

private:
    mutable boost::mutex    mutex_;

    DBus            * dbus_;

    DBusProxy       * proxy_;

    SkypeServiceC   * service_;

    bool            is_inited_;

    std::string     error_msg_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_WRAP_H
