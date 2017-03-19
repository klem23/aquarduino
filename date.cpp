#include "date.h"

Date::Date(){
  type = TIME;
  
  h = 0;
  mn = 0;
  sec = 0;
}

Date::Date(uint8_t hour, uint8_t minute, uint8_t second){
       type = TIME;
  
       h = hour;
       mn = minute;
       sec= second; 
}

Date::Date(uint32_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second){
       type = DATE;
  
       y = year;
       m = month;
       d = day;
       h = hour;
       mn = minute;
       sec= second; 
}

void Date::set(int hour, int minute, int second){
       type = TIME;
  
       h = hour;
       mn = minute;
       sec= second; 
}

void Date::set(int year, int month, int day, int hour, int minute, int second){
       type = DATE;
  
       y = year;
       m = month;
       d = day;
       h = hour;
       mn = minute;
       sec= second; 
}

boolean Date::operator<(const Date& other){
  if((type == TIME)||(other.type == TIME)){
    if(h < other.h){
      return true;
    }else if(h > other.h){
      return false;
    }else if(mn < other.mn){
      return true;
    }else if(mn > other.mn){
      return false;
    }else if(sec < other.sec){
      return true;
    }else if(sec > other.sec){
      return false;
    }else{
     return false; 
    }
  }else{
    if(y < other.y){
      return true;
    }else if(y > other.y){
      return false;
    }else if(m < other.m){
      return true;
    }else if(m > other.m){
      return false;
    }else if(d < other.d){
      return true;
    }else if(d > other.d){
      return false;
    }else if(h < other.h){
      return true;
    }else if(h > other.h){
      return false;
    }else if(mn < other.mn){
      return true;
    }else if(mn > other.mn){
      return false;
    }else if(sec < other.sec){
      return true;
    }else if(sec > other.sec){
      return false;
    }else{
     return false; 
    }
  }
  
}

boolean Date::operator>(const Date& other){
  if((type == TIME)||(other.type == TIME)){
    if(h > other.h){
      return true;
    }else if(h < other.h){
      return false;
    }else if(mn > other.mn){
      return true;
    }else if(mn < other.mn){
      return false;
    }else if(sec > other.sec){
      return true;
    }else if(sec < other.sec){
      return false;
    }else{
     return false; 
    }
  }else{
    if(y > other.y){
      return true;
    }else if(y < other.y){
      return false;
    }else if(m > other.m){
      return true;
    }else if(m < other.m){
      return false;
    }else if(d > other.d){
      return true;
    }else if(d < other.d){
      return false;
    }else if(h > other.h){
      return true;
    }else if(h < other.h){
      return false;
    }else if(mn > other.mn){
      return true;
    }else if(mn < other.mn){
      return false;
    }else if(sec > other.sec){
      return true;
    }else if(sec < other.sec){
      return false;
    }else{
     return false; 
    }
  }
}

boolean Date::operator<=(const Date& other){
  if((*this < other)||(*this == other)){
    return true;
  }else{
    return false;
  }
}

boolean Date::operator>=(const Date& other){
  if((*this > other)||(*this == other)){
    return true;
  }else{
    return false;
  }
}

boolean Date::operator==(const Date& other){
  if((type == TIME)||(other.type == TIME)){
   if((h == other.h)&&(mn == other.mn)&&(sec == other.sec)){
     return true;
   }else{
     return false;
   }
  }else{
       if((y == other.y)&&(m == other.m)&&(d == other.d)&&(h == other.h)&&(mn == other.mn)&&(sec == other.sec)){
     return true;
   }else{
     return false;
   }
  } 
}

boolean Date::operator!=(const Date& other){
  if((type == TIME)||(other.type == TIME)){
   if((h == other.h)&&(mn == other.mn)&&(sec == other.sec)){
     return false;
   }else{
     return true;
   }
  }else{
       if((y == other.y)&&(m == other.m)&&(d == other.d)&&(h == other.h)&&(mn == other.mn)&&(sec == other.sec)){
     return false;
   }else{
     return true;
   }
  }
}

Date Date::operator+(uint32_t minutes){
   uint32_t tmp_mn = this->mn + minutes;
   uint8_t tmp_h = 0;
  
   tmp_h = tmp_mn / 60;
   tmp_mn = tmp_mn - tmp_h * 60;
  
   tmp_h += this->h;

   if(tmp_h >= 24){
     tmp_h -= 24;
   }
    
   if(this->type == TIME){
     return(Date(tmp_h, tmp_mn, this->sec));
   }else{
     return(Date(this->y, this->m, this->d, tmp_h, tmp_mn, this->sec));
   }
   
}

Date Date::operator-(uint32_t minutes){
   uint32_t tmp_mn;
   int8_t tmp_h;
   uint32_t tmp;
   
   
   if(this->mn > minutes){
     tmp_mn = this->mn - minutes;
     tmp_h = this->h;
   }else{
     tmp = minutes/ 60;
     tmp_h = this->h - tmp;
     if(this->mn > (minutes - tmp * 60)){
       tmp_mn = this->mn - (minutes - tmp * 60) ;
     }else{
       tmp_mn = this->mn - (60 - (minutes - tmp * 60));
       tmp_h--;
     }
   }
  
   if(tmp_h < 0){
     tmp_h = 24 - tmp_h; 
   }
  
   if(this->type == TIME){
     return(Date(tmp_h, tmp_mn, this->sec));
   }else{
     return(Date(this->y, this->m, this->d, tmp_h, tmp_mn, this->sec));
   }
}

uint32_t Date::operator-(Date other){
   uint32_t tmp_mn;
   uint32_t tmp_h;  
  
   if(this->mn > other.mn){
     return ((this->h - other.h)*60 + this->mn - other.mn);
   }else{
     return((this->h - other.h - 1)*60 + 60 - (other.mn - this->mn));
   }
}

Date Date::operator=(const Date& other){
    if((this->type == TIME)||(other.type == TIME)){
      this->h=other.h;
      this->mn=other.mn;
      this->sec=other.sec;
    }else{
      this->y=other.y;
      this->m=other.m;
      this->d=other.d;
      this->h=other.h;
      this->mn=other.mn;
      this->sec=other.sec;
    }
  
}
