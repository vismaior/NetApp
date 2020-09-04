#include <iostream>
#include <thread>

#include <ArgsParser.h>
#include <TcpConnection.h>
#include <Log.h>



int main(int argc, char **argv)
{
    ArgsParser *parser;
    parser = new ArgsParser(argc, argv);

    TcpConnection *tcp_connection;
    tcp_connection = new TcpConnection(parser->getIp(),parser->getPort());
/*
    if (parser->getHost() == "server")
    {
        std::thread tcp(&TcpConnection::serverConnect, tcp_connection);
        tcp.join();
    }
    else
    {
        std::thread tcp(&TcpConnection::clientConnect, tcp_connection);
        tcp.join();
    }
*/

    delete tcp_connection;
    delete parser;

    return 0;
}
