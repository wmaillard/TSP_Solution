#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include <limits.h>


#include "christofides.h"
#include "adjacencyMatrix.h"
#include "simulatedAnnealing.h"

using namespace std;

bool knowOptimal = true;  //If the optimal solution is known, so that we can get our ratio

int opt1 = 108159;  //These are the given optimal routes for the example problems
int opt2 = 2579;
int opt3 = 1573084;
int optNum = 2;  //This is the example problem being worked on
double opt = opt2;  //same as this
double stopAtOptRatio = 1.20;  //Killswitch if a ratio is reached, not implemented right now

string tourFileIn = "examples/tsp_example_2.txt";




bool testTour(vector<int> &tour, vector<vector<int>> &graph);
int calcSize(vector<vector<int>> &graph, vector<int> &hamList);
void trans(vector<int> &newSolution, vector<int> &tour, vector<vector<int>> &graph, int tourLength, bool newTour, vector<vector<int>> &listOfPossibles);
double acceptProb(int oldCost, int newCost, double t);
void printAdjList(std::vector<int>& adjList);

struct vertices {
    int x;
    int y;
    int name;
    int distance;
};







//Information on Prim's Algorithm taken from here: http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
//Returns a MST[i] where i is one vertex, MST[i] is the other vertex, and graph[i][MST[i]] is their edge weight
int main()
{
    cout << "Reading the file and calculating distances..." << endl;
    std:string fileName = tourFileIn;
    vector<vector<int>> graph;
    adjacencyMatrix matrix(fileName, graph);  //read the cities in and create an adjacency matrix
    cout << "Done!\n\n**********************************\n" << endl;

    cout << "Running Christofides Algorithm..." << endl;
    christofides chris(graph);      //Run Christofides algorithm
    vector<int> pathAfterChris = chris.result;  //Extract the resulting path
    cout << "Done!\n\n**********************************\n" << endl;

    cout << "Running Simulated Annealing..." << endl;
    simulatedAnnealing SA(pathAfterChris, graph);
    vector<int> afterAnnealing = SA.result;
    cout << "Done!\n\n**********************************\n" << endl;

    cout << "Path-Length that the Christofides Algorithm Found: " << calcSize(graph, pathAfterChris) << endl;
    cout << "Path-Length Found After Simulated Annealing: " << calcSize(graph, afterAnnealing) << endl;

    if(testTour(pathAfterChris, graph) && testTour(afterAnnealing, graph)){
        cout << "Both are legitimate tours" << endl;
    }
    if (!testTour(pathAfterChris, graph)){
        cout << "The first tour failed!" << endl;
    }
    if(!testTour(afterAnnealing, graph)){
        cout << "The second tour failed!" << endl;
    }


    cout << "\n" << endl;
    /******************Only Relevant if you know the optimal pathlength ******************/





    if(knowOptimal){
        cout << "Optimal Pathlength: " << opt << endl;
        cout << "Our Ratio Before Annealing Ratio: " << calcSize(graph, pathAfterChris) / opt << endl;
        cout << "Our Ratio After Annealing: " << calcSize(graph, afterAnnealing) / opt<< endl;
    }



}

/**********************Graph Tools: Printing, Calculating Tour Length, Checking Tour Validity ************************/

//Test a tour to make sure that it includes all nodes in a graph
//True means that it is good.
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

//Returns the length of a tour, graph is the original adjacency matrix, hamlist is any tour route in a vector i.e.
// [0] = first node visited, [1] = second...

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

