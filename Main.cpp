/*
João Ricardo Louzada
joaotande@yahoo.com.br
Itajubá - MG, UNIFEI 2014
Aqui é Brasil PORRA!
*/
//
//HACKBOT - Project
//
//ABOUT THE CODE.
//This code is a hack for the game Nidhogg. With this code is possible
//Construct bots in order to control the avatars in the game.
//
//Version 1.01.
//
//In this version you can know the avatar's positions and control the
//movement of them and which avatar is running to win.



#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <TlHelp32.h> //PROCESSENTRY
#include <windows.h>
#include <iostream>
#include <string.h>
#include <iostream>      
#include <thread>         
using namespace std;

DWORD GetProcessBaseAddress(HWND window, DWORD pID);
int apertaG();
int apertaA();
int apertaF();
int apertaD();
int apertaM();
int apertaN();
int apertaRightNarrow();
int apertaLeftNarrow();
DWORD getAndressPositionXYellow(HWND window, DWORD pID, HANDLE phandle);
DWORD getAndressPositionXOrange(HWND hwnd, DWORD pid, HANDLE phandle);
void playerOne(HWND hwnd, DWORD pid, HANDLE phandle);
void playerTwo(HWND hwnd, DWORD pid, HANDLE phandle);
DWORD setPlayerOnePosition(HWND hwnd, DWORD pid, HANDLE phandle, DWORD value);
DWORD getPlayerOnePosition(HWND hwnd, DWORD pid, HANDLE phandle);
DWORD setPlayerTwoPosition(HWND hwnd, DWORD pid, HANDLE phandle, DWORD value);
DWORD getPlayerTwofPosition(HWND hwnd, DWORD pid, HANDLE phandle);
DWORD getAndressRunningCharacter(HWND hwnd, DWORD pid, HANDLE phandle);
int getRunner(HWND hwnd, DWORD pid, HANDLE phandle);


int main()
{
	DWORD pid;
	DWORD baseAndress;
	HWND hwnd;
	
	hwnd = FindWindow(NULL, "Nidhogg");// You need put here the title of the main windows of the process that you wanna read and write on.
	if (!hwnd)
	{
		cout << "Window not found!\n";
		cin.get();
	}
	else
	{
		GetWindowThreadProcessId(hwnd, &pid);
		//PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD; // This are the kinds os autorizations to manipulate memory from onther process.
		HANDLE phandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD, 0, pid);// This line give the autorizations to use the space of memory from another process.
		if (!phandle)
		{
			cout << "Could not get handle!\n";
			cin.get();
		}
		else
		{
			//thread first(playerOne, hwnd, pid, phandle);//Starts Player One Thread
			//thread second(playerTwo, hwnd, pid, phandle);//Starts Player Two Thread
			cout << "It is working!" << endl;
			
			int old = 0;
			printf("\n\nStarting FIGHT!\n\n");
			while (1){
				int who = getRunner(hwnd, pid, phandle);
				if (old != who){
					if (who == 0) printf("NOBODY is Running!\n");
					if (who == 1) printf("Yellow is Running!\n");
					if (who == 2) printf("Orange is Running!\n");
					if (who == 3) printf("CODE FAILLLL!\n");
					old = who;
				}//fim if
			}//fim while
				
			return 0;
		}
	}
}

DWORD getPlayerOnePosition(HWND hwnd, DWORD pid, HANDLE phandle){
	DWORD address;
	DWORD value;
	
	address = getAndressPositionXYellow(hwnd, pid, phandle);
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	return value;
}

DWORD setPlayerOnePosition(HWND hwnd, DWORD pid, HANDLE phandle, DWORD value){
	DWORD address;
	
	address = getAndressPositionXYellow(hwnd, pid, phandle);
	WriteProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	return value;
}

DWORD getPlayerTwoPosition(HWND hwnd, DWORD pid, HANDLE phandle){
	DWORD address;
	DWORD value;

	address = getAndressPositionXOrange(hwnd, pid, phandle);
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	return value;
}

DWORD setPlayerTwoPosition(HWND hwnd, DWORD pid, HANDLE phandle, DWORD value){
	DWORD address;

	address = getAndressPositionXOrange(hwnd, pid, phandle);
	WriteProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	return value;
}

