import salat
import datetime as dt
import pytz

dhakaLatitude = 23.777176
dhakaLongitude = 90.399452

def generateTime(Y, M, D):
    pt = salat.PrayerTimes(salat.CalculationMethod.ISNA, salat.AsrMethod.STANDARD)

     
    date = dt.date(Y, M, D)
    longitude = dhakaLongitude
    latitude = dhakaLatitude


    dhaka_timezone = pytz.timezone('Asia/Dhaka')

    prayer_times = pt.calc_times(date, dhaka_timezone, longitude, latitude)
    
    return prayer_times

 
    

f = open("dateTxt.txt", "r")
s = f.read()
f.close()

#print(s)
y = s[0:4]
m = s[5:7]
d = s[8:10]
# print(y)
# print(m)
# print(d)
yy = int(y)
mm = int(m)
dd = int(d)

  


prayer_times = generateTime(yy, mm, dd)

fajr = str(prayer_times['fajr'])[11:16]
dhuhr = str(prayer_times['dhuhr'])[11:16]
asr = str(prayer_times['asr'])[11:16]
maghrib = str(prayer_times['maghrib'])[11:16]
isha = str(prayer_times['isha'])[11:16]

sunrise = str(prayer_times['sunrise'])[11:16]
sunset = maghrib



A1 = int(asr[0:2]) - 12
A2 = asr[3:5]

M1 = int(maghrib[0:2]) - 12
M2 = maghrib[3:5]

I1 = int(isha[0:2]) - 12
I2 = isha[3:5]

# print(int(t1) - 12)
# print(t2)

# print(I1)

with open("prayer_time.txt", "w") as f:
    f.write(f"Fajr:        {fajr} AM - {sunrise}  AM\n")
    f.write(f"Dhuhr:    {dhuhr} PM - 0{A1}:{A2}  PM\n")
    f.write(f"Asr:         0{A1}:{A2} PM - 0{M1}:{M2} PM\n")
    f.write(f"Maghrib: 0{M1}:{M2} PM - 0{I1}:{I2} PM\n")
    f.write(f"Isha:        0{I1}:{I2} PM - {fajr} AM\n")

with open("waqt_time.txt", "w") as f:
    f.write(f"{fajr}\n{dhuhr}\n{asr}\n{maghrib}\n{isha}\n{sunrise}")


S1 = int(sunset[0:2]) - 12
S2 = sunset[3:5]

with open("sunrise_sunset.txt", "w") as f:
    f.write(f"Sunrise: {sunrise} AM\n")
    f.write(f"Sunset:  0{S1}:{S2} PM\n")


# print(prayer_times)

# print(sunrise)
 

# print("Fajr Time:", fajr)
# print("Dhuhr Time:", dhuhr)
# print("Asr Time:", asr)
# print("Maghrib Time:", maghrib)
# print("Isha Time:", isha)
