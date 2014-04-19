/*

C++ wrapper for GDK.

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

// $Id: gdk_wrap.h 414 2014-04-18 22:51:52Z serge $

#ifndef GDK_WRAP_H
#define GDK_WRAP_H

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START

class GdkWrap
{
private:
    GdkWrap();

public:
    static GdkWrap& get();

    ~GdkWrap();

    bool init();
    bool start();
    bool shutdown();

    bool is_inited() const;
    bool is_running() const;

private:



private:

    bool    is_inited_;
    bool    is_running_;
};


NAMESPACE_SKYPE_WRAP_END

#endif  // GDK_WRAP_H
