#include "header.h"

int main(int argc, char **argv)
{
	char path[MAX_PATH];
	if (argc < 2)
	{
		printf("Usage: %s <dll path> ", argv[0]);
		return 1;
	}
	strcpy_s(path, argv[1]);

	//OpenProcess
	int pid = GetProcId("AssaultCube");
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	if (hProc == NULL)
		fatal("OpenProcess");
	
	//Memory Allocation
	VOID* PathAddr = VirtualAllocEx(hProc, NULL, 1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (PathAddr == NULL)
		fatal("VirtualAllocEx");

	//Write path
	if (WriteProcessMemory(hProc, PathAddr, path, strlen(path), NULL))
		cout << "Successfully writing DLL path to address 0x" << (int*)PathAddr << endl;

	//Create thread
	HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, PathAddr, 0, NULL);
	if (hThread == NULL)
		fatal("CreateRemoteThread");

	CloseHandle(hProc);
	CloseHandle(hThread);
	return 0;
}