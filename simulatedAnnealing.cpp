#include "simulatedAnnealing.h"

simulatedAnnealing::simulatedAnnealing(std::vector<int> &tour, std::vector<std::vector<int>> &graph)
{
    result = annealing(tour, graph);

}

simulatedAnnealing::~simulatedAnnealing()
{
    //dtor
}
//return a path after simulated annealing
std::vector<int> simulatedAnnealing::annealing(std::vector<int> &tour, std::vector<std::vector<int>> &graph){

    srand(time(NULL));
 //0.001 is amazing for #2;

    std::vector<int> current = tour;
    std::vector<int> best = current;

    int currentDistance = calcSize(graph, current);
    int bestDistance = calcSize(graph, best);

    bool newTour = true;


    std::vector<int> newSolution;

    double t = temperature;
    while(t > 1){
        trans(newSolution, current, graph, currentDistance);
        int neighborDistance = calcSize(graph, newSolution);

        if(acceptProb(currentDistance, neighborDistance, t) > ((double) rand() / (RAND_MAX))){
            current = newSolution;
            currentDistance = neighborDistance;
            newTour = true;
            t *= (1 - coolingRate);
        }
        else newTour = false;
        if(currentDistance < bestDistance){
            best = current;
            bestDistance = currentDistance;

        }
        //cout << "Best Distance: " << bestDistance << endl; //turn on to watch as the ratio decreases
        //cout << "Opt Ratio: " << bestDistance / opt << endl;
        //t *= (1 - coolingRate); //original spot!!, new spot above seems to work better, more manageable temperature ranges (1 - 1000ish)

    }
    return best;
}

int simulatedAnnealing::calcSize(std::vector<std::vector<int>> &graph, std::vector<int> &hamList){
    int pathLength = 0;
    int u, v;
    for(int i = 0; i < hamList.size() - 1; i++){
        u = hamList.at(i);
        v = hamList.at(i + 1);

        pathLength += graph.at(u).at(v);
    }
    pathLength += graph[hamList.at(hamList.size() - 1)][hamList.at(0)];
    return pathLength;

}

void simulatedAnnealing::trans(std::vector<int> &newSolution, std::vector<int> &tour, std::vector<std::vector<int>> &graph, int tourLength){ //tested, works
    //This is a 2-opt transformation
    //It puts the new, transformed solution into newSolution

    newSolution = tour;
    int u = tour.at(rand() % tour.size());
    int v = tour.at(rand() % tour.size());


    int right = tour.size() * 2 + v - 1;
    if(u != v){
        for(int i = u + 1; i % tour.size() != v; i++){
              int temp = tour.at(i % tour.size());
              newSolution.at(i %  tour.size()) = tour.at(right % tour.size());
              newSolution.at(right % tour.size()) = temp;
              right--;
        }
    }

}
double simulatedAnnealing::acceptProb(int oldCost, int newCost, double t){
    if(newCost < oldCost){
        return 1.0;
    }
    return exp(oldCost - newCost)/t;

}

