#include <math.h>
#include <particule.hpp>
const float G = 6.334*pow(10,-15);

double dist(vector<double> v1, vector<double> v2) //calcule la distance entre v1 et v2
{
    double L = pow((v2[1]-v1[1]),2)+pow((v2[2]-v1[2]),2)+pow((v2[0]-v1[0]),2);
    L = pow(L,1/2);
    return(L);
};


Particule MAJ_forces(&Particule part, float epsilon, float rayon, boite* B)
{
    if(B.fille !=NULL && dist(boite.cdm-part.pos)<rayon )  //surcharger l'opérateur - pour des vecteurs !
    {
        boite* temp = B.fille;
        B = temp;
        while(B!=NULL)
        {
            part = MAJ_forces(part, epsilon, B);
            boite* tempsoeur= B.soeur;
            B= tempsoeur
        };
    }
    else{
        r=dist(part.position, B.cdm);
            norm = G*part1.mass*B.mass;
            if (r>epsilon)
            {
                norm=-norm/(r**3); //a la place on divise par r cube et on multiplie par le vecteur u2-u1 non normé
            };
            else
            {
                norm=-norm/(epsilon**3);
            };
            part.force[1]+=norm*(part.position[1]-B.cdm[1]);
            part.force[2]+=norm*(part.position[2]-B.cdm[2]);
            part.force[0]+=norm*(part.position[0]-B.cdm[0]);
        
        //ici on rajoute la force du a la boite

    };
};


Liste_Particules MAJ_forces(&Liste_Particules LP, float epsilon) //maj des forces appliqués aux particules  (PENSER A CREER LA LISTE PARTICULE)
{
    for (Particule part1 in LP)
    {
       
       
       
       
        /*part1.force[1]=0;
        part1.force[2]=0;
        part1.force[0]=0;
        for (Particule part2 in LP)
        {
            r=dist(part1.position, part2.position);
            norm = G*part1.mass*part2.mass;
            if (r>epsilon)
            {
                norm=-norm/(r**3); //a la place on divise par r cube et on multiplie par le vecteur u2-u1 non normé
            };
            else
            {
                norm=-norm/(epsilon**3);
            };
            part1.force[1]+=norm*(part1.position[1]-part2.position[1]);
            part1.force[2]+=norm*(part1.position[2]-part2.position[2]);
            part1.force[0]+=norm*(part1.position[0]-part2.position[0]);
        };*/
    };
};


Liste_Particules initialisationVitesse(&Liste_Particules LP, float dt)
{
    for (part in LP)
    {
        part.vitesse[1] += (dt*part.force[1])/(2*part.masse);
        part.vitesse[2] += (dt*part.force[2])/(2*part.masse);
        part.vitesse[0] += (dt*part.force[0])/(2*part.masse);
    };
};

Liste_Particules MAJ_pos(&Liste.Particules LP, float dt)
{
    for (part in LP)
    {
        part.position[1] += dt*part.vitesse[1];
        part.position[2] += dt*part.vitesse[2];
        part.position[0] += dt*part.vitesse[0];
    };
};

Liste_Particules MAJ_vitesse(&Liste_Particules LP, float dt)
{
    for (part in LP)
    {
        part.vitesse[1] += dt*part.force[1]/part.mass;
        part.vitesse[2] += dt*part.force[2]/part.mass;
        part.vitesse[0] += dt*part.force[0]/part.mass;
    };
};
