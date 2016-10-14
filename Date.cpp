//
//  Date.cpp
//  BondOptions
//
//  Created by George McWilliams on 12/27/15.
//  Copyright © 2015 George McWilliams. All rights reserved.
//

#include "Date.hpp"

///////////////////////////// construction //////////
Date::Date(const int& d, const int& m, const int& y) {
    day_ = d;
    month_ = m;
    year_ = y; // this assumes year_ is given fully, not Y2K corrections
};
///////////////////////////// inline definitions //////////
Date::Date(){ year_= 0; month_= 0; day_= 0;}
int Date::day() const { return day_; }
int Date::month() const { return month_; }
int Date::year() const { return year_; }
void Date::set_day (const int& day) { Date::day_= day; }
void Date::set_month(const int& month) { Date::month_= month; }
void Date::set_year(const int& year) { Date::year_= year; }
bool Date::valid() const {
    // This function will check the given Date is valid or not.
    // If the Date is not valid then it will return the value false.
    // Need some more checks on the year, though
    if (year_<0) return false;
    if (month_>12 || month_<1) return false;
    if (day_>31 || day_<1) return false;
    if ((day_==31 &&
         ( month_==2 || month_==4 || month_==6 || month_==9 || month_==11) ) )
        return false;
    if ( day_==30 && month_==2) return false;
    if ( year_<2000){
        if ((day_==29 && month_==2) && !((year_-1900)%4==0)) return false;
    }
    if ( year_>2000){
        if ((day_==29 && month_==2) && !((year_-2000)%4==0)) return false;
    }
    return true;
}

void Date::fixDay() {
// Note: assumes month_, year_ are valid and day_>0
    while(!this->valid()) {
        if (day_>31) {
            day_ -= 31;
            month_ += 1;
        }
        if ((day_==31 &&
             ( month_==2 || month_==4 || month_==6 || month_==9 || month_==11) ) ) {
            day_ -= 30;
            month_ += 1;
        }
        if ( day_==30 && month_==2) {
            day_ -= 29;
            month_ += 1;
        }
        if ( year_<2000){
            if ((day_==29 && month_==2) && !((year_-1900)%4==0)) {
                day_ -= 28;
                month_ += 1;
            }
        }
        if ( year_>2000){
            if ((day_==29 && month_==2) && !((year_-2000)%4==0)) {
                day_ -= 28;
                month_ += 1;
            }
        }
        this->fixMonth();
    }
    
}

void Date::fixMonth() {
    while(month_ > 12) {
        month_ -= 12;
        year_ += 1;
    }
}

void Date::add_day(const int& dayInc) {
    if(this->valid()) {
        day_ += dayInc;
        this->fixDay();
    } else {
        // Throw error: invalid date
    }
}

void Date::add_month(const int& monthInc) {
    if(this->valid()) {
        month_ += monthInc;
        this->fixMonth();
    } else {
        // Throw error: invalid date
    }
}
void Date::add_year(const int& yearInc) { Date::year_+= yearInc; }

// Helper functions for increment/decrement operators
inline Date next_Date(const Date& d){
    Date ndat;
    if (!d.valid()) { return ndat; };
    ndat=Date((d.day()+1),d.month(),d.year()); if (ndat.valid()) return ndat;
    ndat=Date(1,(d.month()+1),d.year()); if (ndat.valid()) return ndat;
    ndat = Date(1,1,(d.year()+1)); return ndat;
}
inline Date previous_Date(const Date& d){
    Date ndat;
    if (!d.valid()) { return ndat; }; // return zero
    ndat = Date((d.day()-1),d.month(),d.year()); if (ndat.valid()) return ndat;
    ndat = Date(31,(d.month()-1),d.year()); if (ndat.valid()) return ndat;
    ndat = Date(30,(d.month()-1),d.year()); if (ndat.valid()) return ndat;
    ndat = Date(29,(d.month()-1),d.year()); if (ndat.valid()) return ndat;
    ndat = Date(28,(d.month()-1),d.year()); if (ndat.valid()) return ndat;
    ndat = Date(31,12,(d.year()-1)); return ndat;
}

Date Date::operator ++(int){ // postfix operator
    Date d = *this;
    *this = next_Date(d);
    return d;
}

Date Date::operator ++(){ // prefix operator
    *this = next_Date(*this);
    return *this;
}

Date Date::operator --(int){ // postfix operator, return current value
    Date d = *this;
    *this = previous_Date(*this);
    return d;
}

Date Date::operator --(){ // prefix operator, return new value
    *this = previous_Date(*this);
    return *this;
}

bool operator == (const Date& d1,const Date& d2){
    // check for equality
    if (!d1.valid()) { return false; };
    if (!d2.valid()) { return false; };
    if ( (d1.day()==d2.day())
        && (d1.month()==d2.month())
        && (d1.year()==d2.year())) {
        return true;
    };
    return false;
}
bool operator !=(const Date& d1, const Date& d2){
    return !(d1==d2);
}
bool operator < (const Date& d1, const Date& d2){
    if (!d1.valid()) { return false; }; // not meaningful, return anything
    if (!d2.valid()) { return false; }; // should really be an exception, but ?
    if (d1.year()<d2.year()) { return true;}
    else if (d1.year()>d2.year()) { return false;}
    else { // same year
        if (d1.month()<d2.month()) { return true;}
        else if (d1.month()>d2.month()) { return false;}
        else { // same month
            if ( d1.day()<d2.day()) { return true;}
            else { return false; }
        }
    }
    return false;
}

bool operator > (const Date& d1, const Date& d2) {
    if (d1==d2) { return false;}; // this is strict inequality
    if (d1<d2) { return false; };
    return true;
}

bool operator <=(const Date& d1, const Date& d2){
    if (d1==d2) { return true; }
    return (d1<d2);
}

bool operator >=(const Date& d1, const Date& d2) {
    if (d1==d2) { return true;};
    return (d1>d2);
};

inline long long_Date(const Date& d) {
    if (d.valid()){ return d.year() * 10000 + d.month() * 100 + d.day(); };
    return -1;
};

std::ostream & operator << (std::ostream& os, const Date& d){
    if (d.valid()) { os << long_Date(d); }
    else { os << "invalid Date"; };
    return os;
}

double yearFrac(const Date& d1, const Date& d2, int dayCount) {
    
    // To do:
    // - implement different dayCount schemes
    
    double yearInc = d2.year() - d1.year();
    double monthInc = d2.month() - d1.month();
    double dayInc = d2.day() - d1.day();
    
    return (yearInc + monthInc/12 + dayInc/365.25);
}





