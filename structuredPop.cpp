//
// Created by Morgan Lavenstein Bendall on 11/15/22.
// hello

#include "structuredPop.h"

structedPop::structedPop()
{

}
structedPop::structedPop(int a, int a_m, int t, vector<double> u_age){
    age = a;
    age_max = a_m;
    time = t;
    u_0a = u_age;
}

double structedPop::trapizoidalRule(vector<double> u){
    // Compute the integral at given t

    // Computing sum of first and last terms
    double s = k_ind(0) * u[0]+ k_ind(age_max - 1) * u[age_max - 1];

    // Adding middle terms
    for (int i = 1; i < time_max; i++){
        s += 2 * k_ind(i) * u[i];
    }

    return (1 / 2) * s;
}

vector<double> structedPop::compute_bc_t0(vector<double> & u_t0){

    vector<double> u = u_0a;

    for (int t = 0; t < time_max; t++){
        u_t0[t] = trapizoidalRule(u);
    }
}

void structedPop::upwindMethod(){
    vector<vector<double>> sol;
    vector<double> U = u_0a;    // initialize U
    vector<double> U_temp;      // temporary

    U_temp.assign(time_max, 0.);

    for(int t = 0; t < time_max; t++){

        // Holds the solution at each time-step
        sol[t] = U;

        // Set boundary condition
        U[0] = trapizoidalRule(U);

        // Calculate the soluti
        for(int a = 1; a < age_max; a++){
            U_temp[a] = U[a] - dt * (mu_ind[a] * U[a] - ((U[a] - U[a-1])/da));
        }

        U = U_temp;
    }


}
