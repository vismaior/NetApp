/*
 * TcpConnection.h
 *
 *  Created on: Aug 19, 2020
 *      Author: pawel
 */

#ifndef TCPCONNECTION_H_
#define TCPCONNECTION_H_


#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <sys/un.h>
#include <errno.h>
#include <netdb.h>		// freeaddrinfo()

#include <Log.h>


class TcpConnection
{
private:
    std::string ip;
    std::string port;
    int sSock;
    int cSock;
    struct addrinfo address_info;
    struct addrinfo *res;
    struct addrinfo *rp;
    struct sockaddr_in client_addr;

    int connection();

public:
    TcpConnection(std::string m_ip, std::string m_port);
    TcpConnection(const TcpConnection &)
    {
        Log::deb(__PRETTY_FUNCTION__);
    }

    ~TcpConnection()
    {
        Log::deb(__PRETTY_FUNCTION__);
    }

    void serverConnect();
    void clientConnect();
    static constexpr int clientsCount = 100;
    static constexpr int bufferSize = 1024;
};



#endif /* TCPCONNECTION_H_ */
