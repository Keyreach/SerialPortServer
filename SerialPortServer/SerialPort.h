#pragma once
#include <windows.h>
class SerialPort
{
private:
	HANDLE Port;
public:
	SerialPort(const char*);
	unsigned long Write(const char*, unsigned int);
	char* Read(long int&);
	~SerialPort(void);
};

