#include "Logger.hpp"

Logger::Logger(const std::string path)
{
    fh.open(path, std::ios::app);
}

Logger::~Logger()
{
    fh<<std::endl<<std::endl;
    fh.close();
}

Logger& Logger::operator<<(std::string s)
{
    fh<<s<<std::endl;
    return *this;
}
