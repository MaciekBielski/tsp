#include "Chromosome.hpp"

Chromosome::Chromosome():
    chromSz(0),
    age(0),
    elements( std::vector<uint8_t>({}) ),
    value(0),
    distance(0),
    ratio(0.0)
{}

/* Creates the new chromosome with pseudorandom generator.
 * chromSz elements from the range [0, citiesNb) are randomly generated,
 * each two subsequent elements of the chromosome has to be different
 */
Chromosome::Chromosome(const size_t citiesNb, const size_t chromSz):
    chromSz(chromSz),
    age(0),
    value(0),
    distance(0),
    ratio(0.0)
{
    for(size_t i=0; i<chromSz; i++)
    {
        uint8_t nextElem;
        do
        {
            nextElem =  rand() % citiesNb;
        //}while( i>0 && nextElem==elements.at(i-1) );
        }while( i>0 && !isAllowed(nextElem) );
        elements.push_back(nextElem);
    }
}

/* Creates the new chromosome out of provided elements,
 * i.e: elements can be output of crossing operator.
 */
Chromosome::Chromosome(const std::vector<uint8_t> &elems):
    chromSz(elems.size()),
    age(0),
    elements(elems),
    value(0),
    distance(0),
    ratio(0.0)
{}

Chromosome::Chromosome(const Chromosome &ch):
    chromSz(ch.chromSz),
    age(ch.age),
    value(ch.value),
    distance(ch.distance),
    ratio(ch.ratio)
{
    elements = ch.elements;
}

Chromosome& Chromosome::operator=(const Chromosome& ch)
{
    chromSz = ch.chromSz;
    age = ch.age;
    elements = ch.elements;
    value = ch.value;
    distance = ch.distance;
    ratio = ch.ratio;
    return *this;
}

std::string Chromosome::str() const
{
    std::ostringstream out;
    out<<"|";
    for(std::vector<uint8_t>::const_iterator it = elements.begin(); it!= elements.end(); it++)
        out<<" "<<(int)*it;
    //out<<"| size: "<<getChromSz()<<"\tvalue: "<<getValue()<<" , distance: "<<getDistance()<<" , ratio: "<<getRatio();
    out<<"| f: "<<getRatio();
    return out.str();
}

bool Chromosome::isAllowed(uint8_t newEl) const
{
    bool out = true;
    if( std::find(elements.begin(), elements.end(), newEl) != elements.end() )
        out = false;
    return out;
}

bool Chromosome::isEqual(const Chromosome &c) const
{
    bool out = true;
    if (elements.size() != c.elements.size())
        out = false;
    else
    {
        for(size_t i = 0; i<elements.size(); i++)
            if (elements[i] != c.elements[i])
            {
                out = false;
                break;
            }
    }
    return out;
}

bool Chromosome::operator==(const Chromosome& ch) const
{
    return this->isEqual(ch);    
}
