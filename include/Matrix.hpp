#ifndef MATRIX_HPP
#define MATRIX_HPP
// clang-format off
#include<iostream>
#include<array>
#include<map>
#include<vector>
#include <complex>
#include <fstream>
#include <iomanip>

namespace algebra{
    enum StorageOrdering{ row,col};
    //@note Take the habit of using doxygena for commentsing classes and functions
    // nuovo comparison operator per map Dati
    template<StorageOrdering S>
    struct cmp{
        bool operator() (std::array<std::size_t,2> const & A, std::array<std::size_t,2> const & B)const{
            if(S==StorageOrdering::col){     
                //@note A little trick that is also quite efficient, using tie:
                // return std::tie(A[1],A[0])<std::tie(B[1],B[0]);      
                if(A[1]<B[1])
                    return true;
                else if((A[1]==B[1]) & (A[0]<B[0]))
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
            std::vector<std::size_t> ColIndx;   //RowIndx     //OSS: nomi "azzeccati" per row_order ma usati in col_order (ColIndex->RowIndex)
            std::vector<std::size_t> RowPoint;  //ColPoint                                                                (RowPoint->ColPoint)
            std::vector<T> val;
            unsigned int nze=0; // numero non zero element
            unsigned int nrow=0; //numero righe
            unsigned int ncol=0; //numero colonne 
        public:
    
            // costruttore con map con cmp come comparison operator
            //@note pass the map as const & to avoid useless copies.
            Matrix(std::map<std::array<std::size_t,2>,T,cmp<S>>);

            // costruttore con map normale
            // @note you could have made a template constructor ans used if constexpr
            // to separate the two implementations
            // template<StorageOrdering U>
            // Matrix(std::map<std::array<std::size_t,2>,T,cmp<U>> D);
            Matrix(std::map<std::array<std::size_t,2>,T>);

            // costruttore con size matrix(nrow,ncol)
            Matrix(unsigned int, unsigned int);

            //Default costruttore
            Matrix()=default;

            // non const call operator che aggiune elemento se non presente o modifica se presente
            T& operator() (const std::size_t ,const std::size_t );

            // const call operator 
            T operator() (const std::size_t ,const std::size_t ) const;
           
            // estrae riga k se presente, altrimenti ridà mappa vuota
            //@note Why no estrai_riga, to make things clearer?
            std::map<std::array<std::size_t,2>,T> estrai(const std::size_t ) const;

            // resize nze ncol nrow 
            void resizeGen();

            // metodo che aggiorna nrow ncol per inserimento nuovo elemento ({i,j}, val)
            void resizeNewEl(std::size_t, std::size_t);

            // compress metod popola vettori per rappresentazione CSR
            void compress();

            // uncompress metod popola Dati e svuota vettori (CSR->COOmap)
            void uncompress();

            // check se forma compressa : se mappa di dati vuota e vettori hanno almeno un valore->true
            //                            se inizializzata vuota-> false
            //                            se map dati popolata-> false 
            //oss: per scontato che non si verifichi mai caso dati e vettori popolati contemporanemnte(per costruzione metodi e constructor)
            bool is_compress()const;

            //scalar product matrice vettore
          
            template <class U, StorageOrdering Z>
            friend std::vector<U> operator * (const Matrix<U,Z> &,const std::vector<U> &);

            // overload version per gestire casi in cui valori di M e/o di v siano complex
            template <class U, StorageOrdering Z>
            friend std::vector<std::complex<U>> operator * (const Matrix<std::complex<U>,Z> &,const std::vector<U> &);

            template <class U, StorageOrdering Z>
            friend std::vector<std::complex<U>> operator * (const Matrix<U,Z> &,const std::vector<std::complex<U>> &);

            template <class U, StorageOrdering Z>
            friend std::vector<std::complex<U>> operator * (const Matrix<std::complex<U>,Z> &,const std::vector<std::complex<U>> &);


            /// Stream operator. utile per debug
            template <class U, StorageOrdering Z>
            friend std::ostream & operator<<(std::ostream &stream, Matrix<U,Z> &M);

            /// Stream operator per const matrix. utile per debug
            template <class U, StorageOrdering Z>
            friend std::ostream & operator<<(std::ostream &stream,const Matrix<U,Z> &M);

            /// read metod
            void read(const std::string& filename);

            //print vettori CSR utile per debug
            void printvett();

            //getter
            unsigned int getNrow();
            unsigned int getNcol();
            unsigned int getNze();

    };


template <class T, StorageOrdering S> 
std::vector<T> operator * (const Matrix<T,S> & M, const std::vector<T> & v){
    if constexpr(S== StorageOrdering::row){
        std::vector<T> prod; 
        prod.reserve(M.nrow); 
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
            for (auto it=M.Dati.lower_bound({i,0}); it!=M.Dati.lower_bound({i+1,0}); it++){
                sum+=it->second*v[it->first[1]];
            }
            prod.push_back(sum);
            sum=0;
            }
        return prod;
    }
    if constexpr (S==StorageOrdering::col){
        if(M.is_compress()){
            std::vector<T> prod(M.nrow);
            for(unsigned int i=0; i<M.RowPoint.size()-1; i++){
                for(unsigned int j=M.RowPoint[i]; j<M.RowPoint[i+1]; j++)
                    prod[M.ColIndx[j]]+=M.val[j] *v[i]; // i indice colonna, Colindx[j]= riga, j scorre Index e quindi val
            }
            return prod;
        }
      //uncompress()
      unsigned int ncol= (M.Dati.rbegin())->first[1]; //num col in matrice
      std::vector<T> prod(M.nrow); // gia size=nrow perche poi elementi aggiunti con []= e non pushback        
      for (unsigned int t=0; t<=ncol; t++){
        for (auto it=M.Dati.lower_bound({0,t}); it!=M.Dati.lower_bound({0,t+1}); it++){
            prod[it->first[0]]+=it->second*v[t];
        }
      }
      return prod;
    }
}

// overload di operator* per complex
template <class T, StorageOrdering S>
std::vector<std::complex<T>> operator * (const Matrix<std::complex<T>,S> & M,const std::vector<T> & v){
    if constexpr(S== StorageOrdering::row){
        std::vector<std::complex<T>> prod; //size=numero righe di matrix, poi devi riservare spazio fin da subito
        prod.reserve(M.nrow); 
        std::complex<T> sum=0;
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
            for (auto it=M.Dati.lower_bound({i,0}); it!=M.Dati.lower_bound({i+1,0}); it++){
                sum+=it->second*v[it->first[1]];
            }
            prod.push_back(sum);
            sum=0;
            }
        return prod;
    }
    if constexpr (S==StorageOrdering::col){
        if(M.is_compress()){
            std::vector<std::complex<T>> prod(M.nrow);
            for(unsigned int i=0; i<M.RowPoint.size()-1; i++){
                for(unsigned int j=M.RowPoint[i]; j<M.RowPoint[i+1]; j++)
                    prod[M.ColIndx[j]]+=M.val[j] *v[i]; // i indice colonna, Colindx[j]= riga, j scorre Index e quindi val
            }
            return prod;
        }
      //uncompress()
      unsigned int ncol= (M.Dati.rbegin())->first[1]; //num col in matrice
      std::vector<std::complex<T>> prod(M.nrow); // gia size=nrow perche poi elementi aggiunti con []= e non pushback        
      for (unsigned int t=0; t<=ncol; t++){
        for (auto it=M.Dati.lower_bound({0,t}); it!=M.Dati.lower_bound({0,t+1}); it++){
            prod[it->first[0]]+=it->second*v[t];
        }
      }
      return prod;
    }
}

//@note Some code duplication here, you could have made the code more generic by declaring a template of the form
// template<class T, class U, StorageOrdering S>
// std::vector<U> operator * (const Matrix<T,S> & M, const std::vector<U> & v){
// and then sort out the cases with if constexpr and type traits. You avoid reapeating the same code twice.

template <class T, StorageOrdering S>
std::vector<std::complex<T>> operator * (const Matrix<T,S> & M,const std::vector<std::complex<T>> & v){
    if constexpr(S== StorageOrdering::row){
        std::vector<std::complex<T>> prod; //size=numero righe di matrix, poi devi riservare spazio fin da subito
        prod.reserve(M.nrow); 
        std::complex<T> sum=0;
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
            for (auto it=M.Dati.lower_bound({i,0}); it!=M.Dati.lower_bound({i+1,0}); it++){
                sum+=it->second*v[it->first[1]];
            }
            prod.push_back(sum);
            sum=0;
            }
        return prod;
    }
    if constexpr (S==StorageOrdering::col){
        if(M.is_compress()){
            std::vector<std::complex<T>> prod(M.nrow);
            for(unsigned int i=0; i<M.RowPoint.size()-1; i++){
                for(unsigned int j=M.RowPoint[i]; j<M.RowPoint[i+1]; j++)
                    prod[M.ColIndx[j]]+=M.val[j] *v[i]; // i indice colonna, Colindx[j]= riga, j scorre Index e quindi val
            }
            return prod;
        }
      //uncompress()
      unsigned int ncol= (M.Dati.rbegin())->first[1]; //num col in matrice
      std::vector<std::complex<T>> prod(M.nrow); // gia size=nrow perche poi elementi aggiunti con []= e non pushback        
      for (unsigned int t=0; t<=ncol; t++){
        for (auto it=M.Dati.lower_bound({0,t}); it!=M.Dati.lower_bound({0,t+1}); it++){
            prod[it->first[0]]+=it->second*v[t];
        }
      }
      return prod;
    }
}

