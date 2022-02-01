#ifndef boite.hpp
#define boite.hpp
#include <iostream>
#include <cmath>
#include <vector>
using namespace std ;

// classe boite

class boite
{   public:
        int level;
        vector<double> center;
        vector<double> mass_center;
        double mass;
        Particule * particule;
        Boite * boite_fille = NULL;
        Boite * boite_soeur = NULL;
        }