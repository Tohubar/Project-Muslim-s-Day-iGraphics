#include <stdio.h>
#include <time.h>
#include <math.h>

char s[6][100];
int w[6][2];
char remainingTime[20];

int waqt_i;
int hr, mi, se;
int azantime = 0;

void checkWaqtTime();
void updateRemWaqtime();

void checkWaqtTime()
{
    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    hr = localTime->tm_hour;
    mi = localTime->tm_min;
    se = localTime->tm_sec;

    FILE *fp;
    fp = fopen("waqt_time.txt", "r");

    int i = 0;

    if (fp != NULL)
    {
        while (fgets(s[i], 100, fp))
        {
            sscanf(s[i], "%d:%d", &w[i][0], &w[i][1]);
            i++;
        }
    }
    else
        printf("Error loading data");
    fclose(fp);

    // printf("%d %d\n", w[5][0], w[5][1]);
    // printf("%d %d", hour, hr);

    if ((hr >= w[0][0] && hr <= w[5][0]))
    {
        if (hr == w[0][0] && mi < w[0][1])
            waqt_i = 4;
        else if (hr == w[5][0] && mi >= w[5][1])
            waqt_i = -1;
        else
            waqt_i = 0;
    }
    else if ((hr >= w[1][0] && hr <= w[2][0]))
    {
        if (hr == w[1][0] && mi < w[1][1])
            waqt_i = -1;
        else if (hr == w[2][0] && mi >= w[2][1])
            waqt_i = 2;
        else
            waqt_i = 1;
    }
    else if ((hr >= w[2][0] && hr <= w[3][0]))
    {
        if (hr == w[2][0] && mi < w[2][1])
            waqt_i = 1;
        else if (hr == w[3][0] && mi >= w[3][1])
            waqt_i = 3;
        else
            waqt_i = 2;
    }
    else if ((hr >= w[3][0] && hr <= w[4][0]))
    {
        if (hr == w[3][0] && mi < w[3][1])
            waqt_i = 2;
        else if (hr == w[4][0] && mi >= w[4][1])
            waqt_i = 4;
        else
            waqt_i = 3;
    }
    else if ((hr > w[5][0] && hr < w[1][0]))
    {
        waqt_i = -1;
    }
    else
        waqt_i = 4;

    if ((hr == w[0][0] && mi == w[0][1]) || (hr == w[1][0] && mi == w[1][1]) || (hr == w[2][0] && mi == w[2][1]) || (hr == w[3][0] && mi == w[3][1]) || (hr == w[4][0] && mi == w[4][1]))
        azantime = 1;
}

void updateRemWaqtime()
{
    if (waqt_i == 0)
    {
        sprintf(remainingTime, "%02d:%02d:%02d\n", w[5][0] - hr, abs(w[5][1] - mi), 60 - se);
    }
    else if (waqt_i == 1)
    {
        sprintf(remainingTime, "%02d:%02d:%02d\n", w[2][0] - hr, abs(w[2][1] - mi), 60 - se);
    }
    else if (waqt_i == 2)
    {
        sprintf(remainingTime, "%02d:%02d:%02d\n", w[3][0] - hr, abs(w[3][1] - mi), 60 - se);
    }
    else if (waqt_i == 3)
    {
        sprintf(remainingTime, "%02d:%02d:%02d\n", w[4][0] - hr, abs(w[4][1] - mi), 60 - se);
    }
    else if (waqt_i == 4)
    {
        int h;
        if (hr >= 0 && hr <= w[0][0])
            h = w[0][0] - hr;
        else
            h = 24 - hr + w[0][0];

        int nT = h * 3600 + (w[0][1] - mi) * 60 - se;
        int hh = nT / 3600;
        nT %= 3600;
        int mm = nT / 60;
        nT %= 60;
        int ss = nT;
        sprintf(remainingTime, "%02d:%02d:%02d\n",hh, mm, ss);
    }
}

// int main()
// {
//     checkWaqtTime();
//     printf("\n%d", waqt_i);
// }