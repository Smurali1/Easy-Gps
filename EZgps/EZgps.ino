//EZgps program -Jonathan
//Basically a frame for use in creating code with ublox GPS stuff
//Not really optimized for anything except usability at the moment

#include <TinyGPS.h>
#include <SoftwareSerial.h>

//#define Serial1 gpsserial; //Hardware Serial option
SoftwareSerial gpsserial = SoftwareSerial(2,3);

struct GPSdata{
  float GPSLat=0;
  float GPSLon=0;
  unsigned long GPSTime=0;
  long GPSAlt=0;
  int GPSSats=-1;
};
TinyGPS gps;
unsigned long cur=0;
GPSdata gpsInfo;
GPSdata preserve;

void setup() {
  gpsserial.begin(9600);
  GPSINIT();
  gpsserial.end();
  gpsserial.begin(115200);
  Serial.begin(115200);
  Serial.println("Init:-");
}

void loop() {
 //Parse GPS
 preserve = gpsInfo;
  while (gpsserial.available()){
   if (gps.encode(gpsserial.read())){
	 gpsInfo = getGPS();
     break;
   }
 }
 //---
 //Print to screen
  if(millis()>=(cur+250)){
    cur=millis();
	output();
	//chang
  }
  //---
  
  //DO OTHER STUFF
  delay(10);//Not needed
}