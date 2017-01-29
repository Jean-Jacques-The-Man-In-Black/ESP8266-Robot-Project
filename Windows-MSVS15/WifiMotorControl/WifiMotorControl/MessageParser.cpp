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

bool MessageParser::IsCommandMessage(unsigned char inputMessage)
{
	return inputMessage >> 7;
}