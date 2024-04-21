#include<iostream>
#include"Matrix.cpp"
#include<iterator>
#include "chrono.hpp" //g++ -I. -I/mnt/c/Users/Cosimo\ Solidoro/Desktop/PACS/Esempi/pacs-examples/Examples/src/Utilities main.cpp -o main
using namespace algebra;

int main(){
  // prova constructor
/*   // per righe---------> ok (compila) 
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::row>> mapR={{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}};
    Matrix<int,StorageOrdering::row> MR(mapR); 

   //per colonne---------> ok 
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::col>> mapC={{{0,0},1},{{0,1},3},{{1,0},2},{{1,1},4}};
    //std::map<std::array<std::size_t,2>,int> mapC={{{0,0},1},{{0,1},4},{{1,1},2},{{1,2},5},{{2,2},3},{{2,3},6}};
    Matrix<int,StorageOrdering::col> MC(mapC);
*/

 /* //estri--------->ok
    //righe
    std::map<std::array<std::size_t,2>,int> DR(MR.estrai(0));
    for(auto it= DR.begin(); it!=DR.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }
    //colonne
    std::map<std::array<std::size_t,2>,int> DC(MC.estrai(0));
    for(auto it= DC.begin(); it!=DC.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }
*/
    

/*    // compress(),uncompress(),is_compress() per R--->ok 
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
*/

 /*   // call operator righe
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
    

    //call operator colonne     
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
/*  // call op const
    // per righe---->ok
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::row>> mapR={{{0,0},1},{{0,1},2},{{1,1},4}};
    const Matrix<int,StorageOrdering::row> MR(mapR); 
    std::cout<<"m(0,0)= 1:"<<MR(0,0)<<"m(10,10)=0 :"<<MR(10,10)<<std::endl;
   //per colonne ----->ok 
    std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::col>> mapC{{{0,0},1},{{0,1},3},{{1,1},4}};
    //std::map<std::array<std::size_t,2>,int> mapC={{{0,0},1},{{0,1},4},{{1,1},2},{{1,2},5},{{2,2},3},{{2,3},6}};
    const Matrix<int,StorageOrdering::col> MC(mapC);
    std::cout<<"m(0,0)= 1:"<<MC(0,0)<<"m(10,10)=0 :"<<MC(10,10)<<std::endl;
*/
  //prova 
   /*  std::map<std::array<std::size_t,2>,int,cmp<StorageOrdering::col>> mapp={{{0,0},1},{{1,1},2}};
    Matrix<int,StorageOrdering::col> N(mapp);
    std::cout<<N<<std::endl;
     
   Matrix<int,StorageOrdering::col> M;
    M(0,1)=3;
    M(0,2)=2;
    M(1,2)=1;
    M(2,1)=4;
    M(2,2)=2;
    M.compress();
    std::vector<int> v={1, 2, 3};
    std::vector<int> sol;
    //sol=M*v;
    sol=operator*(M,v);
    for(auto x: sol){
        std::cout<<"soluzione"<<x<<std::endl;
        }

    std::cout<<M;
*/

/*// capire se M(i,j) chiamata elemento non presente ridà 0(quindi chiama const ()) o chiama non const () e quindi aggiunto elemento
Matrix<int,StorageOrdering::row> M;
M(1,1);
std::cout<<M;
*/
/*// prova costruttori: const matrix con passaggio Dati--->ok
//                                 "             sz ---> ok
const Matrix<int,StorageOrdering::row> MM({{{0,1},1}});
const Matrix<int,StorageOrdering::row> NN(3);
MM(3,3);
std::cout<<MM<<std::endl<<NN;
*/

/* //prova errori se indici non presenti in compress matrix in non const call op

  Matrix<int,StorageOrdering::row> MM({{{0,1},1}});
  MM.compress();
  std::cout<<MM(0,0)<<std::endl;
  MM.uncompress();
  std::cout<<MM;
*/
/*
//prova complex std::complex<T>
    Matrix<std::complex<int>, StorageOrdering::row> M({{{0,0},1},{{1,1},{4,2}}}); //{{{0,0},1},{{1,1},4}}
    M(0,0)={10,34};
    std::cout<<M;
    M.compress();
    M.printvett();
    M.uncompress();
     std::cout<<M;
     M.printvett();
     std::vector<std::complex<int>> v={{1,1},{2,2}};
     std::cout<<std::is_same_v(decltype(M*v),std::complex<int>);
*/


    

    //prova tempo
    Matrix<double,StorageOrdering::row> M;
    M.read("matriceprova.mtx"); 
    Matrix<double,StorageOrdering::col> N;
    N.read("matriceprova.mtx"); 

    std::vector<double> v(M.getNrow(),2); 

    std::vector<double> solr(M.getNrow());
    std::vector<double> solrc(M.getNrow());
    std::vector<double> solc(N.getNrow());
    std::vector<double> solcc(N.getNrow());
    
    Timings::Chrono tempoRU;
    Timings::Chrono tempoRC;
    Timings::Chrono tempoCU;
    Timings::Chrono tempoCC;

    tempoRU.start();
    solr=M*v;
    tempoRU.stop();

    M.compress();
    tempoRC.start();
    solrc=M*v;
    tempoRC.stop();

    tempoCU.start();
    solc=N*v;
    tempoCU.stop();

    N.compress();
    tempoCC.start();
    solcc=N*v;
    tempoCC.stop();

    std::cout<< "R uncompress: "<<tempoRU<<std::endl;
    std::cout<< "R compress: "<<tempoRC<<std::endl;
    std::cout<< "C uncompress: "<<tempoCU<<std::endl;
    std::cout<< "C compress: "<<tempoCC<<std::endl;
    // risultati confermano compress piu veloce sia in row sia in col(numeri risultati cambiano ad ogni run ma ordien di grandezza simile)
    //R uncompress: Elapsed Time= 1.116400e+03 microsec

    //R compress: Elapsed Time= 3.910000e+01 microsec

    //C uncompress: Elapsed Time= 8.788000e+02 microsec

    //C compress: Elapsed Time= 1.930000e+01 microsec

    return 0;
} 

