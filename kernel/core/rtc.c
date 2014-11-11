/* Real Time Clock (Motorola MC146818) */

#include <types.h>
#include <io.h>
#include <rtc.h>

/* This function will return the current system date & time in the passed pointer parameters. 

   Note : The year is only 2 digits and the RTC is Real Time Clock  and donot confuse it with the Y2K problem.

   The Day of week problem is still unsolved
*/
void get_time(sys_time_t * system_time)
{
    /* Checking whether we can read the time now or not
    according to some documentation the MSB in Status A will
    remain 1 (invalid time) only a millisecond*/
    int time_out;
    
    outb(RTC_INDEX_REG, RTC_STATUS_A);    //check status - read access
    time_out=1000;
    while(inb(RTC_VALUE_REG) & 0x80)
        if(time_out< 0)
            return;
        else
            time_out--;
    
    outb(RTC_INDEX_REG, RTC_DAY);         //get day value
    system_time->day = inb(RTC_VALUE_REG);
    outb(RTC_INDEX_REG, RTC_MONTH);       //get month value
    system_time->month = inb(RTC_VALUE_REG);
    outb(RTC_INDEX_REG, RTC_YEAR);        //get year 
    system_time->year = inb(RTC_VALUE_REG);
    
    outb(RTC_INDEX_REG, RTC_DAY_OF_WEEK); //get day of week - **** problem
    system_time->day_of_week = inb(RTC_VALUE_REG);
    
    outb(RTC_INDEX_REG, RTC_SECOND);
    system_time->second = inb(RTC_VALUE_REG);
    outb(RTC_INDEX_REG, RTC_MINUTE);
    system_time->minute = inb(RTC_VALUE_REG);
    outb(RTC_INDEX_REG, RTC_HOUR);
    system_time->hour = inb(RTC_VALUE_REG);
    
    outb(RTC_INDEX_REG, RTC_STATUS_B);
    outb(RTC_VALUE_REG, 2);
    
    return;
}
/* Returns 0 on success and 1 on failue */
unsigned char set_time(sys_time_t * system_time)
{
    /* Checking whether we can read the time now or not
    according to some documentation the MSB in Status A will
    remain 1 (invalid time) only a millisecond*/
    int time_out;
    
    outb(RTC_INDEX_REG, RTC_STATUS_A);    //checking status -read access
    time_out=1000;
    while(inb(RTC_VALUE_REG) & 0x80)
        if (time_out< 0)
            return 1;
        else
            time_out--;
    
    outb(RTC_INDEX_REG, RTC_DAY);
    outb(RTC_VALUE_REG, system_time->day);
    outb(RTC_INDEX_REG, RTC_MONTH);
    outb(RTC_VALUE_REG, system_time->month);
    outb(RTC_INDEX_REG, RTC_YEAR);
    outb(RTC_VALUE_REG, system_time->year);

    outb(RTC_INDEX_REG, RTC_SECOND);
    outb(RTC_VALUE_REG, system_time->second);
    outb(RTC_INDEX_REG, RTC_MINUTE);
    outb(RTC_VALUE_REG, system_time->minute);
    outb(RTC_INDEX_REG, RTC_HOUR);
    outb(RTC_VALUE_REG, system_time->hour);

    return 0;
}
