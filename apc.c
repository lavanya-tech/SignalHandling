#include <stdio.h>
#include <Windows.h>

// Define an APC function that will be called when the APC is dequeued
VOID CALLBACK MyAPCProc(ULONG_PTR dwParam)
{
    printf("APC called with parameter: %lu\n", dwParam);
}

int main()
{
    HANDLE hThread;
    DWORD dwThreadId;

    // Create a new thread to run the APC on
    hThread = CreateThread(NULL, 0, NULL, NULL, 0, &dwThreadId);

    // Register an APC for the new thread
    QueueUserAPC(MyAPCProc, hThread, (ULONG_PTR)1234);

    // Wait for the thread to finish before exiting the program
    WaitForSingleObject(hThread, INFINITE);

    return 0;
}
