/*
 * ArgsParser.cpp
 *
 *  Created on: Aug 24, 2020
 *      Author: pawel
 */

#include <ArgsParser.h>

ArgsParser::ArgsParser (int &argc, char **argv)
{

	if (argc > 1 && std::string(argv[1]) == "-h")
	{
		std::cout << "Parameters:" << std::endl;
		std::cout << "-h\t\t help" << std::endl;
		std::cout << "-s,-c\t\t server/client" << std::endl;
		std::cout << "-p\t\t port" << std::endl;
		std::cout << "-i\t\t ip eg. 192.168.222.183 (for client only)" << std::endl;
		std::cout << "-t\t\t task" << std::endl;
	}

	for (int i=1; i < argc; ++i)
	{
		this->params.push_back(std::string(argv[i]));
	}

	if (cmdOptionExists("-i"))
	{
		bool res = parseIp(getCmdOption("-i"));
		if (!res)
		{
			std::cout << "error " << std::endl;
			throw std::out_of_range("Invalid IP");
		}
	}

	if (cmdOptionExists("-p"))
	{
		bool res = parsePort(getCmdOption("-p"));
		if (!res)
		{
			std::cout << "error " << std::endl;
			throw std::out_of_range("Invalid port");
		}
	}
}

const std::string& ArgsParser::getCmdOption(const std::string &option) const
{
	std::vector<std::string>::const_iterator it;
	it =  std::find(this->params.begin(), this->params.end(), option);
	if (it != this->params.end() && ++it != this->params.end())
	{
		return *it;
	}
	static const std::string empty_string("");
	return empty_string;
}

bool ArgsParser::cmdOptionExists(const std::string &option) const
{
    return std::find(this->params.begin(), this->params.end(), option) != this->params.end();
}

bool ArgsParser::strToInt(const std::string &str, const std::string &srcDesc, int minRange, int maxRange)
{
	int num;

	try
	{
		num = std::stoi(str);
	}
	catch (std::invalid_argument const &e)
	{
		std::cout << "1 Invalid "<<  srcDesc << " argument." << std::endl;
		return false;
	}
	catch (std::out_of_range const &e)
	{
		std::cout << "2 Invalid " << srcDesc << " argument." << std::endl;
		return false;
	}

	if (num < minRange || num > maxRange)
	{
		std::cout << "3 Invalid " << srcDesc << " argument." << std::endl;
		return false;
	}

	return true;
}

bool ArgsParser::parseIp(std::string ip)
{
	std::replace(ip.begin(), ip.end(), '.', ' ');	// replace '.' with space
	std::istringstream iss(ip);
	std::vector<std::string> results ((std::istream_iterator<std::string>(iss)),
	                                   std::istream_iterator<std::string>());		// split string
	for (std::string i : results)
	{
		std::cout << "checking ip: " << i ;

		if (!strToInt(i, "ip", 0, 255))
		{
			std::cout << " - NOK" << std::endl;
			return false;
		}
		else
		{
			std::cout << " - OK" << std::endl;
		}
	}

	return true;
}

bool ArgsParser::parsePort(std::string port)
{
	std::cout << "checking port: " << port ;
	if (!strToInt(port, "port", 0, 65535))
	{
		std::cout << " - NOK" << std::endl;
		return false;
	}

	std::cout << " - OK" << std::endl;

	return true;
}

