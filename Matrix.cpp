#include"Matrix.hpp"


using namespace algebra;

//costruttore
template <class T, StorageOrdering S>
Matrix<T,S>::Matrix(std::map<std::array<std::size_t,2>,T,cmp<S>> D):Dati(D),nze(D.size()){
    resizeGen();
}

template <class T, StorageOrdering S>
Matrix<T,S>::Matrix(std::map<std::array<std::size_t,2>,T> M){
    for (auto it=M.begin(); it!=M.end(); it++ ){
        Dati[it->first]=it->second;
    }
    resizeGen();
}

//costruttore sz matrix(size= nrighe ncol)
template<class T, StorageOrdering S>
Matrix<T,S>::Matrix(unsigned int row, unsigned int col):nrow(row),ncol(col){}

//call operator non cons.   
template <class T, StorageOrdering S>
T& Matrix<T,S>::operator() (const std::size_t i,const std::size_t j){
    if (is_compress()){
        if constexpr(S==StorageOrdering::row){
                for(unsigned int jj=RowPoint[i]; jj<RowPoint[i+1]; jj++){
                    if(ColIndx[jj]==j)
                        return val[jj];    //ritorna ref a vettore di valori in posizione i j 
                } 
                //ERRORE SE INDICI NON PRESENTI IN MATRIX.   
                std::cout<<"elemento ("<<i<<", "<<j<<") non presente in compressed matrix"<<std::endl;
                std::exit(1);  
        }
        if constexpr(S==StorageOrdering::col){
                for(unsigned int jj=RowPoint[j]; jj<RowPoint[j+1]; jj++){
                    if(ColIndx[jj]==i)
                        return val[jj];    //ritorna ref a vettore di valori in posizione i j 
                }
                //ERRORE SE INDICI NON PRESENTI IN MATRIX 
                std::cout<<"elemento ("<<i<<", "<<j<<") non presente in compressed matrix"<<std::endl;
                std::exit(1);  
        }
    }
    if(Dati.find({i,j})==Dati.end()){ // se elemento non presente aggiorna ncol nrow
        resizeNewEl(i,j);
        return Dati[{i,j}];        // cosi se poszione(i,j) non presente viene aggiunta
        }
    return Dati.at({i,j});         //PROBLEMA: se in main chiamo M(i,j) con i,j non presenti ma solo per lettura viene aggiunto {{i,j},0} a Dati
                                  //SOLUZIONE: fare call op() per lettura e subscri op [] per sovrascrivere o aggiungere 
    
} 

