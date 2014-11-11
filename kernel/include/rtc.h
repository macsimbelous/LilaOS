/* Real Time Clock (Motorola MC146818) */
#ifndef _RTC_H
#define _RTC_H

//Регистры команд RTC
#define RTC_INDEX_REG 0x70
#define RTC_VALUE_REG 0x71

//редистры данных RTC
#define RTC_SECOND 0
#define RTC_MINUTE 2
#define RTC_HOUR   4

#define RTC_DAY_OF_WEEK  6

#define RTC_DAY   7
#define RTC_MONTH 8
#define RTC_YEAR  9

#define RTC_STATUS_A 0x0A
#define RTC_STATUS_B 0x0B
#define RTC_STATUS_C 0x0C
#define RTC_STATUS_D 0x0D

struct _sys_time_t
{
    unsigned short year; 
    unsigned short month; 
    unsigned short day_of_week; 
    unsigned short day; 
    unsigned short hour; 
    unsigned short minute; 
    unsigned short second; 
    unsigned short milliseconds; 
}; 
typedef struct _sys_time_t sys_time_t;

void get_time(sys_time_t * system_time);
unsigned char set_time(sys_time_t * system_time);
 
#endif
