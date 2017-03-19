#ifndef DATE_H
#define DATE_H

#include "Arduino.h"

#define TIME 0
#define DATE 1

class Date{

  public:
  
    uint32_t y;
    uint8_t m;
    uint8_t d;
    uint8_t h;
    uint8_t mn;
    uint8_t sec;
    
    uint8_t type;
  
    Date();
    Date(uint8_t hour, uint8_t minute, uint8_t second = 0);
    Date(uint32_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second = 0);
    
    void set(int hour, int minute, int second = 0);
    void set(int year, int month, int day, int hour, int minute, int second = 0);
    
    boolean operator<(const Date& other);
    boolean operator>(const Date& other);
    boolean operator<=(const Date& other);
    boolean operator>=(const Date& other);
    boolean operator==(const Date& other);
    boolean operator!=(const Date& other);
    
    Date operator+(uint32_t minutes);
    Date operator-(uint32_t minutes);
    uint32_t operator-(Date other);
    Date operator=(const Date& other);
};

#endif
