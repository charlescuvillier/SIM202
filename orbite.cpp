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
    if(A.fille !=NULL && dist(A.cdm-part.position)<rayon )  //surcharger l'opérateur - pour des vecteurs !
    {
        Boite* temp = A.fille;
        A = temp;
        while(A!=NULL)
        {
            part = MAJ_forces(part, epsilon, A);
            Boite* tempsoeur= A.soeur;
            A= tempsoeur;
        }
    }
    else{
        float r=dist(part.position, A.cdm);
        float norm = G*part1.mass*A.mass;
        if (r>epsilon)
        {
            norm=-norm/(pow(r,3)); //a la place on divise par r cube et on multiplie par le vecteur u2-u1 non normé
        }
        else
        {
            norm=-norm/(pow(epsilon,3));
        }
        part.force[1]+=norm*(part.position[1]-A.cdm[1]);
        part.force[2]+=norm*(part.position[2]-A.cdm[2]);
        part.force[0]+=norm*(part.position[0]-A.cdm[0]);
        
        //ici on rajoute la force du a la boite

    }
    return(part); //on renvoie la particule avec ses forces mises à jour
}



Liste_Particules initialisationVitesse(&Liste_Particules LP, float dt)
{
    for (part in LP)
    {
        part.vitesse[1] += (dt*part.force[1])/(2*part.masse);
        part.vitesse[2] += (dt*part.force[2])/(2*part.masse);
        part.vitesse[0] += (dt*part.force[0])/(2*part.masse);
    }
}

Liste_Particules MAJ_pos(&Liste.Particules LP, float dt)
{
    for (part in LP)
    {
        part.position[1] += dt*part.vitesse[1];
        part.position[2] += dt*part.vitesse[2];
        part.position[0] += dt*part.vitesse[0];
    }
}

Liste_Particules MAJ_vitesse(&Liste_Particules LP, float dt)
{
    for (part in LP)
    {
        part.vitesse[1] += dt*part.force[1]/part.mass;
        part.vitesse[2] += dt*part.force[2]/part.mass;
        part.vitesse[0] += dt*part.force[0]/part.mass;
    }
}
