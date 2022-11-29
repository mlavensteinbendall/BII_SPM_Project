//
// Created by Morgan Lavenstein Bendall on 11/15/22.
// hello

#include "structuredPop.h"


void structuredPop::setProblem(int a, int t, double d_age, double d_time, vector<double> u, vector<double> mu){
    age_max = a;
    time_max = t;
    da = d_age;
    dt = d_time;
    u_0a = u;
    mu_ind = mu;
}

//double structuredPop::k_ind(int a){
//
//    return 5 * exp(-a/10);
//}

double structuredPop::u_t0(vector<double> u){

    // Computing sum of first and last terms
    double s = 0.; // newborns and dead can't reproduce  //(k_ind(0) * u[0]) + (k_ind(age_max) * 0);   //

    // Adding middle terms
    for (int i = 8; i < age_max; i++){
        // s += 2 * k_ind(i) * u[i];
        s += k_ind(i) * u[i];
    }

    //return s/2;
    return s;
}


void structuredPop::upwindMethod(vector<vector<double>> &sol){

    vector<double> U = u_0a;    // initialize U
    vector<double> U_temp;      // temporary
   // double temp;

    U_temp.assign(age_max, 0.);
    //sol.resize(time_max * age_max);

    for(int t = 0; t < time_max + 1; t++){
        // Holds the solution at each time-step
        sol.push_back(U);

        // Set boundary condition
        U_temp[0] = u_t0(U);

        // Calculate the solution
        for(int a = 1; a < age_max; a++){
            U_temp[a] = U[a] - (dt * (mu_ind[a] * U[a] + ((U[a] - U[a-1])/da)));

            if(U_temp[a] < 0){
                U_temp[a] = 0;
            }

        }

        U = U_temp;
    }


}
