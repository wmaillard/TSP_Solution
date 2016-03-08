#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H
#include "findMST.h"
#include "minWeightPerfect.h"
#include "euler.h"
#include <vector>

class christofides
{
    public:
        christofides(std::vector<std::vector<int>> &graph);
        virtual ~christofides();
        std::vector<int> result;
    protected:
    private:
};

#endif // CHRISTOFIDES_H
