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
#define MAX_QUEUE 10

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

void setup()
{

  Serial.begin(115200);

  pinMode(DOOR_SW_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(SSID, PASS);

  while (WL_CONNECTED != WiFi.status())
  {
    delay(500);
  }

  return;
}

void loop()
{
  double curr = 0.0;
  double prior = 0.0;

  if (true == door_closed())
  {

    read_temp(&curr);

    queue_add(&curr);

    if (true == queue_full())
    {
      queue_remove(&prior);
    }
  }

  Serial.print("Current: " + String(curr, 4));
  Serial.print("Prior: " + String(prior, 4));
  Serial.println();

  delay(1000);

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
    if (MAX_QUEUE - 1 == temps.tail)
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