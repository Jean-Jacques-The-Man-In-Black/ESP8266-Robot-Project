#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H


void printCharByteValues(unsigned char input);

class MessageParser
{
public:
	MessageParser();
	
	bool IsCommandMessage(unsigned char inputMessage);

};

#endif // !MESSAGEPARSER_H

