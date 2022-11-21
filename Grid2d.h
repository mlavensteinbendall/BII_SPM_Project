//
// Created by Morgan Lavenstein Bendall on 11/15/22.
//

#ifndef BII_SPM_PROJECT_GRID2D_H
#define BII_SPM_PROJECT_GRID2D_H

#include <iostream>
#include <vector>

class Grid2d  {
    // Creating 2d grid
private:
    // Setting the grid based on the domain and resolution.
    double dx;
    double dy;
    long N;
    long M;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

public:
    double get_dx();
    double get_dy();

    double get_xmin();
    double get_xmax();
    double get_ymin();
    double get_ymax();

    // Constructor to create object
    Grid2d();

    //Constructor to initialize the values
    Grid2d(long NN, long MM, double xMin, double xMax, double yMin, double yMax);

    // getting indices from the grid position (grid is stored as a vector)
    long i_from_n(long n);
    long j_from_n(long n);

    // return vector position n from index (i, j)
    long n_from_ij(long i, long j);

    //Return position of x and y from the position n
    double x_from_n(long n);
    double y_from_n(long n);

    //Getting N and M
    long get_N();
    long get_M();

    // output file in VTK format
    void print_VTK_format(std::string output_file);
    void print_VTK_format(std::vector<double> &F, std::string data_name,
                          std::string file_name);
};

#endif //BII_SPM_PROJECT_GRID2D_H
