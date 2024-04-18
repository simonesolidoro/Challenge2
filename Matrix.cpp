#include"Matrix.hpp"

using namespace algebra;

//costruttore
template <class T, StorageOrdering S>
Matrix<T,S>::Matrix(std::map<std::array<std::size_t,2>,T> D){
    if(S==StorageOrdering::row)
        DatiR.insert(D.begin(),D.end());
    if(S==StorageOrdering::col)  
        DatiC.insert(D.begin(),D.end());                    
        /*for(auto it=D.begin(); it!=D.end(); it++)  // alternativa
            DatiC[{it->first}]=it->second;*/
};

//call operator non const(return reference per poter modificare)
template <class T, StorageOrdering S>
T& Matrix<T,S>::operator() (std::size_t i,std::size_t j){
    if (is_compress()){
        for(unsigned int jj=RowPoint[i]; jj<RowPoint[i+1]; jj++){
            if(ColIndx[jj]==j)
                return val[jj];    //ritorna ref a vettore di valori in posizione i j 
        } 
        this->uncompress();
        return this->operator()(i,j);  //se in forma compress chiamato () con posizione non gia diversa da 0, uncompress e ricorsive (costoso computazionalmente) 
    }       ///!!!! problema: cosi cambia formato   
    else 
        return DatiR[{i,j}];        // cosi se poszione(i,j) non presente viene aggiunta  
};

// call operator const (leave user look for i,j in range of matrix)
template <class T,StorageOrdering S>
T Matrix<T,S>::operator() (std::size_t i,std::size_t j)const{
    if(is_compress()){
        for(unsigned int jj=RowPoint[i]; jj<RowPoint[i+1]; jj++){
            if(ColIndx[jj]==j)
                return val[jj];     
        }
        return 0;
    }
    if(DatiR.find({i,j}) != DatiR.end())
        return DatiR.at({i,j});
    else
        return 0;

}

// metodo che estrae riga k
template <class T,StorageOrdering S>
std::map<std::array<std::size_t,2>,T> Matrix<T,S>::estrai(const std::size_t k){
    std::map<std::array<std::size_t,2>,T> riga; //map contenente riga K/o colonna
    if(S==StorageOrdering::row){
        for (auto it=DatiR.lower_bound({k,0}); it!=DatiR.lower_bound({k+1,0}); it++){
            riga[it->first]=it->second;
        }
        return riga;}
    if(S==StorageOrdering::col){ //per ora non funziona/non provato l if messo solo per salvare come funziona (upper, {0,k}) 
                for (auto it=DatiC.upper_bound({0,k}); it!=DatiC.upper_bound({0,k+1}); it++){
            riga[it->first]=it->second;
        }
        return riga;}

}

// comprime dati-->vectors
template <class T,StorageOrdering S>
void Matrix<T,S>::compress(){
    if(S==StorageOrdering::row){
        unsigned int nrow = (DatiR.rbegin())->first[0];//--Dati.end() rida it a ultimo elemento di map, (--Dati.end())->first[0] rida numero di righe di matrice
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
        DatiR.clear();//svuotata map di dati una volta passati da dinamic a CSR
    }
    if(StorageOrdering::col){
        unsigned int ncol = (DatiC.rbegin())->first[0];//--Dati.end() rida it a ultimo elemento di map, (--Dati.end())->first[0] rida numero di colonna di matrice
        unsigned int point = 0; //per inserire posizione di primo elemento non vuoto in riga 
        RowPoint.push_back(point); //primo elemento sempre 0;
        for (unsigned int i=0; i<=ncol; i++){   // <= perchè in Dati.first indice riga è gia indice che parte da 0
            auto R=estrai(i);
            for (auto it=R.begin(); it!=R.end(); it++){
                val.push_back(it->second);
                ColIndx.push_back(it->first[0]);
                point++;
                }
            RowPoint.push_back(point);
        }
        DatiC.clear();//svuotata map di dati una volta passati da dinamic a CSR
    }
}

template <class T,StorageOrdering S>
void Matrix<T,S>::uncompress(){
    if(S==StorageOrdering::row){
        for(unsigned int i=0; i<RowPoint.size()-1; i++){
            for(unsigned int j=RowPoint[i]; j<RowPoint[i+1]; j++){
                DatiR[{i,ColIndx[j]}]=val[j];
            
            }
        }
    }
    if(S==StorageOrdering::col){
        for(unsigned int i=0; i<RowPoint.size()-1; i++){
            for(unsigned int j=RowPoint[i]; j<RowPoint[i+1]; j++){
                DatiC[{ColIndx[j],i}]=val[j];
            
            }
        }
    }
    ColIndx.clear();
    val.clear();
    RowPoint.clear();
}

template <class T, StorageOrdering S>  // da migliorare basta val non vuoto per false in row e col...
bool Matrix<T,S>::is_compress()const{
    if(S==StorageOrdering::row){
        if(DatiR.empty() & !val.empty())
            return true;
        else 
            return false;
    }
    if(S==StorageOrdering::col){
        if(DatiC.empty() & !val.empty())
            return true;
        else 
            return false;
    }
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


