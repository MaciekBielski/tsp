#include "CXOp.hpp"
//constructors and destructors

CXOp::CXOp()
{
    std::cout<<"cx operator: "<<std::endl;
}

CXOp::~CXOp()
{
    std::cout<<"cx destruction"<<std::endl;
}

//virtual function implementation
const std::vector<Chromosome> CXOp::run(std::vector<Chromosome>& in)
{
    std::vector<Chromosome> out;

    return out;
}
