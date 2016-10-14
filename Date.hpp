//
//  Date.hpp
//  BondOptions
//
//  Created by George McWilliams on 12/27/15.
//  Copyright © 2015 George McWilliams. All rights reserved.
//

#ifndef Date_hpp
#define Date_hpp

#include <stdio.h>
#include <iostream>

class Date {
private:
    void fixDay();
    void fixMonth();
protected:
    int year_;
    int month_;
    int day_;
public:
    Date();
    Date(const int&, const int&, const int&);
    bool valid(void) const;
    int day() const;
    int month() const;
    int year() const;
    void set_day(const int&);
    void set_month(const int&);
    void set_year(const int&);
    void add_day(const int&);
    void add_month(const int&);
    void add_year(const int&);
    Date operator ++(); // prefix
    Date operator ++(int); // postfix
    Date operator --(); // prefix
    Date operator --(int); // postfix
};
bool operator == (const Date&, const Date&); // comparison operators
bool operator != (const Date&, const Date&);
bool operator < (const Date&, const Date&);
bool operator > (const Date&, const Date&);
bool operator <= (const Date&, const Date&);
bool operator >= (const Date&, const Date&);
std::ostream& operator << ( std::ostream& os, const Date& d); // output operator
double yearFrac(const Date&, const Date&, int);

#endif /* Date_hpp */

