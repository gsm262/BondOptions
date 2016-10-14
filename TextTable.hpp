//
//  TextTable.hpp
//  BondOptions
//
//  Created by George McWilliams on 9/11/16.
//  Copyright © 2016 George McWilliams. All rights reserved.
//

#ifndef TextTable_hpp
#define TextTable_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

class TextTable {
    
private:
    typedef std::vector< std::string> vecStrTyp;
    typedef std::map<std::string, vecStrTyp> headerVecMapType;  // Vector needs to change to vector* so retrieveVec can return reference
    
    headerVecMapType headerVecMap;
    std::vector<std::string> headerVec;
    std::string fileName;
    char delim;
    int nRows;
    
public:
    TextTable(std::string fileName_, char delim_=','): fileName(fileName_), delim(delim_) { this->readFile();};
    void readFile();
    void print() const;
    
    vecStrTyp retrieveVec(const std::string& header_) const;
};


#endif /* TextTable_hpp */

