#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>


class simulatedAnnealing
{
    public:
        simulatedAnnealing(std::vector<int> &tour, std::vector<std::vector<int>> &graph);
        virtual ~simulatedAnnealing();
        double temperature = 5; //10 works well for #2, need to make this dependent on n
        double coolingRate = 0.1; //0.001 works for #2

        int calcSize(std::vector<std::vector<int>> &graph, std::vector<int> &hamList);
        std::vector<int> annealing(std::vector<int> &tour, std::vector<std::vector<int>> &graph);
        double acceptProb(int oldCost, int newCost, double t);
        void trans(std::vector<int> &newSolution, std::vector<int> &tour, std::vector<std::vector<int>> &graph, int tourLength);

        std::vector<int> result;

    protected:
    private:
};

#endif // SIMULATEDANNEALING_H
