#include<iostream>
#include"Matrix.cpp"
#include<iterator>
using namespace algebra;

int main(){
/*   // prova constructor
   // per righe---------> ok (compila) 
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::row>> mapR={{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}};
    Matrix<int,StorageOrdering::row> MR(mapR); 

   //per colonne---------> ok 
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::col>> mapC={{{0,0},1},{{0,1},3},{{1,0},2},{{1,1},4}};
    //std::map<std::array<std::size_t,2>,int> mapC={{{0,0},1},{{0,1},4},{{1,1},2},{{1,2},5},{{2,2},3},{{2,3},6}};
    Matrix<int,StorageOrdering::col> MC(mapC);
*/
/*
  //estri--------->ok
    //righe
    std::map<std::array<std::size_t,2>,int> DR(MR.estrai(1));
    for(auto it= DR.begin(); it!=DR.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }
    //colonne
    std::map<std::array<std::size_t,2>,int> DC(MC.estrai(0));
    for(auto it= DC.begin(); it!=DC.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }
*/
/*    

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
    // non const------>ok 
    Matrix<int,StorageOrdering::row> NR; //+ defaul const
    NR(0,0)=1;
    NR(0,1)=2;
    NR(1,0)=3;
    NR(1,1)=4;
    NR.compress();
    NR.printvett();
    NR(1,1)=5;
    NR.printvett();
    
*/
/*    //call operator colonne     
    // non const------>ok
    Matrix<int,StorageOrdering::col> NC; //+ defaul const
    NC(0,0)=1;
    NC(0,1)=3;
    NC(1,0)=2;
    NC(1,1)=4;
    NC.compress();
    NC.printvett();
    NC(1,1)=5;
    NC.printvett();
*/
  // call op const
    // per righe---->ok
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::row>> mapR={{{0,0},1},{{0,1},2},{{1,1},4}};
    const Matrix<int,StorageOrdering::row> MR(mapR); 
    std::cout<<"m(0,0)= 1:"<<MR(0,0)<<"m(10,10)=0 :"<<MR(10,10)<<std::endl;
   //per colonne ----->ok 
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::col>> mapC{{{0,0},1},{{0,1},3},{{1,1},4}};
    //std::map<std::array<std::size_t,2>,int> mapC={{{0,0},1},{{0,1},4},{{1,1},2},{{1,2},5},{{2,2},3},{{2,3},6}};
    const Matrix<int,StorageOrdering::col> MC(mapC);
    std::cout<<"m(0,0)= 1:"<<MC(0,0)<<"m(10,10)=0 :"<<MC(10,10)<<std::endl;

    std::cout<<MR(1,0);
    std::cout<<MC(1,0);

    

   
   return 0;
} 

