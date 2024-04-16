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

           //print vettori CSR
           void printvett();
       

    };
};