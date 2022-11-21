//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//

#ifndef BII_SPM_PROJECT_SL_METHOD_H
#define BII_SPM_PROJECT_SL_METHOD_H

#include "Grid2d.h"
#include <vector>

// Semi-Lagrangian Method
class SL_method {
private:
    Grid2d sl_grid;
    std::vector<double> sol;
    std::vector<double> vel_u;
    std::vector<double> vel_v;
    void find_departure(int n, double & x_d, double & y_d, double dt);

public:
    void set_grid(Grid2d & new_grid){sl_grid = new_grid;}
    std::vector<double> get_sol(){ return sol;}
    void set_velocity(std::vector<double> & vel_u0, std::vector<double> & vel_v0);
    void set_velocity_one_term(double &x_0, double &y_0);
    void solve_advection (std::vector<double> & sol_0, double t0, double tf, double dt);
};

#endif //BII_SPM_PROJECT_SL_METHOD_H
