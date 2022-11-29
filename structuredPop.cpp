//
// Created by Morgan Lavenstein Bendall on 11/15/22.
// hello

#include "structuredPop.h"


void structuredPop::setProblem(int a, int t, vector<double> u){
    age_max = a;
    time_max = t;
    u_0a = u;
}

double structuredPop::trapezoidalRule(vector<double> u){
    // Compute the integral at given t

    // Computing sum of first and last terms
    double s = k_ind(0) * u[0]+ k_ind(age_max - 1) * u[age_max - 1];

    // Adding middle terms
    for (int i = 1; i < time_max; i++){
        s += 2 * k_ind(i) * u[i];
    }

    return (1 / 2) * s;
}


void structuredPop::upwindMethod(vector<vector<double>> &sol){

    vector<double> U = u_0a;    // initialize U
    vector<double> U_temp;      // temporary

    U_temp.assign(age_max, 0.);
    //sol.resize(time_max * age_max);

    for(int t = 0; t < time_max; t++){

        // Holds the solution at each time-step
        sol.push_back(U);

        // Set boundary condition
        U[0] = trapezoidalRule(U);

        // Calculate the soluti
        for(int a = 1; a < age_max; a++){
            U_temp[a-1] = U[a] - dt * (mu_ind[a] * U[a] - ((U[a] - U[a-1])/da));
        }

        U = U_temp;
    }


}
