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

// $Id: example.cpp 1357 2015-01-09 18:08:15Z serge $

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>         // cout

#include "skype_io.h"               // SkypeIo

class SkypeCallback: virtual public skype_wrap::ISkypeCallback
{
public:
    SkypeCallback()
    {
    }

    // callback interface
    virtual void consume( const skype_wrap::Event * e )
    {
    }
};


int main( int argc, char **argv )
{
    skype_wrap::SkypeIo sio;

    bool b = sio.init();

    if( !b )
    {
        std::cout << "cannot initialize SkypeIo - " << sio.get_error_msg() << std::endl;
        return 0;
    }

    SkypeCallback test;

    sio.register_callback( &test );

    boost::thread_group Tg;

    Tg.create_thread( boost::bind( &skype_wrap::SkypeIo::control_thread, &sio ) );
    Tg.create_thread( boost::bind( &skype_wrap::SkypeIo::main_thread, &sio ) );

    Tg.join_all();

    std::cout << "Done! =)" << std::endl;

    return 0;
}
