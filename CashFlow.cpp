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
    double freqD = static_cast<double>(freq_);
    nRows = ceil(freqD*matYears);
    
    double yfLoop, yfLoopPrev(0), intLoop, prinLoop, factLoop(1), factLoopPrev(1);
    
    for(size_t i=0; i<nRows; ++i) {
        yfLoop      = matYears - (nRows - i - 1)/freqD;
        intLoop     = coupon_*face_*factLoop*(yfLoop - yfLoopPrev);        ///freqD;
        factLoop    = factLoop*(1 - (yfLoop-yfLoopPrev)*annPrepayRate_);
        prinLoop    = (factLoopPrev - factLoop)*face_;
        //prinLoop    = face_*factLoop*(annPrepayRate_/freq_);
        //factLoop    -= prinLoop/face_;
        if(i == nRows - 1) {
            // Add remaining principle to prinLoop
            prinLoop += factLoop*face_;
        }
        cfVec.push_back(IndividualCashFlow(yfLoop, intLoop, prinLoop, factLoop));
        yfLoopPrev      = yfLoop;
        factLoopPrev    = factLoop;
    }
}

void CashFlow::print() {
    std::cout << "n\tYearfrac\tInterest\tPrinciple\tFactor" << std::endl;
    for(size_t i=0; i<nRows; ++i) {
        std::cout << i << "\t"
        << cfVec[i].get_YearFrac() << "\t\t"
        << cfVec[i].get_Interest() << "\t\t"
        << cfVec[i].get_Principle() << "\t\t"
        << cfVec[i].get_Factor() << std::endl;
    }
}

