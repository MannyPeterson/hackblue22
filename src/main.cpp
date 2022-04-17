#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SparkFun_TMP117.h>

#include "/home/manny/Documents/misc/secrets.h"

#define DOOR_SW_PIN 17

void read_temp(void);
void event_send(void);

const char *ssid = SSID;
const char *pass = PASS;

String host = "ec2-44-234-32-170.us-west-2.compute.amazonaws.com";

String product_id = "INSIGNIA%20NS%2DCF26WH9";
String customer_id = "8923742934234";
String serial_no = "21G07W00331";
double temperature = 0.0;

HTTPClient http;
TMP117 tmp117;

void setup()
{

  Serial.begin(115200);

  Wire.begin(SDA, SCL);
  Wire.setClock(400000);
  tmp117.begin();

  pinMode(DOOR_SW_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssid, pass);

  while (WL_CONNECTED != WiFi.status())
  {
    delay(500);
  }

  return;
}

void loop()
{
}

void read_temp(void)
{

  while (false == tmp117.dataReady())
  {
    delay(500);
  }

  temperature = tmp117.readTempF();

  return;
}

void event_send(void)
{

  String request = "http://" + host + "/event%5Freceive.php?cid=" + customer_id + "&pid=" + product_id + "&sn=" + serial_no + "&tmp=" + String(temperature, 3);

  http.begin(request.c_str());

  http.GET();

  Serial.println(http.getString());

  http.end();

  return;
}