template <class T, StorageOrdering S>
std::vector<std::complex<T>> operator * (const Matrix<std::complex<T>,S> & M,const std::vector<std::complex<T>> & v){
    if constexpr(S== StorageOrdering::row){
        std::vector<std::complex<T>> prod; //size=numero righe di matrix, poi devi riservare spazio fin da subito
        prod.reserve(M.nrow); 
        std::complex<T> sum=0;
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
            for (auto it=M.Dati.lower_bound({i,0}); it!=M.Dati.lower_bound({i+1,0}); it++){
                sum+=it->second*v[it->first[1]];
            }
            prod.push_back(sum);
            sum=0;
            }
        return prod;
    }
    if constexpr (S==StorageOrdering::col){
        if(M.is_compress()){
            std::vector<std::complex<T>> prod(M.nrow);
            for(unsigned int i=0; i<M.RowPoint.size()-1; i++){
                for(unsigned int j=M.RowPoint[i]; j<M.RowPoint[i+1]; j++)
                    prod[M.ColIndx[j]]+=M.val[j] *v[i]; // i indice colonna, Colindx[j]= riga, j scorre Index e quindi val
            }
            return prod;
        }
      //uncompress()
      unsigned int ncol= (M.Dati.rbegin())->first[1]; //num col in matrice
      std::vector<std::complex<T>> prod(M.nrow); // gia size=nrow perche poi elementi aggiunti con []= e non pushback        
      for (unsigned int t=0; t<=ncol; t++){
        for (auto it=M.Dati.lower_bound({0,t}); it!=M.Dati.lower_bound({0,t+1}); it++){
            prod[it->first[0]]+=it->second*v[t];
        }
      }
      return prod;
    }
}



