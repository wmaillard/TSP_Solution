#include "christofides.h"

christofides::christofides(std::vector<std::vector<int>> &graph)
{
    findMST mst(graph);
    minWeightPerfect mwp(mst.MST, graph);
    euler theTour(mwp.adjListMST);


    //Turn the Euler tour in result into a Hamiltonian Circuit**
    std::vector<bool> passed;
    passed.resize(theTour.tourList.size(), false);
    result = theTour.tourList;


    for(int i = 0; i < result.size(); i++){
        if(passed.at(result.at(i)) == true){
            result.erase(result.begin() + i);
            i--;
        }
        else passed.at(result.at(i)) = true;
    }
    //*************


}

christofides::~christofides()
{
    //dtor
}
