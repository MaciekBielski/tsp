#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <fstream>

class Logger
{
    private:
        Logger(std::string path);
        std::ofstream fh;
    public:
        static Logger& getInstance(const std::string path)
        {
            static Logger l(path);
            return l;
        }
        ~Logger();
        Logger& operator<<(std::string s);
        Logger(Logger &l);              //don't implement
        void operator=(Logger &l);      //don't implement
};

#endif /* LOGGER_HPP */
