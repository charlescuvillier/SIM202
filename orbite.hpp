//importer sqrt
const G = 1;

float dist(float* v1, float* v2) //calcule la distance entre v1 et v2
{
    float L = (v2[1]-v1[1])**2+(v2[2]-v1[2])**2+(v2[3]-v1[3])**2;
    float L = sqrt(L);
    return(L);
};

Liste_Particule MAJ_forces(&Liste_Particule LP, epsilon) //maj des forces appliqués aux particules  (PENSER A CREER LA LISTE PARTICULE)
{
    for (Particule part1 in LP)
    {
        part1_force[1]=0;
        part1_force[2]=0;
        part1_force[3]=0;
        for (Particule part2 in LP)
        {
            r=dist(part1_position, part2_position);
            norm = G*part1_mass*part2_mass;
            if (r>epsilon)
            {
                norm=-norm/(r**3); //a la place on divise par r cube et on multiplie par le vecteur u2-u1 non normé
            };
            else
            {
                norm=-norm/(epsilon**3);
            };
            part1_force[1+]=norm*(part1_position[1]-part2_position[1]);
            part1_force[2]+=norm*(part1_position[2]-part2_position[2]);
            part1_force[3]+=norm*(part1_position[3]-part2_position[3]);
        };
    };
};


Liste_particules MAJ_vitesse_un_demi(&Liste_Particule, float dt)