#include "boite.hpp"
#include <vector>
#include <iostream>

using namespace std;

//constructeurs
Boite::Boite(int niv, vector<double> centr, double taill){
    this->niveau = niv;
    this->centre = centr;
    this->masse = 0;
    this->centre_masse = vector<double>(3,0.);
    this->taille = taill;
    this->particule=nullptr;
    this->boite_fille=nullptr;
    this->boite_soeur= nullptr ;
    this->PointeurParticuleDansBoite;
    this->sousBoites = vector<Boite*>(1,nullptr);
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
{  for(int i =0; i<3;i++)
        {
        if (P.position[i] < centre[i]-taille/2  || P.position[i] > centre[i]+taille/2 ){return false;}
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
    this->sousBoites[0] = new Boite(this->niveau+1, nv_centre,this->taille/2);
    //en haut a gauche derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites.push_back(new Boite(niveau+1, nv_centre,taille/2));
    //en haut a droite derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites.push_back(new Boite(niveau+1, nv_centre,taille/2));
    //en haut a droite devant
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]+taille/4;
    sousBoites.push_back(new Boite(niveau+1, nv_centre,taille/2));
    //en bas a gauche devant
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites.push_back(new Boite(niveau+1, nv_centre,taille/2));
    //en bas a gauche derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]-taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites.push_back(new Boite(niveau+1, nv_centre,taille/2));
    //en bas a droite derriere
    nv_centre[0] = centre[0]-taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites.push_back(new Boite(niveau+1, nv_centre,taille/2));
    //en bas a droite devant
    nv_centre[0] = centre[0]+taille/4;
    nv_centre[1] = centre[1]+taille/4;
    nv_centre[2] = centre[2]-taille/4;
    sousBoites.push_back(new Boite(niveau+1, nv_centre,taille/2));
}

void Boite::generation(vector<Particule*> ListepParticules){
    //fonction reccursive permettant la generation des boites
    //de sorte de creer toutes les boites terminales
    //ListepParticules est une vecteur de pointeur de Particule
    if(ListepParticules.size()==1){
        this->masse= ListepParticules[0]->masse;
        this->centre_masse = ListepParticules[0]->position;
        this->particule = ListepParticules[0];
        //delete &ListepParticules;
    }
    else{
        //il y a plusieurs particule, il faut subdiviser la boite
        subdivision();
        cout << "\ndebut de la subdivision : \n" ;
        //il faut maintenant remplir les listes de particules des sous boites
        for(int i=0; i<ListepParticules.size(); i++){
            cout <<"\non place maintenant la particule :\n" << *ListepParticules[i] << " \n";
            for(Boite* pB : sousBoites){
                if(pB->contient(*ListepParticules[i])) {
                    cout << "ajout dans une sous boite -> ...";
                    pB->PointeurParticuleDansBoite.push_back(ListepParticules[i]);
                    //on complete les caracteristiques de la boite
                    pB->masse += ListepParticules[i]->masse;
                    pB->centre_masse[0] += ListepParticules[i]->masse*(ListepParticules[i]->position[0]); 
                    pB->centre_masse[1] += ListepParticules[i]->masse*(ListepParticules[i]->position[1]);
                    pB->centre_masse[2] += ListepParticules[i]->masse*(ListepParticules[i]->position[2]);  
                    // il faudra ensuite diviser ces coordonnees par la masse totale de la boite
                    cout << " -> fin de l'ajout \n";
                }
            }//fin du parcours des sous boites
        } //  
        //toutes les particules ont ete attribuees a une sous boite
        //on supprime maintenenant les sous boites vides et on scinde les boites contenant plusieurs particules

        /* ________ test :  ________
        cout << "\nla taille de B.sousboite est :"<< this->sousBoites.size() <<"\n";
        cout << "les sous boites sont:\n";
        for(Boite* pB : sousBoites){
            cout<< pB;
        }
        cout << "\nOn supprime les sous boites vides\n";
        */
        // _______________ SUPRESSION DES SOUS BOITES VIDES _______________
        int k=0; //k indique le nb de sous boites supprimees
        for(int l =0; l+k<8; l++){
            if ( (this->sousBoites[l]->PointeurParticuleDansBoite.size() == 0) && (this->sousBoites[l]->particule == nullptr)){
                /*_______ test _______
                cout<< this->sousBoites[l];
                cout << "suppression de la sous boite\n";
                */
                sousBoites.erase(sousBoites.begin() +l);
                k++;
                l--;
            }
            else{}
        }
        // on corrige les centre de masse
        for (Boite *pB : sousBoites){
            pB->centre_masse[0] /= pB->masse;
            pB->centre_masse[1] /= pB->masse;
            pB->centre_masse[2] /= pB->masse;
        }

        /* ________ test :  ________ */
        cout << "\nla taille de B.sousboite est :"<< this->sousBoites.size() <<"\n";
        cout <<"Les boites restantes dans sous boites sont:\n";
        for(Boite* pB : sousBoites){
            cout<< pB;
        }   
        
        //on attribut les boites soeurs et la boite fille
        this->boite_fille = sousBoites[0];
        for(int j =0; j<sousBoites.size()-1; j++){
            sousBoites[j]->boite_soeur = sousBoites[j+1];
        } 

        cout << "\nfin de la subdivision, on subdivise les boites filles si necessaire \n";
        //on subdivise les sous boites si necessaire (appel reccursif)
        for(int j =0; j<sousBoites.size(); j++){
            cout<<"debut de la sous generation : ";
            //cout<< sousBoites[j]<< *sousBoites[j]->PointeurParticuleDansBoite[0];
            sousBoites[j]->generation(sousBoites[j]->PointeurParticuleDansBoite);
            cout<<"fin de la sous generation \n"; // -> ne s'affiche pas : problème dans l'appel reccursif
        }
    }
}

ostream& operator<<(ostream& os, const Boite B){
    os<<"   Niveau : " << B.niveau << " ; Taille : " << B.taille << '\n';
    os<<"   Centre : ("<< B.centre[0] << ", " << B.centre[1] << ", " << B.centre[2] << ") \n";
    os<<"   Centre de masse : ("<< B.centre_masse[0] << ", " << B.centre_masse[1] << ", " << B.centre_masse[2] << ") \n";
    os<<"   Boite fille :";
    if( B.boite_fille != NULL) {
        os<< *B.boite_fille <<"\n" ;
        Boite * p = B.boite_fille;
        while (p->boite_soeur != NULL){
                os << p->boite_soeur;
                p = p->boite_soeur->boite_soeur; 
        }
    }
    else {os<<"Pas de boite fille \n";}
    os<<"Particule :";
    if( B.particule != NULL) {os<< *B.particule ;}
    else {os<<"Pas de particule \n";}
    return os;
}

ostream& operator<<(ostream& os, const Boite* pB){
    os<<"   Niveau : " << pB->niveau << " ; Taille : " << pB->taille << '\n';
    os<<"   Centre : ("<< pB->centre[0] << ", " << pB->centre[1] << ", " << pB->centre[2] << ") \n";
    os<<"   Centre de masse : ("<< pB->centre_masse[0] << ", " << pB->centre_masse[1] << ", " << pB->centre_masse[2] << ") \n";
    os<<"   Boite fille :";
    if( pB->boite_fille != NULL) {
        os<< pB->boite_fille <<"\n" ;
        Boite * p = pB->boite_fille;
        while (p->boite_soeur != NULL){
                os << p->boite_soeur;
                p = p->boite_soeur->boite_soeur; 
        }
    }
    else {os<<"Pas de boite fille \n";}
    os<<"   Particule :";
    if( pB->particule != NULL) {os<< *pB->particule ;}
    else {os<<"Pas de particule \n";}
    return os;
}