// call operator const (lasciato ad utente non richiedere indici fuori da matrice )
template <class T,StorageOrdering S>
T Matrix<T,S>::operator() (const std::size_t i,const std::size_t j)const{
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

// metodo che estrae riga/colonna k e restituisce copia.
template <class T,StorageOrdering S>
std::map<std::array<std::size_t,2>,T> Matrix<T,S>::estrai(const std::size_t k) const{
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

// resize generale di nze, nrow, ncol
template<class T, StorageOrdering S>
void Matrix<T,S>::resizeGen(){
    nze=Dati.size();
    auto ultimo=Dati.rbegin();
    if constexpr(S== StorageOrdering::row){
        nrow=(ultimo->first[0])+1; //+1 perche elemnti di matrice partono da 0, nrow e ncol invce sono numero esatto di colonne e righe 
        for (auto it=Dati.begin(); it!= Dati.end(); it++){
            if(it->first[1]>=ncol)
                ncol=(it->first[1])+1;
        }
    } 
    if constexpr(S== StorageOrdering::col){
        ncol=(ultimo->first[1])+1; //+1 perche elemnti di matrice partono da 0, nrow e ncol invce sono numero esatto di colonne e righe 
        for (auto it=Dati.begin(); it!= Dati.end(); it++){
            if(it->first[0]>=nrow)
                nrow=(it->first[0])+1;
        }
    }   
}


// resize per aggiunta nuovo elemento
template<class T, StorageOrdering S>
void Matrix<T,S>::resizeNewEl(std::size_t i, std::size_t j){
    if(i>=nrow)
        nrow=i+1;
    if(j>=ncol)
        ncol=j+1;
    nze++;
}

// comprime dati-->vectors
template <class T,StorageOrdering S>
void Matrix<T,S>::compress(){
    int b;
    if constexpr(S==StorageOrdering::row){
        b=0;
    }
    if constexpr(S==StorageOrdering::col){
        b=1;
    }
        unsigned int n = (Dati.rbegin())->first[b];//numero righe o colonne
        unsigned int point = 0; //per inserire posizione di primo elemento non vuoto in riga 
        RowPoint.push_back(point); //primo elemento sempre 0;
        for (unsigned int i=0; i<=n; i++){   // <= perchè in Dati.first indice riga/colonna è gia indice che parte da 0
            if constexpr(S==StorageOrdering::row){
                for (auto it=Dati.lower_bound({i,0}); it!=Dati.lower_bound({i+1,0}); it++){
                    val.push_back(it->second);
                    ColIndx.push_back(it->first[1]);
                    point++;
                    }
                RowPoint.push_back(point);
            }
            if constexpr(S==StorageOrdering::col){
                for (auto it=Dati.lower_bound({0,i}); it!=Dati.lower_bound({0,i+1}); it++){
                    val.push_back(it->second);
                    ColIndx.push_back(it->first[0]);
                    point++;
                    }
                RowPoint.push_back(point);
            }
        }
        Dati.clear();//svuotata map di dati una volta passati da dinamic a CSR
}

template <class T,StorageOrdering S>
void Matrix<T,S>::uncompress(){
        for(unsigned int i=0; i<RowPoint.size()-1; i++){
            for(unsigned int j=RowPoint[i]; j<RowPoint[i+1]; j++){
                if constexpr(S==StorageOrdering::row)
                    Dati[{i,ColIndx[j]}]=val[j];
                if constexpr(S==StorageOrdering::col)
                    Dati[{ColIndx[j],i}]=val[j];
            
            }
        }
    ColIndx.clear();
    val.clear();
    RowPoint.clear();
}

template <class T, StorageOrdering S>  // 
bool Matrix<T,S>::is_compress()const{
    if(Dati.empty() & !val.empty())
        return true;
    else 
        return false;
   
}

/*template<class T, StorageOrdering S>                      OSS: altra versione non serve modificare file togliendo %intro, nrow ncol nze
void Matrix<T,S>::read(const std::string& filename){             ma if dentro while, uso getline ecc quindi meno efficente. meglio usare questa
    std::ifstream file(filename);                                versione e modificare a mano file di matrice eliminando %commenti e nrow ncol nze
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    unsigned int i;
    unsigned int j;
    T val;
    while(file >> i>> j>> val){
        this->operator()(i,j)=val;
    }
}*/
template<class T, StorageOrdering S>
void Matrix<T,S>::read(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    unsigned int i;
    unsigned int j;
    T val;
    bool rigaInfo = false;
    std::string line;
        while (std::getline(file, line)) {
        if (line[0] == '%') {
            // Skip comments
            continue;
        }

        if (!rigaInfo) {
            std::istringstream iss(line);
            iss >> nrow >> ncol; // non copiato numero non zero element perche quando aggiunge op () aggiunge +1 a nze
            rigaInfo = true;
        } else {
            std::istringstream iss(line);
            iss >> i >> j >> val;
            this->operator()(i,j) = val;
        }
    }
}

    // getter
    template<class T,StorageOrdering S>
    unsigned int Matrix<T,S>::getNrow(){ return nrow;}

    template<class T,StorageOrdering S>
    unsigned int Matrix<T,S>::getNcol(){ return ncol;}

    template<class T,StorageOrdering S>
    unsigned int Matrix<T,S>::getNze(){ return nze;}



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



