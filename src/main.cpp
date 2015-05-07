#include "Globals.hpp"
#include "DataGenerator.hpp"
#include "Family.hpp" 
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstdint>

/*
 *  -l<filename> - loads data from the file
 *  -d - demo
 *  -s<filename> - saves data in the file
 *  -n - number of cities (default == 10), mod 256, effect only for generation
 *  -p - number of chromosoms in a population (default: 20)
 *  -a - number of ancestors - best chromosoms taken from previous generation (default: 2)
 *  -c - crossing operator type (default: 1 - the only implemented)
 *  -g - number of newly generated chromosoms (default 2)
 *  -i - max iterations
 *  -x - crossing probability (default: 0.8)
 *  -y - mutation probability (default: 0.4)
 *  -u - max age (default:0 - not implemented yet)
 *  -v - profit threshold relative to previous best (default: 0.01)
 *  -w - max number of non-profit iterations allowed (default: 5)
 */

static const uint8_t DEFAULT_CITIES_NB = 10;
static const std::string DEFAULT_DATA_PATH = "data.csv";

int main(int argc, char **argv)
{
    //pseudorandom generator initialization
    srand(time(NULL));
    int opt; 
    uint8_t count, popSz=20, ancSz=2, genSz=2, maxIter=100, maxAge=0, maxNonProfitIter=10, cxType=1; 
    float pc=0.8, pm=0.4, minProfitRel=0.5;
    bool COUNT = false, DEMO = false, LOAD = false, SAVE = false;
    std::string filepath;
    while ( (opt = getopt(argc, argv, "dl::s::n:g:a:c:p:i:x:y:u:v:w:")) != -1 )
    {
        switch (opt)
        {
            case 'd':
                DEMO = true; break;
            case 'l':
                LOAD = true;
                filepath = (optarg != NULL) ? std::string(optarg) : DEFAULT_DATA_PATH;
                break;
            case 's':
                SAVE = true;
                filepath = (optarg != NULL) ? std::string(optarg) : DEFAULT_DATA_PATH;
                break;
            case 'n':
                COUNT = true;
                count = (uint8_t) std::strtol(optarg, NULL, 10);
                break;
            case 'g':
                genSz = (uint8_t) std::strtol(optarg, NULL, 10);
                break;
            case 'a':
                ancSz = (uint8_t) std::strtol(optarg, NULL, 10);
                break;
            /* only PMX operator already implemented */
            // case 'c':
            //     cxType = (uint8_t) std::strtol(optarg, NULL, 10);
            //     if(cxType != 1 && cxType != 2 && cxType != 3)
            //         cxType = 1;
            //     break;
            case 'p':
                popSz = (uint8_t) std::strtol(optarg, NULL, 10);
                break;
            case 'i':
                maxIter = (uint8_t) std::strtol(optarg, NULL, 10);
                break;
            case 'x':
                pc = std::strtof(optarg, NULL);
                pc = static_cast<float>(static_cast<int>(pc*1000))/1000;
                break;
            case 'y':
                pm = std::strtof(optarg, NULL);
                pm = static_cast<float>(static_cast<int>(pm*1000))/1000;
                break;
            case 'u':
                maxAge = (uint8_t) std::strtol(optarg, NULL, 10);
                break;
            case 'v':
                minProfitRel = std::strtof(optarg, NULL);
                minProfitRel = static_cast<float>(static_cast<int>(minProfitRel*1000))/1000;
                break;
            case 'w':
                maxNonProfitIter = (uint8_t) std::strtol(optarg, NULL, 10);
                break;
            default:
                fprintf(stderr, "Unknown option");
                exit(EXIT_FAILURE);
                break;
        }
    }
    if(DEMO && !LOAD && !SAVE)
    {
        std::cout<<"Demo:\n\n";
        count = COUNT ? count : DEFAULT_CITIES_NB;
        DataGenerator graph = DataGenerator(count);
        graph.print();
    }
    else if(!DEMO && LOAD && !SAVE)
    {
        if(COUNT)
            std::cout<<" -n option has no effect\n";
        std::cout<<"Loading data from: "<<filepath<<"\n\n";
        DataGenerator graph = DataGenerator(filepath);
        Family fm(graph,cxType);
        fm.setCitiesNb(graph.getCitiesNb());
        fm.setChromSz(graph.getCitiesNb());
        fm.setPopSz(popSz);
        fm.setAncCount(ancSz);
        fm.setGenSz(genSz);
        fm.setPc(pc);
        fm.setPm(pm);
        fm.setMaxAge(maxAge);
        fm.setMaxIter(maxIter);
        fm.setMinProfitRel(minProfitRel);
        fm.setMaxNonProfitIter(maxNonProfitIter);
        logger<<"\nBEST:"<<fm.run().str();
    }
    else if(!DEMO && !LOAD && SAVE) 
    {
        count = COUNT ? count : DEFAULT_CITIES_NB;
        std::cout<<"Generation and saving data as: "<<filepath<<"\n\n";
        DataGenerator graph = DataGenerator(count);
        graph.print();
        graph.save(filepath);
    }
    else if(!DEMO && !LOAD && !SAVE)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(stderr, "Bad option combination \n\n");
        exit(EXIT_FAILURE);
    }
}
