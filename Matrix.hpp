#include<iostream>
#include<array>
#include<map>
#include<vector>

namespace algebra{
    enum StorageOrdering{ row,col};
    
    // nuovo comparison operator per map in StorageOrdering per colonne
    template<StorageOrdering S>
    struct cmp{
        bool operator() (std::array<std::size_t,2> const & A, std::array<std::size_t,2> const & B)const{
            if(S==StorageOrdering::col){           
                if(A[1]<B[1])
                    return true;
                else if(A[1]==B[1] & A[0]<B[0])
                    return true;
                return false;
            }
            else 
                return A<B;
        }
    };

    template <class T, StorageOrdering S>
    class Matrix {
        private:  
            std::map<std::array<std::size_t,2>,T,cmp<S>> Dati;  //cmp per col
            std::vector<std::size_t> ColIndx;   //RowIndx     //OSS: nomi "azzeccati" per row_order ma usati identici in col_order 
            std::vector<std::size_t> RowPoint;  //ColPoint
            std::vector<T> val;
            unsigned int nze; // numero non zero element
            unsigned int nr; //numero righe
            unsigned int nc; //numero colonne 
        public:
    
            // costruttore 
            Matrix(std::map<std::array<std::size_t,2>,T,cmp<S>>);

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

            /// Stream operator. utile per debug
            template <class U, StorageOrdering Z>
            friend std::ostream & operator<<(std::ostream &stream, Matrix<U,Z> &M);

            //print vettori CSR utile per debug
            void printvett();
       

    };


template <class T, StorageOrdering S>
std::vector<T> operator * (Matrix<T,S> M, std::vector<T> v){
    if (S== StorageOrdering::row){
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
    if (S==StorageOrdering::col){
        if(M.is_compress()){
            std::vector<T> prod(5);// messo 5 nrow finche non imolemento nrow e ncol in privat member
            for(unsigned int i=0; i<M.RowPoint.size()-1; i++){
                for(unsigned int j=M.RowPoint[i]; j<M.RowPoint[i+1]; j++)
                    prod[j]+=M.val[j] *v[i];
            }
            return prod;
        }
      //uncompress()
      unsigned int ncol= (M.Dati.rbegin())->first[1]; //num col in matrice
      // !!!!!  SERVE NROW
      std::vector<T> prod(5); // gia size=nrow perche poi elementi aggiunti con []= e non pushback        
      for (unsigned int t=0; t<=ncol; t++){
        auto C=M.estrai(t);
        for (auto it=C.begin(); it!=C.end();it++){
            prod[it->first[0]]+=it->second*v[t];
        }
      }
      return prod;
    }
    // manca per col sia compree sia uncompress
}



template <class T, StorageOrdering S>
std::ostream & operator<<(std::ostream &stream, Matrix<T,S> &M){
    // per uncompress form sia row sia col
    for (auto j = M.Dati.begin(); j != M.Dati.end(); ++j)
        {
        stream << j->first[0]<< ", "<< j->first[1] << ", "<< j->second<< "\n";
        }
    return stream;

    // manca compress per row e col
}


};