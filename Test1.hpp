//
//  Test1.hpp
//  BondOptions
//
//  Created by George McWilliams on 12/27/15.
//  Copyright © 2015 George McWilliams. All rights reserved.
//

#ifndef Test1_hpp
#define Test1_hpp

#include <stdio.h>
#include <iterator>
#include <fstream>
#include "Date.hpp"
#include "Parameter.hpp"
#include "YieldCurve1.hpp"
#include "TextTable.hpp"
#include <unistd.h> // For getcwd function in getWorkingDir

class Test1 {
public:
    void testDate1() const;
    void testParam1() const;
    void testYC1() const;
    void getWorkingDir() const;
    void testTextTable() const;
};

#endif /* Test1_hpp */

