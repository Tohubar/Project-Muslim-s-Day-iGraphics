#include <stdio.h>
#include <time.h>

char cTime[50], date[100];
int hour, m, sec;

void CurrentDateTime();

void CurrentDateTime(){
    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    //hr = localTime->tm_hour;

    hour = localTime->tm_hour;
    m = localTime->tm_min;
    sec = localTime->tm_sec;
    if(hour > 12) hour =hour - 12;
    if(hour == 0) hour = 12;
    
    sprintf(date, "%04d-%02d-%02d\n", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);
    sprintf(cTime, "%02d:%02d:%02d\n", hour, m, sec);
}


// int main(){
//     CurrentDateTime();
//     printf("%s", date);
// }
