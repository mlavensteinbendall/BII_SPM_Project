#include <iostream>
#include <vector>
#include "rapidcsv.h"
#include <cmath>

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

        vector<double> u_0a;        // u(0,a) - Amount of DMs at start in each age range
        u_0a.assign(a_max, 0.);
        u_0a[5] = 5.;               // 5 DMs that are 6-day and seeded

        vector<double> u_t0;        // u(t,0) - Amount of newborns each day

        for(int i = 0; i < t_max; i++){
            //u_t0[i] = trapizoidalRule(i);
        }









//    vector<double> k_ind;
//    k_ind.assign(103, 0.);


//    for (int i = 0; i < 103; i++){
//        k_ind[i] = 5. * exp(-i/10);
//        cout << "t = " << i << setprecision(15) << ": " << k_ind[i] << endl;
//    }

    return 0;
}
