/*

C++ wrapper for skype_service.

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

// $Id: skype_service_c.h 414 2014-04-18 22:51:52Z serge $

#ifndef SKYPE_SERVICE_C_H
#define SKYPE_SERVICE_C_H

#include <string>                   // std::string
#include "i_observer.h"             // IObserver

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START

// forward declaration of C structures
struct _SkypeService;
typedef struct _SkypeService SkypeService;


NAMESPACE_SKYPE_WRAP_START

class SkypeServiceC
{

public:
    SkypeServiceC();
    ~SkypeServiceC();

    bool init( const std::string & service_path, IObserver * observer );
    bool shutdown();

    bool is_inited() const;

    SkypeService   *get();

    const std::string & get_service_path() const;

private:


private:
    SkypeService        * service_object_;

    std::string         service_path_;
};

NAMESPACE_SKYPE_WRAP_END

#endif  // SKYPE_SERVICE_C_H