void playerOne(HWND hwnd, DWORD pid, HANDLE phandle){//Control averything about player ONE
	DWORD value;
	
	while (1){
		apertaA();
		/*
		if (getPlayerOnePosition(hwnd, pid, phandle) < 1146044416){
			value = 1149804544;
			setPlayerOnePosition(hwnd, pid, phandle, value);
		}
		if (getPlayerOnePosition(hwnd, pid, phandle) > 1149804544){
			value = 1146044416;
			setPlayerOnePosition(hwnd, pid, phandle, value);
		}*/
		apertaG();
		apertaF();
		apertaD();
		/*
		if (getPlayerOnePosition(hwnd, pid, phandle) < 1146044416){
			value = 1149804544;
			setPlayerOnePosition(hwnd, pid, phandle, value);
		}
		if (getPlayerOnePosition(hwnd, pid, phandle) > 1149804544){
			value = 1146044416;
			setPlayerOnePosition(hwnd, pid, phandle, value);
		}
		*/
		apertaG();
		apertaF();
	}
}

void playerTwo(HWND hwnd, DWORD pid, HANDLE phandle){//Control everything about player TWO.
	DWORD value;
	
	while (1){
		apertaM();
		apertaN();
		apertaRightNarrow();
		apertaLeftNarrow();
	}
}

int getRunner(HWND hwnd, DWORD pid, HANDLE phandle){// return 0 nobody is running (starting game), return 1 Yellow is running, return 2 Orange is Running, return 3 == fail.
	DWORD Runner = getAndressRunningCharacter(hwnd, pid, phandle);
	if (Runner == 0x00000000) return 0; //return 0 nobody is running (starting game)
	DWORD Orange = getAndressPositionXOrange(hwnd, pid, phandle);
	DWORD Yellow = getAndressPositionXYellow(hwnd, pid, phandle);
	if (Orange == Runner) return 2; //return 2 Orange is Running
	if (Yellow == Runner) return 1; //return 1 Yellow is running

	return 3; //return 3 == fail
}


DWORD getAndressRunningCharacter(HWND hwnd, DWORD pid, HANDLE phandle){
	DWORD address;
	DWORD InicialAndress = 0x002C608C;
	DWORD value;
	DWORD baseAndress;

	baseAndress = GetProcessBaseAddress(hwnd, pid);
	address = InicialAndress + baseAndress;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x00;
	if (value == 0x00000000) return 0x00000000;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x690;
	if (value == 0x00000000) return 0x00000000;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0xc;
	if (value == 0x00000000) return 0x00000000;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0xb8;
	if (value == 0x00000000) return 0x00000000;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x8;
	if (value == 0x00000000) return 0x00000000;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x50;
	if (value == 0x00000000) return 0x00000000;

	return address;
}

DWORD getAndressPositionXOrange(HWND hwnd, DWORD pid, HANDLE phandle){
	DWORD address;
	DWORD InicialAndress = 0x002C608C;
	DWORD value;
	DWORD baseAndress;

	baseAndress = GetProcessBaseAddress(hwnd, pid);
	address = InicialAndress + baseAndress;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x0;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x548;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0xc;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0xb0;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x8;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x50;

	return address;
}

DWORD getAndressPositionXYellow(HWND hwnd, DWORD pid, HANDLE phandle){
	DWORD address;
	DWORD InicialAndress = 0x002C608C;
	DWORD value;
	DWORD baseAndress;
	
	baseAndress = GetProcessBaseAddress(hwnd, pid);
	address = InicialAndress + baseAndress;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x0;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x550;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0xc;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0xb0;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x8;
	ReadProcessMemory(phandle, (LPVOID)address, &value, sizeof(value), 0);
	address = value + 0x50;
	
	return address;
}

DWORD GetProcessBaseAddress(HWND window, DWORD pID)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	MODULEENTRY32 module;
	module.dwSize = sizeof(MODULEENTRY32);
	Module32First(snapshot, &module);
	DWORD base = (DWORD)module.modBaseAddr;
	//################################################## Show the process list
	//do {// If uncomented show alll base andress.
	//	printf("ModuleName: %S\n", module.szExePath);
	//printf("Base Addr : 0x%08X\n\n", module.modBaseAddr);
	//} while (Module32Next(snapshot, &module));
	//##################################################
	CloseHandle(snapshot);
	return base;
}

int apertaG()
// ver site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VkKeyScan('G'), 0xa2, 0, 0); // ‘A’ Press
	Sleep(600);//O pulo pode demorar de 0 até 600 tempos do sleep (pulo completo = 600)
	keybd_event(VkKeyScan('G'), 0xa2, KEYEVENTF_KEYUP, 0); // ‘A’ Release
	Sleep(10);
	return 0;
}

