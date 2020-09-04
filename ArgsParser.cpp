/*
 * ArgsParser.cpp
 *
 *  Created on: Aug 24, 2020
 *      Author: pawel
 */

#include <ArgsParser.h>

ArgsParser::ArgsParser (int &argc, char **argv)
{
    Log::deb(__PRETTY_FUNCTION__);

    // add available parameters
    paramap = { {"-h", "help"},
                {"-c", "client"},
                {"-s", "server"},
                {"-p", "port"},
                {"-i", "ip eg. 192.168.222.183 (for client only)"},
                {"-t", "task"}
              };

    // print help on screen with available parameters "-h"
    if (argc > 1 && std::string(argv[1]) == paramap.begin()->first)
    {
        Log::inf("Available parameters:");
        for (auto p : paramap)
        {
            Log::inf(p.first + "\t" + p.second);
        }
        exit(1);
    }

    // read and save parameters from command line
    for (int i=1; i < argc;+ ++i)
    {
        this->params.push_back(std::string(argv[i]));
    }

    if (cmdOptionExists("-s"))
    {
        this->host = "server";
    }
    else if (cmdOptionExists("-c"))
    {
        this->host = "client";

        if (cmdOptionExists("-i")) // checks "-i" ip parameter
        {
            bool res = parseIp(this->ip = getCmdOption("-i"));
            if (!res)
            {
                Log::err("Error : Invalid IP.");
                throw std::out_of_range("Invalid IP.");
            }
        }
        else
        {
            Log::err("Use -i. Parameter missing.");
            exit(1);
        }
    }
    else
    {
        Log::err("Use -c or -s. Parameter missing.");
        exit(1);
    }


    if (cmdOptionExists("-p"))
    {
        bool res = parsePort(this->port = getCmdOption("-p"));
        if (!res)
        {
            Log::err("Error : Invalid port.");
            throw std::out_of_range("Invalid port.");
        }
    }
    else
    {
        Log::err("Use -p. Parameter missing.");
        exit(1);
    }

}

const std::string ArgsParser::getPort() const
{
    return this->port;
}

const std::string ArgsParser::getIp() const
{
    return this->ip;
}

const std::string ArgsParser::getHost() const
{
    return this->host;
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

bool ArgsParser::strToInt(const std::string &str, const std::string &srcDesc, int minRange, int maxRange)
{
    int num;

    try
    {
        num = std::stoi(str);
    }
    catch (std::invalid_argument const &e)
    {
        Log::err(" Invalid " + srcDesc + " argument.");
        return false;
    }
    catch (std::out_of_range const &e)
    {
        Log::err(" Invalid " + srcDesc + " argument.");
        return false;
    }

    if (num < minRange || num > maxRange)
    {
        Log::err(" Invalid " + srcDesc + " argument.");
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
    for (const std::string &i : results)
    {
        Log::deb("checking ip: " + i);

        if (!strToInt(i, "ip", 0, 255))
        {
            Log::err("NOK");
            return false;
        }
        else
        {
            Log::deb("OK");
        }
    }

    return true;
}

bool ArgsParser::parsePort(const std::string &port)
{
    Log::deb("checking port: " + port);
    if (!strToInt(port, "port", 0, 65535))
    {
        Log::err("NOK");
        return false;
    }

    Log::deb("OK");

    return true;
}


