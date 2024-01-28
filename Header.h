#pragma once
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
using namespace std;

void fatal(const char* error) {
	std::cerr << "[!!] Error while " << error << std::endl;
	exit(-1);
}

DWORD GetProcId(const char* ProcName)
{
	HWND hWindow = FindWindow(nullptr, ProcName);
	DWORD ProcId;
	GetWindowThreadProcessId(hWindow, &ProcId);
	return ProcId;
}
