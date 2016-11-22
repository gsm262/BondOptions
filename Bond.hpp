//
//  Bond.hpp
//  BondOptions
//
//  Created by George McWilliams on 9/25/16.
//  Copyright © 2016 George McWilliams. All rights reserved.
//

#ifndef Bond_hpp
#define Bond_hpp

#include <stdio.h>
#include <vector>
#include "CashFlow.hpp"
#include "Date.hpp"
#include "YieldCurve1.hpp"

class BondBase {
public:
    BondBase();
    virtual ~BondBase() {};
    
    virtual double PriceFromYield(YieldCurve yc_);
    virtual double PriceFromYield(double ytm_);
    virtual double YieldFromPrice(double Price);
    virtual double YieldFromPrice(double Price, YieldCurve yc_);    // Z- yield
    virtual double OasFromPrice(double Price, YieldCurve yc_);
    virtual std::vector<double> GetOAanalytics(double Price, YieldCurve yc_);    // Get OA Yield, OAS, OAD
    // Note: may need to take Pricing Engine input! (eg curve/rate simulator)
    
private:
    CashFlow cf;
    Date maturity;
    double price;
    int freq;
    double faceValue;
    
    //CallSchedule cs;  // NEED TO IMPLEMENT CALL SCHEDULE - to be used in OA analytics
};

class Bond {
    Bond();
    double PriceFromYield(YieldCurve yc_) {return innerBond->PriceFromYield(yc_);}
    double PriceFromYield(double ytm_) {return innerBond->PriceFromYield(ytm_);}
    double YieldFromPrice(double Price) {return innerBond->YieldFromPrice(Price);}
    double YieldFromPrice(double Price, YieldCurve yc_) {return innerBond->YieldFromPrice(Price, yc_);}
    double OasFromPrice(double Price, YieldCurve yc_) {return innerBond->OasFromPrice(Price, yc_);}
    std::vector<double> GetOAanalytics(double Price, YieldCurve yc_) {return innerBond->GetOAanalytics(Price, yc_);}
    
private:
    BondBase* innerBond;
};


class FixedNonCall: public BondBase{
    
    
};





#endif /* Bond_hpp */
