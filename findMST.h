<<<<<<< HEAD
#ifndef FINDMST_H
#define FINDMST_H
#include <vector>
#include <limits.h>
#include <stdio.h>


//Information on Prim's Algorithm taken from here: http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/

//Returns a MST[i] where i is one vertex, MST[i] is the other vertex, and graph[i][MST[i]] is their edge weight


class findMST
{
    public:
        findMST(std::vector<std::vector<int>> &graph);
        virtual ~findMST();
        int numVertices;
        int getMinKey(int keys[], bool includedVertices[]);
        std::vector<int> MST;



    protected:
    private:
};

#endif // FINDMST_H
=======
#ifndef FINDMST_H
#define FINDMST_H
#include <vector>
#include <limits.h>
#include <stdio.h>


//Information on Prim's Algorithm taken from here: http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/

//Returns a MST[i] where i is one vertex, MST[i] is the other vertex, and graph[i][MST[i]] is their edge weight


class findMST
{
    public:
        findMST(std::vector<std::vector<int>> &graph);
        virtual ~findMST();
        int numVertices;
        int getMinKey(int keys[], bool includedVertices[]);
        std::vector<int> MST;



    protected:
    private:
};

#endif // FINDMST_H
>>>>>>> origin/master
