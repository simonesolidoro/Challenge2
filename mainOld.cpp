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
    std::map<std::array<std::size_t,2>,int> D(M.estrai(1));
    for(auto it= D.begin(); it!=D.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }

    M.compress();
    M(0,5)=3; 

 // prova compress uncompress is compress
    std::cout<<M.is_compress()<<std::endl;
    M.compress();
    std::cout<<M.is_compress()<<std::endl;
    M.printvett();
    M.uncompress();
    std::cout<<M.is_compress()<<std::endl;
    std::cout<<M(1,2)<<" "<<M(2,7)<<" "<<M(4,8);
    M.printvett();

 /*   //prova estrai
    Matrix<int,StorageOrdering::row> M;
    M(0,0)=1;
    M(0,1)=2;
    M(1,1)=4;
    M(1,0)=3;
    std::map<std::array<std::size_t,2>,int> D(M.estrai(0));
    for(auto it= D.begin(); it!=D.end();it++){
        std::cout<<it->first[0]<<" "<<it->first[1]<<" value: "<<it->second<<std::endl;
    }*/


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


   /* //prova prodotto M*v
    Matrix<int,StorageOrdering::col> M;
    M(0,1)=3;
    M(0,2)=2;
    M(1,2)=1;
    M(2,1)=4;
    M(2,2)=2;
    //M.compress();
    std::vector<int> v={1, 2, 3};
    std::vector<int> sol;
    //sol=M*v;
    sol=operator*(M,v);
    for(auto x: sol){
        std::cout<<"soluzione"<<x<<std::endl;
        }*/
    return 0;}