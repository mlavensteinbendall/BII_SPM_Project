cmake_minimum_required(VERSION 3.23)
project(BII_SPM_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(BII_SPM_project
        main.cpp
        #structuredPop.cpp
        #structuredPop.h
        Grid2d.cpp
        Grid2d.h
        #SL_method.cpp
        #SL_method.h
        rapidcsv.h
        mathtools.cpp
        mathtools.h
        MortalityRate.csv
        )
