#include "minWeightPerfect.h"

minWeightPerfect::minWeightPerfect(std::vector<int> &MST, std::vector<std::vector<int>> &graph)
{
    minSpanTree = MST;
   // makeAdjList(false);
   // makeAdjList(false);

    makeAdjList(true);
   // deleteEdgesFromOdd();
    makeAdjMatrix(graph);

    //adjList.resize(mwpSubgraph.size(), -1);

    int length = INT_MAX;
    int closest;
    for(int i = 0; i < mwpSubgraph.size(); i++){
        closest = -1;
        length = INT_MAX;
        for(int j = i + 1; j < mwpSubgraph.at(i).size(); j++){
            bool notIn = true;
            for(int k = 0; k < adjListMST.at(axisLabels.at(i)).size(); k++){  //~O(1) time
                if(adjListMST.at(axisLabels.at(i)).at(k) == axisLabels.at(j)){
                    notIn = false;
                    break;
                }
            }
            if(mwpSubgraph.at(j).size() > 0 && mwpSubgraph.at(i).at(j) < length && notIn){
                length = mwpSubgraph.at(i).at(j);
                closest = j;
            }


        }
      /*  if(adjListMST.at(axisLabels.at(i)).size() == 1 && adjListMST.at(axisLabels.at(i)).at(0) == -1)
            adjListMST.at(axisLabels.at(i)).clear();*/
       // if(adjListMST.at(axisLabels.at(i)).size() % 2 == 1 && closest != i){
       if(closest != -1){
        adjListMST.at(axisLabels.at(i)).push_back(axisLabels.at(closest));
        adjListMST.at(axisLabels.at(closest)).push_back(axisLabels.at(i));
        mwpSubgraph.at(i).clear();
        mwpSubgraph.at(closest).clear();
       }
}
}




minWeightPerfect::~minWeightPerfect()
{
    //dtor
}



void minWeightPerfect::makeAdjList(bool oddsOnly){
        for(int i = 0; i < minSpanTree.size(); i++){
            std::vector<int> edgeList;
            int degree = 0;
            if(minSpanTree.at(i) != -1){
                edgeList.push_back(minSpanTree.at(i));
                degree++;
            }
            for(int j = 1; j < minSpanTree.size(); j++){
               if(minSpanTree.at(j) == i){
                  degree++;
                  edgeList.push_back(j);
               }
            }
            adjListMST.push_back(edgeList);

              if  (degree % 2 == 0){
                    edgeList.clear(); //if even clear, probably could be more efficient, but won't make a big difference
                }
            adjListOddsMST.push_back(edgeList);

}
}

void minWeightPerfect::makeAdjMatrix(std::vector<std::vector<int>> &graph){
    int rows = 0;
    for(int i = 0; i < adjListOddsMST.size(); i++){
        if(adjListOddsMST.at(i).size() > 0){
            axisLabels.push_back(i);
            rows++;
        }
    }
    mwpSubgraph.resize(rows);

    for(int i = 0; i < mwpSubgraph.size(); i++){
        mwpSubgraph.at(i).resize(rows, 0);
    }
    for(int i = 0; i < mwpSubgraph.size(); i++){
        for (int j = i + 1; j < mwpSubgraph.size(); j++){
            mwpSubgraph[i][j] = graph[axisLabels[i]][axisLabels[j]];
        }
    }


}





//from here: http://www.geeksforgeeks.org/maximum-bipartite-matching/
//************This is not mine and needs to be rewritten
// A DFS based recursive function that returns true if a
// matching for vertex u is possible


// Returns maximum number of matching from M to N




//************
/*Find maximal matching of all edges with zero weight from here:
    http://www.cs.dartmouth.edu/~ac/Teach/CS105-Winter05/Notes/kavathekar-scribe.pdf*/
/* Now do step 3 and 4 here https://en.wikipedia.org/wiki/Hungarian_algorithm
or iterative step here: http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Assignment/algorithm.html*/
