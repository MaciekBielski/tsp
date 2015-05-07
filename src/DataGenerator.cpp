#include "DataGenerator.hpp"
//test change
DataGenerator::DataGenerator(size_t d)
{
    citiesNb = (d>maxCities) ? maxCities : d;
    generate(citiesNb);
}

DataGenerator::DataGenerator(const std::string &filename)
{
    load(filename);
}
void DataGenerator::generate(size_t citiesNb)
{
    /* cities matrix generation */
    distM.resize(citiesNb);
    for (size_t i=0; i<citiesNb; i++)
    {
        distM[i].resize(citiesNb);
        distM[i][i] = 0;        //main diagonal
        for (size_t j=i+1; j<citiesNb; j++)
            distM[i][j] = rand() % maxDist +1; 
        for (size_t k=0; k<i; k++)
            distM[i][k] = distM[k][i]; 
    }
    /* passengers matrix generation 
     * for each city - vector element - consecutive numbers are destinations of subsequent passengers,
     * the number of passengers in each city is random [0-9] and their destinations too,
     * city's index : [0-citiesNb)
     */
    passengers.resize(citiesNb);
    for(std::vector< std::vector<uint8_t> >::iterator it = passengers.begin() ; it != passengers.end() ; it++)
    {
        size_t passNb = (size_t) (rand() % 10); 
        int index = it - passengers.begin();
        for(size_t sz = 0; sz<passNb; sz++)
        {
            uint8_t dest; 
            do
                dest = (uint8_t) (rand()%citiesNb) ;
            while(dest == index);
            it->push_back(dest);
        }
    }
}

void DataGenerator::print() const
{
    std::ostringstream out;
    for(size_t i=0; i<citiesNb; i++, out << std::endl )
        for(size_t j=0; j<citiesNb; j++)
            out << distM[i][j] <<" "; 
    out<<std::endl;
    for(size_t i=0; i<citiesNb; i++)
    {
        out<<"C"<<i<<"("<<passengers[i].size()<<")"<<": ";
        for(std::vector<uint8_t>::const_iterator it = passengers[i].begin(); it!= passengers[i].end(); it++)
            out<<(int)*it<<" ";
        out<<std::endl;
    }
    std::cout<<out.str();
}

void DataGenerator::save(const std::string &filepath) const
{
    std::ofstream out;
    out.open(filepath, std::ofstream::out | std::ofstream::trunc);
    if(out.good())
    {
        out<<"citiesNb: "<<citiesNb<<std::endl<<std::endl;
        for(size_t i=0; i<distM.size(); i++)
        {
            std::vector<int> row = distM[i];
            std::copy(row.begin(), row.end(), std::ostream_iterator<int>(out,"\t"));
            out<<std::endl;
        }
        out<<std::endl;
        for(size_t i=0; i<citiesNb; i++)
        {
            out<<"C"<<i<<": ";
            for(std::vector<uint8_t>::const_iterator it = passengers[i].begin(); it!= passengers[i].end(); it++)
                out<<(int)*it<<" ";
            out<<std::endl;
        }
    }
    out.close();
}

void DataGenerator::load(std::string filename)
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if(in.good())
    {
        /* reading dimension */
        std::string tmpNb;
        in>>tmpNb;
        if (tmpNb=="citiesNb:")
        {
            in>>citiesNb;
            distM.resize(citiesNb);
            for(size_t i=0; i<citiesNb; i++)
            {
                distM[i].resize(citiesNb);
                for(size_t j=0; j<citiesNb; j++)
                   in>>distM[i][j];
            }
            /* for each city:
             * ignore characters until :, then parse all integers until end of line
             * make use of strtol
             */
            passengers.resize(citiesNb);
            for(size_t i=0; i<citiesNb; i++)
            {
                std::vector<uint8_t> tmpDest = parseDestinations(in);
                passengers[i].swap(tmpDest);
            }
        }
        else
        {
            std::cerr<<"opening error"<<std::endl;
        }
    }
    in.close();
}

std::vector<uint8_t> DataGenerator::parseDestinations (std::ifstream &is)
{
    std::string tmpLine;
    std::vector<uint8_t> destinations;
    is.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    std::getline(is, tmpLine);
    const char *start = tmpLine.c_str();
    char *end;
    for(long n = strtol(start, &end, 10);
            start != end;
            n = strtol(start, &end, 10)
       )
    {
        start = end;
        destinations.push_back((uint8_t)n);
    }
    return destinations;
}
