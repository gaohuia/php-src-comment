#include <stdio.h>
#include <string.h>

typedef int (*Callback)(char *);


void call(Callback callback)
{
	int ret = callback((char*)"gaohuia");
	printf("ret=%d\n", ret);
}

int HiCallback(char *username)
{
	printf("Hi, %s\n", username);
	return strlen(username);
}

int main(int argc, char const *argv[])
{

	Callback callback;
	if (true) {
		callback = HiCallback;
	}

	call(callback);
	return 0;
}