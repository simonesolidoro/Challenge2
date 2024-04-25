#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<iostream>
#include<array>
#include<map>
#include<vector>
#include <complex>
#include <fstream>
#include <iomanip>

namespace algebra{
    enum StorageOrdering{ row,col};
    
    // nuovo comparison operator per map Dati
    template<StorageOrdering S>
    struct cmp{
        bool operator() (std::array<std::size_t,2> const & A, std::array<std::size_t,2> const & B)const{
            if(S==StorageOrdering::col){           
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
            Matrix(std::map<std::array<std::size_t,2>,T,cmp<S>>);

            // costruttore con map normale
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
            std::map<std::array<std::size_t,2>,T> estrai(const std::size_t ) const;

            // resize generale 
            void resizeGen();

            // metodo che aggiorna nrow ncol per inserimento nuovo elemento ({i,j}, val)
            void resizeNewEl(std::size_t, std::size_t);

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
            friend std::vector<U> operator * (const Matrix<U,Z> &,const std::vector<U> &);

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


template <class T, StorageOrdering S> // DA OTTIMIZZARE col e row 
std::vector<T> operator * (const Matrix<T,S> & M, const std::vector<T> & v){
    if constexpr(S== StorageOrdering::row){
        std::vector<T> prod; //size=numero righe di matrix, poi devi riservare spazio fin da subito
        prod.reserve(M.nrow); 
        T sum=0;
        if(M.is_compress()){ // da ottimizzare, variabile sum superflua credo possibile prod.push_back() e poi prod[]=+..
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
            std::vector<T> prod(M.nrow);// messo 5 nrow finche non imolemento nrow e ncol in privat member
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



template <class T, StorageOrdering S>
std::ostream & operator<<(std::ostream &stream, Matrix<T,S> &M){
    // per uncompress form sia row sia col
    stream << std::setprecision(std::numeric_limits<T>::digits10 + 1);
    stream.setf(std::ios_base::scientific, std::ios_base::floatfield);
    for (auto j = M.Dati.begin(); j != M.Dati.end(); ++j)
        {
        stream << j->first[0]<< ", "<< j->first[1] << ", "<< j->second<< "\n";
        }
    stream<< "nze: "<<M.nze<<" , "<< "nrow: "<<M.nrow<<" , "<<"ncol: "<<M.ncol<<"\n ";
    return stream;

    // manca compress per row e col
}

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
