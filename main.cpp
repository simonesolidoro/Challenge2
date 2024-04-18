#include<iostream>
#include"Matrix.cpp"
#include<iterator>
using namespace algebra;

int main(){
   // prova constructor
   // per righe---------> ok (compila) 
    std::map<std::array<std::size_t,2>,int> mapR={{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}};
    Matrix<int,StorageOrdering::row> MR(mapR); 

   //per colonne---------> ok 
    std::map<std::array<std::size_t,2>,int> mapC={{{0,0},1},{{0,1},3},{{1,0},2},{{1,1},4}};
    Matrix<int,StorageOrdering::col> MC(mapC);

    //estri--------->ok
    //righe
    std::map<std::array<std::size_t,2>,int> DR(MR.estrai(1));
    for(auto it= DR.begin(); it!=DR.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }
    //colonne
    std::map<std::array<std::size_t,2>,int> DC(MC.estrai(1));
    for(auto it= DC.begin(); it!=DC.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }

    // compress(),uncompress(),is_compress() per R--->ok 
    std::cout<<"è compressa (0): "<<MR.is_compress()<<std::endl;
    MR.compress();
    std::cout<<"è compressa (1): "<<MR.is_compress()<<std::endl;
    MR.printvett();
    MR.uncompress();
    std::cout<<"è compressa (0): "<<MR.is_compress()<<std::endl;
    MR.printvett();

    // compress(),uncompress(),is_compress() per C 
    std::cout<<"è compressa (0): "<<MC.is_compress()<<std::endl;
    MC.compress();
    std::cout<<"è compressa (1): "<<MC.is_compress()<<std::endl;
    MC.printvett();
    MC.uncompress();
    std::cout<<"è compressa (0): "<<MC.is_compress()<<std::endl;
    MC.printvett();


    // call operator righe
    /*
    // non const------>ok 
    Matrix<int,StorageOrdering::row> NR; //+ defaul const
    NR(0,0)=1;
    NR(0,1)=2;
    NR(1,0)=3;
    NR(1,1)=4;
    NR.compress();
    NR.printvett();*/

   return 0;
} 

