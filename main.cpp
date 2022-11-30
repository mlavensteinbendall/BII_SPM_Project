#include <iostream>
#include <vector>
#include "rapidcsv.h"
#include "structuredPop.h"

using namespace std;

int main() {
    //// INITIAL CONDITIONS -- set all parameters for problem

    // Reads in MortalityRate.csv
    rapidcsv::Document doc("../MortalityRate.csv", rapidcsv::LabelParams(0, -1));

//    int a_min = 0;          // min. age
//    int t_min = 0;          // min. days

    int a_max = 91;         // max. age
    int t_max = 102;        // max. days
    double da = 1;          // partition in age
    double dt = 1;          // partition in time

    vector<double> u_0a;            // u(0,a) - Amount of DMs at start in each age range
    u_0a.assign(a_max, 0.);   // set to zero
    u_0a[6] = 5.;                   // 5 DMs that are 6-day and seeded

    vector<double> mu_ind = doc.GetColumn<double>("Mortality Rate"); // mortality rate at each age

    // Check that mu_ind is read in correctly
    if (mu_ind.size() == a_max) {
        cout << "mu_ind valid." << endl;
    }
    else{
        cout << "mu_ind invalid." << endl;
        return 1;
    }

    vector<vector<double>> sol;     // population of age-groups at each time-step

    vector<double> totalDms;        // total population at each time-step
    totalDms.assign(t_max, 0.);
    double temp = 0.;

    structuredPop DMs;      // Structured Population Model
    DMs.setProblem(a_max, t_max, da, dt, u_0a, mu_ind);

    ofstream outTotalPop("totalDMs.csv");   // output total population at each time-step
    ofstream outSol("solution.csv");        // output population of age-groups at each time-step



    //// SOLVE PROBLEM -- using structuredPop to find the solution and output to csv files.

    DMs.upwindMethod(sol);

//  View solution at a particular time-step
//    for(int i = 0 ; i < a_max; i++){
//        cout << "u(0,"  << i << ") = " << sol[0][i] << endl;
//    }

    totalDms = DMs.getTotalPop();   // retrieve the total population at each time-step

//  Print total population to csv
    for (auto& row : totalDms) {
        outTotalPop << row <<'\n';
    }

//  Print solution to csv
    for (auto& row : sol) {
        for (auto col : row)
            outSol << col <<',';
        outSol << '\n';
    }

    return 0;
}
