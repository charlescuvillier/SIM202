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
