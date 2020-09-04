/*
 * ArgsParser.h
 *
 *  Created on: Aug 24, 2020
 *      Author: pawel
 */

#ifndef ARGSPARSER_H_
#define ARGSPARSER_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <functional>
#include <list>
#include <utility>
#include <Log.h>


class ArgsParser
{
    private:
        std::vector <std::string> params;
        std::list <std::pair < std::string, std::string> > paramap;
        std::string ip;
        std::string port;
        std::string host;
        const std::string& getCmdOption(const std::string &option) const;
        bool parseIp(std::string ip);
        bool parsePort(const std::string &port);
        bool strToInt(const std::string &str, const std::string &srcDesc, int minRange, int maxRange);

        std::function < bool(const std::string &) > cmdOptionExists = [this](const std::string &option)  // check if option exists
                { return std::find(this->params.begin(), this->params.end(), option) != this->params.end(); };

    public:
        ArgsParser(int &argc, char **argv);
        ArgsParser(const ArgsParser &)
        {
            Log::deb(__PRETTY_FUNCTION__);
        }

        ~ArgsParser()
        {
            Log::deb( __PRETTY_FUNCTION__);
        }

        const std::string getPort() const;
        const std::string getIp() const;
        const std::string getHost() const;
};



#endif /* ARGSPARSER_H_ */
