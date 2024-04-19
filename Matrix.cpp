#include"Matrix.hpp"

using namespace algebra;

//costruttore
template <class T, StorageOrdering S>
Matrix<T,S>::Matrix(std::map<std::array<std::size_t,2>,T,cmp<S>> D):Dati(D){}

//call operator non const(return reference per poter modificare)
template <class T, StorageOrdering S>
T& Matrix<T,S>::operator() (std::size_t i,std::size_t j){
    if (is_compress()){
        if constexpr(S==StorageOrdering::row){
                for(unsigned int jj=RowPoint[i]; jj<RowPoint[i+1]; jj++){
                    if(ColIndx[jj]==j)
                        return val[jj];    //ritorna ref a vettore di valori in posizione i j 
                } 
                // Da fare: ERRORE SE INDICI NON PRESENTI IN MATRIX   
        }
        if constexpr(S==StorageOrdering::col){
                for(unsigned int jj=RowPoint[j]; jj<RowPoint[j+1]; jj++){
                    if(ColIndx[jj]==i)
                        return val[jj];    //ritorna ref a vettore di valori in posizione i j 
                }
                // DA Fare: ERRORE SE INDICI NON PRESENTI IN MATRIX 
        }
    }
    return Dati[{i,j}];        // cosi se poszione(i,j) non presente viene aggiunta
} 

// call operator const (leave user look for i,j in range of matrix)
template <class T,StorageOrdering S>
T Matrix<T,S>::operator() (std::size_t i,std::size_t j)const{
    
    if(is_compress()){
        if constexpr(S==StorageOrdering::row){
            for(unsigned int jj=RowPoint[i]; jj<RowPoint[i+1]; jj++){
                if(ColIndx[jj]==j)
                    return val[jj];     
            }
            return 0;
        }
        if constexpr(S==StorageOrdering::col){
            for(unsigned int jj=RowPoint[j]; jj<RowPoint[j+1]; jj++){
                if(ColIndx[jj]==i)
                    return val[jj];     
            }
           return 0;
        }
    }
    if(Dati.find({i,j}) != Dati.end())
        return Dati.at({i,j});
    else
        return 0;
}

// metodo che estrae riga k
template <class T,StorageOrdering S>
std::map<std::array<std::size_t,2>,T> Matrix<T,S>::estrai(const std::size_t k){
    std::map<std::array<std::size_t,2>,T> riga; //map contenente riga K/o colonna
    if constexpr(S==StorageOrdering::row){
        for (auto it=Dati.lower_bound({k,0}); it!=Dati.lower_bound({k+1,0}); it++){
            riga[it->first]=it->second;
        }
        return riga;}
    if constexpr(S==StorageOrdering::col){  
        for (auto it=Dati.lower_bound({0,k}); it!=Dati.lower_bound({0,k+1}); it++){
            riga[it->first]=it->second;
        }
        return riga;}

}

// comprime dati-->vectors
template <class T,StorageOrdering S>
void Matrix<T,S>::compress(){
    int a;
    int b;
    if constexpr(S==StorageOrdering::row){
        a=1;
        b=0;
    }
    if constexpr(S==StorageOrdering::col){
        a=0;
        b=0;
    }
        unsigned int n = (Dati.rbegin())->first[b];//numero righe o colonne
        unsigned int point = 0; //per inserire posizione di primo elemento non vuoto in riga 
        RowPoint.push_back(point); //primo elemento sempre 0;
        for (unsigned int i=0; i<=n; i++){   // <= perchè in Dati.first indice riga/colonna è gia indice che parte da 0
            auto R=estrai(i);
            for (auto it=R.begin(); it!=R.end(); it++){
                val.push_back(it->second);
                ColIndx.push_back(it->first[a]);
                point++;
                }
            RowPoint.push_back(point);
        }
        Dati.clear();//svuotata map di dati una volta passati da dinamic a CSR
}

template <class T,StorageOrdering S>
void Matrix<T,S>::uncompress(){
    if(S==StorageOrdering::row){
        for(unsigned int i=0; i<RowPoint.size()-1; i++){
            for(unsigned int j=RowPoint[i]; j<RowPoint[i+1]; j++){
                Dati[{i,ColIndx[j]}]=val[j];
            
            }
        }
    }
    if(S==StorageOrdering::col){
        for(unsigned int i=0; i<RowPoint.size()-1; i++){
            for(unsigned int j=RowPoint[i]; j<RowPoint[i+1]; j++){
                Dati[{ColIndx[j],i}]=val[j];
            
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
        if(Dati.empty() & !val.empty())
            return true;
        else 
            return false;
    }
    if(S==StorageOrdering::col){
        if(Dati.empty() & !val.empty())
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


