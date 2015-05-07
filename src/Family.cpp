#include "Family.hpp"

//constructors and destructors

Family::Family(const DataGenerator &data, uint8_t cxType):
   data(data), 
   evaluator(Evaluator::getInstance(data)),
   generations(nullptr)
{
    switch(cxType)
    {
        case 1:
            crossOp = new PMXOp(); 
            break;
        case 2:
            crossOp = new OXOp();
            break;
        case 3:
            crossOp = new CXOp();
            break;
    }
}

Family::~Family()
{
    /* destroying all populations thas has been generated,
     * generations points to the newest population
     */
    while(generations!=nullptr)
    {
        Population* toRemove = generations;
        generations = toRemove->prev;
        if(generations != nullptr)
            generations->next = nullptr;
        delete toRemove;
    }

    /* destroying object of crossing operator */
    delete crossOp;
    crossOp = nullptr;
}

const Chromosome Family::run()
{
    Chromosome out;
    logger<<"nr iteracji | start_fcji_celu | stop_fcji_celu | poprawa\n";
    /* create first generation, generations points to the populations list,
     * after generation each population is evaluated
     */ 
    double lastF = 0.0, currF = 0.0, diff=0.0;
    size_t maxNPI = this->getMaxNonProfitIter(), NPICnt = 0;
    double diffTh = getMinProfitRel();
    for(size_t i=0; i<maxIter && NPICnt<maxNPI; i++)
    {
        std::ostringstream ost;
        if (!generations)
        {
            generations = new Population(*this);
        }
        else
        {
            /* when next generation is created then generations points to it */
            Population *old = generations;
            generations = old->nextGeneration();
            generations->prev = old;
            old->next = generations;
        }
            evaluator.popEval(*generations);
            evaluator.setPopOfBest(generations);
            out = (evaluator.getPopOfBest())->getElements()[0];
            lastF = currF;
            currF = generations->getElements()[0].getRatio();
            if(currF != 0)
                diff = 100*(currF - lastF)/currF;
            if( diff < diffTh )
                NPICnt++;
            else
                NPICnt=0;
            ost<<i<<"\t"<<lastF<<"\t"<<currF<<"\t"<<diff;
            logger<<ost.str();
    }
    return out;    
}

void Family::setPopSz(size_t ps)
{
    if (citiesNb <= 2)
    {
        fprintf(stderr, "Number of cities is too small\n");
        exit(EXIT_FAILURE);
    }
    else if (citiesNb ==3)
        ps = (ps > 3) ? 3 : ps;
    else if (citiesNb == 4)
        ps = (ps >12 ) ? 12 : ps;
    else
        ps = (ps > POP_SZ_MAX) ? POP_SZ_MAX : ps;
    this->popSz = ps;
}
