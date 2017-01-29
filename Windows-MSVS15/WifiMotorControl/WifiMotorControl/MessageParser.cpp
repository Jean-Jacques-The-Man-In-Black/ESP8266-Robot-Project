#include <ESP8266WiFi.h>
#include "MessageParser.h"

void printCharByteValues(unsigned char input)
{
	Serial.print("Byte data:");
	for (int i = 7; i >= 0; --i)
	{
		Serial.print((input & (1 << i)) >> i);
	}
	Serial.println(";");
}

MessageParser::MessageParser()
{

}

void MessageParser::begin()
{
	pinMode(pinRightSpeed, OUTPUT);
	pinMode(pinRightDirection, OUTPUT);
	pinMode(pinLeftSpeed, OUTPUT);
	pinMode(pinLeftDirection, OUTPUT);
}

bool MessageParser::newMessage(char* messageBuffer, int bufferLength)
{
	if (bufferLength <= 0) return false;
	switch (messageBuffer[0])
	{
	case SENDACKNOWLEDGE:
		//Not done yet	
		if (bufferLength < SENDACKNOWLEDGELENGTH) return false;
		break;
	case CHANGERIGHTMOTOR:
		if (bufferLength < CHANGERIGHTMOTORLENGTH) return false;
		changeMotor(pinRightSpeed, pinRightDirection, messageBuffer[1], messageBuffer[2]);
		break;
	case CHANGELEFTMOTOR:
		if (bufferLength < CHANGELEFTMOTORLENGTH) return false;
		changeMotor(pinLeftSpeed, pinLeftDirection, messageBuffer[1], messageBuffer[2]);
		break;
	case CHANGEBOTHMOTORS:
		if (bufferLength < CHANGEBOTHMOTORSLENGTH) return false;
		changeMotor(pinRightSpeed, pinRightDirection, messageBuffer[1], messageBuffer[2]);
		changeMotor(pinLeftSpeed, pinLeftDirection, messageBuffer[3], messageBuffer[4]);
		break;
	default:
		Serial.println("Parsing error!");
		break;
	}
}

void MessageParser::changeMotor(uint8_t MotorSpeedPin, uint8_t MotorDirectionPin, bool direction, int power)
{
	digitalWrite(MotorDirectionPin, direction);
	analogWrite(MotorSpeedPin, power*10);
}



