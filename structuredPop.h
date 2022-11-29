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
    int da;
    int dt;
    vector<double> u_t0;    // u(t,0)   - size 102
    vector<double> u_0a;    // u(0,a)   - size 91
    vector<double> mu_ind;

    double k_ind(int a){return 5 * exp(-a/10);};    // fecundity rate
    double trapezoidalRule(vector<double> u);

public:
    void upwindMethod(vector<vector<double>> &sol);
    void setProblem(int a, int t, vector<double> u);
};


#endif //BII_SPM_PROJECT_STRUCTUREDPOP_H
