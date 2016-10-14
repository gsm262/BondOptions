//
//  Parameter.cpp
//  BondOptions
//
//  Created by George McWilliams on 10/25/15.
//  Copyright © 2015 George McWilliams. All rights reserved.
//

#include "Parameter.hpp"
#include <iostream>


// ---------------------------------------------------
// Parameter

//Parameter::Parameter() : InnerObjectPtr(0) {}

Parameter::Parameter(const Parameter& origHandle) {
    InnerObjectPtr = origHandle.InnerObjectPtr->clone();
}

Parameter::Parameter(const ParameterBase& BaseObj) {
    InnerObjectPtr = BaseObj.clone();
}

Parameter& Parameter::operator=(const Parameter& origHandle) {
    
    if(&origHandle != this) {
        delete InnerObjectPtr;
        InnerObjectPtr = origHandle.InnerObjectPtr->clone();
    }
    return *this;
}

Parameter::~Parameter() {
    delete InnerObjectPtr;
}

// ---------------------------------------------------
// ParameterConstant

ParameterConstant::ParameterConstant(double d1) : ConstantParam(d1) {
    ConstantParamSquared = ConstantParam*ConstantParam;
}

double ParameterConstant::IntegrateOverTime(double t1, double t2) const {
    return(ConstantParam*(t2 - t1));
}

double ParameterConstant::IntegrateSquareOverTime(double t1, double t2) const {
    return(ConstantParamSquared*(t2 - t1));
}

void ParameterConstant::UpdateParam(double t1, double t2, double val) {
    ConstantParam = val/(t2-t1);
    ConstantParamSquared = ConstantParam*ConstantParam;
}

void ParameterConstant::PrintParams() const {
    std::cout << "Constant Parameter" << std::endl;
    std::cout << " - param = " << ConstantParam << std::endl;
    std::cout << " - param^2 = " << ConstantParamSquared << std::endl;
}

// ---------------------------------------------------
// ParameterPWLinear

ParameterPWLinear::ParameterPWLinear(const std::vector<double>& LinearParam_, const std::vector<double>& TimeVec_) : LinearParam(LinearParam_), TimeVec(TimeVec_) {
    
    LinearParamSquared.resize(LinearParam.size());
    
    for(size_t i=0; i<LinearParam.size(); ++i) {
        LinearParamSquared[i] = LinearParam[i]*LinearParam[i];
    }
}

double ParameterPWLinear::IntegrateOverTime(double t1, double t2) const {
    return(PWLinearIntegrate(LinearParam, TimeVec, t1, t2));
}

double ParameterPWLinear::IntegrateSquareOverTime(double t1, double t2) const {
    return(PWLinearIntegrate(LinearParamSquared, TimeVec, t1, t2));
}

void ParameterPWLinear::UpdateParam(double t1, double t2, double val) {
// Note:
// - val = integral(t1, t2)
    
    // Assumes t2 > last element in TimeVec
    double lastTime = TimeVec.back();
    if(t2 <= lastTime) {
        // Throw error
        std::cout << "**ParameterPWLinear: Throw error here. t2 must be > lastTime!" << std::endl;
    }
    double lastIntegral = IntegrateOverTime(t1, lastTime);
    double param_t2 = 2*(val - lastIntegral)/(t2 - lastTime) - LinearParam.back();
    
    TimeVec.push_back(t2);
    LinearParam.push_back(param_t2);
    LinearParamSquared.push_back(param_t2*param_t2);
    
}

