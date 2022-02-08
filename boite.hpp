#ifndef boite_hpp
#define boite_hpp
#include <iostream>
#include <cmath>
#include <vector>
#include <particule.hpp>
using namespace std ;

// classe boite

class Boite
{   public:
        int niveau;
        double taille;
        vector<double> centre;
        vector<double> centre_masse;
        double masse;
        Particule * particule; //
        Boite * boite_fille = NULL;  //pointeur vers la premiere boite fille
        Boite * boite_soeur = NULL;  //pointeur vers la premiere boite soeur

        //constructeur de la boite
        Boite(int niveau, vector<double>, double masse);
        }
        //constructeur des boites filles
        void constructionBoiteFille();

#endif //boite.hpp
