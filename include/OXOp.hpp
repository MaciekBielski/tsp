#ifndef OX_OP
#define OX_OP

#include <iostream>
#include <vector>

#include "CrossOp.hpp"
#include "Chromosome.hpp"

class OXOp : public CrossOp
{
    public:
        OXOp();
        ~OXOp();
        const std::vector<Chromosome> run(std::vector<Chromosome>& in);
};

#endif /*OX_OP*/
