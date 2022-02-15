#ifndef BOITE_HPP
#define BOITE_HPP

#include<vector>
#include <iostream>
#include "Particule.hpp"
using namespace std;

class Boite {
  private:
    int niveau;
    double centre_x;
    double centre_y;
    double centre_masse_x;
    double centre_masse_y;
    double masse;
    int nb_particules;
    vector<Particule*> particules;
    Boite* nordOuest;
    Boite* nordEst;
    Boite* sudOuest;
    Boite* sudEst;
    int capacity;

  public:
    Boite(int niv,double x,double y,double masse_x, double masse_y,double m, int capacity_);
    ~Boite();
    bool contient(Particule* part);
    void insert(Particule* part);
    void subdivise();
    vector<double> calcul_force(Particule P, double theta,double eps);
    void nouveau();

    // ACCESSOR
    int getPos(int);
    Boite* getSubBox(int);
};

#endif //BOITE_HPP
