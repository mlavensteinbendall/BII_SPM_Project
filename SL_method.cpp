//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//

#include "SL_method.h"
#include "Grid2d.h"
#include "mathtools.h"
#include <cmath>
#include <vector>
#include <algorithm>

void SL_method::set_velocity(std::vector<double> &u_0, std::vector<double> &v_0){
    // Velocity field is V(x,y) = (-y,x)
    for(int n = 0; n < sl_grid.get_N() * sl_grid.get_M(); n++ ){
        u_0[n] = - sl_grid.y_from_n(n);
        v_0[n] =   sl_grid.x_from_n(n);
    }
}

void SL_method::set_velocity_one_term(double &x0, double &y0) {
    // Velocity field is V(x,y) = (-y,x)
    // storing x0 and y0 to ensure they are not overridden
    double x1 = x0;
    double y1 = y0;

    // Evaluating the velocity field
    x0 = -y1;
    y0 =  x1;
}


void SL_method::find_departure(int n, double &x_d, double &y_d, double dt) {

    double x_0 = sl_grid.x_from_n(n);
    double y_0 = sl_grid.y_from_n(n);

    double x_star = x_0 - 0.5 * dt * vel_u[n];
    double y_star = y_0 - 0.5 * dt * vel_v[n];

    // interpolate vel_u, vel_v at (x_star, y_star)
    double vel_u_star = -y_star;
    double vel_v_star =  x_star;

    x_d = x_0 - dt * vel_u_star;
    y_d = y_0 - dt * vel_v_star;

    // std::cout << x_d << "     " << y_d << std::endl;
}


void SL_method::solve_advection(std::vector<double> &sol_0, double t0, double tf, double dt) {

    // Creating the velocity field used for the SL method
    vel_u.assign(sl_grid.get_N()*sl_grid.get_M(), 0.);
    vel_v.assign(sl_grid.get_N()*sl_grid.get_M(), 0.);
    set_velocity(vel_u, vel_v);

    // Initializing the departure point for the SL Method
    double xd = 0;
    double yd = 0;

//    std::cout << "Solving the SL Method for: " << std::endl;
//    std::cout << "t0 = " << t0 << std::endl;
//    std::cout << "tf = " << tf << std::endl;
//    std::cout << "dt = " << dt << std::endl << std::endl;

    // setting up number of iterations required to solve the SL method
    int max_itr = ceil((tf - t0) / (dt));
//    std::cout << "max_itr = " << max_itr << std::endl << std:: endl;

    // Running the SL method
    sol.assign(sl_grid.get_N()*sl_grid.get_M(), 0.);
    char name[250];
    for (int i = 1; i <= max_itr; i++) {

        //std::cout << "itr = " << i << "  tn = " << t0 + i * dt << "...";
        for (int n = 0; n < sl_grid.get_N() * sl_grid.get_M(); n++) {
            find_departure(n, xd, yd, dt);
            sol[n] = quadratic_interpolation(sl_grid, sol_0, xd, yd);
        }


        //std::cout << "done." << std::endl;
        sol_0 = sol;
        sprintf(name, "../sl_sol_N=%i_itr=%i.vtk", sl_grid.get_N(), i);
        sl_grid.print_VTK_format(name);
        sl_grid.print_VTK_format(sol, "Phi", name);
    }
    // std::cout << std::endl;
}
