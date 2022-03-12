#ifndef boite_hpp
#define boite_hpp
#include <iostream>
#include <cmath>
#include <vector>
#include "particule.hpp"
using namespace std ;

// classe boite

class Boite
{   public:
        int niveau;
        double taille;
        vector<double> centre;
        vector<double> centre_masse;
        double masse;
        Particule * particule; //vaut NULL si il n'y a pas exactement 1 particule dans la boite
        Boite * boite_fille;  //pointeur vers la premiere boite fille
        Boite * boite_soeur;  //pointeur vers la premiere boite soeur
        vector<Particule*> PointeurParticuleDansBoite; //sert uniquement lors de la construction des boites
        vector<Boite*> sousBoites; //sert uniquement lors de la construction des boites
        //constructeur de la boite
        Boite(int niveau, vector<double>, double masse);
        //destructeur
        ~Boite();
        //constructeur des boites filles
        void constructionBoiteFille();
        //fonction pour savoir si il y a une paticule P
        bool contient(const Particule& P) const;
        //bilan des forces (Adrien)

        //constructeurs
        Boite(double taille = 1.0);
        Boite(vector<double> centre, int niveau, double taille);
        //generation des boites
        void insertion(Particule * part);
        void subdivision();
        void generation(vector<Particule*> ListeParticule);
};

ostream& operator<<(ostream& os, const Boite B);
ostream& operator<<(ostream& os, const Boite* B);
#endif //boite.hpp