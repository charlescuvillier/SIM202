#include "particule.hpp"

Particule::Particule(vector<double>& pos, double m){
    this->position.resize(2);
    this->position = pos;
    this->vitesse.resize(2,0);
    this->force.resize(2,0);
    this->masse = m;
}

Particule::Particule(vector<double>& v, vector<double>& F){
    this->vitesse = v;
    this->force = F;
}
