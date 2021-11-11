#define led 2
#define relay 13
#define buzzer 25
#define button1 0
#define button2 34
#define touchPin T0

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {23, 22, 21, 19}; //inputs
byte colPins[COLS] = {5, 17, 16}; //outputs
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char kp, Y, K, INCODE[8], character, pass[4] = {'1', '2', '3', '4'};
int i;
WebServer server(80);
IPAddress    stIP, gateway, subnet;
String esid, epass = "";
unsigned long waitCount = 0;
uint8_t conn_stat = 0;         //  ( 0: down, 1: starting, 2: up)
float touchValue = 56;
