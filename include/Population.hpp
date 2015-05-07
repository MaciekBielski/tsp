#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <random>

#include "Chromosome.hpp"
#include "CrossOp.hpp"
#include "Globals.hpp"
class Family; 

class Population
{
    private:
        const Family& family;                               //family - common
        size_t id;                                          //population id
        std::vector<Chromosome> elements;                   //elements of the population
        Population(const Family& family, const size_t id);  //private constructor of non-first generation
        void select(
            std::vector<Chromosome>& inElems, 
            std::vector<Chromosome>& outElems);
        size_t findIndex(float *cumDist, size_t sz, float r);
        void mutate(std::vector<Chromosome>& elems);
    public:
        //constructors
        Population(const Family& family);                   //first generation constructor
        ~Population();
        Population *next;                             //next generation
        Population *prev;                             //previous population
        //member functions
        Population *nextGeneration();
        std::vector<Chromosome>& getElements();
        std::string str();
        bool contains(const Chromosome &ch);
        size_t getId() const;
};
#include "Family.hpp"

inline std::vector<Chromosome>& Population::getElements() { return this->elements; }
inline size_t Population::getId() const { return this->id; }

#endif /* POPULATION_HPP*/
