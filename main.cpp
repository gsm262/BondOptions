//
//  main.cpp
//  BondOptions
//
//  Created by George McWilliams on 10/25/15.
//  Copyright © 2015 George McWilliams. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "parameter.hpp"
#include "Date.hpp"
#include "Test1.hpp"
#include "TextTable.hpp"
#include "YieldCurve1.hpp"

#include <unistd.h>

int main(int argc, const char * argv[]) {
    std::string workingDir("/Users/GeorgeMcWilliams/Documents/Computing/C++/BondOptions/BondOptions");
    //*
    Test1 t1;
    t1.testYC1();
    t1.testTextTable();
    //*/
    
    
    // Test TextTable
    /*
    TextTable mmdRates(inDir);
    mmdRates.readFile();
    mmdRates.print();
     */
    
    
    //YieldCurve y1(inDir);
    
    return 0;
}







