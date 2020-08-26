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
//#include <exception>


class ArgsParser
{
    private:
        std::vector <std::string> params;
    	const std::string& getCmdOption(const std::string &option) const;
    	bool cmdOptionExists(const std::string &option) const;
    	bool parseIp(std::string ip);
    	bool parsePort(std::string port);
    	bool strToInt(const std::string &str, const std::string &srcDesc, int minRange, int maxRange);

    public:
	ArgsParser (int &argc, char **argv);
};



#endif /* ARGSPARSER_H_ */
