#include "iGraphics.h"
#include "getTime.h"
#include "clock.h"
#include "waqt.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#pragma  comment(lib, "winmm.lib")

#define HEIGHT    750
#define WIDTH     700
#define azanUrl   "audio/Mevlan Kurtishi - Adhan.wav"
#define buttonUrl "audio/button click2.wav"

int alarmTimerIndex;
int azanTimerIndex;
int repeatAlarmIndex;
int alarmTimeDiff;
int aH, aM, aS;
int Year, Month, Day;
int r, g, b;

int y            = 650;
int img_i        = 0;
int sura_i       = -1;
int h1           = 0;
int m1           = 0;
int se1          = 0;
int repeatFlag   = 0;
int getAlarmTime = 0;
int ringAzan     = 0;
int ringAlarm    = 0;
int aF           = 0;
int alF          = 0;
int strIndex     = 0;
int pm           = 0;
int am           = 0;
int setClick     = 0;
int resetClick   = 0;
int pBoxR        = 75;
int pBoxG        = 135;
int pBoxB        = 95;
int todayFlag    = 1;
int nextPrevFlag = 0;
int playIndex    = 0;
int surah_y      = 50;
int settingClick = 0;
int alarmSelect  = 0;
int saveClick    = 0;
int buttonClick  = 1;
int on           = 1;
int off          = 0;

char alarmTime[20];
char alarmTimerStr[20];
char aT[20];
char showDate[20];
char image[2][100]     = {"Resources/BG.bmp", "Resources/settingPic.bmp"};
char surahImg[5][100]  = {"Resources/al fatihah sh yn design.bmp"};
char sura_title[5][50] = {"Resources/Ftitle.bmp"};
char waqt[5][10]       = {"  Fajr", " Dhuhr", "    Asr", "Maghrib", "   Isha"};
char surahName[5][10]  = {"Al-Fatiha", "Yaseen", "Ar-Rahman", "Al-Falaq", "Al-Naas"};
char surahUrl[5][100]  = {"audio/Surah Al Fatiha.wav", "audio/036 Surah Yasin.wav", "audio/Surah Ar-Rahman.wav", "audio/Surah Falaq.wav", "audio/114 Surah An Nas.wav"};
char alarmUrl[3][60]   = {"audio/Laa ilaha ilallah.wav", "audio/Assalatu Khairum Minan Naum.wav", "audio/Islamic ringtone.wav"};

void drawSurahPage();
void drawPrayerTimeBox();
void drawCheckWaqtBox();
void drawAlarmBox();
void playAlarm();
void alarmRepeat();
void isAzantime();
void alarmFunction();
void alarmTimer(int t);
void alarmSetFunction();
void aSetClick();
void alarmResetFunction();
void aResetClick();
void alarmDismissF();
void musicPlay();
void drawSurahTitle();
void writeDateInTxt();
void todayPrayertime();
void nextDayPrayerTime();
void previousDayPrayerTime();
void settingPage();
void drawSettingPage();
void buttonSoundF();

