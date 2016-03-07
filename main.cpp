#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include "adjacencyMatrix.h"
#include <limits.h>
#include "findMST.h"
#include "minWeightPerfect.h"
#include "euler.h"
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>
#include <float.h>

using namespace std;

int opt1 = 108159;
int opt2 = 2579;
int opt3 = 1573084;
int optNum = 3;
double opt = opt3;
int tries = 40000000000;
//int numSwaps = 2;




double stopAtOptRatio = 1.10;

string tourFileIn = "examples/tsp_example_3.txt"; //shooting for 1966355"
double temperature = 10000; //good at 100 for 2
double numberAnneals = 1000000;

int calcSize(vector<vector<int>> &graph, vector<int> &hamList);
void trans(vector<int> &newSolution, vector<int> &tour, vector<vector<int>> &graph, int tourLength, bool newTour, vector<vector<int>> &listOfPossibles);
double acceptProb(int oldCost, int newCost, double t);

struct vertices {
    int x;
    int y;
    int name;
    int distance;
};

vector<int> annealing(vector<int> &tour, vector<vector<int>> &graph, double t, vector<vector<int>> &listOfPossibles){
    srand(time(NULL));

    double coolingRate;
    coolingRate = 0.0001; //0 to 1, 1 is fastest
    vector<int> current = tour;
    vector<int> best = current;
    int currentDistance = calcSize(graph, current);
    int bestDistance = calcSize(graph, best);
    bool newTour = true;


    vector<int> newSolution;

    while(t > 1){
        trans(newSolution, current, graph, currentDistance, newTour, listOfPossibles);
        int neighborDistance = calcSize(graph, newSolution);

        if(acceptProb(currentDistance, neighborDistance, t) > ((double) rand() / (RAND_MAX))){
            current = newSolution;
            currentDistance = neighborDistance;
            newTour = true;
        }
        else newTour = false;
        if(currentDistance < bestDistance){
            best = current;
            bestDistance = currentDistance;
        }

        t *= (1 - coolingRate);

    }

    return best;


}
double acceptProb(int oldCost, int newCost, double t){
    if(newCost < oldCost){
        return 1.0;
    }
    return exp(oldCost - newCost)/t;

}
void trans(vector<int> &newSolution, vector<int> &tour, vector<vector<int>> &graph, int tourLength, bool newTour, vector<vector<int>> &listOfPossibleEdges){ //tested, works
    newSolution = tour;




  /*  for(int i = 0; i < tour.size() - 1; i++){
        int x = 0;
        int y = 0;
        x = tour.at(i);
        y = tour.at(i + 1);
        int distance = graph[x][y];
        if(distance < 0.10 * tourLength){  // calcSize(graph, tour)
            vector<int> coords;
            coords.push_back(x);
            coords.push_back(y);
            listOfPossibleEdges.push_back(coords);
        }
    }*/
    /*
    int u = listOfPossibleEdges.at(rand() % listOfPossibleEdges.size()).at(0);
    int v = listOfPossibleEdges.at(rand() % listOfPossibleEdges.size()).at(1);

*/
    int u = tour.at(rand() % tour.size());
    int v = tour.at(rand() % tour.size());

    int temp = newSolution.at(u);
    newSolution.at(u) = newSolution.at(v);
    newSolution.at(v) = temp;

}
bool testTour(vector<int> &tour, vector<vector<int>> &graph){
    int sum = 0;
    for(int i = 0; i < graph.size(); i++){
        sum += i;
    }
    for(int i = 0; i < tour.size(); i++){
        sum -= tour.at(i);
    }
    if(sum == 0){
        return true;
    }
    else return false;

}
int calcSize(vector<vector<int>> &graph, vector<int> &hamList){
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

void printGraph(vector<vector<int>> &graph){
  for(int i = 0; i < graph.size(); i++){
        for(int j = 0; j < graph.at(i).size(); j++){
            std::cout<< graph.at(i).at(j) << " ";
        }
        std::cout << endl;
    }

}

void printAxisLabels(vector<int> &labels){
    for(int i = 0; i < labels.size(); i++){
            cout<< labels.at(i) << " ";
    }
    cout << endl;
}

void printAdjList(std::vector<std::vector<int>>& adjList){
    for(int i = 0; i < adjList.size(); i++){
        std::cout << i << ": ";
        for(int j = 0; j < adjList.at(i).size(); j++){
            std::cout << adjList.at(i).at(j) << ", ";
        }
        std::cout << std::endl;
    }
}

void printAdjList(std::vector<std::vector<int>>& adjList, std::vector<int>& axisLabels){
    for(int i = 0; i < adjList.size(); i++){
        std::cout << axisLabels[i] << ": ";
        for(int j = 0; j < adjList.at(i).size(); j++){
            std::cout << axisLabels[adjList.at(i).at(j)] << ", ";
        }
        std::cout << std::endl;
    }
}

void printAdjList(std::vector<int>& adjList, std::vector<int>& axisLabels){
    for(int i = 0; i < adjList.size(); i++){
        std::cout << axisLabels[i] << ": ";
        if(adjList.at(i) == -1)
            std::cout << "none";
        else
            std::cout << axisLabels[adjList.at(i)];

        std::cout << std::endl;
    }
}

void printAdjList(std::vector<int>& adjList){
    for(int i = 0; i < adjList.size(); i++){
        std::cout << i << ": " ;
        if(adjList.at(i) == -1)
            std::cout << "none";
        else
            std::cout << adjList.at(i);

        std::cout << std::endl;
    }
}


vector<int> multiAnneal(vector<int> &hamList, vector<vector<int>> &graph){

double t = temperature;

cout << "temp: " << t << endl;
vector<int> afterAnnealing;
vector<int> bestOfBest;
double bestRatio = 1;
double theRatio = 1;
double bestTemp = t;
int newSize =  calcSize(graph, hamList);
int oldSize = calcSize(graph, hamList);
double bestOptRatio = (double) oldSize / opt;
int matches = 1;



vector<vector<int>> listOfPossibles;
/*
int currentDistance = newSize;

for(int i = 0; i < graph.size(); i++){
    for (int j = i + 1; j < graph.size(); j++){
        if(graph.at(i).at(j) < graph.size() * .1){ // < max distance that we want to check for
            vector<int> coords;
            coords.push_back(i);
            coords.push_back(j);
            listOfPossibles.push_back(coords);
        }
    }
}
*/
for (int i = 0; i < numberAnneals && tries > matches; i++){

afterAnnealing =  annealing(hamList, graph, t, listOfPossibles);

newSize = calcSize(graph, afterAnnealing);
oldSize = calcSize(graph, hamList);

theRatio = (double) newSize / oldSize;



if(theRatio < bestRatio && i != 0){
    bestRatio = theRatio;
    bestOfBest = afterAnnealing;
    bestOptRatio = newSize / opt;
    matches = 0;

}
else matches++;

cout << "Best Opt Ratio: " << bestOptRatio << endl;

}

return bestOfBest;
};



//Information on Prim's Algorithm taken from here: http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
//Returns a MST[i] where i is one vertex, MST[i] is the other vertex, and graph[i][MST[i]] is their edge weight
int main()
{
    std:string fileName = tourFileIn;
    vector<vector<int>> graph;
    adjacencyMatrix matrix(fileName, graph);

findMST mst(graph);

minWeightPerfect mwp(mst.MST, graph);


euler theTour(mwp.adjListMST);


vector<bool> passed;
passed.resize(theTour.tourList.size(), false);
vector<int> hamList = theTour.tourList;


for(int i = 0; i < hamList.size(); i++){
    if(passed.at(hamList.at(i)) == true){
        hamList.erase(hamList.begin() + i);
        i--;
    }
    else passed.at(hamList.at(i)) = true;
}

cout << "****************" << endl;
//printAdjList(hamList);




cout << "****************" << endl;
cout << "****************" << endl;


vector<int> bestOfBest = hamList;
vector<int> bestOfBestMax = hamList;
double bestOfBestMaxRatio = calcSize(graph, bestOfBestMax) / opt;

while(bestOfBestMaxRatio > stopAtOptRatio){
    vector<int> bestOfBest = multiAnneal(hamList, graph);
    double bestOfBestRatio = calcSize(graph, bestOfBest) / opt;
    if(bestOfBestRatio < bestOfBestMaxRatio){
        bestOfBestMaxRatio = bestOfBestRatio;
        bestOfBestMax = bestOfBest;
    }
    cout << "Best so far: " << bestOfBestMaxRatio << endl;
}




//cout << "Best Ratio: " << bestRatio << endl;
//printAdjList(bestOfBest);
cout << "PathLength of the best of the best of the best: " << calcSize(graph, bestOfBestMax) << endl;


cout << "optimal: " << opt << endl;
cout << "Optimation ratio: " << calcSize(graph, bestOfBestMax) / opt<< endl;


/*

cout << "All tasks?: " << mwp.checkAllTasks() << endl;
//columns


printGraph(mwp.bpGraph);
cout << "\n Max edges: " << mwp.maxBPM(mwp.bpGraph) << endl;
cout << "Num vertices: " << mwp.bpGraph.size() << endl;
printAdjList(mwp.matchR, mwp.axisLabels);
//printAdjList(mwp.adjListPerfect, mwp.axisLabels);
int x = 1;
int y = 0;
while(x != y){
mwp.iterative();
printGraph(mwp.mwpSubgraph);
printGraph((mwp.bpGraph));
x = mwp.maxBPM(mwp.bpGraph);
y = mwp.bpGraph.size();
cout << "\n Max edges: " << x << endl;
cout << "Num vertices: " << y << endl;
printAdjList(mwp.matchR, mwp.axisLabels);
//printGraph(mwp.mwpSubgraph);
}*/


/*
std::vector<std::vector<int>> zeroWeightSubgraph;
for(int i = 0; i < mst.adjMatrixOdds.size(); i++){
    for(int j = 0; j < mst.adjMatrixOdds.at(i).size(); j++){
         if(j != i && )
}


vector<vector<int>> maxMatching;
for(int i = 0; i < mst.adjMatrixOdds.size(); i++){
    vector<int> xy;
    xy.push_back(-1);
    xy.push_back(-1);
    minWeight = INT_MAX;
    for(int j = 0; j < mst.adjMatrixOdds.at(i).size(); j++){
       if(j != i && mst.adjMatrixOdds[i][j] <= 0){
            if(minWeight > graph[mst.axisLabels[i]][mst.axisLabels[j]]){
                minWeight = graph[mst.axisLabels[i]][mst.axisLabels[j]];
                xy.at(0) = mst.axisLabels[i];
                xy.at(1) = mst.axisLabels[j];
            }
       }
    }
    if(xy[0] != -1 && xy[1] != -1)
        maxMatching.push_back(xy);
}
cout << "\n\n\n**************\n\n" << endl;
cout << "Num Edges: " << maxMatching.size() << endl;
for(int i = 0; i < maxMatching.size(); i++){
    cout << "x: " << maxMatching.at(i).at(0) <<"y: " << maxMatching.at(i).at(1) << endl;
}*/

}

