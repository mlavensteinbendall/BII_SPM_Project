#include <iostream>
#include <vector>
#include "rapidcsv.h"
#include <cmath>
#include "structuredPop.h"

using namespace std;


int main() {
    // INITIAL CONDITIONS - set all parameters for problem

        rapidcsv::Document doc("../MortalityRate.csv", rapidcsv::LabelParams(0, -1));

        vector<double> mu_ind = doc.GetColumn<double>("Mortality Rate");
//        cout << "Read " << mu_ind.size() << " values." << endl;
//
//        for (int i = 0; i < mu_ind.size(); i++){
//            cout << "t = " << i+1 << ": " << mu_ind[i] << endl;
//        }

        int a_min = 0;      // min. age
        int a_max = 91;     // max. age
        int t_min = 0;      // min. days
        int t_max = 102;    // max. days
        int N = 20;         // number of iterations
        double da = 1;          // partition in age
        double dt = 1;          // partition in time

        vector<double> u_0a;            // u(0,a) - Amount of DMs at start in each age range
        u_0a.assign(a_max, 0.);   // set to zero
        u_0a[6] = 5.;                   // 5 DMs that are 6-day and seeded

        structuredPop DMs;

        vector<vector<double>> sol;

        DMs.setProblem(a_max, t_max, da, dt, u_0a, mu_ind);
        DMs.upwindMethod(sol);

        for(int i = 0 ; i < a_max; i++){
            cout << "u(0,"  << i << ") = " << sol[0][i] << endl;
        }

        vector<double> totalDms;
        totalDms.assign(t_max, 0.);
        double temp = 0.;

        for(int i = 0; i < t_max; i++){
            temp = 0.;
            for(int j = 0; j < a_max; j++){
                temp += sol[i][j];
            }
            totalDms[i] = temp;
        }

        ofstream out1("totalDMs.csv");

        for (auto& row : totalDms) {
                out1 << row <<'\n';
        }



        ofstream out("test.csv");

        for (auto& row : sol) {
            for (auto col : row)
                out << col <<',';
            out << '\n';
        }



//    vector<double> k_ind;
//    k_ind.assign(103, 0.);


//    for (int i = 0; i < 103; i++){
//        k_ind[i] = 5. * exp(-i/10);
//        cout << "t = " << i << setprecision(15) << ": " << k_ind[i] << endl;
//    }

    return 0;
}
