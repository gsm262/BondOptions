//
//  Parameter.hpp
//  BondOptions
//
//  Created by George McWilliams on 10/25/15.
//  Copyright © 2015 George McWilliams. All rights reserved.
//

#ifndef Parameter_hpp
#define Parameter_hpp

#include <stdio.h>
#include <vector>

class ParameterBase {
    // Provides interface. No implementation required!
    
private:
    
public:
    ParameterBase() {};
    virtual ~ParameterBase() {};
    
    virtual double IntegrateOverTime(double t1, double t2) const = 0;
    virtual double IntegrateSquareOverTime(double t1, double t2) const = 0;
    virtual void UpdateParam(double t1, double t2, double val) = 0;
    virtual void PrintParams() const = 0;
    virtual ParameterBase* clone() const = 0;
};

class Parameter {
public:
    Parameter() : InnerObjectPtr(0) {};      // Perhaps don't need!
    Parameter(const Parameter& origHandle);
    Parameter(const ParameterBase& BaseObj);
    Parameter& operator=(const Parameter& origHandle);
    virtual ~Parameter();     // Virtual here?
    
    double IntegrateOverTime(double t1, double t2) const {return InnerObjectPtr->IntegrateOverTime(t1, t2);}
    double IntegrateSquareOverTime(double t1, double t2) const {return InnerObjectPtr->IntegrateSquareOverTime(t1, t2);}
    void UpdateParam(double t1, double t2, double val) {InnerObjectPtr->UpdateParam(t1, t2, val);}
    void PrintParams() const {InnerObjectPtr->PrintParams();};
    
private:
    ParameterBase* InnerObjectPtr;
};


class ParameterConstant : public ParameterBase {
    
public:
    
    ParameterConstant() {};
    ParameterConstant(double d1);
    
    // Virtual functions
    double IntegrateOverTime(double t1, double t2) const;
    double IntegrateSquareOverTime(double t1, double t2) const;
    void UpdateParam(double t1, double t2, double val);
    void PrintParams() const;
    ParameterBase* clone() const { return new ParameterConstant(*this); }
    
    
private:
    double ConstantParam;
    double ConstantParamSquared;
    
};


class ParameterPWLinear : public ParameterBase {
    
public:
    
    ParameterPWLinear() {};
    ParameterPWLinear(const std::vector<double>& LinearParam_,
                      const std::vector<double>& TimeVec_);
    
    // Virtual functions
    double IntegrateOverTime(double t1, double t2) const;
    double IntegrateSquareOverTime(double t1, double t2) const;
    void UpdateParam(double t1, double t2, double val);
    void PrintParams() const;
    ParameterBase* clone() const { return new ParameterPWLinear(*this); }
    
private:
    std::vector<double> LinearParam;
    std::vector<double> TimeVec;
    
    std::vector<double> LinearParamSquared;
    std::vector<double> CumulativeParam;
    std::vector<double> CumulativeParamSquared;
    
};

// Helper function
double PWLinearIntegrate(const std::vector<double>& LinearParam,
                         const std::vector<double>& TimeVec,
                         const double t1,
                         const double t2);







#endif /* Parameter_hpp */


