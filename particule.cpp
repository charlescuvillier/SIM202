#include "particule.hpp"

Particule::Particule(vector<double>& pos, double m){
    this->position.resize(3);
    this->position = pos;
    this->masse = m;
    this->vitesse.resize(3,0);
    this->force.resize(3,0);
}

Particule::Particule(vector<double>& v, vector<double>& F){
    this->vitesse = v;
    this->force = F;
}