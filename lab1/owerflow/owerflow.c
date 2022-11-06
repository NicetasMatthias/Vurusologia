#include "stdio.h"

int main (int argv, char argc[])
{
	char buffer[3];	
	printf ("Print up to 3 symbols\n>> ");
	scanf ("%s", buffer);
	printf ("done");
	return 0;
}