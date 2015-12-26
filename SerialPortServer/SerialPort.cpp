#include "SerialPort.h"

SerialPort::SerialPort(const char* portname){
	Port = CreateFileA(
			portname,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
			);
	// Setting stuff
	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
}
unsigned long SerialPort::Write(const char* data, unsigned int size){
	unsigned long written = 0;
	WriteFile(Port, data, size, &written, 0);
	return written;
}
char* SerialPort::Read(long int& bytes){
	const int READ_TIME = 1000;
	OVERLAPPED sync = {0};
	unsigned long wait = 0, read = 0, state = 0, write = 0;
	char buf[1024], *data;
	sync.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	SetCommMask(Port, EV_RXCHAR);
	WaitCommEvent(Port, &state, &sync);
	wait = WaitForSingleObject(sync.hEvent, READ_TIME);
	if(wait == WAIT_OBJECT_0){
		ReadFile(Port, buf, 1024, &read, &sync);
		wait = WaitForSingleObject(sync.hEvent, READ_TIME);
		if(wait == WAIT_OBJECT_0)
			if(GetOverlappedResult(Port, &sync, &read, false)){
				//Write(data, 1);
				data = new char[read];
				//data[read] = '\0';
				memcpy(data, buf, read);
				CloseHandle(sync.hEvent);
				bytes = read;
				return data;
			}
	}
	CloseHandle(sync.hEvent);
	bytes = 0;
	return '\0';
}
SerialPort::~SerialPort(){
	CloseHandle(Port);
}