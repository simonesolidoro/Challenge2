#include <iostream>
#include "Matrix.cpp"
using namespace algebra;
int main(){
    Matrix<double,StorageOrdering::row> M({{{0,0},1},{{1,2},3},{{3,3},8}});
    std::map<std::array<std::size_t,2>,double> N(M.estrai(3));
    std::cout<<N[{3,3}]<<std::endl;
    return 0;
}