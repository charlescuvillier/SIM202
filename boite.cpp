#include 'boite.hpp'
#include <vector>
#include <iostream>
using namespace std;

//constructeurs
Boite::Boite(int niv, vector<double> centr, double mass){
    this->niveau = niv;
    this->centre = centr;
    this->masse = mass;
    
}

Boite::Boite(int dim, double rayon){
	this->niveau = 0;
	this->centre = Vecteur(2,0) ;
	this->rayon = rayon;
	this->masse = 0;
	particule = NULL;
}


//constructeur de boite fille pour la boite courante
void Boite::constructionBoiteFille()
{   int nv_niveau = niveau +1;
    double nv_rayon = rayon/2;
    }

//savoir si la boite contient une particule P
bool Boite::contient(const Particule& P) const
{   vecteur<double> coin_1 = centre-rayon;
    vecteur<double> coin_2 = centre+rayon;
    return coin_1(1) <P.position && P.position < coin_2(1) && coin_1(2) <P.position && P.position < coin_2(2) && coin_1(3) <P.position && P.position < coin_2(3);
}
