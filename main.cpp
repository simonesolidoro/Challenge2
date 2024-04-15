#include<iostream>
#include"Matrix.cpp"
#include<iterator>
using namespace algebra;
int main(){
    // prova fino a compress() 
    Matrix<int,StorageOrdering::row> M;
    M(0,4)=40;
    M(1,2)=21;
    M(1,4)=41;
    M(2,3)=32;
    M(2,7)=72;
    M(3,5)=53;
    M(4,8)=84;
    std::map<std::array<std::size_t,2>,int> D(M.estrai(4));
    for(auto it= D.begin(); it!=D.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }

    M.compress();
    M.printvett();
    M.uncompress();
    std::cout<<M(1,2)<<" "<<M(2,7)<<" "<<M(4,8);

    /*
    Matrix<int,StorageOrdering::row> N;
    N(0,2)=1;
    N(2,3)=5;
    std::cout<<N(2,3)<<std::endl;
    N.compress();
    N.printvett();
    //std::cout<<N(0,2);
    N.uncompress();
    //std::cout<<N(2,3);*/
    return 0;
}