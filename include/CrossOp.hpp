#ifndef CROSS_OP
#define CROSS_OP

#include <iostream>
#include <vector>
class Chromosome;

class CrossOp
{
    public:
        virtual ~CrossOp() {};
        virtual const std::vector<Chromosome> run(std::vector<Chromosome>& in) = 0;
};

#endif /*CROSS_OP*/
