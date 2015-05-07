#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <algorithm>

class Chromosome
{
    private:
        size_t chromSz;                     //size of the chromosome
        uint8_t age;                        //age of the chromosome 
        std::vector< uint8_t > elements;     
        int value;
        int distance;
        float ratio;
    public:
        Chromosome();
        Chromosome(const size_t citiesNb, const size_t chromSz);
        Chromosome(const std::vector<uint8_t> &elements);
        Chromosome(const Chromosome &ch);
        Chromosome& operator=(const Chromosome& ch);
        bool operator==(const Chromosome& ch) const;
        //getters and setters
        size_t getChromSz() const;
        void setChromSz( size_t chSz);
        std::vector< uint8_t >& getElements();
        uint8_t getAge() const;
        void incrementAge();
        int getValue() const;
        void setValue(int value);
        int getDistance() const;
        void setDistance(int dist);
        float getRatio() const;
        void setRatio(float rt);
        //member functions
        std::string str() const;
        bool isAllowed(uint8_t el) const;
        bool isEqual(const Chromosome &c) const;
};

inline size_t Chromosome::getChromSz() const { return chromSz; }
inline void Chromosome::setChromSz( size_t chSz){ this->chromSz = chSz; }
inline std::vector< uint8_t >& Chromosome::getElements() { return elements; }
inline uint8_t Chromosome::getAge() const { return age; }
inline void Chromosome::incrementAge(){ age++; }
inline int Chromosome::getValue() const{ return value; }
inline void Chromosome::setValue(int value){ this->value = value; }
inline int Chromosome::getDistance() const { return distance; }
inline void Chromosome::setDistance(int dist) { this->distance = dist; }
inline float Chromosome::getRatio() const { return ratio; } 
inline void Chromosome::setRatio(float rt) { this->ratio = rt; }

#endif /* CHROMOSOME_HPP*/ 
