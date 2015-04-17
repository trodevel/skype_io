/*

SkypeIo usage example.

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

// $Revision: 1703 $ $Date:: 2015-04-14 #$ $Author: serge $

#include <thread>           // std::thread
#include <functional>       // std::bind
#include <iostream>         // cout

#include "../utils/dummy_logger.h"      // dummy_log_set_log_level
#include "skype_io.h"       // SkypeIo
#include "event.h"          // Event

class SkypeCallback: virtual public skype_wrap::ISkypeCallback
{
public:
    SkypeCallback()
    {
    }

    // callback interface
    virtual void consume( const skype_wrap::Event * e )
    {
        std::cout << "got event " << e->get_type() << std::endl;

        delete e;
    }
};


int main( int argc, char **argv )
{
    dummy_logger::set_log_level( log_levels_log4j::TRACE );

    skype_wrap::SkypeIo sio;

    bool b = sio.init();

    if( !b )
    {
        std::cout << "cannot initialize SkypeIo - " << sio.get_error_msg() << std::endl;
        return 0;
    }

    SkypeCallback test;

    sio.register_callback( &test );

    std::thread t( std::bind( &skype_wrap::SkypeIo::control_thread, &sio ) );

    t.join();

    std::cout << "Done! =)" << std::endl;

    return 0;
}
