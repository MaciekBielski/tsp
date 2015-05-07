#ifndef PMX_OP
#define PMX_OP

#include <iostream>
#include <vector>

#include "CrossOp.hpp"
#include "Chromosome.hpp"
#include "Globals.hpp"

class PMXOp : public CrossOp
{
    private:
        size_t cut1=0, cut2=0;
        void init(const size_t maxLength);
        void pairCross(
                Chromosome &p1, 
                Chromosome &p2, 
                std::vector<uint8_t> &c1, 
                std::vector<uint8_t> &c2)
            const;
    public:
        PMXOp();
        ~PMXOp();
        const std::vector<Chromosome> run(std::vector<Chromosome>& in);
};

#endif /*PMX_OP*/
