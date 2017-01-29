#ifndef WIFIMOTORCONTROL_H
#define WIFIMOTORCONTROL_H

#include <ESP8266WiFi.h>
#include "ClientHandler.h"
#include "MessageParser.h"


bool setMotor(char *valueArray);
bool setMotor(int motor, int direction, int power, int duration);

#endif // !WIFIMOTORCONTROL_H