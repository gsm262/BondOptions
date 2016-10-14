//
//  TextTable.cpp
//  BondOptions
//
//  Created by George McWilliams on 9/11/16.
//  Copyright © 2016 George McWilliams. All rights reserved.
//

#include "TextTable.hpp"



void TextTable::readFile() {
    
    std::string line, word;
    std::ifstream myfile(fileName.c_str());
    
    // Reset internal variables
    headerVec.clear();
    headerVecMap.clear();
    nRows = 0;
    
    if (myfile.is_open())
    {
        // Populate headerVec first
        if(getline(myfile, line, '\r')) {
            std::istringstream ss(line);
            vecStrTyp emptyVec;
            while(getline (ss, word, delim)) {
                headerVec.push_back(word);
                std::pair<std::string, vecStrTyp> pairIn(word, emptyVec);
                headerVecMap.insert(pairIn);
            }
        }
        
        while ( getline (myfile, line, '\r') )
        {
            std::istringstream ss(line);
            int colCount(0);
            while(getline (ss, word, delim)) {
                headerVecMap[headerVec[colCount]].push_back(word);
                ++colCount;
            }
            ++nRows;
        }
        myfile.close();
    }
}


void TextTable::print() const {
    for(vecStrTyp::const_iterator i=headerVec.begin(); i!=headerVec.end(); ++i) {
        std::cout << *i << '\t';
    }
    std::cout << std::endl;

    int rowNum;
    
    while(rowNum < nRows) {
        for(int i=0; i<headerVec.size(); ++i) {
            std::cout << headerVecMap.at(headerVec[i])[rowNum] << '\t';
        }
        std::cout << std::endl;
        ++rowNum;
    }
}


std::vector< std::string> TextTable::retrieveVec(const std::string& header_) const {
    headerVecMapType::const_iterator search = headerVecMap.find(header_);
    
    if(search == headerVecMap.end()) {
        //std::string errStr(header_+" not contained in map!");
        std::cout << header_+" not contained in map!" << std::endl;
        std::cout << "Keys in Map are as follows:" << std::endl;
        for(search = headerVecMap.begin(); search != headerVecMap.end(); ++ search) {
            std::cout << "\t" << search->first << std::endl;
        }
        std::cout << "TextTable is as follows:" << std::endl;
        this->print();
        throw header_+" not contained in map!";
    }
    return(search->second);
}







