/*
 * TcpConnection.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: pawel
 */
#include <TcpConnection.h>

TcpConnection::TcpConnection(std::string m_ip, std::string m_port): ip(m_ip), port(m_port) // @suppress("Class members should be properly initialized")
{
	memset(&address_info, 0, sizeof address_info);

	address_info.ai_family = AF_INET;
    address_info.ai_socktype = SOCK_STREAM;
    address_info.ai_protocol = IPPROTO_TCP;
    address_info.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    address_info.ai_canonname = NULL;
    address_info.ai_addr = NULL;
    address_info.ai_next = NULL;

    std::cout << "TcpConnection constructor" << std::endl;
}

int TcpConnection::connect()
{
    if ((sock = getaddrinfo(NULL, port.c_str(), &address_info, &res)) != 0)
    {
        std::cerr << "getaddrinfo error: " << gai_strerror(errno) << std::endl;
        return sock;
    }

    for (rp = res; rp != NULL; rp = rp->ai_next)
    {
    	sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    	if (sock == -1)
    	{
    		std::cerr << "opening socket error: " << gai_strerror(errno) << std::endl;
    		continue;
    	}

    	if (bind(sock, rp->ai_addr, rp->ai_addrlen) == 0)
    	{
    		break;                  /* Success */
    	}
    	close(sock);
	}

    if (rp == NULL)
    {               /* No address succeeded */
    	std::cerr << "bind error: " << gai_strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);           /* No longer needed */

    return 0;
}

void TcpConnection::server()
{
	if(listen(sock, clientsCount) == -1)
	{
		perror("listen");
		exit(1);
	}
}

