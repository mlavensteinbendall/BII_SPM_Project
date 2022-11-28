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

double structedPop::trapizoidalRule(int t, int ds, int n, vector<double> u){

    // Computing sum of first and last terms
    double s = k_ind(0) * u[0]+ k_ind(age_max - 1) * u[age_max - 1];

    // Adding middle terms
    for (int i = 1; i < n; i++){
        s += 2 * k_ind(i) * u[i];
    }

    return (1 / 2) * s;
}

//void structedPop::bc_t0(){
//    for(int i = 0; i < time_max; i++){
//        //u_t0[i] = trapizoidalRule(100);
//    }
//}

void structedPop::compute_u_t0(vector<double> & u_t0){

    int n = 100;
    int ds = age_max/n;
    vector<double> u = u_0a;

    // need to use u(0,a) to compute the first u(t,s) and then it should just build from that
    // Computing sum of first and last terms

    // Adding middle terms
    for (int t = 0; t < time_max; t++){

        u_t0[t] = trapizoidalRule(t, ds, n, u);

        for (int i = 0; i < age_max; i++){
            u[i] = u[i+1];
        }
    }
}

void structedPop::upwindMethod(){
    //double sol[time_max][age_max];
    vector<double> U = u_0a;
    double U_temp[time_max];


//    for(int i = 0; i < ; i++)
//    {
//        U[i] = u_0a[i];
//    }

    for(int t = 1; t < time_max; t++){
        U_temp[t] = U[t] - dt * (mu_ind[t] * U[t] - ((U[t] - U[t-1])/da));

        for(int a = 0; a < age_max; a++){

        }

    }

    U = U_temp;

}