void ParameterPWLinear::PrintParams() const {
    size_t len = TimeVec.size();
    std::cout << "PW linear Parameter" << std::endl;
    std::cout << " - timeVec = [";
    for(size_t i = 0; i < len; ++i) {
        std::cout << TimeVec[i] << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << " - paramVec = [";
    for(size_t i = 0; i < len; ++i) {
        std::cout << LinearParam[i] << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << " - paramVec^2 = [";
    for(size_t i = 0; i < len; ++i) {
        std::cout << LinearParamSquared[i] << ", ";
    }
    std::cout << "]" << std::endl;
}


// End of class

// ---------------------------------------------------
// Helper functions

// Integrater
double PWConstIntegrate(const std::vector<double>& PWConstParam,
                         const std::vector<double>& TimeVec,
                         const double t1,
                         const double t2) {
    
    // First get start and end index
    size_t ind1 = 0;
    size_t ind2 = TimeVec.size() - 1;
    
    for(size_t i = 0; i < TimeVec.size() - 1; ++i) {
        if(t1 >= TimeVec[i] & t1 <= TimeVec[i+1])
            ind1 = i;
        
        if(t2 >= TimeVec[i] & t2 <= TimeVec[i+1]) {
            ind2 = i;
            break;
        }
        
    }
    
    // Perform integration
    double cumSum = 0;
    if(ind1 == ind2) {
        cumSum += PWConstParam[ind1]*(t2 - t1);
    } else {
        // End points
        cumSum += PWConstParam[ind1]*(TimeVec[ind1+1] - t1);
        cumSum += PWConstParam[ind2]*(t2 - TimeVec[ind2]);
        
        for(size_t i = ind1 + 1; i < ind2; ++i) {
            cumSum += PWConstParam[i]*(TimeVec[i+1] - TimeVec[i]);
        }
    }
    return(cumSum);
}

double PWLinearIntegrate(const std::vector<double>& LinearParam,
                         const std::vector<double>& TimeVec,
                         const double t1,
                         const double t2) {
    
    // First get start and end index
    size_t ind1 = 0;
    size_t ind2 = TimeVec.size() - 1;
    
    for(size_t i = 0; i < TimeVec.size() - 1; ++i) {
        if(t1 >= TimeVec[i] & t1 <= TimeVec[i+1])
            ind1 = i;
        
        if(t2 >= TimeVec[i] & t2 <= TimeVec[i+1]) {
            ind2 = i;
            break;
        }
    }
    
    // Perform integration
    double cumSum = 0;
    if(ind1 == ind2) {
        if(ind1 == 0) {
            cumSum += LinearParam[ind1]*(t2 - t1);  // Constant parameter
        } else {
            
        }
    } else {
        // End points
        cumSum += LinearParam[ind1]*(TimeVec[ind1+1] - t1);
        cumSum += LinearParam[ind2]*(t2 - TimeVec[ind2]);
        
        for(size_t i = ind1 + 1; i < ind2; ++i) {
            cumSum += LinearParam[i]*(TimeVec[i+1] - TimeVec[i]);
        }
    }
    return(cumSum);
}


// Linear interpolation

std::vector<double> LinearInterp(const std::vector<double>& xIn,
                                 const std::vector<double>& yIn,
                                 const std::vector<double>& xOut,
                                 size_t extrap) {
    // extrap=0 => const extrapolation
    // extrap=1 => linear extrapolation
    std::vector<double> yOut(xOut.size(), 0.0);
    
    //size_t ind1 = 0;
    size_t ind2 = xIn.size() - 1;
    
    for(size_t i = 0; i < xOut.size(); ++i) {
        // First find index in xIn
        ind2 = xIn.size() - 1;
        for(size_t jj = 0; jj < xIn.size() ; ++jj) {
            if(xIn[jj] >= xOut[i]) {
                ind2 = jj;
                break;
            }
        }
        
        // Deal with extrapolation
        
        if(extrap == 0 && ind2 == 0) { // Left-side extrap
                yOut.push_back(yIn[0]);
        } else if(extrap == 0 && xIn[ind2] < xOut[i]) {    // Right-side extrap
            yOut.push_back(yIn[ind2]);
        } else {
        
            // Interpolation (or linear extrap)
            yOut.push_back(yIn[ind2-1]
                           + (yIn[ind2] - yIn[ind2-1])*
                                (xOut[i] - xIn[ind2-1])/(xIn[ind2] - xIn[ind2-1]));
        }
    }
    return yOut;
}



// Need to:
// - Cache results (using CsumulativeParam)
// - Provide a way to add parameters
// - Provide a way to update parameters























