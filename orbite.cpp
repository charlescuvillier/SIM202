#include <math.h>
#include "particule.hpp"
#include "Boite.hpp"
const float G = 6.334*pow(10,-15);

double dist(vector<double> v1, vector<double> v2) //calcule la distance entre v1 et v2
{
    double L = pow((v2[1]-v1[1]),2)+pow((v2[2]-v1[2]),2)+pow((v2[0]-v1[0]),2);
    L = pow(L,1/2);
    return(L);
}


Particule MAJ_forces(Particule& parti, float epsilon, float rayon, Boite* B)
{
    Boite* A=B;
    Particule& part = parti;
    if(A->boite_fille !=NULL && dist(A->centre_masse, part.position)<rayon )  //ok
    {
        Boite* temp = A->boite_fille;
        A = temp;
        while(A!=NULL)
        {
            part = MAJ_forces(part, epsilon, rayon, A);
            Boite* tempsoeur= A->boite_soeur;
            A= tempsoeur;
        }
    }
    else{
        float r=dist(part.position, A->centre_masse);
        float norm = G*part.masse*A->masse;
        if (r>epsilon)
        {
            norm=-norm/(pow(r,3)); //a la place on divise par r cube et on multiplie par le vecteur u2-u1 non normé
        }
        else
        {
            norm=-norm/(pow(epsilon,3));
        }
        part.force[1]+=norm*(part.position[1]-A->centre_masse[1]);
        part.force[2]+=norm*(part.position[2]-A->centre_masse[2]);
        part.force[0]+=norm*(part.position[0]-A->centre_masse[0]);
        
        //ici on rajoute la force du a la boite

    }
    return(part); //on renvoie la particule avec ses forces mises à jour
}



vector<Particule*> initialisationVitesse(vector<Particule*> LP, float dt)
{
    for (Particule* part : LP)
    {
        part->vitesse[1] += (dt*part->force[1])/(2*part->masse);
        part->vitesse[2] += (dt*part->force[2])/(2*part->masse);
        part->vitesse[0] += (dt*part->force[0])/(2*part->masse);
    }
    return LP;
}

vector<Particule*> MAJ_pos(vector<Particule*> LP, float dt)
{
    for (Particule* part : LP)
    {
        part->position[1] += dt*part->vitesse[1];
        part->position[2] += dt*part->vitesse[2];
        part->position[0] += dt*part->vitesse[0];
    }
    return LP;
}

vector<Particule*> MAJ_vitesse(vector<Particule*> LP, float dt)
{
    for (Particule* part : LP)
    {
        part->vitesse[1] += dt*part->force[1]/part->masse;
        part->vitesse[2] += dt*part->force[2]/part->masse;
        part->vitesse[0] += dt*part->force[0]/part->masse;
    }
    return LP;
}
