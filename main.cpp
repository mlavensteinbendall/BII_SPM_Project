#include <iostream>
#include <vector>
#include <fstream>
#include "rapidcsv.h"

using namespace std;


int main() {

        rapidcsv::Document doc("/Users/morganlavensteinbendall/Documents/Math_233/BII-StructedPopModel/MortalityRate.csv", rapidcsv::LabelParams(0, -1));

        std::vector<double> close = doc.GetColumn<double>("Mortality Rate");
        std::cout << "Read " << close.size() << " values." << std::endl;

        for (int i = 0; i < close.size(); i++){
            cout << "t = " << i+1 << ": " << close[i] << endl;
        }

    return 0;
}
