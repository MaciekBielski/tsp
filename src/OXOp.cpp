#include "OXOp.hpp"
//constructors and destructors

OXOp::OXOp()
{
    std::cout<<"ox operator: "<<std::endl;
}

OXOp::~OXOp()
{
    std::cout<<"ox destruction"<<std::endl;
}

//virtual function implementation
const std::vector<Chromosome> OXOp::run(std::vector<Chromosome>& in)
{
    std::vector<Chromosome> out;

    return out;
}
