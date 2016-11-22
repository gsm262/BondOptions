//
//  CashFlow.hpp
//  BondOptions
//
//  Created by George McWilliams on 9/25/16.
//  Copyright © 2016 George McWilliams. All rights reserved.
//

#ifndef CashFlow_hpp
#define CashFlow_hpp

#include <stdio.h>
#include <vector>
#include "math.h"
#include "Date.hpp"

class IndividualCashFlow {
    friend class CashFlow;
public:
    IndividualCashFlow(double yearFrac_,
                       double interest_,
                       double principle_,
                       double factor_):
    yearFrac(yearFrac_),
    interest(interest_),
    principle(principle_),
    factor(factor_)
    {}
    
    const double get_YearFrac()   {return(yearFrac);}
    const double get_Interest()   {return(interest);}
    const double get_Principle()  {return(principle);}
    const double get_Factor()     {return(factor);}
    const double get_TotalCash()  {return(interest + principle);}
private:
    double yearFrac;
    double interest;
    double principle;
    double factor; // % of original Face left outstanding
};

// To do:
// - Implement iterator for CashFlow class (basically just a wrapper for vector iterator
// - Separate floating and fixed interest?

class CashFlow {
public:
    CashFlow(std::vector<double> yearFracs_,
             std::vector<double> interests_,
             std::vector<double> principles_,
             std::vector<double> factors_); // Don't know if we need this constructor...
    CashFlow(Date effectiveDate_,
             Date maturity_,
             double coupon_,
             double face_,
             int freq_,
             double annPrepayRate_
             );
    
    IndividualCashFlow& GetNextCf();
    IndividualCashFlow& GetPreviousCf();
    void print();
    
private:
    /*
    std::vector<double> YearFrac;
    std::vector<double> Interest;
    std::vector<double> Principle;
    std::vector<double> Factor; // % of original Face left outstanding
    */
    
    std::vector<IndividualCashFlow> cfVec;
    
    size_t nRows;
    size_t currentRow;
};

#endif /* CashFlow_hpp */
