//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//
// Objective: Here we will have the properties of our Structured Population Model, which is based on the Sinko-Streifer
// equations.

#ifndef BII_SPM_PROJECT_STRUCTUREDPOP_H
#define BII_SPM_PROJECT_STRUCTUREDPOP_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class structuredPop{
private:
    int age_max;
    int time_max;
    double da;
    double dt;
    vector<double> u_0a;    // u(0,a)   - Amount of DMs we are starting with (size 91)
    vector<double> mu_ind;  // Mortality Rate -- read in from csv

    double k_ind(int a){return 5 * exp(-a/10);};    // Fecundity Rate -- Graph
    //double u_t0(vector<double> u);

public:
    void upwindMethod(vector<vector<double>> &sol);
    void setProblem(int a, int t, double d_age, double d_time, vector<double> u, vector<double> mu);
    double u_t0(vector<double> u);
};


#endif //BII_SPM_PROJECT_STRUCTUREDPOP_H
