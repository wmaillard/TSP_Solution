#include "findMST.h"
//creates mst as a adjacency list
//There is a function in minWeightPerfect to convert adjList to adjMatrix if needed

findMST::findMST(std::vector<std::vector<int>> &graph)
{
    numVertices = graph.size();

    //int anArray[numVertices];  //the min spanning tree

    MST.resize(numVertices);
    int keys[numVertices];
    bool includedVertices[numVertices]; //vertices included in MST

    for(int i = 0; i < numVertices; i++){
        keys[i] = INT_MAX;
        includedVertices[i] = false;
    }

    //initialize the first vertex
    keys[0] = 0;
    MST[0] = -1;

    for(int i = 0; i < numVertices - 1; i++){
        int minVert = getMinKey(keys, includedVertices);
        includedVertices[minVert] = true;

        for(int j = 0; j < numVertices; j++){
            if(graph[minVert][j] && includedVertices[j] == false && graph[minVert][j] < keys[j]){
                MST[j] = minVert;
                keys[j] = graph[minVert][j];
            }
        }
    }






}

findMST::~findMST()
{
    //dtor
}

int findMST::getMinKey(int keys[], bool includedVertices[]){
    int minVert = INT_MAX;
    int min_index;

    for(int i = 0; i < numVertices; i++){
        if(includedVertices[i] ==  false && keys[i] < minVert){
            minVert = keys[i];
            min_index = i;
        }
    }
    return min_index;
}