void iDraw()
{
	iClear();
	updateTime();
	pTime();
	sunSR();
	CurrentDateTime();
	writeDateInTxt();
	updateRemWaqtime();
	checkWaqtTime();

	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 700, 750);

	iShowBMP(0, 0, image[0]);
	// sun set sun rise box
	iSetColor(0, 0, 0);
	iFilledRectangle(5, 670, 200, 60);
	// prayer time box
	iSetColor(pBoxR, pBoxG, pBoxB);
	iFilledRectangle(390, 445, 280, 295);
	if (todayFlag)
		iSetColor(0, 250, 5);
	else
		iSetColor(20, 20, 20);
	iFilledRectangle(460, 700, 147, 35);
	// date time box
	iSetColor(0, 0, 5);
	iFilledEllipse(310, 400, 80, 40, 100);

	// Check waqt block
	iFilledEllipse(307, 690, 70, 50);
	iSetColor(255, 255, 255);
	iText(250, 700, "Current Waqt", GLUT_BITMAP_HELVETICA_18);
	// draw setting button
	iShowBMP(320, 100, "Resources/settingButton2.bmp");

	drawAlarmBox();
	musicPlay();

	if (waqt_i != -1)
	{
		drawCheckWaqtBox();
	}
	else
	{
		iSetColor(255, 20, 100);
		iText(265, 663, "No Waqt", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	drawPrayerTimeBox();
	drawSurahTitle();

	isAzantime();
	if (ringAzan == 1 && aF == 0)
	{
		azanTimerIndex = iSetTimer(1000, playAzan);
		aF++;
		iSetColor(100, 50, 10);
		iText(240, 420, "Playing....", GLUT_BITMAP_HELVETICA_18);
		iShowBMP(240, 380, "Resources/azan(call to prayer).bmp");
	}

	if (settingClick)
		drawSettingPage();
}

void buttonSoundF()
{
	if (buttonClick)
		PlaySound(TEXT(buttonUrl), NULL, SND_FILENAME | SND_ASYNC);
}

void drawSettingPage()
{

	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 700, 750);

	iShowBMP(75, 0, image[1]);

	iSetColor(130, 130, 130);
	iFilledRectangle(530, 20, 80, 30);
	iSetColor(40, 10, 20);
	iText(537, 27, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(25, 200, 250);
	iRectangle(95, 60, 227, 192);
	iSetColor(190, 160, 180);
	iText(100, 220, "ALARM RINGTONE", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(100, 200, 140);
	iLine(95, 210, 322, 210);
	iSetColor(80, 100, 80);
	if (saveClick)
		iSetColor(200, 200, 200);
	iFilledRectangle(260, 65, 55, 25);
	iSetColor(250, 250, 250);
	if (saveClick)
		iSetColor(0, 0, 0);
	if (saveClick)
		iText(267, 73, "SAVED", GLUT_BITMAP_HELVETICA_12);
	else
		iText(263, 70, "SAVE", GLUT_BITMAP_HELVETICA_18);

	iSetColor(240, 20, 50);
	iCircle(125, 180, 15, 100);
	iCircle(125, 140, 15, 100);
	iCircle(125, 100, 15, 100);

	iSetColor(10, 0, 20);
	if (alarmSelect == 0)
		iSetColor(250, 250, 250);
	iFilledCircle(125, 180, 13, 100);
	iSetColor(10, 0, 20);
	if (alarmSelect == 1)
		iSetColor(250, 250, 250);
	iFilledCircle(125, 140, 13, 100);
	iSetColor(10, 0, 20);
	if (alarmSelect == 2)
		iSetColor(250, 250, 250);

	iFilledCircle(125, 100, 13, 100);
	iSetColor(20, 250, 100);
	iText(150, 172, "ALARM 1", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(150, 132, "ALARM 2", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(150, 92, "ALARM 3", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(200, 230, 180);
	iText(430, 220, "CLICK SOUND", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(25, 200, 250);
	iRectangle(420, 210, 182, 40);

	iSetColor(230, 160, 50);
	iText(432, 170, "ON", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(230, 160, 50);
	iText(430, 130, "OFF", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(20, 250, 10);
	if (on == 0)
		iSetColor(255, 255, 255);
	iFilledCircle(502, 177, 12, 100);
	iFilledCircle(560, 177, 12, 100);
	iFilledRectangle(502, 165, 58, 25);
	if (on)
	{
		iSetColor(250, 10, 100);
		iFilledCircle(558, 177, 12, 100);
	}
	else
	{
		iSetColor(20, 10, 10);
		iFilledCircle(504, 177, 12, 100);
	}

	iSetColor(20, 250, 10);
	if (off == 0)
		iSetColor(255, 255, 255);
	iFilledCircle(502, 137, 12, 100);
	iFilledCircle(560, 137, 12, 100);
	iFilledRectangle(502, 125, 58, 25);
	if (off)
	{
		iSetColor(250, 10, 100);
		iFilledCircle(558, 137, 12, 100);
	}
	else
	{
		iSetColor(20, 10, 10);
		iFilledCircle(504, 137, 12, 100);
	}
}
void settingPage()
{
	settingClick = 1;
}

void todayPrayertime()
{
	sscanf(date, "%d-%d-%d", &Year, &Month, &Day);
	strcpy(showDate, date);
	todayFlag = 1;
	nextPrevFlag = 0;

	pBoxR = 75;
	pBoxG = 135;
	pBoxB = 95;
}
void nextDayPrayerTime()
{
	Day++;
	if (Month == 2 && Day > 29)
	{
		Month++;
		Day = 1;
	}
	else if (Day > 30)
	{
		Month++;
		Day = 1;
	}
	if (Month > 12)
	{
		Year++;
		Month = 1;
		Day = 1;
	}

	sprintf(showDate, "%04d-%02d-%02d", Year, Month, Day);
	todayFlag = 0;
	nextPrevFlag++;

	if (nextPrevFlag > 0)
	{
		pBoxR = 120;
		pBoxG = 100;
		pBoxB = 120;

		pBoxR -= 5;
		pBoxG += 5;
		pBoxB += 5;

		if (pBoxR <= 50)
			pBoxR = 80;
		if (pBoxG >= 160)
			pBoxG = 120;
		if (pBoxB <= 50)
			pBoxB = 90;

		r = pBoxR;
		g = pBoxG;
		b = pBoxB;
	}
}
void previousDayPrayerTime()
{
	Day--;
	if (Day < 1)
	{
		Month--;
		if (Month == 2)
			Day = 29;
		else
			Day = 30;
	}
	if (Month < 1)
	{
		Year--;
		Month = 12;
		Day = 30;
	}

	sprintf(showDate, "%04d-%02d-%02d", Year, Month, Day);
	todayFlag = 0;
	nextPrevFlag--;

	if (nextPrevFlag < 0)
	{
		pBoxR = 200;
		pBoxG = 120;
		pBoxB = 100;

		pBoxR -= 5;
		pBoxG += 5;
		pBoxB += 5;

		if (pBoxR <= 50)
			pBoxR = 100;
		if (pBoxG >= 250)
			pBoxG = 140;
		if (pBoxB <= 50)
			pBoxB = 100;

		r = pBoxR;
		g = pBoxG;
		b = pBoxB;
	}
}

void writeDateInTxt()
{
	FILE *fp = fopen("dateTxt.txt", "w");
	fprintf(fp, "%d-%02d-%d", Year, Month, Day);
	fclose(fp);
}

void aSetClick()
{
	setClick = 1;
	resetClick = 0;
	getAlarmTime = 0;
	strIndex = 0;

	alarmFunction();
	strcpy(alarmTime, " ");
	alarmTimerIndex = iSetTimer(alarmTimeDiff * 1000, playAlarm);
}

void aResetClick()
{
	resetClick = 1;
	setClick = 0;
	getAlarmTime = 0;
	am = 0;
	pm = 0;
	strIndex = 0;
	strcpy(alarmTime, " ");
	h1 = 0;
	m1 = 0;
	se1 = 0;
	ringAlarm = 0;
	// PlaySound(NULL, NULL, 0);
}

void alarmDismissF()
{
	resetClick = 1;
	setClick = 0;
	getAlarmTime = 0;
	am = 0;
	pm = 0;
	strIndex = 0;
	strcpy(alarmTime, " ");
	h1 = 0;
	m1 = 0;
	se1 = 0;
	ringAlarm = 0;
	iPauseTimer(repeatAlarmIndex);
	PlaySound(NULL, NULL, 0);
}

void playAzan()
{
	PlaySound(TEXT(azanUrl), NULL, SND_FILENAME | SND_ASYNC);
	ringAzan = 1;
	iPauseTimer(azanTimerIndex);
}

void alarmTimer(int t)
{
	if (t < 0)
		t = 0;
	aH = t / 3600;
	t %= 3600;
	aM = t / 60;
	t %= 60;
	aS = t;
}
void alarmFunction()
{
	sscanf(alarmTime, "%d:%d:%d", &h1, &m1, &se1);
	sprintf(aT, "%02d:%02d:%02d", h1, m1, se1);

	int s1;
	int s2;

	if (hr < 12)
	{
		if (am)
		{
			s1 = h1 * 3600 + m1 * 60 + se1;
			s2 = hr * 3600 + mi * 60 + se;
			alarmTimeDiff = s1 - s2;
			if (alarmTimeDiff < 0)
				alarmTimeDiff *= -1;

			if (s1 < s2)
				alarmTimeDiff = 24 * 3600 - alarmTimeDiff;

			alarmTimer(alarmTimeDiff);
		}

		if (pm)
		{
			s1 = h1 * 3600 + m1 * 60 + se1;
			s2 = (12 - hr) * 3600 + (60 - mi) * 60 + 60 - se;
			alarmTimeDiff = s1 + s2;

			alarmTimer(alarmTimeDiff);
		}
	}

	else if (hr == 12)
	{
		if (am)
		{
			s1 = h1 * 3600 + m1 * 60 + se1;
			s2 = hr * 3600 + mi * 60 + se;

			alarmTimeDiff = 24 * 3600 - (s2 - s1);

			alarmTimer(alarmTimeDiff);
		}
		if (pm)
		{
			int h0 = h1;
			if (h0 == 12)
				h0 = 0;
			s1 = h0 * 3600 + m1 * 60 + se1;
			s2 = mi * 60 + se;

			alarmTimeDiff = s1 - s2;
			if (alarmTimeDiff < 0)
				alarmTimeDiff *= -1;

			if (s1 < s2)
				alarmTimeDiff = 24 * 3600 - alarmTimeDiff;

			alarmTimer(alarmTimeDiff);
		}
	}
	 
	else
	{
		if (pm)
		{
			int h0 = h1;
			if (h0 == 12)
				h0 = 0;
			s1 = h0 * 3600 + m1 * 60 + se1;
			s2 = (hr - 12) * 3600 + mi * 60 + se;

			alarmTimeDiff = s2 - s1;
			if (alarmTimeDiff < 0)
				alarmTimeDiff *= -1;

			if (s1 < s2)
				alarmTimeDiff = 24 * 3600 - alarmTimeDiff;
			alarmTimer(alarmTimeDiff);
		}
		if (am)
		{
			int h0 = h1;
			if (h0 == 12)
				h0 = 0;

			s1 = h0 * 3600 + m1 * 60 + se1;
			s2 = (24 - hr) * 3600 + (60 - mi) * 60 + 60 - se;
			alarmTimeDiff = s1 + s2;

			alarmTimer(alarmTimeDiff);
		}
	}
}

void alarmRepeat()
{
	if (repeatFlag < 4)
	{
		PlaySound(TEXT(alarmUrl[alarmSelect]), NULL, SND_FILENAME | SND_ASYNC);
	}
	else
		iPauseTimer(repeatAlarmIndex);

	repeatFlag++;
}

void playAlarm()
{
	PlaySound(TEXT(alarmUrl[alarmSelect]), NULL, SND_FILENAME | SND_ASYNC);
	ringAlarm = 1;
	repeatAlarmIndex = iSetTimer(36000, alarmRepeat);
	iPauseTimer(alarmTimerIndex);
}
void isAzantime()
{
	if ((hr == w[0][0] && mi == w[0][1]) || (hr == w[1][0] && mi == w[1][1]) || (hr == w[2][0] && mi == w[2][1]) || (hr == w[3][0] && mi == w[3][1]) || (hr == w[4][0] && mi == w[4][1]))
		ringAzan = 1;
}

void drawSurahPage()
{

	iShowBMP(0, 0, image[1]);
	iSetColor(r, g, b);
	iFilledRectangle(20, 700, 100, 40);
	iSetColor(255, 0, 5);
	iText(30, 710, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);

	iShowBMP(20, 600, sura_title[0]);

	if (sura_i)
	{
		iShowBMP(300, 400, surahImg[0]);
	}
}

void drawPrayerTimeBox()
{
	if (todayFlag)
		iSetColor(55, 30, 40);
	else
		iSetColor(200, 150, 160);
	iText(470, 710, showDate, GLUT_BITMAP_TIMES_ROMAN_24);

	// Showing namaj waqt name and time
	iSetColor(255, 255, 255);
	iText(400, 665, prayT[0], GLUT_BITMAP_HELVETICA_18);

	iText(400, 615, prayT[1], GLUT_BITMAP_HELVETICA_18);

	iText(400, 565, prayT[2], GLUT_BITMAP_HELVETICA_18);

	iText(400, 515, prayT[3], GLUT_BITMAP_HELVETICA_18);

	iText(400, 465, prayT[4], GLUT_BITMAP_HELVETICA_18);

	iSetColor(30, 70, 60);
	iLine(390, 690, 390 + 280, 690);
	iLine(390, 650, 390 + 280, 650);
	iLine(390, 640, 390 + 280, 640);
	iLine(390, 600, 390 + 280, 600);
	iLine(390, 590, 390 + 280, 590);
	iLine(390, 550, 390 + 280, 550);
	iLine(390, 540, 390 + 280, 540);
	iLine(390, 500, 390 + 280, 500);
	iLine(390, 490, 390 + 280, 490);
	iLine(390, 450, 390 + 280, 450);

	iSetColor(160, 160, 160);
	iFilledRectangle(390, 360, 280, 75);
	iShowBMP(604, 370, "Resources/rightArr2.bmp");
	iShowBMP(400, 370, "Resources/leftArr2.bmp");

	iSetColor(130, 130, 130);
	iFilledRectangle(490, 370, 70, 30);
	iSetColor(0, 0, 0);
	iRectangle(490, 370, 70, 30);

	iSetColor(20, 100, 150);
	iText(463, 410, "Change Date", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(100, 50, 130);
	iText(492, 378, "TODAY", GLUT_BITMAP_HELVETICA_18);

	// Sunset Sunrise text
	iSetColor(250, 255, 55);
	iText(30, 710, sun[0], GLUT_BITMAP_HELVETICA_18);

	iSetColor(255, 200, 255);
	iText(30, 680, sun[1], GLUT_BITMAP_HELVETICA_18);

	iSetColor(0, 255, 2);
	iText(495 - 230, 395, cTime, GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(210, 210, 215);
	if (hr < 12)
		iText(580 - 230, 410, "AM", GLUT_BITMAP_HELVETICA_12);
	else
		iText(580 - 230, 410, "PM", GLUT_BITMAP_HELVETICA_12);

	 
}

void drawCheckWaqtBox()
{
	if (todayFlag)
	{
		iSetColor(34, 25, 20);
		iFilledRectangle(390, y - 50 * waqt_i, 280, 40);
	}
	iSetColor(255, 20, 100);
	iText(265, 663, waqt[waqt_i], GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(40, 10, 20);
	iFilledRectangle(238, 595, 141, 30);
	iSetColor(200, 50, 170);
	iText(245, 605, "Remaining Time", GLUT_BITMAP_HELVETICA_18);
	iSetColor(230, 230, 230);
	iFilledRectangle(260, 550, 100, 40);
	iSetColor(0, 0, 0);
	iText(269, 562, remainingTime, GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawAlarmBox()
{
	iSetColor(200, 120, 50);
	iFilledRectangle(390, 50, 280, 300);

	iSetColor(150, 150, 150);
	iFilledRectangle(430, 300, 200, 45);
	iSetColor(5, 5, 10);
	iText(440, 315, "SET AN ALARM", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(170, 170, 170);
	iFilledRectangle(395, 210, 270, 80);
	iSetColor(50, 5, 10);
	iText(400, 265, "(HH:MM:SS)  AM/PM", GLUT_BITMAP_HELVETICA_18);

	iSetColor(0, 0, 0);
	iLine(588, 210, 588, 290);
	iLine(395, 250, 588, 250);

	iSetColor(5, 5, 10);
	iFilledRectangle(400, 215, 110, 30);
	if (getAlarmTime)
	{
		iSetColor(255, 0, 5);
		iRectangle(399, 213, 113, 33);
	}
	iSetColor(0, 255, 0);
	iText(410, 225, alarmTime, GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(200, 25, 200);
	iRectangle(517, 215, 30, 30);
	iRectangle(550, 215, 30, 30);

	iSetColor(0, 255, 200);
	if (am)
	{
		iFilledRectangle(517, 217, 29, 27);
	}

	if (pm)
	{
		iFilledRectangle(550, 217, 29, 27);
	}

	iSetColor(55, 30, 40);
	if (setClick)
		iSetColor(0, 200, 25);
	iFilledRectangle(595, 250, 60, 35);
	iSetColor(255, 30, 40);
	if (setClick)
		iSetColor(20, 10, 200);
	iText(604, 259, "SET", GLUT_BITMAP_TIMES_ROMAN_24);

	if (setClick)
	{
		if (h1 == 0)
		{
			PlaySound(NULL, NULL, 0);
			iSetColor(20, 20, 150);
			iText(400, 150, "Please. Set Time for Alarm...", GLUT_BITMAP_HELVETICA_18);
		}

		else
			alarmSetFunction();
	}

	iSetColor(255, 0, 0);
	if (resetClick)
		iSetColor(0, 0, 200);
	iFilledRectangle(592, 217, 68, 22);
	iSetColor(0, 0, 0);
	iText(596, 221, "RESET", GLUT_BITMAP_HELVETICA_18);
}

void alarmSetFunction()
{

	sprintf(alarmTimerStr, "%02d:%02d:%02d", aH, aM, aS);
	iSetColor(200, 150, 150);
	iFilledRectangle(395, 160, 270, 40);
	iSetColor(10, 10, 5);
	iText(400, 175, "ALARM TIME=> ", GLUT_BITMAP_HELVETICA_18);
	iSetColor(0, 25, 200);
	iText(535, 172, aT, GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0, 25, 200);
	if (am)
		iText(625, 172, "AM", GLUT_BITMAP_TIMES_ROMAN_24);
	if (pm)
		iText(625, 172, "PM", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(200, 150, 150);
	iFilledRectangle(395, 110, 270, 40);

	if (ringAlarm)
	{
		iSetColor(20, 20, 170);
		iText(430, 125, "....RINGING ALARM....", GLUT_BITMAP_HELVETICA_18);

		iSetColor(25, 10, 20);
		iFilledRectangle(470, 60, 103, 35);
		iSetColor(255, 40, 20);
		iText(475, 70, "DISMISS", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else
	{
		iSetColor(100, 10, 120);
		iText(400, 125, "Remaining Time ->", GLUT_BITMAP_HELVETICA_18);

		iSetColor(0, 0, 0);
		iText(565, 122, alarmTimerStr, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	Sleep(1000);
	alarmTimeDiff--;
	alarmTimer(alarmTimeDiff);
}

void iMouseMove(int mx, int my)
{
}

void musicPlay()
{

	iShowBMP(15, 280, "Resources/playbackControl.bmp");
	if (playIndex)
		iShowBMP(78, 278, "Resources/play2.bmp");
}
void drawSurahTitle()
{
	iSetColor(150, 80, 140);
	iFilledRectangle(5, 340, 200, 325);

	iShowBMP(15, 627, "Resources/surahBoxTitle.bmp");

	iSetColor(30, 70, 60);
	iRectangle(35, 360, 140, 240);

	iSetColor(30, 10, 160);
	iLine(35, 560, 175, 560);
	iLine(35, 550, 175, 550);
	iLine(35, 510, 175, 510);
	iLine(35, 500, 175, 500);
	iLine(35, 460, 175, 460);
	iLine(35, 450, 175, 450);
	iLine(35, 410, 175, 410);
	iLine(35, 400, 175, 400);

	if (sura_i != -1)
	{
		iSetColor(20, 20, 20);
		iFilledRectangle(33, 560 - surah_y * sura_i + 1, 143, 39);
	}

	iSetColor(10, 205, 150);
	iText(60, 575, surahName[0], GLUT_BITMAP_HELVETICA_18);
	iText(60, 525, surahName[1], GLUT_BITMAP_HELVETICA_18);
	iText(60, 475, surahName[2], GLUT_BITMAP_HELVETICA_18);
	iText(60, 425, surahName[3], GLUT_BITMAP_HELVETICA_18);
	iText(60, 375, surahName[4], GLUT_BITMAP_HELVETICA_18);
}
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
 
		// Alarm click start
		if (mx >= 400 && mx <= 510 && my >= 215 && my <= 245)
		{
			if (on)
				buttonSoundF();
			if (getAlarmTime == 0)
				getAlarmTime = 1;
			else
				getAlarmTime = 0;
		}
		if (mx >= 517 && mx <= 547 && my >= 215 && my <= 245)
		{
			if (on)
				buttonSoundF();
			am = 1;
			pm = 0;
			setClick = 0;
			resetClick = 0;
		}
		if (mx >= 550 && mx <= 590 && my >= 215 && my <= 245)
		{
			if (on)
				buttonSoundF();
			pm = 1;
			am = 0;
			setClick = 0;
			resetClick = 0;
		}

		if (mx >= 595 && mx <= 655 && my >= 250 && my <= 285)
		{
			if (on)
				buttonSoundF();
			aSetClick();
		}

		if (mx >= 592 && mx <= 660 && my >= 217 && my <= 250)
		{
			if (on)
				buttonSoundF();
			aResetClick();
		}

		if (ringAlarm == 1 && mx >= 470 && mx <= 573 && my >= 60 && my <= 95)
		{
			if (on)
				buttonSoundF();
			alarmDismissF();
		}
		// end alarm click

		// playback Click
		if (mx >= 78 && mx <= 127 && my >= 280 && my <= 324)
		{
			if (on)
				buttonSoundF();
			if (playIndex == 0)
			{
				playIndex = 1;
			}
			else
			{
				playIndex = 0;
			}
			 
			if (playIndex && sura_i != -1)
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			else
				PlaySound(NULL, NULL, 0);
		}
		if (mx >= 24 && mx <= 56 && my >= 289 && my <= 317)
		{
			if (on)
				buttonSoundF();
			if (sura_i == -1)
				sura_i = 4;
			else
			{
				sura_i--;
				sura_i %= 5;
			}
			if (sura_i == -1)
				sura_i = 4;

			if (playIndex)
			{
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		if (mx >= 149 && mx <= 182 && my >= 290 && my <= 317)
		{
			if (on)
				buttonSoundF();
			if (sura_i == -1)
				sura_i = 0;
			else
			{
				sura_i++;
				sura_i %= 5;
			}

			if (playIndex)
			{
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			}
		}

		// surahName title click
		if (mx >= 35, mx <= 175 && my >= 560 && my <= 600)
		{
			if (on)
				buttonSoundF();
			if (sura_i != 0)
				playIndex = 0;
			sura_i = 0;
			if (playIndex == 0)
			{
				playIndex = 1;
			}
			else
			{
				playIndex = 0;
			}

			if (playIndex)
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			else
			{
				PlaySound(NULL, NULL, 0);
				sura_i = -1;
			}
		}
		if (mx >= 35, mx <= 175 && my >= 510 && my <= 550)
		{
			if (on)
				buttonSoundF();
			if (sura_i != 1)
				playIndex = 0;
			sura_i = 1;
			if (playIndex == 0)
			{
				playIndex = 1;
			}
			else
			{
				playIndex = 0;
			}

			if (playIndex)
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			else
			{
				PlaySound(NULL, NULL, 0);
				sura_i = -1;
			}
		}
		if (mx >= 35, mx <= 175 && my >= 460 && my <= 500)
		{
			if (on)
				buttonSoundF();
			if (sura_i != 2)
				playIndex = 0;
			sura_i = 2;
			if (playIndex == 0)
			{
				playIndex = 1;
			}
			else
			{
				playIndex = 0;
			}

			if (playIndex)
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			else
			{
				PlaySound(NULL, NULL, 0);
				sura_i = -1;
			}
		}
		if (mx >= 35, mx <= 175 && my >= 410 && my <= 450)
		{
			if (on)
				buttonSoundF();
			if (sura_i != 3)
				playIndex = 0;
			sura_i = 3;
			if (playIndex == 0)
			{
				playIndex = 1;
			}
			else
			{
				playIndex = 0;
			}

			if (playIndex)
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			else
			{
				PlaySound(NULL, NULL, 0);
				sura_i = -1;
			}
		}
		if (mx >= 35, mx <= 175 && my >= 360 && my <= 400)
		{
			if (on)
				buttonSoundF();

			if (sura_i != 4)
				playIndex = 0;
			sura_i = 4;
			if (playIndex == 0)
			{
				playIndex = 1;
			}
			else
			{
				playIndex = 0;
			}

			if (playIndex)
				PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
			else
			{
				PlaySound(NULL, NULL, 0);
				sura_i = -1;
			}
		}

		// Change day
		if (mx >= 605 && mx <= 656 && my >= 370 && my <= 420)
		{
			if (on)
				buttonSoundF();
			nextDayPrayerTime();
		}

		if (mx >= 402 && mx <= 451 && my >= 370 && my <= 420)
		{
			if (on)
				buttonSoundF();
			previousDayPrayerTime();
		}

		if (mx >= 490 && mx <= 580 && my >= 370 && my <= 400)
		{
			if (on)
				buttonSoundF();
			todayPrayertime();
		}

		if (mx >= 320 && mx <= 380 && my >= 100 && my <= 165)
		{
			if (on)
				buttonSoundF();
			settingPage();
		}
		// 530, 20, 80, 30
		if (mx >= 530 && mx <= 610 && my >= 20 && my <= 50)
		{
			if (on)
				buttonSoundF();
			settingClick = 0;
		}

		if (settingClick == 1 && mx >= 110 && mx <= 140 && my >= 165 && my <= 195)
		{
			if (on)
				buttonSoundF();
			if (alarmSelect != 0)
			{
				alarmSelect = 0;
				PlaySound(TEXT(alarmUrl[alarmSelect]), NULL, SND_FILENAME | SND_ASYNC);
			}
			else
			{
				alarmSelect = -1;
				PlaySound(NULL, NULL, 0);
			}
		}
		if (settingClick == 1 && mx >= 110 && mx <= 140 && my >= 125 && my <= 155)
		{
			if (on)
				buttonSoundF();
			if (alarmSelect != 1)
			{
				alarmSelect = 1;
				PlaySound(TEXT(alarmUrl[alarmSelect]), NULL, SND_FILENAME | SND_ASYNC);
			}
			else
			{
				alarmSelect = -1;
				PlaySound(NULL, NULL, 0);
			}
		}
		if (settingClick == 1 && mx >= 110 && mx <= 140 && my >= 85 && my <= 115)
		{
			if (on)
				buttonSoundF();
			if (alarmSelect != 2)
			{
				alarmSelect = 2;
				PlaySound(TEXT(alarmUrl[alarmSelect]), NULL, SND_FILENAME | SND_ASYNC);
			}
			else
			{
				alarmSelect = -1;
				PlaySound(NULL, NULL, 0);
			}
		}
		// 260, 65, 55, 25
		if (settingClick == 1 && alarmSelect != -1 && mx >= 260 && mx <= 315 && my >= 65 && my <= 90)
		{
			if (on)
				buttonSoundF();
			if (!saveClick)
				saveClick = 1;
			else
				saveClick = 0;
			PlaySound(NULL, NULL, 0);
		}
		// 502,165, 58, 25
		if (settingClick && mx >= 490 && mx <= 572 && my >= 165 && my <= 190)
		{
			if (on)
			{
				on = 0;
				off = 1;
			}
			else
			{
				on = 1;
				off = 0;
			}
		}

		if (settingClick && mx >= 490 && mx <= 572 && my >= 125 && my <= 150)
		{
			if (off)
			{
				off = 0;
				on = 1;
			}
			else
			{
				on = 0;
				off = 1;
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iKeyboard(unsigned char key)
{
	if (getAlarmTime)
	{
		if (key != '\b')
		{
			alarmTime[strIndex] = key;
			strIndex++;
			alarmTime[strIndex + 1] = '\0';
		}
		else
		{
			if (strIndex <= 0)
				strIndex = 0;
			else
				strIndex--;
			alarmTime[strIndex] = '\0';
		}
	}

	if (key == '\r' && sura_i != -1)
	{
		PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
	}
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{

		exit(0);
	}

	else if (key == GLUT_KEY_UP)
	{
		if (sura_i == -1)
			sura_i = 4;
		else
		{
			sura_i--;
			sura_i %= 5;
		}
		if (sura_i == -1)
			sura_i = 4;

		if (playIndex)
		{
			PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (sura_i == -1)
			sura_i = 0;
		else
		{
			sura_i++;
			sura_i %= 5;
		}
		if (playIndex)
		{
			PlaySound(TEXT(surahUrl[sura_i]), NULL, SND_FILENAME | SND_ASYNC);
		}
	}
	 
}

int main()
{
	CurrentDateTime();
	sscanf(date, "%d-%d-%d", &Year, &Month, &Day);
	strcpy(showDate, date);
	writeDateInTxt();
	updateTime();
	iInitialize(WIDTH, HEIGHT, "Muslim's Day");

	return 0;
}
