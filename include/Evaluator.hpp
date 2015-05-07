#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <iostream>
#include <algorithm>
#include "DataGenerator.hpp"
class Chromosome;
class Population;

class Evaluator
{
    private:
        typedef std::vector<uint8_t> uint8Vector;
        typedef std::vector<int> intVector;
        struct Passenger
        {
            uint8_t origin, destination, id;
            int distance;
            std::string str() const;
        };
        Evaluator(const DataGenerator &data);
        static Population *popOfBest;
        const DataGenerator &data;
        void computeValue(Chromosome &ch);
        Passenger createPassenger(size_t id, uint8Vector::iterator orig, uint8Vector::iterator dest, std::vector< intVector > distances);
        static bool sortEval(const Chromosome& a, const Chromosome& b);
    public:
        //instance provider
        static Evaluator& getInstance(const DataGenerator& data)
        {
            static Evaluator e(data);
            return e;
        }
        //member functions
        void popEval(Population &pop);
        Population* getPopOfBest() const;
        void setPopOfBest(Population* popOfBest);
        Evaluator(Evaluator const&);            //don't implement
        void operator=(Evaluator const&);       //don't implement
};
#include "Population.hpp"

inline Population* Evaluator::getPopOfBest() const { return popOfBest; }

#endif /* EVALUATOR_HPP*/
