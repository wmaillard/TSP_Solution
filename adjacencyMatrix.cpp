#include "adjacencyMatrix.h"


adjacencyMatrix::adjacencyMatrix(std::string fileName, std::vector<std::vector<int>> &adjMatrix)
{
    std::ifstream infile(fileName);
    int name, x, y, distance;
    std::vector<vertices> coordinates;
    vertices aNode;
    while (infile >> aNode.name >> aNode.x >> aNode.y){
        aNode.distance = nearbyint(sqrt(pow((aNode.x - 0), 2) + pow((aNode.y - 0), 2)));
        coordinates.push_back(aNode);
    }

    for(int i = 0; i < coordinates.size(); i++){
        std::vector<int> aRow;
        for(int j = 0; j < coordinates.size(); j++){
           aRow.push_back(nearbyint(sqrt(pow((coordinates.at(i).x - coordinates.at(j).x), 2) + pow((coordinates.at(i).y - coordinates.at(j).y), 2))));
        }
        adjMatrix.push_back(aRow);
    }
}

adjacencyMatrix::~adjacencyMatrix()
{
    //dtor
}
