#include<iostream>
#include"Matrix.cpp"
#include<iterator>
#include "chrono.hpp"

using namespace algebra;

int main(){
    // test whit chrono utility
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

    std::cout<< "Row-major uncompress: "<<tempoRU<<std::endl;
    std::cout<< "Row-major compress: "<<tempoRC<<std::endl;
    std::cout<< "Colum-major uncompress: "<<tempoCU<<std::endl;
    std::cout<< "Column-major compress: "<<tempoCC<<std::endl;
    // risultati confermano compress piu veloce sia in row sia in col
    return 0;
}