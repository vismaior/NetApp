/*
 * TcpConnection.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: pawel
 */
#include <TcpConnection.h>

TcpConnection::TcpConnection(std::string m_ip, std::string m_port) :
                      ip(m_ip), port(m_port), res(nullptr), rp(nullptr), cSock(0), sSock(0)
{
    Log::deb(" __PRETTY_FUNCTION__");

    memset(&address_info, 0, sizeof address_info);

    address_info.ai_family = AF_INET;
    address_info.ai_socktype = SOCK_STREAM;
    address_info.ai_protocol = IPPROTO_TCP;
    address_info.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    address_info.ai_canonname = NULL;
    address_info.ai_addr = NULL;
    address_info.ai_next = NULL;
}

void TcpConnection::serverConnect()
{
    Log::deb(" __PRETTY_FUNCTION__");
    if ((sSock = getaddrinfo(NULL, port.c_str(), &address_info, &res)) != 0)
    {
        std::cerr << "getaddrinfo error: " << gai_strerror(errno) << std::endl;
        throw;
    }

    std::cout << "socket()" << std::endl;
    for (rp = res; rp != NULL; rp = rp->ai_next)
    {
        sSock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sSock == -1)
        {
            std::cerr << "opening socket error: " << gai_strerror(errno) << std::endl;
            continue;
        }

        std::cout << "bind()" << std::endl;
        if (bind(sSock, rp->ai_addr, rp->ai_addrlen) == 0)
        {
            break;      /* Success */
        }
        close(sSock);
    }

    if (rp == NULL)
    {               /* No address succeeded */
        std::cerr << "bind error: " << gai_strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);           /* No longer needed */

    std::cout << "listen()" << std::endl;
    if(listen(sSock, clientsCount) == -1)
    {
        std::cerr << "listen() error: " << gai_strerror(errno) << std::endl;
        throw;
    }

    int clientSize = sizeof(client_addr);

    Log::inf("Waiting for new client...");

    while (1)
    {
        if ((cSock = accept( sSock, (struct sockaddr *) &client_addr, (socklen_t*) &clientSize)) < 0)
        {
            std::cerr << "accept() error: " << gai_strerror(errno) << std::endl;
        }

        std::cout << "Opened new communication with client." << std::endl;
        break;
    }
}

void TcpConnection::clientConnect()
{
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    /// Define sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(std::stoi(this->port));  /// Server Port
    servaddr.sin_addr.s_addr = inet_addr(this->ip.c_str());  /// server ip

    //Connect to the server, successfully return 0, error return - 1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    std::cout << "Connected to server." <<std::endl;
}
