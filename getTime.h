#include <stdio.h>
#include <stdlib.h>

char prayT[5][100];
char sun[2][20];

void updateTime();
void pTime();
void sunSR();
void playAzan();

void updateTime() {
   system("python c2.py");
    
}

 

void pTime()
{

	FILE *fp;
	fp = fopen("prayer_time.txt", "r");
	int i = 0;
	if (fp != NULL)
	{
		while (fgets(prayT[i], 100, fp))
		{
			i++;
		}
	}
	else
		printf("Error loading prayer_time");
	fclose(fp);
}

void sunSR()
{
	FILE *fp;
	fp = fopen("sunrise_sunset.txt", "r");
	int i = 0;
	if(fp != NULL)
	{
		while(fgets(sun[i], 20, fp))
		{
			i++;
		}
	}
	else printf("Error Loading sunrise_sunset");
	fclose(fp);
}
// int main()
// {
// 	updateTime();
// }