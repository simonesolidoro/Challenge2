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
        std::map<std::array<std::size_t,2>,T> riga; //map contenente riga K
        for (auto it=Dati.lower_bound({k,0}); it!=Dati.lower_bound({k+1,0}); it++){
            riga[it->first]=it->second;
        }
        return riga; 
}

template <class T,StorageOrdering S>
void Matrix<T,S>::compress(){
    unsigned int nrow = (Dati.rbegin())->first[0];//--Dati.end() rida it a ultimo elemento di map, (--Dati.end())->first[0] rida numero di righe di matrice
    unsigned int point = 0; //per inserire posizione di primo elemento non vuoto in riga 
    RowPoint.push_back(point); //primo elemento sempre 0;
    for (unsigned int i=0; i<=nrow; i++){   // <= perchè in Dati.first indice riga è gia indice che parte da 0
        auto R=estrai(i);
        for (auto it=R.begin(); it!=R.end(); it++){
            val.push_back(it->second);
            ColIndx.push_back(it->first[1]);
            point++;
            }
        RowPoint.push_back(point);
    }
    Dati.clear();//svuotata map di dati una volta passati da dinamic a CSR
}

template <class T,StorageOrdering S>
void Matrix<T,S>::uncompress(){
    for(unsigned int i=0; i<RowPoint.size()-1; i++){
        for(unsigned int j=RowPoint[i]; j<RowPoint[i+1]; j++){
            Dati[{i,ColIndx[j]}]=val[j];
        
        }
    }
    ColIndx.clear();
    val.clear();
    RowPoint.clear();
}


template <class T, StorageOrdering S>
void Matrix<T,S>::printvett(){
    std::cout<<"colindx: ";
    for (unsigned int x: ColIndx)
        std::cout<<x<<" ";
    std::cout<<std::endl;
    std::cout<<"val: ";
     for (T x: val)
        std::cout<<x<<" ";
    std::cout<<std::endl;
    std::cout<<"Roepoint: ";
     for (unsigned int x: RowPoint)
        std::cout<<x<<" ";
    std::cout<<std::endl;
}

