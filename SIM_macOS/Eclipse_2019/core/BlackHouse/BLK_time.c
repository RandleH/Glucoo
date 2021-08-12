
#include "BLK_time.h"


// @Template: 2020-02-23 13:45:00
volatile const char* __PST2BJT( const char YYYYMMDD_HHMMSS[20] ){
    //...//
    static char result[20] = {
        [0 ... 3]   = '0',
        [4]         = '-',
        [5 ... 6]   = '0',
        [7]         = '-',
        [8 ... 9]   = '0',
        [10]        = ' ',
        [11 ... 12] = '0',
        [13]        = ':',
        [14 ... 15] = '0',
        [16]        = ':',
        [17 ... 18] = '0',
        [19]        = '\0'
    };
    
    static const char mDay[12] = { 31,30,31,30,31,30,31,31,30,31,30,31};
    
    char* t = (char*)YYYYMMDD_HHMMSS;
    int year   = (t[0]-'0')*1000+(t[1]-'0')*100+(t[2]-'0')*10+(t[3]-'0');
    int month  = (t[5]-'0')*10 + (t[6]-'0');
    int day    = (t[8]-'0')*10 + (t[9]-'0');
    int hour   = (t[11]-'0')*10 + (t[12]-'0');
    int min    = (t[14]-'0')*10 + (t[15]-'0');
    int sec    = (t[17]-'0')*10 + (t[18]-'0');
    
#ifdef RH_DEBUG
    RH_ASSERT(t[19] == '\0');
#endif
    hour  += 15;
    day   += (hour  > 23);
    month += (day   > mDay[ (t[5]-'0')*10 + (t[6]-'0') - 1 ] );
    year  += (month > 12);
    
    if(hour > 23)
        hour -= 24;
    if(day  > mDay[ (t[5]-'0')*10 + (t[6]-'0') - 1 ] )
        day  = 0;
    if(month > 12)
        month -= 12;
    if(year > 9999)
        year = 0;
    
    
    result[0]  = (year/1000)   +'0';
    result[1]  = (year/100)%10+'0';
    result[2]  = (year/10)%10+'0';
    result[3]  = (year)%10+'0';
    
    result[5]  = (month/10)+'0';
    result[6]  = month%10+'0';
    
    result[8]  = (day/10)+'0';
    result[9]  = day%10+'0';
    
    result[11]  = (hour/10)+'0';
    result[12]  = hour%10+'0';
    
    result[14]  = (min/10)+'0';
    result[15]  = min%10+'0';
    
    result[17]  = (sec/10)+'0';
    result[18]  = sec%10+'0';
    
    return (volatile char*)result;
}
