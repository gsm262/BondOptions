//
//  Test1.cpp
//  BondOptions
//
//  Created by George McWilliams on 12/27/15.
//  Copyright © 2015 George McWilliams. All rights reserved.
//

#include "Test1.hpp"

void Test1::testDate1() const{
    std::cout << "** Starting test of Date class**" << std::endl;
    
    Date d1;
    d1.set_day(1);
    d1.set_month(2);
    Date d2(28, 2, 2000);
    Date d3(28, 2, 2001);
    
    std::vector<Date> dateVec;
    
    std::cout << d2.day() << std::endl;
    std::cout << d2.month() << std::endl;
    std::cout << d2.year() << std::endl;
    std::cout << "d2 = " << d2 << std::endl;
    d2.add_month(24);
    std::cout << "After adding 24M, d2 = " << d2 << std::endl;
    d2.add_day(1);
    std::cout << "After adding 1 day, d2 = " << d2 << std::endl;
    d2.add_day(366);
    std::cout << "After adding 366 days, d2 = " << d2 << std::endl;
    
    dateVec.push_back(d1);
    dateVec.push_back(d2);
    dateVec.push_back(d3);
    //*
    for(size_t i=0; i<dateVec.size(); ++i) {
        std::cout << "d" << i+1 << " = " << ++dateVec[i] << std::endl;
    }
    
    /*
    std::vector<Date>::iterator it;
    for(std::vector<Date>::iterator it = dateVec.begin(); it < dateVec.end(); ++it) {
        std::cout << "d" << " = " << *it << std::endl;
    }
    //*/
    
    std::cout << "d1 > d2 is " << (d1 > d2) << std::endl;
    std::cout << "d2 > d3 is " << (d2 > d3) << std::endl;
    std::cout << "d3 > d1 is " << (d3 > d1) << std::endl;
    std::cout << "d1 < d2 is " << (d1 < d2) << std::endl;
    std::cout << "d2 < d3 is " << (d2 < d3) << std::endl;
    std::cout << "d3 < d1 is " << (d3 < d1) << std::endl;
    
    std::cout << "yearFrac(d2,d3) = " << yearFrac(d2,d3,1) << std::endl;
    
}

void Test1::testParam1() const{
    
    // Need to test:
    // - ParameterConstant and ParameterLinear return same values for cases where parameter is constant
    // -
    
    std::vector<Parameter> paramVec;
    
    ParameterConstant p1(10.0);
    
    std::vector<double> tVec;
    std::vector<double> pVec(5, 10.0);
    for(size_t i=0; i<5; ++i) {
        tVec.push_back(i+1);
    }
    
    ParameterPWLinear p2(pVec, tVec);
    
    paramVec.push_back(p1);
    paramVec.push_back(p2);
    
    for(size_t i=0; i<paramVec.size(); ++i) {
        paramVec[i].PrintParams();
        std::cout << "int param =" << paramVec[i].IntegrateOverTime(3.3, 9.4) << std::endl;
        std::cout << "int param^2 =" << paramVec[i].IntegrateSquareOverTime(3.3, 9.4) << std::endl;
        
        paramVec[i].UpdateParam(5.0, 10.0, 100);
        paramVec[i].PrintParams();
    }
    
    
}


void Test1::testYC1() const {
    std::cout << "** Starting test of Yield Curve class**" << std::endl;
    
    std::string inFile("/Users/GeorgeMcWilliams/Documents/Computing/C++/BondOptions/BondOptions/MMD_Rates.csv");
    //YieldCurve mmd1("..\MMD_Rates.csv");
    
    std::ifstream file(inFile.c_str());
    
    if(file.is_open()) {
        std::cout << "file is open!" << std::endl;
        file.close();
    } else {
        std::cout << "file is NOT open!" << std::endl;
    }
    
    YieldCurve y1(inFile);

    std::cout << "DF(0,10) = " << y1.getDf(0, 10) << std::endl;
    std::cout << "DF(1.5,9.2) = " << y1.getDf(1.5,9.2) << std::endl;
    
}


void Test1::getWorkingDir() const {
    
    char buffer[1000];
    char *answer = getcwd(buffer, sizeof(buffer));
    std::string s_cwd;
    if (answer)
    {
        std::cout << "Current dir = " << answer << std::endl;
    }

}

void Test1::testTextTable() const {
    
    std::string workingDir("/Users/GeorgeMcWilliams/Documents/Computing/C++/BondOptions/BondOptions");
    std::string inDir(workingDir + "/MMD_Rates.csv");
    TextTable mmdRates(inDir);
    mmdRates.readFile();
    mmdRates.print();
    
    // To test error...
    // std::vector<std::string> strVec1(mmdRates.retrieveVec("Rates2"));
    
}












