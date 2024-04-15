#include<iostream>
#include"Matrix.cpp"
#include<iterator>
using namespace algebra;
int main(){
    Matrix<int,StorageOrdering::row> M;
    M(1,2)=21;
    M(1,4)=41;
    M(2,3)=32;
    M(2,7)=72;
    M(4,8)=84;
    std::map<std::array<std::size_t,2>,int> D(M.estrai(1));
    for(auto it= D.begin(); it!=D.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }

    M.compress();
    M.printvett();

    return 0;
}