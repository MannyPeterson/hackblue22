#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SparkFun_TMP117.h>

#include "/home/manny/Documents/misc/secrets.h"

#define DEBUG_ON

#define DOOR_SW_PIN 17
#define SERVER "ec2-44-242-156-251.us-west-2.compute.amazonaws.com"
#define PRODUCT_ID "INSIGNIA%20NS%2DCF26WH9"
#define CUSTOMER_ID "8923742934234"
#define SERIAL_NO "21G07W00331"
#define MAX_QUEUE 10
#define TEMP_CHANGE_THRESHOLD 1
#define TEMP_DANGER_THRESHOLD 45.0

typedef struct Queue_s
{
  double arr[MAX_QUEUE];
  int head;
  int tail;
  int size;
} Queue;

Queue temps;

void read_temp(double *tmp_);
void event_send(double *tmp_);
int door_closed(void);
double queue_peek(void);
int queue_empty(void);
int queue_full(void);
int queue_size(void);
void queue_add(double *tmp_);
void queue_remove(double *tmp_);
int temp_trend(double *curr_, double *prior_);

void setup()
{

  temps.head = 0;
  temps.tail = -1;
  temps.size = 0;

#if defined(DEBUG_ON)
  Serial.begin(115200);
#endif

  // pinMode(DOOR_SW_PIN, INPUT_PULLUP);
  pinMode(DOOR_SW_PIN, INPUT_PULLDOWN);

  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(SSID, PASS);

  while (WL_CONNECTED != WiFi.status())
  {
    delay(100);
  }

  return;
}

void loop()
{
  double curr = 0.0;
  double prior = 0.0;
  int trend = 0;

  if (true == door_closed())
  {

    read_temp(&curr);

    queue_add(&curr);

    if (true == queue_full())
    {
      queue_remove(&prior);

      trend = temp_trend(&curr, &prior);
    }
  }

  if ((TEMP_DANGER_THRESHOLD < curr) && (0 < trend))
  {
    event_send(&curr);
#if defined(DEBUG_ON)
    Serial.println("debug: curr = " + String(curr, 4) + ", prior = " + String(prior, 4) + ", trend = " + String(trend) + " EVENT SENT!");
#endif
  }
  else
  {
#if defined(DEBUG_ON)
    Serial.println("debug: curr = " + String(curr, 4) + ", prior = " + String(prior, 4) + ", trend = " + String(trend));
#endif
  }

  delay(60000);

  return;
}

void read_temp(double *tmp_)
{
  TMP117 tmp117;

  Wire.begin(SDA, SCL);
  Wire.setClock(400000);
  tmp117.begin();

  while (false == tmp117.dataReady())
  {
    delay(100);
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

int door_closed(void)
{
  int ret = false;

  if (LOW == digitalRead(DOOR_SW_PIN))
  {
    ret = true;
  }

  return ret;
}

double queue_peek(void)
{
  return temps.arr[temps.head];
}

int queue_empty(void)
{
  int ret = false;

  if (0 == temps.size)
  {
    ret = true;
  }

  return ret;
}

int queue_full(void)
{
  int ret = false;

  if (MAX_QUEUE == temps.size)
  {
    ret = true;
  }

  return ret;
}

int queue_size(void)
{
  return temps.size;
}

void queue_add(double *tmp_)
{

  if (false == queue_full())
  {
    if ((MAX_QUEUE - 1) == temps.tail)
    {
      temps.tail = -1;
    }

    temps.arr[++temps.tail] = *tmp_;
    temps.size++;
  }

  return;
}

void queue_remove(double *tmp_)
{
  *tmp_ = temps.arr[temps.head++];

  if (MAX_QUEUE == temps.head)
  {
    temps.head = 0;
  }

  temps.size--;

  return;
}

int temp_trend(double *curr_, double *prior_)
{
  int ret = 0;

  double change = 0.0;

  change = *curr_ - *prior_;

  if (abs(change) < TEMP_CHANGE_THRESHOLD)
  {
    ret = 0;
  }
  else if (change < 0)
  {
    ret = -1;
  }
  else if (change > 0)
  {
    ret = 1;
  }

  return ret;
}