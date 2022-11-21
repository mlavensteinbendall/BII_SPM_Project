//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//

#include "mathtools.h"
#include <cmath>
#include "Grid2d.h"
#include <vector>

// Function to find the minmod of 4 numbers
double minmod_of_4_numbers (double a, double b, double c, double d) {
    // Summing the signs of the numbers (positive = 0; negative = 1)
    int sum_of_signs = std::signbit(a) + std::signbit(b) + std::signbit(c) + std::signbit(d);
    switch (sum_of_signs) {
        // Case 1: all of the numbers are positive (sum_of_signs = 0)
        case 0:
            if (a < b && a < c && a < d) {
                return a;
            }
            else if (b < c && b < d) {
                return b;
            }
            else if (c < d) {
                return c;
            }
            else {
                return d;
            }

            // Case 2: all of the numbers are negative (sum_of_signs = 4)
        case 4:
            if (a > b && a > c && a > d) {
                return a;
            }
            else if (b > c && b > d) {
                return b;
            }
            else if (c > d) {
                return c;
            }
            else {
                return d;
            }

            // Default case: Not all numbers are the same sign
        default:
            return 0;
    }
}

// Function to compute the quadratic interpolation of a function at a point (x,y) using the minmod of the second derivative
double quadratic_interpolation(Grid2d & grid , std::vector<double> & func, double x, double y) {
    // Initialization necessary variables
    double phi;
    double dx = grid.get_dx();
    double dy = grid.get_dy();
    long i;
    long j;


    // Determining the cell C based on the location of x and y
    if ((x > grid.get_xmin() && x < grid.get_xmax()) && (y > grid.get_ymin() && y < grid.get_ymax())) {
        i = floor((x - grid.get_xmin()) / dx);
        j = floor((y - grid.get_ymin()) / dy);
    } else if ((x > grid.get_xmin() && x < grid.get_xmax()) && y >= grid.get_ymax()) {
        i = floor((x - grid.get_xmin()) / dx);
        j = grid.get_M() - 2;
    } else if ((x > grid.get_xmin() && x < grid.get_xmax()) && y <= grid.get_ymin()) {
        i = floor((x - grid.get_xmin()) / dx);
        j = 0;
    } else if (x >= grid.get_xmax() && (y > grid.get_ymin() && y < grid.get_ymax())) {
        i = grid.get_N() - 2;
        j = floor((y - grid.get_ymin()) / dy);
    } else if (x >= grid.get_xmax() && y >= grid.get_ymax()) {
        i = grid.get_N() - 2;
        j = grid.get_M() - 2;
    } else if (x >= grid.get_xmax() && y <= grid.get_ymin()) {
        i = grid.get_N() - 2;
        j = 0;
    } else if (x <= grid.get_xmin() && (y > grid.get_ymin() && y < grid.get_ymax())) {
        i = 0;
        j = floor((y - grid.get_ymin()) / dy);
    } else if (x <= grid.get_xmin() && y >= grid.get_ymax()) {
        i = 0;
        j = grid.get_M() - 2;
    } else if (x <= grid.get_xmin() && y <= grid.get_ymin()) {
        i = 0;
        j = 0;
    }
    // testing to see if the correct cell was found (the bottom left corner of the cell)
//     std::cout << "i = " << i << "   j = " << j << std::endl;


    // Compute the finite difference for phi_xx
    //func is phi
    double phixx_ij;
    double phixx_ip1j;
    double phixx_ijp1;
    double phixx_ip1jp1;

    double phiyy_ij;
    double phiyy_ip1j;
    double phiyy_ijp1;
    double phiyy_ip1jp1;

    // Getting phixx using second order finite difference
    // We do not want to have i = N or N-1 because that makes i + 1 terms fall outside of the grid.
    if (i > 0 && i < grid.get_N() - 2) {
        phixx_ij = (func[grid.n_from_ij(i - 1, j)] - 2 * func[grid.n_from_ij(i, j)] + func[grid.n_from_ij(i + 1, j)]) /
                   (dx * dx);
        phixx_ip1j =
                (func[grid.n_from_ij(i, j)] - 2 * func[grid.n_from_ij(i + 1, j)] + func[grid.n_from_ij(i + 2, j)]) /
                (dx * dx);
        phixx_ijp1 = (func[grid.n_from_ij(i - 1, j + 1)] - 2 * func[grid.n_from_ij(i, j + 1)] +
                      func[grid.n_from_ij(i + 1, j + 1)]) / (dx * dx);
        phixx_ip1jp1 = (func[grid.n_from_ij(i, j + 1)] - 2 * func[grid.n_from_ij(i + 1, j + 1)] +
                        func[grid.n_from_ij(i + 2, j + 1)]) / (dx * dx);
    } else if (i == 0) {
        phixx_ij = (2 * func[grid.n_from_ij(i, j)] - 5 * func[grid.n_from_ij(i + 1, j)] +
                    4 * func[grid.n_from_ij(i + 2, j)] - func[grid.n_from_ij(i + 3, j)]) / (dx * dx);
        phixx_ip1j =
                (func[grid.n_from_ij(i, j)] - 2 * func[grid.n_from_ij(i + 1, j)] + func[grid.n_from_ij(i + 2, j)]) /
                (dx * dx);
        phixx_ijp1 = (2 * func[grid.n_from_ij(i, j + 1)] - 5 * func[grid.n_from_ij(i + 1, j + 1)] +
                      4 * func[grid.n_from_ij(i + 2, j + 1)] - func[grid.n_from_ij(i + 3, j + 1)]) / (dx * dx);
        phixx_ip1jp1 = (func[grid.n_from_ij(i, j + 1)] - 2 * func[grid.n_from_ij(i + 1, j + 1)] +
                        func[grid.n_from_ij(i + 2, j + 1)]) / (dx * dx);
    } else if (i == grid.get_N() - 2) {
        phixx_ij = (func[grid.n_from_ij(i - 1, j)] - 2 * func[grid.n_from_ij(i, j)] + func[grid.n_from_ij(i + 1, j)]) /
                   (dx * dx);
        phixx_ip1j =
                (-func[grid.n_from_ij(i - 2, j)] + 4 * func[grid.n_from_ij(i - 1, j)] - 5 * func[grid.n_from_ij(i, j)] +
                 2 * func[grid.n_from_ij(i + 1, j)]) / (dx * dx);
        phixx_ijp1 = (func[grid.n_from_ij(i - 1, j + 1)] - 2 * func[grid.n_from_ij(i, j + 1)] +
                      func[grid.n_from_ij(i + 1, j + 1)]) / (dx * dx);
        phixx_ip1jp1 = (-func[grid.n_from_ij(i - 2, j + 1)] + 4 * func[grid.n_from_ij(i - 1, j + 1)] -
                        5 * func[grid.n_from_ij(i, j + 1)] + 2 * func[grid.n_from_ij(i + 1, j + 1)]) / (dx * dx);
    }

    // Getting phiyy using second order difference
    // We do not want to have j = M or M-1 because that makes j + 1 terms fall outside of the grid.
    if (j > 0 && j < grid.get_M() - 2) {
        phiyy_ij = (func[grid.n_from_ij(i, j - 1)] - 2 * func[grid.n_from_ij(i, j)] + func[grid.n_from_ij(i, j + 1)]) /
                   (dy * dy);
        phiyy_ip1j = (func[grid.n_from_ij(i + 1, j - 1)] - 2 * func[grid.n_from_ij(i + 1, j)] +
                      func[grid.n_from_ij(i + 1, j + 1)]) / (dy * dy);
        phiyy_ijp1 =
                (func[grid.n_from_ij(i, j)] - 2 * func[grid.n_from_ij(i, j + 1)] + func[grid.n_from_ij(i, j + 2)]) /
                (dy * dy);
        phiyy_ip1jp1 = (func[grid.n_from_ij(i + 1, j)] - 2 * func[grid.n_from_ij(i + 1, j + 1)] +
                        func[grid.n_from_ij(i + 1, j + 2)]) / (dy * dy);
    } else if (j == 0) {
        phiyy_ij = (2 * func[grid.n_from_ij(i, j)] - 5 * func[grid.n_from_ij(i, j + 1)] +
                    4 * func[grid.n_from_ij(i, j + 2)] - func[grid.n_from_ij(i, j + 3)]) / (dy * dy);
        phiyy_ip1j = (2 * func[grid.n_from_ij(i + 1, j)] - 5 * func[grid.n_from_ij(i + 1, j + 1)] +
                      4 * func[grid.n_from_ij(i + 1, j + 2)] - func[grid.n_from_ij(i + 1, j + 3)]) / (dy * dy);
        phiyy_ijp1 =
                (func[grid.n_from_ij(i, j)] - 2 * func[grid.n_from_ij(i, j + 1)] + func[grid.n_from_ij(i, j + 2)]) /
                (dy * dy);
        phiyy_ip1jp1 = (func[grid.n_from_ij(i + 1, j)] - 2 * func[grid.n_from_ij(i + 1, j + 1)] +
                        func[grid.n_from_ij(i + 1, j + 2)]) / (dy * dy);
    } else if (j == grid.get_M() - 2) {
        phiyy_ij = (func[grid.n_from_ij(i, j - 1)] - 2 * func[grid.n_from_ij(i, j)] + func[grid.n_from_ij(i, j + 1)]) /
                   (dy * dy);
        phiyy_ip1j = (func[grid.n_from_ij(i + 1, j - 1)] - 2 * func[grid.n_from_ij(i + 1, j)] +
                      func[grid.n_from_ij(i + 1, j + 1)]) / (dy * dy);
        phiyy_ijp1 =
                (-func[grid.n_from_ij(i, j - 2)] + 4 * func[grid.n_from_ij(i, j - 1)] - 5 * func[grid.n_from_ij(i, j)] +
                 2 * func[grid.n_from_ij(i, j + 1)]) / (dy * dy);
        phiyy_ip1jp1 = (-func[grid.n_from_ij(i + 1, j - 2)] + 4 * func[grid.n_from_ij(i + 1, j - 1)] -
                        5 * func[grid.n_from_ij(i + 1, j)] + 2 * func[grid.n_from_ij(i + 1, j + 1)]) / (dy * dy);
    }


    // Finding the minmod of phixx and phiyy
    double minmod_phixx = minmod_of_4_numbers(phixx_ij, phixx_ip1j, phixx_ijp1, phixx_ip1jp1);
    double minmod_phiyy = minmod_of_4_numbers(phiyy_ij, phiyy_ip1j, phiyy_ijp1, phiyy_ip1jp1);

    // std::cout << minmod_phixx << "      " << minmod_phiyy << std::endl;

    // Solving the interpolation problem

    double x_i = grid.get_xmin() + i * dx;
    double y_j = grid.get_ymin() + j * dy;
    double x_ip1 = x_i + dx;
    double y_jp1 = y_j + dy;

    phi  = func[grid.n_from_ij(i    ,   j)]  * ( x_ip1 - x   ) * ( y_jp1 - y   ) / (dx*dy) ;
    phi += func[grid.n_from_ij(i+1  ,   j)]  * ( x     - x_i ) * ( y_jp1 - y   ) / (dx*dy) ;
    phi += func[grid.n_from_ij(i    , j+1)]  * ( x_ip1 - x   ) * ( y     - y_j ) / (dx*dy) ;
    phi += func[grid.n_from_ij(i+1  , j+1)]  * ( x     - x_i ) * ( y     - y_j ) / (dx*dy) ;
    phi -= ((x - x_i) * (x_ip1 - x) * minmod_phixx) / 2;
    phi -= ((y - y_j) * (y_jp1 - y) * minmod_phiyy) / 2;

    return phi;
}

// Function to find the l-inf norm error of two vectors
double norm_of_error(std::vector<double> &x_vec, std::vector<double> & y_vec){
    long size_x_vec = x_vec.size();
    long size_y_vec = y_vec.size();

    if (size_x_vec != size_y_vec) {
        throw std::invalid_argument("ERROR: The two vectors are not the same size.");
    }
    double max_error = 0.;
    double error;
    int  max_error_n;
    for (int i = 0; i < size_x_vec; i++) {
        error = sqrt(pow(x_vec[i] - y_vec[i], 2));
        if (error > max_error) {
            max_error = error;
            max_error_n = i;
        }

    }
    // std::cout << "Problem is at n = " << max_error_n << std::endl;
    return max_error;
}
