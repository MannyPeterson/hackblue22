#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SparkFun_TMP117.h>

#include "/home/manny/Documents/misc/secrets.h"

#define DOOR_SW_PIN 17
#define SERVER "ec2-44-234-32-170.us-west-2.compute.amazonaws.com"
#define PRODUCT_ID "INSIGNIA%20NS%2DCF26WH9"
#define CUSTOMER_ID "8923742934234"
#define SERIAL_NO "21G07W00331"

void read_temp(double *tmp_);
void event_send(double *tmp_);

const char *ssid = SSID;
const char *pass = PASS;

TMP117 tmp117;

void setup()
{

  Serial.begin(115200);

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

void read_temp(double *tmp_)
{

  Wire.begin(SDA, SCL);
  Wire.setClock(400000);
  tmp117.begin();

  while (false == tmp117.dataReady())
  {
    delay(500);
  }

  *tmp_ = tmp117.readTempF();

  return;
}

void event_send(double *tmp_)
{
  HTTPClient client;
  String server = String(SERVER);
  String product_id = String(PRODUCT_ID);
  String customer_id = String(CUSTOMER_ID);
  String serial_no = String(SERIAL_NO);
  String tmp = String(*tmp_, 3);

  String request = String("http://" + server + "/event%5Freceive.php?cid=" + customer_id + "&pid=" + product_id + "&sn=" + serial_no + "&tmp=" + tmp);

  client.begin(request.c_str());

  client.GET();

  client.end();

  return;
}