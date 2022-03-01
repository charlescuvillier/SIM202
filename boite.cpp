#include "boite.hpp"
#include <vector>
#include <iostream>

using namespace std;

//constructeurs
Boite::Boite(int niv, vector<double> centr, double taill){
    this->niveau = niv;
    this->centre = centr;
    this->masse = 0;
    this->centre_masse;
    this->taille = taill;
    this->particule=nullptr;
    this->boite_fille=nullptr;
    this->boite_soeur= nullptr ;
    this->PointeurParticuleDansBoite;
}
/*
Boite::Boite(int niv, vector<double> centr, double mass){
    this->niveau = niv;
    this->centre = centr;
    this->masse = mass;
    this->centre_masse;
    this->taille = 0;
    this->particule = nullptr;
    this->boite_fille = nullptr;
    this->boite_soeur = nullptr;
    this->PointeurParticuleDansBoite;
}
*/
//destructeur
Boite::~Boite(){
    delete boite_fille;
    delete boite_soeur;
    delete &PointeurParticuleDansBoite;
    delete &sousBoites;
}


//constructeur de boite fille pour la boite courante
void Boite::constructionBoiteFille()
{   int nv_niveau = niveau +1;
    double nv_taille = taille/2;
    }

//savoir si la boite contient une particule P
bool Boite::contient(const Particule& P) const
{  for(int i =1; i<4;i++)
        {
        if (centre[i]-taille/2 > P.position[i] || P.position[i]<centre[i]+taille/2) return false;
        }
    return true;
}
//insertion de particule
void Boite::insertion(Particule* ppart){
    if(!contient(*ppart))
        {//la particule n'est pas dans la boite
        return;
        }
    //on ajoute la particule
    PointeurParticuleDansBoite.push_back(ppart);
}

//subdivision d'une boite en 4 boites filles
void Boite::subdivision(){
    //on cree d'abord la boite en haut a gauche devant
    vector<double> nv_centre = vector<double>(3,0.);
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites= vector<Boite>(1,Boite(niveau+1, nv_centre,taille/2));
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
    sousBoites= vector<Boite>(1,Boite(niveau+1, nv_centre,taille/2));
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

void Boite::generation(vector<Particule*> ListepParticules){
    //fonction reccursive permettant la generation des boites
    //de sorte de creer toutes les boites terminales
    //ListepParticules est une vecteur de pointeur de Particule
    if(ListepParticules.size()==1){
        Particule * particule = ListepParticules[0] ;
        this->masse= ListepParticules[0]->masse;
        this->centre_masse = ListepParticules[0]->position;
        delete &ListepParticules;
    }
    else{
        //il y a plusieurs particule, il faut subdiviser la boite
        subdivision();
        //il faut maintenant remplir les listes de particules des sous boites
        int i=0; //contient la position de la particule courante dans la liste
        for(Particule* ppart : ListepParticules){
            for(Boite B : sousBoites){
                if(B.contient(*ppart)) {
                    B.PointeurParticuleDansBoite.push_back(ppart);
                    ListepParticules.erase(ListepParticules.begin() +i);
                    //on complete les caracteristiques de la boite
                    B.masse += ppart->masse;
                    double m = ppart->masse;
                    B.centre_masse[0] += ppart->masse*(ppart->position[0]); 
                    B.centre_masse[1] += ppart->masse*(ppart->position[1]);
                    B.centre_masse[2] += ppart->masse*(ppart->position[2]);  
                    // il faudra ensuite diviser ces coordonnees par le nombre de particule de la boite
                }
                B.centre_masse[0] /= B.PointeurParticuleDansBoite.size();
                B.centre_masse[1] /= B.PointeurParticuleDansBoite.size();
                B.centre_masse[2] /= B.PointeurParticuleDansBoite.size();
            }//fin du parcours des sous boites
            i++;} //  
        //toutes les particules ont ete attribuees a une sousboite
        //on supprime maintenenant les sous boites vides et on scinde les boites contenant plusieurs particules
        i=0;
        for(Boite B : sousBoites){
            if (B.PointeurParticuleDansBoite.size() == 0 && B.particule == nullptr){
                sousBoites.erase(sousBoites.begin() +i);
                //B.~Boite;
            }
            B.generation(B.PointeurParticuleDansBoite);
            i++;
        }
        //on attribut les boites soeurs et la boite fille
        this->boite_fille = &sousBoites[0];
        for(int j =0; j<i-1; j++){
            sousBoites[j].boite_soeur = &sousBoites[j+1];
        }
        //on subdivise les sous boites si necessaire (appel reccursif)
        for(int j =0; j<i-1; j++){
            sousBoites[j].generation(sousBoites[j].PointeurParticuleDansBoite);
        }
    }
}

ostream& operator<<(ostream& os, const Boite &B){
    os<<"Niveau : " << B.niveau << " ; Rayon : " << B.taille << '\n';
    os<<"Centre : ("<< B.centre[0] << ", " << B.centre[1] << ", " << B.centre[2] << ") '\n";
    os<<"Centre de masse : ("<< B.centre_masse[0] << ", " << B.centre_masse[1] << ", " << B.centre_masse[2] << ") '\n";
    os<<"Boite fille \n";
    if( B.boite_fille != NULL) {os<< &B.boite_fille ;}
    else {os<<"Pas de boite fille \n";}
    os<<"Particule :";
    if( B.particule != NULL) {os<< &B.particule ;}
    else {os<<"Pas de particule \n";}
    return os;
}
