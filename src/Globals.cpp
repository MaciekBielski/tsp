#include "Globals.hpp"
//
//
//
std::random_device rd; 
std::mt19937 gen(rd());

/* Logger initialization */
Logger &logger = Logger::getInstance("files/output.txt");
