<<<<<<< HEAD
#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include <math.h>
#include <vector>
#include <string>
#include <fstream>



class adjacencyMatrix
{
    public:
        adjacencyMatrix(std::string fileName, std::vector<std::vector<int>> &adjMatrix);
        virtual ~adjacencyMatrix();
        struct vertices {
        int x;
        int y;
        int name;
        int distance;
        };
        //std::vector<std::vector<int>> adjMatrix;
    protected:
    private:
};

#endif // ADJACENCYMATRIX_H
=======
#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include <math.h>
#include <vector>
#include <string>
#include <fstream>



class adjacencyMatrix
{
    public:
        adjacencyMatrix(std::string fileName, std::vector<std::vector<int>> &adjMatrix);
        virtual ~adjacencyMatrix();
        struct vertices {
        int x;
        int y;
        int name;
        int distance;
        };
        //std::vector<std::vector<int>> adjMatrix;
    protected:
    private:
};

#endif // ADJACENCYMATRIX_H
>>>>>>> origin/master
