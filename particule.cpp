#include "particule.hpp"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

Particule::Particule(vector<double>& pos, double m,vector<double>& v, vector<double>& F){
    this->position.resize(3);
    this->position = pos;
    this->masse = m;
    this->vitesse.resize(3,0);
    this->vitesse = v;
    this->force.resize(3,0);
    this->force = F;
}

ostream& operator<<(ostream& os, const Particule P){
    os<<"Position : ("<<P.position[0]<<P.position[1]<<P.position[2]<<")"<<"\n";
    os<<"Masse : "<< P.masse <<"\n";
    os<<"Vitesse : ("<<P.vitesse[0]<<P.vitesse[1]<<P.vitesse[2]<<")"<<"\n";
    os<<"Force : ("<<P.force[0]<<P.force[1]<<P.force[2]<<")"<<"\n";
    return os;
}