template <class T, StorageOrdering S>
std::ostream & operator<<(std::ostream &stream, Matrix<T,S> &M){
    stream << std::setprecision(std::numeric_limits<T>::digits10 + 1);
    stream.setf(std::ios_base::scientific, std::ios_base::floatfield);
    for (auto j = M.Dati.begin(); j != M.Dati.end(); ++j)
        {
        stream << j->first[0]<< ", "<< j->first[1] << ", "<< j->second<< "\n";
        }
    stream<< "nze: "<<M.nze<<" , "<< "nrow: "<<M.nrow<<" , "<<"ncol: "<<M.ncol<<"\n ";
    return stream;
}


//stream operator per matrix in uncompress form utile per debug
template <class T, StorageOrdering S>
std::ostream & operator<<(std::ostream &stream, const Matrix<T,S> &M){
    // per uncompress form sia row sia col
    stream << std::setprecision(std::numeric_limits<T>::digits10 + 1);
    stream.setf(std::ios_base::scientific);
    for (auto j = M.Dati.begin(); j != M.Dati.end(); ++j)
        {
        stream << j->first[0]<< ", "<< j->first[1] << ", "<< j->second<< "\n";
        }
    stream<< "nze: "<<M.nze<<" , "<< "nrow: "<<M.nrow<<" , "<<"ncol: "<<M.ncol<<"\n ";
    return stream;
}

};

#endif
