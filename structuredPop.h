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

class structedPop {

public:
    structedPop();
    structedPop(int a, int a_m, int t, vector<double> u_age);
    void upwindMethod();


private:
    int age;
    int age_max;
    int time;
    int time_max;
    int da;
    int dt;
    vector<double> u;
    vector<double> u_t0;    // u(t,0)   - size 102
    vector<double> u_0a;    // u(0,a)   - size 91
    vector<double> mu_ind;

    vector<double> u_pop;
    double k_ind(int a){return 5 * exp(-a/10);};    // fecundity rate
    double trapizoidalRule(vector<double> u);
    vector<double> compute_bc_t0(vector<double> & u_t0);

};


#endif //BII_SPM_PROJECT_STRUCTUREDPOP_H
