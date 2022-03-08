#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "boite.hpp"
#include "particule.hpp"
#include "constantes.hpp"

using namespace std;

Boite generationDuSysteme(int N){
    //N est le nombre de particule dans le systeme
    vector<Particule*> vect_pPart;
    vector<double> centre_masse_m = vector<double>(3,0); //centre de masse du systeme
    while(vect_pPart.size()<N){
        //on cree une particule suivant le protocole fournit dans l'enonce
        vector<double> vect_nul = vector<double>(3,0);
        Particule P(vect_nul,1./N,vect_nul,vect_nul);
        //on determine la position de la particule
        double X1 = rand()/(double)RAND_MAX;
        double r = pow(0.999*pow(X1,-2./3.)-1,-1./2.);
        double X2 = rand()/(double)RAND_MAX;
        double X3 = rand()/(double)RAND_MAX;
        double X4 =rand()/(double)RAND_MAX;
        double u_r = sqrt(pow(X2,2)+pow(X3,2)+pow(X4,2));
        while(u_r>1){
            X2 = rand()/(double)RAND_MAX;
            X3 = rand()/(double)RAND_MAX;
            X4 =rand()/(double)RAND_MAX;
            u_r = sqrt(pow(X2,2)+pow(X3,2)+pow(X4,2));
        }
        P.position = vector<double>(3,0.);
        P.position[0] = r*(X2/u_r) + R;
        P.position[1] = r*(X3/u_r);
        P.position[2] = r*(X4/u_r);
        //on determine la vitesse de la particule
        double X5 = rand()/(double)RAND_MAX;
        double X6 = rand()/(double)RAND_MAX;
        double g = pow(X5,2)*pow(1-pow(X5,2),7./2.);
        while (X6>10*g){
            X5 = rand()/(double)RAND_MAX;
            X6 = rand()/(double)RAND_MAX;
            g = pow(X5,2)*pow(1-pow(X5,2),7./2.);
        }
        double q = X5;
        double v_e = sqrt(2)*pow(1+pow(r,2),-0.25);
        double X7 = rand()/(double)RAND_MAX;
        double X8 = rand()/(double)RAND_MAX;
        double X9 = rand()/(double)RAND_MAX;
        double u_v = sqrt(pow(X7,2)+pow(X8,2)+pow(X8,2));
        while(u_v>1){
            X7 = rand()/(double)RAND_MAX;
            X8 = rand()/(double)RAND_MAX;
            X9 =rand()/(double)RAND_MAX;
            u_v = sqrt(pow(X7,2)+pow(X8,2)+pow(X9,2));
        }
        P.vitesse[0]= v_e*(X7/u_v);
        P.vitesse[1]= v_e*(X8/u_v);
        P.vitesse[2]= v_e*(X9/u_v);
        //on ajoute la particule a la liste et on l'affiche
        cout << "ajout de la Particule "<<vect_pPart.size()<<": \n " <<P;
        vect_pPart.push_back(&P);
        //on modifie le centre de masse du systeme
        centre_masse_m[0] = pow(N,-2)*X1;
        centre_masse_m[1] = pow(N,-2)*X2;
        centre_masse_m[2] = pow(N,-2)*X3;
        
        }
    cout << "________________ FIN DE LA GENERATION DES PARTICULES ________________ \n";
    //une fois les particules crees, on creer les boites
    //creation de la boite mere (taille 1)
    vector<double> centre_m(3,0);
    centre_m[0] = R; centre_m[1] = 0.; centre_m[2] =0.;
    Boite Boite_mere = Boite(1., centre_m, taille);
    Boite_mere.centre_masse = centre_masse_m;
    //generation des sous boites
    Boite_mere.generation(vect_pPart);
    return Boite_mere;
}

//test generation
int main(){
    /*cout <<"test  particule \n";
    vector<double> v(3,1.);
    vector<double> v0(3,0.);
    Particule P = Particule(v, 10. , v0 , v0);
    cout << P ;
    cout << "test boite \n";
    Boite B = Boite(2, v, 4.);
    B.particule = &P;
    cout << B ;
    */
    Boite Boite_mere = generationDuSysteme(10);
    cout << Boite_mere;
    return 0;
}




//evolution du systeme

void evolution(Boite B){
    //fait passer la systeme de l'instant t à l'instant t+dt
    
}
