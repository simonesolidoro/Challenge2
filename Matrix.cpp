#include"Matrix.hpp"

using namespace algebra;

//costruttore
template <class T, StorageOrdering S>
Matrix<T,S>::Matrix(std::map<std::array<std::size_t,2>,T> D){
    Dati.insert(D.begin(),D.end());
};

//call operator non const(return reference per poter modificare)
template <class T, StorageOrdering S>
T& Matrix<T,S>::operator() (std::size_t i,std::size_t j){
    return Dati[{i,j}];         // cosi se poszione(i,j) non presente viene aggiunta
    //return Dati.at({i,j});    // se posizione non presente-> out_of_range, non aggiunge 
};



template <class T,StorageOrdering S>
std::map<std::array<std::size_t,2>,T> Matrix<T,S>::estrai(const std::size_t k){

    
        std::array<std::size_t,2> indici={k};    // {k,0}
        std::array<std::size_t,2> ind_due={k+1}; // {k+1,0} in modo che ciclo for termini appena finiti elementi con key {k,*}
        std::map<std::array<std::size_t,2>,T> riga; //map contenente riga K
        for (auto it=Dati.lower_bound(indici); it!=Dati.lower_bound(ind_due); it++){
            riga[it->first]=it->second;
        }
        return riga; 
}


