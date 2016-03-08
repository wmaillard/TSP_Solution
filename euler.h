<<<<<<< HEAD
#ifndef EULER_H
#define EULER_H
#include <vector>

#include <stack>


class euler
{
    public:
        euler(std::vector<std::vector<int>> &adjList);
        virtual ~euler();
        std::vector<int> discovered;
        std::vector<std::vector<int>> tour; //edgeList tour where i is node and tour[i] are the connected nodes
        std::vector<std::vector<int>> adjListMSTPlus;
        int countForBridge(int vertex);
        void removeEdge(int u, int v);
        bool canRemove(int u, int v);
        std::vector<int> tourList;
    protected:
    private:
};

#endif // EULER_H
=======
#ifndef EULER_H
#define EULER_H
#include <vector>

#include <stack>


class euler
{
    public:
        euler(std::vector<std::vector<int>> &adjList);
        virtual ~euler();
        std::vector<int> discovered;
        std::vector<std::vector<int>> tour; //edgeList tour where i is node and tour[i] are the connected nodes
        std::vector<std::vector<int>> adjListMSTPlus;
        int countForBridge(int vertex);
        void removeEdge(int u, int v);
        bool canRemove(int u, int v);
        std::vector<int> tourList;
    protected:
    private:
};

#endif // EULER_H
>>>>>>> origin/master
