//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//
// Objective: Here we will have the properties of our Structured Population Model, which is based on the Sinko-Streifer
// equations.

#ifndef BII_SPM_PROJECT_STRUCTUREDPOP_H
#define BII_SPM_PROJECT_STRUCTUREDPOP_H

#include <iostream>
#include <vector>

class structedPop {

public:
    structedPop();
    structedPop(int a, int a_m, int t, double M);
    std::vector<double> population(int t);

private:
    int age;
    int age_max;
    int time;

    int r;
    int s;
    int L;      // Length

    std::vector<double> u_pop;

    double M(int t, int r, int s, int L);   // Biomass
    double





};


#endif //BII_SPM_PROJECT_STRUCTUREDPOP_H
