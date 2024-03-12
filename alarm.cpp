
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
//#include "iGraphics.h"

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib")



int setAlarm(int hour, int mi, int se)
{
    int hh, mm, ss;

    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    // hr = localTime->tm_hour;

    hh = localTime->tm_hour;
    mm = localTime->tm_min;
    ss = localTime->tm_sec;

    int h, m, s, H, M, S, x = 0, flag = 0;
    // printf("Enter current time now in 24 hrs format [HH:MM:SS]: ");
    // scanf("%d%d%d",&H,&M,&S);

    H = hh;
    M = mm;
    S = ss;

    h = hour;
    m = mi;
    s = se;

    if (h < 24 && m < 60 && s < 60 && H < 24 && M < 60 && S < 60)
    {
        while (1)
        {
            if (H == h && M == m && S == s)
            {
                return 1;
            }
             
            system("cls");
            printf("%d:%d:%d", H, M, S);
            Sleep(1000);
            S++;
            if (S == 60)
            {
                S = 0;
                M++;
            }
            if (M == 60)
            {
                M = 0;
                H++;
            }
            if (H == 24)
            {
                H = 0;
            }
             
        }
    }
    else
    {
        printf("\n\n!!!!!Invalid_time_format_check_It\a!!!!!\n\n");
    }
}

int main()
{
    int h, m, s;

    printf("Set alarm[HH:MM:SS]: ");
    scanf("%d%d%d", &h, &m, &s);

    int i = setAlarm(h, m, s);
    if(i == 1){
       printf("Alarm is ringing");
    }

    return 0;
}