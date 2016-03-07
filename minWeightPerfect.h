#ifndef MINWEIGHTPERFECT_H
#define MINWEIGHTPERFECT_H
#include <vector>
#include <limits.h>
#include <iostream>
#include <string.h>
#include <stack>


class minWeightPerfect
{
    public:
        minWeightPerfect(std::vector<int> &MST, std::vector<std::vector<int>> &graph); //y
        virtual ~minWeightPerfect(); //y
        void makeAdjList(bool oddsOnly);
            std::vector<int> minSpanTree;
            std::vector<std::vector<int>> adjListOddsMST;
            std::vector<std::vector<int>> adjListMST; //where the result is stored
        void makeAdjMatrix(std::vector<std::vector<int>> &graph);
            std::vector<int> axisLabels;
            std::vector<std::vector<int>> mwpSubgraph;

    protected:
    private:
};

#endif // MINWEIGHTPERFECT_H
