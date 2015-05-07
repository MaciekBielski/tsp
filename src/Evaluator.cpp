#include "Evaluator.hpp"

//static non-const data initialization
Population* Evaluator::popOfBest = nullptr;

Evaluator::Evaluator(const DataGenerator &dt):
    data(dt)
{}

void Evaluator::computeValue(Chromosome &ch)
{
    uint8Vector path = ch.getElements();
    std::vector< uint8Vector > passengers = data.getPassengers();
    std::vector< intVector > distances = data.getDistances();
    std::vector< Passenger > passList;
    size_t passCounter = 0;
    int sumValue = 0;
    int distance = 0;
    float ratio = 0.0f;

    /* Iterates through all stops on a given path with the exception of the last one
     * because nobody gets in on the last stop
     */
    for(uint8Vector::iterator it = path.begin(); it != (path.end()-1); it++)
    {
        /*all destinations for the given stop *it
         */
        for(uint8_t &dest : passengers.at(*it))
        {
            /* check whether the destination is reachable on a given path
             */
            uint8Vector::iterator subIt = it;
            subIt = std::find(it, path.end(), dest);
            if(subIt != path.end())
            {
                /* destination is reachable through a given path - create a passenger and
                 * add it to the passengers list
                 */
                Passenger p = createPassenger(passCounter++,it,subIt,distances);
                passList.push_back(p);
            }
        }
        /* add the distance between the given stop and the next one to the accumulated sum of passed distances
         */
        distance += distances[*it][*(it+1)];
    }
    /* now all the passengers for a given path have been created so we can count the 'price' for their journeys
     * sumValue is the sum of all prices of the passengers
     */
    for(Passenger &p : passList)
    {
        sumValue += p.distance;
    }
    /* computing the ratio of the accumulated prices - profit to the kilometers passed,
     * setting precision to 3 digits 
     */ 
    ratio = static_cast<float>(static_cast<int>( (sumValue/(float)distance) * 1000)/1000.0f);
    /* saving the information computed into the chromosome's guts
     */
    ch.setValue(sumValue);
    ch.setDistance(distance);
    ch.setRatio(ratio);
}

Evaluator::Passenger Evaluator::createPassenger(size_t id, uint8Vector::iterator orig, uint8Vector::iterator dest, std::vector< intVector > distances)
{
    Passenger out;
    out.id = id; 
    out.origin = *orig;
    out.destination = *dest;
    out.distance = 0;
    /* computing the 'price' for that passenger that is the distance passed - no coefficients */
    for(;orig != dest; orig++)
    {
        int start = *orig;
        int stop = *(orig+1);
        out.distance += distances[start][stop];
    }
    return out;
}

void Evaluator::popEval(Population &pop)
{
    /* Gets the population and evaluates each chromosome of it. After that
     * sorts the population.
     * - sets it in Population object as the best chromosome of that population
     * - check whether the best chromosome is better than the best chromosome in
     *   the best population pointed by *popOfBest, if yes than update
     */ 
    std::vector<Chromosome>& popElements = pop.getElements();
    for(Chromosome &p : popElements)
        computeValue(p);
    /* sorting the chromosomes after computation
     */
    std::sort(popElements.begin(), popElements.end(), sortEval);
}

void Evaluator::setPopOfBest(Population* ptr)
{
    /* first population case */
    if(popOfBest == nullptr)
        popOfBest = ptr; 
    /* each next population */
    else
    {
        Chromosome curr = (popOfBest->getElements())[0];
        Chromosome cand = (ptr->getElements())[0];
        if(cand.getRatio() > curr.getRatio() )
            popOfBest = ptr;
    }
}
std::string Evaluator::Passenger::str() const
{
    std::ostringstream out;
    out<<(int)id<<": "<<(int)origin<<" - "<<(int)destination<<"  "<<distance;
    return out.str();
}

bool Evaluator::sortEval(const Chromosome& a, const Chromosome& b)
{
    return (a.getRatio() > b.getRatio());
}
