#include <stdio.h>
#include <string.h>

void never()
{
	puts("call never function");
}

void vulnerable(char* arg)
{
	char buff[10];
	strcpy(buff, arg);
}

int main(int argc, char **argv)
{
	puts("start");
	vulnerable(argv[1]);
	return (0);
}
