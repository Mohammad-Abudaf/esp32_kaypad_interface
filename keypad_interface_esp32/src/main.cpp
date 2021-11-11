#include "1_Libraries_Identifiers.h"
#include "2_WebPages.h"
#include "3_WebServerHandlers.h"
#include "4_Functions.h"

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  digitalWrite(led, 0);
  digitalWrite(relay, 0);
  digitalWrite(buzzer, 0);

  WiFi.mode(WIFI_STA);
  esid = "C701";
  epass = "20192020";
  stIP = IPAddress(192, 168, 0, 22);
  gateway = IPAddress(192, 168, 0, 1);
  subnet = IPAddress(255, 255, 255, 0);
  webserverHandlers();
}

void loop() {
  cheakWiFiConnection();
  touchValue = 0.9 * touchValue + 0.1 * touchRead(touchPin);
  if (touchValue < 50)
  {
    digitalWrite(led, 0);
    digitalWrite(relay, 0);
    digitalWrite(buzzer, 0);
  }

  for (i = 0; i <= 7; i++) // up to 8 digits password
  {
    digitalWrite(buzzer, 1); delay(50);  digitalWrite(buzzer, 0); delay(50);
    kp = 0;
    do
    {
      kp = keypad.getKey();
      cheakWiFiConnection();
    } while (!kp);
    Serial.println(kp);
    if (kp == '#')
    {
      varify();
      break;    //Restart new Trial
    }
    else if (kp == '*')
      i = i - 2;
    else
      INCODE[i] = kp ;
  }
}
