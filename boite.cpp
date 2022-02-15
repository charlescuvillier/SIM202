#include 'boite.hpp'
#include <vector>
#include <iostream>
using namespace std;

//constructeurs
Boite::Boite(int niv, vector<double> centr, double taill){
    this->niveau = niv;
    this->centre = centr;
    this->masse = 0;
    this->centre_masse= NULL;
    this->taille = taill;
    this->*particule = NULL;
    this->*boite_fille=NULL;
    this->*boite_soeur=NULL;
    this->PointeurParticuleDansBoite = NULL;
}

Boite::Boite(int niv, vector<double> centr, double mass){
    this->niveau = niv;
    this->centre = centr;
    this->masse = mass;
    this->centre_masse= NULL;
    this->taille = 0;
    this->*particule = NULL;
    this->*boite_fille=NULL;
    this->*boite_soeur=NULL;
    this->PointeurParticuleDansBoite = NULL;
}

Boite::Boite(int dim, double taille){
	this->niveau = 0;
	this->centre = Vector(3,0) ;
	this->taille = taille;
	this->masse = 0;
	this->centre_masse= NULL;
    this->*particule = NULL;
    this->*boite_fille=NULL;
    this->*boite_soeur=NULL;
    this->PointeurParticuleDansBoite = NULL;
}
//destructeur
Boite::~Boite(){
    delete boite_fille;
    delete boite_soeur;
    delete particule;
    delete sousBoites;
}

//constructeur de boite fille pour la boite courante
void Boite::constructionBoiteFille()
{   int nv_niveau = niveau +1;
    double nv_taille = taille/2;
    }

//savoir si la boite contient une particule P
bool Boite::contient(const Particule& P) const
{   vector<double> coin_1 = centre-taille;
    vector<double> coin_2 = centre+taille;

    return coin_1(1) <P.position && P.position < coin_2(1) && coin_1(2) <P.position && P.position < coin_2(2) && coin_1(3) <P.position && P.position < coin_2(3);
}

//insertion de particule
void Boite::insert(Particule* part){
    if(!contient(part))
        {//la particule n'est pas dans la boite
        return;
        }
    //on ajoute la particule
    this->PointeurParticuleDansBoite.push_back(part);
}

//subdivision d'une boite en 4 boites filles
void Boite::subdivision(){
    //on cree d'abord la boite en haut a gauche devant
    vector<double> nv_centre = vector(3,0.);
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites= vector(1,Boite(niveau+1, nv_centre,taille/2));
    //en haut a gauche derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites.push_back(Boite(niveau+1, nv_centre,taille/2));
    //en haut a droite derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites.push_back(Boite(niveau+1, nv_centre,taille/2));
    //en haut a droite devant
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites.push_back(Boite(niveau+1, nv_centre,taille/2));
    //en bas a gauche devant
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites= vector(1,Boite(niveau+1, nv_centre,taille/2));
    //en bas a gauche derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites.push_back(Boite(niveau+1, nv_centre,taille/2));
    //en bas a droite derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites.push_back(Boite(niveau+1, nv_centre,taille/2));
    //en bas a droite devant
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites.push_back(Boite(niveau+1, nv_centre,taille/2));
}

void Boite::generation(vector<*Particule> ListeParticule){
    //fonction reccursive permettant la generation des boites
    //de sorte de creer toutes les boites terminales
    if(ListeParticule.size()==1){
        *Particule = ListeParticule[0] &;
        this->masse= ListeParticule[0].masse;
        this->centre_masse = ListeParticule[0].position;
        this->
    }
}
