#include<iostream>
#include<array>
#include<map>
#include<vector>

namespace algebra{
    enum StorageOrdering{ row,col};

    template <class T, StorageOrdering S>
    class Matrix {
        private:
            std::map<std::array<std::size_t,2>,T> Dati;
            std::vector<std::size_t> ColIndx;
            std::vector<std::size_t> RowPoint;
            std::vector<T> val;
        public:
            // costruttore 
            Matrix(std::map<std::array<std::size_t,2>,T>);

            //Default costruttore
            Matrix()=default;

            // non const call operator che aggiune elemento se non presente o modifica se presente
            T& operator() (std::size_t,std::size_t);

            // const call operator 
            T operator() (std::size_t,std::size_t) const;
           
           // estrae riga k se presente, altrimenti ridà mappa vuota
           std::map<std::array<std::size_t,2>,T> estrai(const std::size_t );

           // compress metod popola vettori per rappresentazione CSR
           void compress();

           // uncompress metod popola Dati e svuota vettori (CSR->COOmap)
           void uncompress();

           // check se forma compressa o uncompress: se mappa di dati vuota e vettori hanno almeno un valore->true
           //                                        se inizializzata vuota-> false
           //                                        se map dati popolata-> false 
           //oss: per scontato che non si verifichi mai caso dati e vettori popolati contemporanemnte(per costruzione metodi e constructor)
           bool is_compress()const;

           //scalar product matrice vettore
           template <class U, StorageOrdering Z>
           friend std::vector<U> operator * (Matrix<U,Z>, std::vector<U>);

           //print vettori CSR
           void printvett();
       

    };


template <class T, StorageOrdering S>
std::vector<T> operator * (Matrix<T,S> M, std::vector<T> v){
    std::vector<T> prod; //size=numero righe di matrix, poi devi riservare spazio fin da subito
    T sum=0;
    if(M.is_compress()){
        for(unsigned int i=0; i<M.RowPoint.size()-1; i++){
            for(unsigned int j=M.RowPoint[i]; j<M.RowPoint[i+1]; j++){
                sum+=v[M.ColIndx[j]]*M.val[j];
            }
            prod.push_back(sum);
            sum=0;
        }
        return prod;
        }
    unsigned int nrow = (M.Dati.rbegin())->first[0];
    for (unsigned int i=0; i<=nrow; i++){   
        auto R=M.estrai(i);
        for(auto & x: R){
            sum+=x.second*v[x.first[1]];
        }
        prod.push_back(sum);
        sum=0;
        }
    return prod;
}
};