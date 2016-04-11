#ifndef __FILES__
#define __FILES__

#include <stdio.h>
#include <conio.h>
#include <FCNTL.H>
#include <io.h>
#include <SYS\STAT.H>

int Jest_Plik(char* plik)
{
	int _plik=open(plik,O_RDONLY);
	if (_plik==-1) return -1;
	close(_plik);
	return 1;
}
int Assign(char* nazwa)
{
	int plik;
	if (Jest_Plik(nazwa)==-1) plik=creat(nazwa,O_RDWR | O_BINARY);
	else
	plik=open(nazwa,O_RDWR | O_BINARY);
	return plik;
}


#endif