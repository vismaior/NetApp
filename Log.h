/*
 * Logger.h
 *
 *  Created on: Sep 3, 2020
 *      Author: pawel
 */

#ifndef LOG_H_
#define LOG_H_

#define RESET       "\033[0m"
#define LIGHTRED    "\033[1;91m"
#define LIGHTGREY   "\033[1;90m"
#define NORMAL      "\033[1;39m"

#include <mutex>
#include <iostream>

class Log
{
    static std::mutex mutex;

public:
    static void err(const std::string &message)
    {
        const std::lock_guard<std::mutex> lock(mutex);
        std::cout << std::string(LIGHTRED + message + RESET + "\n");
    }

    static void deb(const std::string &message)
    {
        const std::lock_guard<std::mutex> lock(mutex);
        std::cout << std::string(LIGHTGREY + message + RESET + "\n");
    }

    static void inf(const std::string &message)
    {
        const std::lock_guard<std::mutex> lock(mutex);
        std::cout << std::string(NORMAL + message + RESET + "\n");
    }
};


#endif /* LOG_H_ */
