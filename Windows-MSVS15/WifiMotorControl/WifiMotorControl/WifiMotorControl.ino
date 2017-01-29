/*
 Name:		WifiMotorControl.ino
 Created:	1/17/2017 7:42:56 PM
 Author:	Jean-Jacques
*/
#include "WifiMotorControl.h"

const char* ssid = "VM796695-2G";
const char* password = "tfxpdacg";
const int PortNumber = 1000;

const size_t bufferLength = 12;	//could be the same thing
const size_t messageLength = 4;

int ledDuration = 1000;
bool ledState = false;
unsigned long refrenceMillis = 0;
char buffer[bufferLength];

const uint8_t pinrightspeed = D1;
const uint8_t pinrightdirection = D3;
const uint8_t pinleftspeed = D2;
const uint8_t pinleftdirection = D4;

WiFiServer server(PortNumber);
WiFiClient client;

ClientHandler clientHandler;

void setup() 
{
	//set up pins
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(pinrightspeed, OUTPUT);
	pinMode(pinrightdirection, OUTPUT);
	pinMode(pinleftspeed, OUTPUT);
	pinMode(pinleftdirection, OUTPUT);


	//set up serial
	Serial.begin(115200);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");

	// Start the server
	server.begin();
	server.setNoDelay(true);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.print("Port number: ");
	Serial.println(PortNumber);
	Serial.println("");

	clientHandler.begin(&server);
}


bool setMotor(char *valueArray)
{
	return setMotor((int)valueArray[0], (int)valueArray[1], (int)valueArray[2], (int)valueArray[3]);
}

bool setMotor(int motor, int direction, int power, int duration)
{
	Serial.println(motor);
	Serial.println(direction);
	Serial.println(power);
	Serial.println(duration);
	if ((motor < 2) && (direction < 2) && (power < 256) && (duration < 256))
	{
		//digitalWrite((motor ? pinrightdirection : pinleftdirection), direction);
		//analogWrite((motor ? pinrightspeed : pinleftspeed), power);
		//analogWrite((motor ? pinrightdirection : pinleftdirection), power);
		//digitalWrite((motor ? pinrightspeed : pinleftspeed), direction);
		return true;
	}
	Serial.print("Conversion Error: ");
	return false;
}

void loop() 
{
	if (clientHandler.updateMessageHandler())
	{
		if (clientHandler.readMessageBuffer(buffer, bufferLength))
		{
			Serial.println("Printing Message Buffer:");
			for (int i = 0; i < bufferLength; ++i)
			{
				printCharByteValues(buffer[i]);
			}
			Serial.println("Done");
		}
	}


	if ((refrenceMillis + ledDuration) < millis())
	{
		ledState = !ledState;
		refrenceMillis += ledDuration;
		digitalWrite(LED_BUILTIN, ledState);
	}
}
