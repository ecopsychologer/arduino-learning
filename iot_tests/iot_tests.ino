//libraries
//#include <Adafruit_ESP8266.h>
#include <AdafruitIO.h>
#include <WiFiClientSecure.h>
#include <AdafruitIO_Dashboard.h>
#include <AdafruitIO_Data.h>
#include <AdafruitIO_Definitions.h>
#include <AdafruitIO_Feed.h>
#include <AdafruitIO_MQTT.h>
#include <AdafruitIO_WiFi.h>
#include <IFTTTMaker.h>

//globals
#define WLANSSID "ssid"
#define WLANPASS "pass"
#define UNAME "jcschoen"
#define IO_KEY "733640ed72464ebab46f9ae07200eabb"
#define SERVER "io.adafruit.com"
#define SERVERPORT 8883
#define IF_KEY "mhrdOLuhDWJcxtvCSICcAwJIASduuRxa"
#define EVENT_NAME "name"
#define IO_PIN 2
#define DATA_PIN A0

WiFiClientSecure client;
IFTTTMaker ifttt(IF_KEY, client);
void setup() {

}

void loop() {
  ifttt.triggerEvent(EVENT_NAME, WLANSSID, ip.toString());
}
