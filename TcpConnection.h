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


class TcpConnection
{
private:
    std::string ip;
    std::string port;
    int sock;
    struct addrinfo address_info, *res, *rp;

public:
    TcpConnection(std::string m_ip, std::string m_port);
    int connect();
    void server();
    static constexpr int clientsCount = 100;
    static constexpr int bufferSize = 1024;
};



#endif /* TCPCONNECTION_H_ */
