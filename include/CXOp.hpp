#ifndef CX_OP
#define CX_OP

#include <iostream>
#include <vector>

#include "CrossOp.hpp"
#include "Chromosome.hpp"

class CXOp : public CrossOp
{
    public:
        CXOp();
        ~CXOp();
        const std::vector<Chromosome> run(std::vector<Chromosome>& in);
};

#endif /*CX_OP*/
