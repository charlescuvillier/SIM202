#include "particule.hpp"

Particule::Particule(vector<double>& pos, double m, vector<double> v){
    this->position.resize(3);
    this->position = pos;
    this->vitesse.resize(3);
    this->vitesse = v;
    this->force.resize(3,0);
    this->masse = m;
}

Particule::Particule(vector<double>& v, vector<double>& F){
    this->vitesse = v;
    this->force = F;
}