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

// metodo che estrae riga k
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

template <class T,StorageOrdering S>
void Matrix<T,S>::compress(){
    unsigned int nrow = (Dati.end()--)->first[0];//Dati.end() rida it a ultimo elemento di map, (Dati.end()--)->first[0] rida numero di righe di matrice
    unsigned int point = 0; //per inserire posizione di primo elemento non vuoto in riga 
    for (unsigned int i=0; i<nrow; i++){  
        auto R=estrai(i);
        if (!R.empty()){
            RowPoint.push_back(point); // prima di for perche solo per primo elemento non vuoto
            for (auto it=R.begin(); it!=R.end(); it++){
                val.push_back(it->second);
                ColIndx.push_back(it->first[1]);
                point++;

            }
        }
    }
    RowPoint.push_back(val.size()); // RowPoint ultimo elemento è numero elemeni totali
    Dati.clear();//svuotata map di dati una volta passati da dinamic a CSR
}

template <class T, StorageOrdering S>
void Matrix<T,S>::printvett(){
    for (unsigned int x: ColIndx)
        std::cout<<x<<" ";
    std::cout<<std::endl;
     for (T x: val)
        std::cout<<x<<" ";
    std::cout<<std::endl;
     for (unsigned int x: RowPoint)
        std::cout<<x<<" ";
    std::cout<<std::endl;
}

