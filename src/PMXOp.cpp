#include "PMXOp.hpp"
//constructors and destructors

PMXOp::PMXOp()
{}

PMXOp::~PMXOp()
{}

void PMXOp::init(const size_t maxLength)
{
    /* randomly generates cut1 and cut2 so as to 0<=cut1<cut2<maxLength */
    std::uniform_int_distribution<size_t> uid1(0, maxLength-1);
    cut1 = uid1(gen);
    std::uniform_int_distribution<size_t> uid2(cut1+1, maxLength);
    cut2 = uid2(gen);
}

const std::vector<Chromosome> PMXOp::run(std::vector<Chromosome>& in)
{
    /* random selection of points of cutting */
    size_t chromSz = in[0].getChromSz();
    init(chromSz);
    std::vector<Chromosome> out;
    for(size_t i=0; i<in.size(); i+=2)
    {
        std::vector<uint8_t> cc1(chromSz), cc2(chromSz);
        pairCross(in[i], in[i+1], cc1, cc2);
        out.push_back(Chromosome(cc1));    
        out.push_back(Chromosome(cc2));    
    }
    return out;
}

void PMXOp::pairCross(
        Chromosome &p1, 
        Chromosome &p2, 
        std::vector<uint8_t> &c1, 
        std::vector<uint8_t> &c2) 
    const
{
    /* each pair of input chromosomes yields a new pair of output chromosomes */
    const std::vector<uint8_t> &e1 = p1.getElements(), &e2 = p2.getElements();

    //guts
    /* first step - building lookUpTable */
    size_t lutSz = p1.getChromSz();
    uint8_t lut1[lutSz], lut2[lutSz];
    /* initialization loop */
    for(size_t i=0; i<lutSz; i++)
    {
        lut1[i] = i;
        lut2[i] = i;
    }
    for(size_t j=cut1; j<cut2; j++)
    {
        lut1[e2[j]] = e1[j];
        lut2[e1[j]] = e2[j];
    }
    /* swapping the numbers between cuts */
    for(size_t j=cut1; j<cut2; j++)
    {
        c1[j] = e2[j];
        c2[j] = e1[j];
    }
    /* filling the fields before first cut */
    for(size_t i=0; i<cut1; i++)
    {
        size_t n1 = lut1[e1[i]];
        size_t n2 = lut2[e2[i]];
        while(lut1[n1] != n1)
            n1 = lut1[n1];
        while(lut2[n2] != n2)
            n2 = lut2[n2];
        c1[i] = n1;
        c2[i] = n2;
    }
    /* filling the fields after the second cut */
    for(size_t i=cut2; i<lutSz; i++)
    {
        size_t n1 = lut1[e1[i]];
        size_t n2 = lut2[e2[i]];
        while(lut1[n1] != n1)
            n1 = lut1[n1];
        while(lut2[n2] != n2)
            n2 = lut2[n2];
        c1[i] = n1;
        c2[i] = n2;
    }
}
