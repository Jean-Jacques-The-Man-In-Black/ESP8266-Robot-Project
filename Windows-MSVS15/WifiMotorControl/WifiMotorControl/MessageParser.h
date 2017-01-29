#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H



void printCharByteValues(unsigned char input);

class MessageParser
{
public:
	MessageParser();
	void begin();
	bool newMessage(char* messageBuffer, int bufferLength);

	//Lot of message definitions
	//Need to do decide on a better way
	//function pointer list?
	static const char SENDACKNOWLEDGE = 0x00;
	static const int SENDACKNOWLEDGELENGTH = 1;
	static const char CHANGERIGHTMOTOR = 0x01;
	static const int CHANGERIGHTMOTORLENGTH = 3;
	static const char CHANGELEFTMOTOR = 0x02;
	static const int CHANGELEFTMOTORLENGTH = 3;
	static const char CHANGEBOTHMOTORS = 0x03;
	static const int CHANGEBOTHMOTORSLENGTH = 5;

	const uint8_t pinRightSpeed = D1;
	const uint8_t pinRightDirection = D3;
	const uint8_t pinLeftSpeed = D2;
	const uint8_t pinLeftDirection = D4;

private:
	void changeMotor(uint8_t MotorSpeedPin, uint8_t MotorDirectionPin, bool direction, int power);

};

#endif // !MESSAGEPARSER_H

