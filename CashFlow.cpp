//
//  CashFlow.cpp
//  BondOptions
//
//  Created by George McWilliams on 9/25/16.
//  Copyright © 2016 George McWilliams. All rights reserved.
//

#include "CashFlow.hpp"

CashFlow::CashFlow(Date effectiveDate_,
                   Date maturity_,
                   double coupon_,
                   double face_,
                   int freq_,
                   double annPrepayRate_
                   ): currentRow(0) {
    
    double matYears = yearFrac(effectiveDate_, maturity_, 1);
    nRows = floor(static_cast<double>(freq_)*matYears);
    
    double yfLoop, intLoop, prinLoop, factLoop;
    for(size_t i=0; i<nRows; ++i) {
        yfLoop = matYears - (nRows - i)*freq_;
        cfVec.push_back(IndividualCashFlow(yfLoop, intLoop, prinLoop, factLoop));
    }
}