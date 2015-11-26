// SerialPortServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include "SerialPort.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	/*const int READ_TIME = 1000;
	OVERLAPPED sync = {0};
	int retval = 0;
	unsigned long wait = 0, read = 0, state = 0, write = 0;*/
	unsigned char dst[100] = {0};
	unsigned long size = sizeof(dst);
	/*HANDLE port = CreateFile(L"\\\\.\\COM11", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	
	sync.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	
	if(port == INVALID_HANDLE_VALUE)
		printf("Error.\n");

	SetCommMask(port, EV_RXCHAR);
	while(1){
		WaitCommEvent(port, &state, &sync);
		//printf("waiting 4 data...\n");
		wait = WaitForSingleObject(sync.hEvent, READ_TIME);
		if(wait == WAIT_OBJECT_0){
			//printf("reading data...\n");
			ReadFile(port, dst, size, &read, &sync);
			wait = WaitForSingleObject(sync.hEvent, READ_TIME);
			if(wait == WAIT_OBJECT_0)
				if(GetOverlappedResult(port, &sync, &read, false)){
					char c = dst[0];
					//memcpy(c, dst, read);
					WriteFile(port, &c, 1, &write, &sync);
					printf("Got %s\n<- %d\n-> %d\n", dst, read, write);
				}
		}
		for(int i=0; i<1024; i++) dst[i] = 0;
	}*/
	/*for(;;){
		if(WaitCommEvent(port, &state, &sync)){
			printf("Got an event\n");
			if(state & EV_RXCHAR){
				ReadFile(port, dst, size, &read, &sync);
				printf("We got %d shit\n", read);
			}
		}
	}*/
	
	//CloseHandle(sync.hEvent);
	char *buf, *response;
	long int readbytes = 0;
	SerialPort port2("\\\\.\\COM11");
	while(1){
		buf = port2.Read(readbytes);
		response = new char[readbytes+4];
		sprintf(response, "%s%04d", buf, readbytes);
		printf("%s\n%d\n", buf, readbytes);
		port2.Write(response, strlen(response));
		//port2.Write(buf, readbytes);
	}

	return 0;
}

