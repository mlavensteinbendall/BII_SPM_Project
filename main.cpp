#include <iostream>
#include <vector>
#include <fstream>
//#include "rapidcsv.h"

using namespace std;


int main() {

    ifstream myFile;
    myFile.open("/Users/morganlavensteinbendall/Documents/Math_233/BII-StructedPopModel/MortalityRate.csv");

    if(myFile.is_open())
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    while(myFile.good()) {
        string line;
        getline(myFile, line, ',');
        cout << line << endl;
    }

//    vector<vector<string>> content;
//    fstream file ("MortalityRate.csv", ios::in);
//    string line, word;
//    vector<string> row;
//
//    if(file.is_open())
//    {
//        while(getline(file, line))
//        {
//            row.clear();
//
//            stringstream str(line);
//
//            while(getline(str, word, ','))
//                row.push_back(word);
//            content.push_back(row);
//        }
//    }
//    else
//        cout<<"Could not open the file\n";
//
//    for(int i=0;i<content.size();i++)
//    {
//        for(int j=0;j<content[i].size();j++)
//        {
//            cout<<content[i][j]<<" ";
//        }
//        cout<<"\n";
//    }

//    ifstream inFile;
//    vector<double> mu_ind;
//    double rate;
//
//    // Open an existing file
//    inFile.open("MortalityRate.csv", ios::in);
//
//    // Get the roll number
//    // of which the data is required
//    int rollnum, roll2, count = 0;
//    cout << "Enter the roll number "
//         << "of the student to display details: ";
//    cin >> rollnum;
//
//    // Read the Data from the file
//    // as String Vector
//    // vector<double> mu_ind;
//    string line, word, temp;

//    for (int i = 0; i < 91, i++) {
//
//        mu_ind[i] = 0;
//
//    }
//
//    while (inFile >> temp) {
//
//        mu_ind.clear();
//
//        // read an entire row and
//        // store it in a string variable 'line'
//        getline(inFile, line);
//
//        // used for breaking words
//        stringstream s(line);
//
//        // read every column data of a row and
//        // store it in a string variable, 'word'
//        while (getline(s, word, ', ')) {
//
//            // add all the column data
//            // of a row to a vector
//            mu_ind.push_back(word);
//        }
//
//    }
//    if (count == 0)
//        cout << "Record not found\n";


//        rapidcsv::Document doc("MortalityRate.csv", rapidcsv::LabelParams(0, -1));
//
//        std::vector<double> close = doc.GetRow<double>("Mortality Rate");
//        std::cout << "Read " << close.size() << " values." << std::endl;




//    inFile.open("MortalityRate.csv");
//    if (inFile.is_open()) {
//        cout << "File has been opened" << endl;
//    }
//    else {
//        cout << "NO FILE HAS BEEN OPENED" << endl;
//    }
//
//    while (!inFile.eof()) {
//        inFile >> rate;
//        cout << "Rate: " << rate << endl;
//    }
//    inFile.close();
//   // for (int i = 0; )


    return 0;
}
