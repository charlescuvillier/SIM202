#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//=================================================================================
//                        class Particule
//=================================================================================

class Particule{
    public :
        vector<double> position; //position instantanée de la particule        
        double masse; //Masse de la particule
        vector<double> vitesse; //Vitesse instantanée de la particule
        vector<double> force; //Force gravitationnelle exercée sur la particule

        Particule(vector<double>& pos, double m,vector<double>& v, vector<double>& F); //constructeur à partir des paramètres la position de la particule
};

#endif