#include <cstdlib>
#include <ctime>

class ModbusSlave {
public:
	char DiscreteInputs[10];
	char Coils[10];
	short InputRegisters[10];
	short HoldingRegisters[10];
	ModbusSlave(){
		srand(time(NULL));
		for(int i=0; i<10; i++){
			DiscreteInputs[i] = rand() % 256;
			Coils[i] = rand() % 256;
			InputRegisters[i] = rand() % 65536;
			HoldingRegisters[i] = rand() % 65536;
		}
	}
	char* ParsePDU(unsigned char *received, int &bytes){
		char Func = received[0];
		short RegAddress = received[1] * 256 + received[2];
		short RegQuantity = received[3] * 256 + received[4];
		char *Response = new char[RegQuantity + 1];
		Response[0] = RegQuantity;
		switch(Func){
		case 1:
			for(int i=1; i<=RegQuantity; i++){
				Response[i] = (DiscreteInputs[(RegAddress + i) / 8] >> ((RegAddress + i) % 8)) & 1;
			}
			break;
		case 2:
			for(int i=1; i<=RegQuantity; i++){
				Response[i] = (Coils[(RegAddress + i) / 8] >> ((RegAddress + i) % 8)) & 1;
			}
			break;
		case 3:
			for(int i=1; i<=RegQuantity; i++){
				Response[i] = InputRegisters[RegAddress + i];
			}
			break;
		case 4:
			for(int i=1; i<=RegQuantity; i++){
				Response[i] = HoldingRegisters[RegAddress + i];
			}
			break;
		default:
			for(int i=1; i<=RegQuantity; i++){
				Response[i] = 0;
			}
		}
		bytes = RegQuantity + 1;
		return Response;
	}
};