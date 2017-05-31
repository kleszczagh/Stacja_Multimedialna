#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>

using namespace std;


int main(int argc, _TCHAR* argv[])
{
	string linia;
	string temperatura = "  ";
	string wyjscie;
	int i;
	fstream plik;
	plik.open("wynik.jpg",ios::in);
	if(getline(plik,linia))
	{
		for(i = 0;i<linia.length();i++)
		{
			if(linia[i] == ',')
			{
				temperatura[0] = linia[i+2];
				temperatura[1] = linia[i+3];
				break;
			}
		}
	}
	static DCB dcb = {0};
	static HANDLE hNumPort;
	char lpBuffor_read[33], lpBuffor_write[33];
	static DWORD RS_ile;

	hNumPort = CreateFile("COM1", GENERIC_WRITE |GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	dcb.DCBlength = sizeof(dcb);

dcb.BaudRate = CBR_9600;
dcb.fParity = FALSE;
dcb.Parity = NOPARITY;
dcb.StopBits = ONESTOPBIT;
dcb.ByteSize = 8;

dcb.fDtrControl = DTR_CONTROL_DISABLE;
dcb.fRtsControl = RTS_CONTROL_DISABLE;

dcb.fOutxCtsFlow = FALSE;
dcb.fOutxDsrFlow = FALSE;
dcb.fDsrSensitivity = FALSE;
dcb.fAbortOnError = FALSE;
dcb.fOutX = FALSE;
dcb.fInX = FALSE;
dcb.fErrorChar = FALSE;
dcb.fNull = FALSE;
if (SetCommState(hNumPort, &dcb))
{
    cout<<"OK";
	wyjscie = "Krakow,T"+ temperatura + "Cz";
	strcpy(lpBuffor_write, "Krakow,T20Cz");
	WriteFile(hNumPort, lpBuffor_write, strlen(lpBuffor_write), &RS_ile, 0);

}
else
{
	std::cout<<"blad"<<std::endl;
	wyjscie = "Krakow,T"+ temperatura + "Cz";
	std::cout<<wyjscie;

}
	CloseHandle(hNumPort);
	char c;
	cin >> c;
	return 0;
}
