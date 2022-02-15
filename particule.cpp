#include "particule.hpp"

Particule::Particule(vector<double>& pos, double m, vector<double> v){
    this->position.resize(2);
    this->position = pos;
    this->vitesse.resize(2);
    this->vitesse = v;
    this->force.resize(2,0);
    this->masse = m;
}

Particule::Particule(vector<double>& v, vector<double>& F){
    this->vitesse = v;
    this->force = F;
}