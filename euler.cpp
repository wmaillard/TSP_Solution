#include "euler.h"

euler::euler(std::vector<std::vector<int>> &adjList)
{
    adjListMSTPlus = adjList;
    std::vector<int> row;
    tour.resize(adjListMSTPlus.size(), row);

    int currentNode = 0;

    while(adjListMSTPlus.at(currentNode).size() > 0){
    int nextNode = -1;

    for(int i = 0; i < adjListMSTPlus.at(currentNode).size(); i++){
        int possibleNode = adjListMSTPlus.at(currentNode).at(i);
        if(canRemove(currentNode, possibleNode)){
            nextNode = possibleNode;
            break;
        }
    }

    removeEdge(currentNode, nextNode);

    tourList.push_back(currentNode);
    tour.at(currentNode).push_back(nextNode);
    currentNode = nextNode;

    }

}

euler::~euler()
{
    //dtor
}

int euler::countForBridge(int vertex){
    int count = 0;
    discovered.clear();
    discovered.resize(adjListMSTPlus.size(), 0);
    std::stack<int> theStack;
    theStack.push(vertex);
    while(!theStack.empty()){
        vertex = theStack.top();
        theStack.pop();
        if(discovered.at(vertex) != 1){
            discovered.at(vertex) = 1;
            count++; //?
            for(int i = 0; i < adjListMSTPlus.at(vertex).size(); i++){
                theStack.push(adjListMSTPlus.at(vertex).at(i));
            }
        }
    }

    return count;

}

bool euler::canRemove(int u, int v){ //edge
    if(adjListMSTPlus.at(u).size() == 1){
        return true;
    }

    int countWithEdge = countForBridge(u);

    removeEdge(u, v);

    int countWOEdge = countForBridge(u);

    adjListMSTPlus.at(u).push_back(v); //add edge back in
    adjListMSTPlus.at(v).push_back(u);

    return (countWithEdge > countWOEdge) ? false : true;

}


void euler::removeEdge(int u, int v){

    for(int i = 0; i < adjListMSTPlus.at(u).size(); i++){
        if(adjListMSTPlus.at(u).at(i) == v){
            adjListMSTPlus.at(u).erase(adjListMSTPlus.at(u).begin() + i);
        }
    }


    for(int i = 0; i < adjListMSTPlus.at(v).size(); i++){
        if(adjListMSTPlus.at(v).at(i) == u){
            adjListMSTPlus.at(v).erase(adjListMSTPlus.at(v).begin() + i);
        }
    }

}












