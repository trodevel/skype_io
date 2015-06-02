/*

SkypeLowIo usage example.

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

#include <thread>           // std::thread
#include <functional>       // std::bind
#include <iostream>         // cout

#include "../utils/dummy_logger.h"      // dummy_log_set_log_level
#include "skype_low_io.h"   // SkypeLowIo

class Callback: virtual public skype_io::ICallback
{
public:

    Callback( skype_io::SkypeLowIo * sio ):
        sio_( sio )
    {
    }

    // callback interface
    virtual void handle( const std::string & s )
    {
        std::cout << "got " << s << std::endl;
    }

    void control_thread()
    {
        std::cout << "type exit or quit to quit: " << std::endl;

        std::string input;

        while( true )
        {
            std::cout << "your command: ";

            std::getline( std::cin, input );

            std::cout << "command: " << input << std::endl;

            if( input == "exit" || input == "quit" )
                break;

            bool b = sio_->send( input );

            if( b == false )
            {
                std::cout << "ERROR: cannot process command '" << input << "'" << std::endl;
            }

        };

        std::cout << "exiting ..." << std::endl;

        sio_->shutdown();
    }

private:
    skype_io::SkypeLowIo * sio_;

};


int main( int argc, char **argv )
{
    dummy_logger::set_log_level( log_levels_log4j::TRACE );

    skype_io::SkypeLowIo sio;

    bool b = sio.init();

    if( b == false )
    {
        std::cout << "cannot initialize SkypeLowIo - " << sio.get_error_msg() << std::endl;
        return 0;
    }

    Callback test( & sio );

    sio.register_callback( &test );

    std::thread t( std::bind( &Callback::control_thread, &test ) );

    t.join();

    std::cout << "Done! =)" << std::endl;

    return 0;
}
