#include <ESP8266WiFi.h>
#include "ClientHandler.h"

void ClientHandler::begin(WiFiServer *_server)
{
	//If a null pointer is passed, what the hell should i do?
	server = _server;
	state = WaitingForClient;
}

bool ClientHandler::updateMessageHandler()
{
	switch (state)
	{
	case WaitingForClient:
		waitingForClient();
		break;

	case WaitingForCommandMessage:
		waitingForCommandMessage();
		break;

	case ReadingMessage:
		readingMessage();
		break;

	case AwaitingAction:
		//More work is needed!
		//isClientConnected();
		break;

	case ReplyingToMessage:
		
		break;

	default:
		Serial.println("STATE ERROR!");
		state = WaitingForClient;
		break;
	}
	return hasNewMessage();
}

bool ClientHandler::readMessageBuffer(char* inputArray, int arrayLength, bool keepBufferFlag)
{
	if (hasNewMessage() && (arrayLength >= BUFFERSIZE))
	{
		for (int i = 0; i < BUFFERSIZE; ++i)
		{
			inputArray[i] = buffer[i];
		}
		
		if (!keepBufferFlag)
		{
			state = WaitingForCommandMessage;
		}
		return true;
	}
	return false;
}


void ClientHandler::waitingForClient()
{
	client = server->available();
	if (!client)
	{
		state = WaitingForClient;
	}
	else
	{
		Serial.println("New Client!");
		state = WaitingForCommandMessage;
	}
}

void ClientHandler::waitingForCommandMessage()
{
	while(client.available() > 0)
	{
		if (commandMessageCheck(client.read()))
		{
			//Serial.println("New Message!");
			readingMessage();
		}
	}
}

void ClientHandler::readingMessage()
{
	while (client.available() > 0)
	{
		unsigned char messageByte = client.read();
		if (commandMessageCheck(messageByte)) return;
		buffer[messageCounter] = messageByte;
		++messageCounter;
		if ((messageCounter >= messageLength))
		{
			//Serial.println("End of message!");
			state = AwaitingAction;
			break;
		}	
	}
}

void ClientHandler::replyingToMessage()
{
	client.write(1);
	state = WaitingForCommandMessage;
}

inline bool ClientHandler::isClientConnected()
{
	if (!client.connected())
	{
		Serial.println("Lost Client!");
		client.stopAll();
		messageLength = 0;
		messageCounter = 0;
		state = WaitingForClient;
		return false;
	}
	return true;
}

inline int ClientHandler::getMessageLength(unsigned char messageByte)
{
	return static_cast<int>(messageByte ^ COMMANDMASK);
}

inline bool ClientHandler::commandMessageCheck(unsigned char messageByte)
{
	if ((messageByte & COMMANDMASK))
	{
		messageLength = getMessageLength(messageByte);
		messageCounter = 0;
		state = ReadingMessage;
		return true;
	}
	return false;
}

inline bool ClientHandler::hasNewMessage()
{
	return AwaitingAction == state;
}
