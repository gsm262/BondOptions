//
//  YieldCurve1.hpp
//  BondOptions
//
//  Created by George McWilliams on 1/18/16.
//  Copyright © 2016 George McWilliams. All rights reserved.
//

#ifndef YieldCurve1_hpp
#define YieldCurve1_hpp

#include <stdio.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "TextTable.hpp"
#include "Parameter.hpp"

class YieldCurve {
public:
    YieldCurve(std::string filePath);   // Currently, only constructor is path to file that contains ifrs already
    
    double getDf(double t1, double t2) { return exp(-ifr.IntegrateOverTime(t1,t2)); }
    
private:
    Parameter ifr;
    
};

// Utility function
double string_to_double( const std::string& s );



#endif /* YieldCurve1_hpp */

