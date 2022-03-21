#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "boite.hpp"
#include "particule.hpp"
#include "constantes.hpp"
#include "orbite.hpp"

using namespace std;

Boite generationDuSysteme(int N){
    // On ouvre le fichier csv, sans supprimer ce qui est déjà present
    ofstream myfile;
    myfile.open ("part.csv", ios::app);
    
    cout << "_______________ DEBUT DE LA GENERATION DES PARTICULES _______________ \n";
    //N est le nombre de particule dans le systeme
    vector<Particule*> vect_pPart;
    vector<double> centre_masse_m = vector<double>(3,0); //centre de masse du systeme
    
    // On rajoute le numero et le temps qui vont être pris en compte dans le fichier csv
    int num = 1;
    
    while(vect_pPart.size()<N){
        //on cree une particule suivant le protocole fournit dans l'enonce
        vector<double> vect_nul = vector<double>(3,0.);
        //Particule P(vect_nul,1./N,vect_nul,vect_nul);
        Particule* pP = new Particule(vect_nul, 1./N, vect_nul, vect_nul);
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
        pP->position = vector<double>(3,0.);
        pP->position[0] = (r*(X2/u_r)*taille) -taille/2;  // petit ecart a l'enonce car on veut 
        pP->position[1] = (r*(X3/u_r)*taille) -taille/2;  // generer des coordonnees dans [-taille/2; taille/2]
        pP->position[2] = (r*(X4/u_r)*taille) -taille/2;  // et pas [0,1]
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
        pP->vitesse[0]= v_e*(X7/u_v);
        pP->vitesse[1]= v_e*(X8/u_v);
        pP->vitesse[2]= v_e*(X9/u_v);
        //on ajoute la particule a la liste et on l'affiche
        vect_pPart.push_back(pP);
        cout << "ajout de la Particule "<<vect_pPart.size()<<": \n"<<*pP;
        //on modifie le centre de masse du systeme
        centre_masse_m[0] = pow(N,-2)*X1;
        centre_masse_m[1] = pow(N,-2)*X2;
        centre_masse_m[2] = pow(N,-2)*X3;
        
        // On ajoute les coordonnees de la particule num dans le fichier csv
        myfile << num << ";" << pP->position[0]<< ";"<< pP->position[1]<< ";"<< pP->position[2] << "\n";
        num = num+1;
        
        }
    // On a fini de modifier le fichier csv pour cette etape
    myfile.close();
    
    cout << "________________ FIN DE LA GENERATION DES PARTICULES ________________ \n";
    cout << "________________  DEBUT DE LA GENERATION DES BOITES  ________________ \n";
    //une fois les particules crees, on creer les boites
    //creation de la boite mere (taille 1)
    vector<double> centre_m(3,0);
    centre_m[0] = 0; centre_m[1] = 0.; centre_m[2] =0.;
    Boite Boite_mere = Boite(1., centre_m, taille);
    Boite_mere.centre_masse = centre_masse_m;
    //generation des sous boites
    Boite_mere.PointeurParticuleDansBoite = vect_pPart;
    Boite_mere.generation(vect_pPart);
    //cout << Boite_mere;
    return Boite_mere;
}

//evolution du systeme
void evolution(vector<Particule*> LP, Boite* pB){
    //fait passer la systeme de l'instant t à l'instant t+dt
    LP= MAJ_pos(LP);
    for (Particule* ppart : LP){
        ppart->force[0]=0;
        ppart->force[1]=0;
        ppart->force[2]=0;
        *ppart = MAJ_forces(*ppart, pB);
    }
    LP=MAJ_vitesse(LP);
}


//test generation
int main(){
    //Creation d'un fichier csv permettant d'avoir les memes constantes entre les fichiers c++ et matlab
    ofstream myfile;
    myfile.open ("const.csv");
    myfile << "Nombre de particules;dt;Taille de la boite\n";
    myfile << Nbp << ";" <<dt << ";" << taille <<"\n";
    myfile.close();

    /*Creation du fichier excel pour stocker les differents points*/
    myfile.open ("part.csv");
    myfile << "Numero particule;Position x;Position y;Postition z\n";
    myfile.close();

    Boite Boite_mere = generationDuSysteme(Nbp);
    //cout << Boite_mere;
    Boite_mere.PointeurParticuleDansBoite = initialisationVitesse(Boite_mere.PointeurParticuleDansBoite);  //initialisation de la vitesse v1/2
    for (int i=0;i<100;i++){
        evolution(Boite_mere.PointeurParticuleDansBoite, &Boite_mere);
    };
    return 0;
}



