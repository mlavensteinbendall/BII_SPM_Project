//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//
// OBJECTIVE: This class is solving a structured population model, which is based on the Sinko-Streifer
// equations. This model was created off of Erica Rutter's "Continuous Structured Population Models for Daphnia magna"
// article. It was simplified by not including biomass M(t) or mortality rate based on biomass mu_dep.
// https://link.springer.com/article/10.1007/s11538-017-0344-8


#ifndef BII_SPM_PROJECT_STRUCTUREDPOP_H
#define BII_SPM_PROJECT_STRUCTUREDPOP_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class structuredPop{
private:
    int age_max;            // max. age
    int time_max;           // max. time
    double da;              // partition in age
    double dt;              // partition in time

    vector<double> u_0a;        // u(0,a)  -- Amount of DMs we are starting with (size 91)
    vector<double> mu_ind;      // Mortality Rate -- read in from csv
    vector<double> totalPop;    // Total Population at each time-step

    double k_ind(int a, vector<double> u); //{return exp(-a/10)*500/(500+totalPopulation(u));};   // Fecundity Rate
    double totalPopulation(vector<double> u);   // Calculate total population at a particular time-step
    double u_t0(vector<double> u);              // Calculate the boundary condition at a particular time

public:
    void upwindMethod(vector<vector<double>> &sol);     // Upwind Method to solve PDE
    void setProblem(int a, int t, double d_age, double d_time, vector<double> u, vector<double> mu);    // Set values
    vector<double> getTotalPop(){return totalPop;};     // Retrieve Total Population at each time-step
};


#endif //BII_SPM_PROJECT_STRUCTUREDPOP_H
