#include<iostream>
#include<array>
#include<map>

namespace algebra{
    enum StorageOrdering{ row,col};

    template <class T, StorageOrdering S>
    class Matrix {
        private:
            std::map<std::array<std::size_t,2>,T> Dati;
        public:
            // costruttore 
            Matrix(std::map<std::array<std::size_t,2>,T>);

            //Default costruttore
            Matrix()=default;

            // non const call operator che aggiune elemento se non presente o modifica se presente
            T& operator() (std::size_t,std::size_t);
           
           // estrae riga k se presente, altrimenti ridà mappa vuota
           std::map<std::array<std::size_t,2>,T> estrai(const std::size_t );

    };
};