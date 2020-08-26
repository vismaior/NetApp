#include <iostream>

#include <ArgsParser.h>
#include <TcpConnection.h>

int main(int argc, char **argv)
{
	std::cout << "Hello world" << std::endl;

	ArgsParser parser(argc, argv);
	TcpConnection tcp("","");
	tcp.connect();
	tcp.server();
	return 0;
}
