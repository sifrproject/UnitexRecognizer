//
// Created by Andon Tchechmedjiev on 08/06/2017.
//

#include <iostream>
#include "server/server.h"

int main(int argc, char* argv[])
{
    try
    {
        asio::io_service io_service;

        server s(io_service, 9876);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}