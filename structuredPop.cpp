//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//
// OBJECTIVE: This class is solving a structured population model, which is based on the Sinko-Streifer
// equations. This model was created off of Erica Rutter's "Continuous Structured Population Models for Daphnia magna"
// article. It was simplified by not including biomass M(t) or mortality rate based on biomass mu_dep.
// https://link.springer.com/article/10.1007/s11538-017-0344-8

#include "structuredPop.h"

void structuredPop::setProblem(int a, int t, double d_age, double d_time, vector<double> u, vector<double> mu){
    // OBJECTIVE -- initialize values in class

    age_max = a;        // set max. age
    time_max = t;       // set max. time
    da = d_age;         // set partition in age
    dt = d_time;        // set partition in time
    u_0a = u;           // set initial population
    mu_ind = mu;        // set mortality rate
    totalPop.assign(time_max, 0.);  // set size of vector for total population
}

//double structuredPop::k_ind(int a, vector<double> u){
//
//
//    return exp(-a/10)*500/(500+totalPopulation(u));
//}

double structuredPop::totalPopulation(vector<double> u){
    //  OBJECTIVE -- calculate the total population for given time-step

    double temp = 0.;

    for(int i = 0; i < age_max; i++){
        temp += u[i];
    }

    return temp;
}


double structuredPop::u_t0(vector<double> u){
    // OBJECTIVE -- use trapezoidal rule to compute the integral to find the boundary condition

    // Computing sum of first and last terms
    double s = 0.;      // newborns and dead can't reproduce

    // Adding middle terms (note: Daphnia Magna can give birth at 8-days-old.)
    for (int i = 7; i < age_max; i++){

        // Need population from previous time-step to get current aged population; hence, u[i] is u[i+1] in the
        // next time-step which we are in.

        s += k_ind(i+1,u) * u[i];       // negated multiplying by 2 because end terms are zero
    }

    return s;
}


void structuredPop::upwindMethod(vector<vector<double>> &sol){
    // OBJECTIVE -- solve the PDE

    vector<double> U = u_0a;    // initialize U
    vector<double> U_temp;      // temporary U

    U_temp.assign(age_max, 0.);

    for(int t = 0; t < time_max + 1; t++){

        // Holds the solution at each time-step
        sol.push_back(U);

        // Calculate total Population
        totalPop[t] = totalPopulation(U);

        // Set boundary condition
        U_temp[0] = u_t0(U);

        // Calculate the solution
        for(int a = 1; a < age_max; a++){

            U_temp[a] = U[a] - (dt * ((mu_ind[a] * U[a]) + ((U[a] - U[a-1])/da)));

            if(U_temp[a] < 0){
                U_temp[a] = 0;      // Population cannot be negative
            }
        }

        U = U_temp;
    }

}
