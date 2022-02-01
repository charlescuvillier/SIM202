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
        vector<double> pos; //position instantanée de la particule
        vector<double> vitesse; //Vitesse instantanée de la particule
        vector<double> force; //Force gravitationnelle exercée sur la particule

        Particule(vector<double>& coord); //constructeur à partir de la position de la particule
        Particule(vector<double> F); //constructeur à partir de la force exercée sur la particule
        Particule(vector<double> v); //constructeur à partir de la vitesse de la particule

        ~Particule(); //destructeur 
};



#endif