#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <iterator>
#include <limits>
#include <cstdint>

class DataGenerator
{
    private:
        std::vector< std::vector<int> > distM;
        std::vector< std::vector<uint8_t> > passengers;
        size_t citiesNb;
        static const int16_t maxDist = 1000;
        static const uint16_t maxCities = std::numeric_limits<uint8_t>::max()+1;
        void generate(size_t citiesNb);
        void load(std::string filename);
        std::vector<uint8_t> parseDestinations (std::ifstream &is);
    public:
        DataGenerator(size_t d);
        DataGenerator(const std::string &filename);
        void print() const;
        void save(const std::string &filepath="data.csv") const;
        //getters and setters
        const std::vector< std::vector<int> >& getDistances() const;
        const std::vector< std::vector<uint8_t> >& getPassengers() const;
        const size_t getCitiesNb() const;
};

inline const std::vector< std::vector<int> >& DataGenerator::getDistances() const { return distM; }
inline const std::vector< std::vector<uint8_t> >& DataGenerator::getPassengers() const { return passengers; }
inline const size_t DataGenerator::getCitiesNb() const { return citiesNb; }

#endif /* DATA_GENERATOR_HPP */