int apertaA()
// ver site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VkKeyScan('A'), 0x9e, 0, 0); // ‘A’ Press
	Sleep(1000);
	keybd_event(VkKeyScan('A'), 0x9e, KEYEVENTF_KEYUP, 0); // ‘A’ Release
	Sleep(10);
	return 0;
}

int apertaLeftNarrow()
// ver site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VK_LEFT, 0x9e, 0, 0); // ‘A’ Press
	Sleep(1000);
	keybd_event(VK_LEFT, 0x9e, KEYEVENTF_KEYUP, 0); // ‘A’ Release
	Sleep(10);
	return 0;
}

int apertaRightNarrow()
// ver site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VK_RIGHT, 0x9e, 0, 0); // ‘A’ Press
	Sleep(1000);
	keybd_event(VK_RIGHT, 0x9e, KEYEVENTF_KEYUP, 0); // ‘A’ Release
	Sleep(10);
	return 0;
}


int apertaF()
// ver site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VkKeyScan('F'), 0xa1, 0, 0); // ‘A’ Press
	Sleep(100);
	keybd_event(VkKeyScan('F'), 0xa1, KEYEVENTF_KEYUP, 0); // ‘Angfdmgnfamgnfdgmfangfmdngfam’ Release
	Sleep(10);
	return 0;
}

int apertaN()
// ver site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VkKeyScan('N'), 0xb1, 0, 0); // ‘A’ Press
	Sleep(1000);
	keybd_event(VkKeyScan('N'), 0xb1, KEYEVENTF_KEYUP, 0); // ‘A’ Release
	Sleep(10);
	return 0;
}

int apertaD()
//see web site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VkKeyScan('D'), 0xa0, 0, 0); // ‘A’ Press
	Sleep(1000);
	keybd_event(VkKeyScan('D'), 0xa0, KEYEVENTF_KEYUP, 0); // ‘A’ Release
	Sleep(10);
	return 0;
}

int apertaM()
//see web site http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
{
	keybd_event(VkKeyScan('M'), 0xb2, 0, 0); // ‘M’ Press
	Sleep(600);
	keybd_event(VkKeyScan('M'), 0xb2, KEYEVENTF_KEYUP, 0); // ‘M’ Release
	Sleep(10);
	return 0;
}
// Infomations extract from http://reverseengineering.stackexchange.com/questions/3482/does-code-injected-into-process-memory-always-belong-to-a-page-with-rwx-access
/*The assumption does not hold true, as it is possible to alter page protection flags after you've allocated memory.
The usual mechanism for code injection on Windows is as follows:
Call OpenProcess for the target process, to get a handle that has appropriate access privileges.
Use VirtualAllocEx to allocate a buffer in the target process, with a set of memory page access flags.
Use WriteProcessMemory to copy the memory to the target.
Either patch existing code to jump to the new code block, or use CreateRemoteThread to execute within the process via a new thread.
Now, there are two options here. The first is that you can specify PAGE_EXECUTE_READWRITE as a flag to VirtualAllocEx, so that you have the right to use WriteProcessMemory on that page, and also the right to execute that memory when you get to step 4. This is the "lazy" way that leads to having RWX buffers hanging around. The alternative way is to pass PAGE_READWRITE when allocating the block, then write the code, and call VirtualProtectEx to swap the flag over to PAGE_EXECUTE_READ before step 4. This gives you an RW buffer when copying data, then an RX buffer when executing.
Pseudocode:*/
/*rights = PROCESS_VM_OPERATION |
PROCESS_VM_READ | PROCESS_VM_WRITE |
PROCESS_QUERY_INFORMATION |
PROCESS_CREATE_THREAD;
handle = OpenProcess(rights, false, pid);
targetAddr = VirtualAllocEx(handle, NULL, 4096, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
buffer = "Hello, world!\0";
bytesWritten = 0;
WriteProcessMemory(handle, targetAddr, buffer, 14, &bytesWritten);
oldProtect = 0;
VirtualProtectEx(handle, targetAddr, 4096, PAGE_EXECUTE_READ, &oldProtect);
threadId = 0;
CreateRemoteThread(handle, NULL, 0, targetAddr, NULL, 0, &threadId);*/

