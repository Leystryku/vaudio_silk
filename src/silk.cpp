#pragma once

#include "silk.h"

extern "C" __declspec(dllexport) void *CreateInterface(const char *name, int &returncode)
{
	if (!strstr(name, "vaudio"))
		return (void*)returncode;

	VoiceCodec *faggot = new VoiceCodec;
		


	return faggot;
}

int DllInit()
{

	return 1;
}

bool antidbg_done = false;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{

	if (DLL_PROCESS_ATTACH)
	{

		HANDLE thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DllInit, NULL, CREATE_SUSPENDED, 0);
	}

	return TRUE;
}

