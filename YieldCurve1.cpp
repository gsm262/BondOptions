//
//  YieldCurve1.cpp
//  BondOptions
//
//  Created by George McWilliams on 1/18/16.
//  Copyright © 2016 George McWilliams. All rights reserved.
//

#include "YieldCurve1.hpp"


YieldCurve::YieldCurve(std::string filePath) {
    //*
    TextTable inTable(filePath);
    
    std::vector<double> yrsToMatVec;
    std::vector<double> ifrVec;
    
    std::cout << "TextTable is as follows:" << std::endl;
    inTable.print();
    std::vector<std:: string> matStrVec(inTable.retrieveVec("Maturities"));
    std::vector<std:: string> ifrStrVec(inTable.retrieveVec("IFR"));
    
    for(size_t i = 0; i < matStrVec.size(); ++i) {
        // NEED CAST HERE! (boost lexical cast)
        yrsToMatVec.push_back(string_to_double(matStrVec[i]));
        ifrVec.push_back(string_to_double(ifrStrVec[i]));
        
    }
    
    ifr = ParameterPWLinear(ifrVec, yrsToMatVec);
     //*/
    
}

double string_to_double( const std::string& s )
{
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0.0;
    return x;
}