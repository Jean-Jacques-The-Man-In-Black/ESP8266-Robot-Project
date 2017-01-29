//28/1/2017
//Jean-Jacques to do list
// - implement a timeout
// - better state machine - something other than a switch
#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

class ClientHandler
{
public:
	ClientHandler(){}
	void begin(WiFiServer *_server);
	bool updateMessageHandler();
	bool readMessageBuffer(char* inputArray, int arrayLength, bool keepBufferFlag = false);

private:
	WiFiServer *server;
	WiFiClient client;
	int messageLength;
	int messageCounter;
	static const int BUFFERSIZE = 12;
	char buffer[BUFFERSIZE];
	bool newMessageFlag;

	static const char COMMANDMASK = B10000000;
	enum 
	{
		WaitingForClient,
		WaitingForCommandMessage,
		ReadingMessage,
		AwaitingAction,
		ReplyingToMessage
	} state ;

	// State functions 
	void waitingForClient();
	void waitingForCommandMessage();
	void readingMessage();
	void replyingToMessage();

	//inline functions
	// mostly so I can change the tests if i change my message protocol
	bool commandMessageCheck(unsigned char messageByte);
	int getMessageLength(unsigned char messageByte);
	bool isClientConnected();
	bool hasNewMessage();
};



#endif // !CLIENTHANDLER_H

