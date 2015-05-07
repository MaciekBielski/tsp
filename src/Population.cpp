#include "Population.hpp"

Population::Population(const Family &family):
    family(family),
    id(0),
    next(nullptr),
    prev(nullptr)
{
    /* first population is created with id=0,
     * popSz <= chromSz! - max number of different chromosomes
     * CAUTION: pointer prev of first population has to be set to nullptr
     * in order to memory deallocation works properly
     */ 
    for(size_t i=0; i<family.getPopSz(); i++)
    {
        Chromosome c;
        do
        {
            c = Chromosome(family.getCitiesNb(), family.getChromSz());
        }
        while(i>0 && this->contains(c));
        elements.push_back(c);        
    }
}

Population::Population(const Family& fm, const size_t id):
    family(fm),
    id(id),
    next(nullptr),
    prev(nullptr)
{}

Population::~Population()
{}

std::string Population::str()
{
    std::ostringstream out;
    out<<"\n-------- "<<id<<" ---------"<<std::endl;
    for(std::vector<Chromosome>::iterator it = elements.begin(); it!= elements.end(); it++)
        out<<it->str()<<std::endl;
    out<<std::endl;
    return out.str();
}

Population* Population::nextGeneration()
{
    Population *out=new Population(this->family, this->id+1);
    /*elements of the new population*/
    std::vector<Chromosome>& parentElems = this->getElements();
    std::vector<Chromosome> selectedElems;
    std::vector<Chromosome>& childElems = out->getElements();
    /* copying the best ancestor chromosomes from the parent population */
    for(size_t i=0; i<family.getAncCount(); i++)
        childElems.push_back(parentElems[i]);
    /* selection chromosomes from previous generation, 
     * the number of them is popSz - ancCount
     * input vector for crossing operator */
    select(parentElems, selectedElems);
    /* some of selected will be crossed */ 
    std::vector<Chromosome> cxOpIn;
    float pc = family.getPc();
    std::uniform_real_distribution<float> urd(0,1);
    size_t crossedCnt=0, rewritedCnt=0;
    for(Chromosome &c : selectedElems)
    {
        /* for each chromosome generate randomly g
         * if rg < pc then this chromosome is to be crossed,
         * otherwise it goes to the new population directly
         */
        float rg = urd(gen);
        if(rg<pc)
        {
            cxOpIn.push_back(c);
            crossedCnt++;
        }
        else
        {
            childElems.push_back(c);
            rewritedCnt++;
        }
    }
    /* applying crossing operator on subsequent pairs of selected chromosomes */
    /* trick - number of crossed elements always even for convienience */
    if(crossedCnt %2 == 1)
    {
        cxOpIn.push_back(cxOpIn[0]);
        childElems.pop_back();
        rewritedCnt--;
    }
    const std::vector<Chromosome> cxOpOut = (family.getCrossOp())->run(cxOpIn);
    for(const Chromosome &c : cxOpOut)
        childElems.push_back(c);
    /* generation new chromosomes */
    for(size_t i=0; i<family.getGenSz(); i++)
        childElems.push_back(Chromosome( family.getCitiesNb(), family.getChromSz()) );
    /* mutation */
    mutate(childElems); 
    return out;
}

bool Population::contains(const Chromosome &ch)
{
    bool out = false;
    if( std::find(elements.begin(), elements.end(), ch) != elements.end() )
        out = true;
    return out;
}

void Population::select(
        std::vector<Chromosome>& inElems, 
        std::vector<Chromosome>& outElems
        )
{
    /* method as described on page 59 */
    /* each chromosome has been evaluated, counting the sum of evaluation marks */
    float ratioSum = 0.0;
    for(Chromosome& c : inElems)
        ratioSum += c.getRatio();
    /* computing selection probability */
    size_t sz = family.getPopSz();
    size_t maxInd = sz-1;
    float selectionProb[sz];
    float cumulativeProb[sz];
    for(size_t i=0; i<sz; i++)
    {
        /* selectionProb and cumulativeProb are in ascending order, whereas inElems is in
         * descending order so subsequent values are inserted from the largest to the smallest
         * index
         */ 
        selectionProb[maxInd-i] = inElems[i].getRatio() / ratioSum;
        cumulativeProb[maxInd-i] = 0.0;
        /* computing the cumulative distribution of ratios */
        for(size_t j=0; j<=i; j++)
            cumulativeProb[maxInd-i] += selectionProb[maxInd-j];
    }
    /* all needed computation have been made, roulette can run */
    std::uniform_real_distribution<float> urd(0, 1);
    size_t howManySelected = family.getPopSz() - family.getAncCount() - family.getGenSz();
    for(size_t i=0; i<howManySelected; i++)
    {
        /* c++11 version uniformly distributed random number */
        float rf = urd(gen);
        /* function that gets random value and returns the proper index based on cumulative
         * probability distribution table computed before
         */
        size_t genId = findIndex(cumulativeProb, maxInd, rf);
        outElems.push_back(inElems[genId]);
    }
}

size_t Population::findIndex(float *cumDist, size_t maxInd, float r)
{
    /* page 60 -  but analogically for descending table;
     * finding index i of an element in cumDist table, such that:
     * - if r <= cumDist[maxInd] then return maxInd, 
     * or else 
     * - if cumDist[maxInd-i-1]< r <= cumDist[maxInd-i], then return maxInd-i
     */
    size_t out=maxInd;
    if ( r > cumDist[maxInd] )
        for(size_t i=1; i<=maxInd; i++)
        {
            if( r > cumDist[maxInd-i] )
                continue;
            else
            {
                out = maxInd-i;
                break;
            }
        }
    return out;
}

void Population::mutate(std::vector<Chromosome>& elems)
{
    /* selection elements to mutate */
    std::uniform_real_distribution<float> furd(0,1);
    for(Chromosome &e : elems)
    {
        if( furd(gen) >= family.getPm() )
            continue;
        std::uniform_int_distribution<int> iurd(0, family.getChromSz()-1);

        /* selection gens to swap */
        uint8_t a = iurd(gen);
        uint8_t b = -1;
        do
        {
            b = iurd(gen);
        }
        while(a==b);
        /* swapping */
        std::vector<uint8_t> &chromElems = e.getElements();
        std::swap(chromElems[a], chromElems[b]);
    }
}
