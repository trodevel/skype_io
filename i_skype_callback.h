/*

Event handler interface.

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

// $Id: i_skype_callback.h 1152 2014-10-16 18:18:55Z serge $

#ifndef I_EVENT_HANDLER_H
#define I_EVENT_HANDLER_H

#include <string>                   // std::string
#include "../utils/types.h"         // uint32
#include "parser_types.h"           // user_status_e, conn_status_e, call_status_e

#include "namespace_skypewrap.h"    // NAMESPACE_SKYPE_WRAP_START

NAMESPACE_SKYPE_WRAP_START


class ISkypeCallback
{
public:

public:
    virtual ~ISkypeCallback() {};

    virtual void on_conn_status( const conn_status_e /*s*/ )                        {};
    virtual void on_user_status( const user_status_e /*s*/ )                        {};
    virtual void on_current_user_handle( const std::string & /*s*/ )                {};
    virtual void on_user_online_status( const std::string & /*u*/, const user_status_e /*s*/ )    {};
    virtual void on_unknown( const std::string & /*g*/ )                            {};
    virtual void on_error( const uint32 /*error*/, const std::string & /*descr*/ )  {};

    virtual void on_call_status( const uint32 /*n*/, const call_status_e /*s*/ )    {};
    virtual void on_call_pstn_status( const uint32 /*n*/, const uint32 /*s*/, const std::string & /*descr*/ )    {};
    virtual void on_call_duration( const uint32 /*n*/, const uint32 /*t*/ )         {};
    virtual void on_call_failure_reason( const uint32 /*n*/, const uint32 /*t*/ )   {};
    virtual void on_call_vaa_input_status( const uint32 /*n*/, const uint32 /*s*/ ) {};
};

NAMESPACE_SKYPE_WRAP_END

#endif  // I_EVENT_HANDLER_H
