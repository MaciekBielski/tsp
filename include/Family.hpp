#ifndef FAMILY_HPP
#define FAMILY_HPP

#include <iostream>
#include <unistd.h>

#include "Logger.hpp"

class Evaluator;
class DataGenerator;
class Population;
class Chromosome;
class CrossOp;
class PMXOp;
class CXOp;
class OXOp;

class Family
{
    private:
        static const size_t POP_SZ_MAX = 60;
        float pc = 0.0;               // crossing probability
        float pm = 0.0;               // mutation probability
        size_t maxIter = 0;         // maximum number of iterations (generations)
        float minProfitRel = 0.0;     /* minimum relative value that is not considered
                                   as an improvement between two consecutive
                                   populations */
        size_t maxNonProfitIter = 0;/* maximum number of iterations with gain less
                                   than minProfitRel allowed */
        size_t popSz = 0;           // number of chromosoms in the population
        size_t chromSz = 0;         // number of elements in a chromosom 
        size_t maxAge = 0;          // maximum age of a chromosome
        size_t genSz = 0;
        size_t ancCount = 0;        /* number of best chromosomes from the previous
                                   generation - ancestors*/
        size_t citiesNb = 0;        // for pseudorandom chromosomes generation

        const DataGenerator &data;
        Evaluator &evaluator;
        CrossOp *crossOp = nullptr;
        Population *generations = nullptr;
    public:
        //constructors and destructors
        Family(const DataGenerator &data, uint8_t cxType);
        ~Family();
        //member functions
        const Chromosome run();
        //getters and setters
        float getPc() const;
        float getPm() const;
        size_t getMaxIter() const;
        float getMinProfitRel() const;
        size_t getMaxNonProfitIter() const;
        size_t getPopSz() const;
        size_t getChromSz() const;
        size_t getAncCount() const;
        size_t getMaxAge() const;
        size_t getGenSz() const;
        size_t getCitiesNb() const;
        const DataGenerator& getDataGenerator() const;
        CrossOp* getCrossOp() const;
        void setPc(float pc);
        void setPm(float pm);
        void setMaxIter(size_t maxIter);
        void setMinProfitRel(float minProfitReal);
        void setMaxNonProfitIter(size_t maxNonProfitIter);
        void setPopSz(size_t popSz);
        void setChromSz(size_t chromSz);
        void setAncCount(size_t crossCount);
        void setGenSz(size_t genSz);
        void setMaxAge(size_t maxAge);
        void setCitiesNb(size_t citiesNb);
};
#include "Evaluator.hpp"
#include "CrossOp.hpp"
#include "PMXOp.hpp"
#include "CXOp.hpp"
#include "OXOp.hpp"

inline float Family::getPc() const { return this->pc; }
inline float Family::getPm() const { return this->pm; }
inline size_t Family::getMaxIter() const { return this->maxIter; }
inline float Family::getMinProfitRel() const { return this->minProfitRel; }
inline size_t Family::getMaxNonProfitIter() const { return this->maxNonProfitIter; }
inline size_t Family::getPopSz() const { return this->popSz; }
inline size_t Family::getChromSz() const { return this->chromSz; }
inline size_t Family::getAncCount() const { return this->ancCount; }
inline size_t Family::getGenSz() const { return this->genSz; }
inline size_t Family::getMaxAge() const { return this->maxAge; }
inline size_t Family::getCitiesNb() const { return this->citiesNb; }
inline const DataGenerator& Family::getDataGenerator() const { return this->data; }
inline CrossOp* Family::getCrossOp() const { return this->crossOp; }
inline void Family::setPc(float pc){ this->pc = pc; }
inline void Family::setPm(float pm){ this->pm = pm; }
inline void Family::setMaxIter(size_t maxIter){ this->maxIter = maxIter; }
inline void Family::setMinProfitRel(float minProfitRel){ this->minProfitRel = minProfitRel; }
inline void Family::setMaxNonProfitIter(size_t maxNonProfitIter){ this->maxNonProfitIter = maxNonProfitIter; }
inline void Family::setChromSz(size_t chromSz){ this->chromSz = chromSz; }
inline void Family::setAncCount(size_t ancCount){ this->ancCount = ancCount; }
inline void Family::setGenSz(size_t genSz) { this->genSz = genSz; }
inline void Family::setMaxAge(size_t maxAge){ this->maxAge = maxAge; }
inline void Family::setCitiesNb(size_t citiesNb){ this->citiesNb = citiesNb; }

#endif /* FAMILY_HPP */
