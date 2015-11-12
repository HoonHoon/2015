#include <Windows.h>
#include <stdio.h>

DWORD Sum;	// data is shared by the thread(s)
// the thread runs in this separate function

DWORD WINAPI Summation(LPVOID Param) {
	DWORD Upper = *(DWORD *)Param;
	for (DWORD i = 0; i <= Upper; i++) {
		Sum += i;

		printf("Summaion...Sum=%d\n", Sum);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI Countings(LPVOID Param) {
	for (DWORD i = 0; i <= 10; i++) {
		printf("Counting Thread:%d\n", i);
		Sleep(1000);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	DWORD ThreadId;
	HANDLE ThreadHandle[2];
	int Param;

	// perform some basic error checking
	if (argc != 2) {
		fprintf(stderr, "An integer parameter is required\n");
		return -1;
	}
	Param = atoi(argv[1]);
	if (Param < 0) {
		fprintf(stderr, "An integer >= 0 is required\n");
		return -1;
	}

	// create the thread
	ThreadHandle[0] = CreateThread(NULL, //default security attributes
		0,								//default stack size
		Summation,						//thread function
		&Param,							// parameter to thread function
		0,								// default creation flags
		&ThreadId						// returns the thread Identifier
		);
			//+alpha thread handles
	ThreadHandle[1] = CreateThread(NULL, 0, Countings, &Param, 0, &ThreadId);

	if (ThreadHandle != NULL) {
		//now wait for the thread to finish
		//WaitForSingleObject(ThreadHandle, INFINITE);
		WaitForMultipleObjects(2, ThreadHandle, TRUE, INFINITE);

		//close the thread handle
		CloseHandle(ThreadHandle);
		
		printf("sum = %d\n", Sum);
	}
}