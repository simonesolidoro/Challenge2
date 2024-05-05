# Challenge2

Questa repo contiene:

-l'implementazione della classe template Matrix, rappresentante una matrice sparsa, nel namespace Algebra.

-Test prodotto matrice-vettore con Chrono utility (main.cpp).

-Matrice in matrix market form (matrice_intestata).

(-./doc, ./include, Makefile)


----------------------------------------------------------------------------------------------------------------------------------------
la classe Matrix è cosi organizzata 
membri privati:
    -Dati:  map rappresentante la matrice in forma COOmap.
            modificando l' operatore di comparazione della mappa (struct cmp in Matrix.hpp) si ottiene row-major ordine o column-major ordine, comparando l'array delle posizioni rispetiveìamente dal primo elemnto(standard) o dall'ultimo.
    -3 vettori per rappresentare la forma CSR CSC
    -nze= non zero element, nrow, ncol

membri pubblici:
    -funzioni richieste esplicitamente in file Challenge23-24-2.pdf in ./doc
    -funzioni aggiuntive utilizzate per debug.
----------------------------------------------------------------------------------------------------------------------------------------

Utilizzo Makefile:  make --> genera eseguibile ./main che legge matrice_intestata e la moltiplica per vettore V=[2 2 2... 2] e con
                             Chrono utility valuta performance di M*V con M in row-major/col-major ordine e compress/uncompress form.
                    make clean
                    make distclean







    


