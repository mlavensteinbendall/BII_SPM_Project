//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//

#ifndef BII_SPM_PROJECT_MATHTOOLS_H
#define BII_SPM_PROJECT_MATHTOOLS_H

#include "Grid2d.h"
#include <vector>

double minmod_of_4_numbers (double a, double b, double c, double d);

double quadratic_interpolation(Grid2d & grid, std::vector<double> & func, double x, double y);

double norm_of_error(std::vector<double> &x_vec, std::vector<double> & y_vec);

double norm_of_error(std::vector<double> &x_vec, std::vector<double> &y_vec);


#endif //BII_SPM_PROJECT_MATHTOOLS_H
