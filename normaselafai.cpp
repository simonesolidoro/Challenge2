in matrix.cpp
template<class T, StorageOrdering S>
template<tipoNorma N>
T Matrix<T,S>::norma(){
    if constexpr(N==tipoNorma::uno){
        if constexpr(S==StorageOrdering::col){
            T max=0;
            for (unsigned int i=0; i<=(*this).ncol; i++){
                T som=0;
                for (auto x: (*this).estrai(i))
                    som+=std::abs(x.second);     // std::abs(std::complex<T>) fa norma non va bene 
                if(som>max)
                    max=som;
            }
        return max;
        }
        if constexpr(S==StorageOrdering::row){
            std::vector<T> sommacolonne(ncol);
            for(auto it=Dati.begin(); it!=Dati.end(); i++){
                sommacolonne[it->first[1]]+=std::abs(it->second);
            }

        }
    }
}


in matrix.hpp 
            // norma 
            template<tipoNorma N>
            T norma();
