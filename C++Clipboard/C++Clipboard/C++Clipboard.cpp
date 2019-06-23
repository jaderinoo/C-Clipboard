#include "pch.h"
#include <windows.h>
#include <iostream>
#include <winuser.h>
#include <winbase.h>
#include <chrono>
#include <ctime> 
#include <string> 
using namespace std;

void clippy();

int main()
{
	clippy();
}

void clippy()
{
	//Initialization
	string copy("Initialization");
	string compare("compare");
	char currentTime[32]{};

	//Pulls initial "copy" from clipboard and sets compare = copy
	if (OpenClipboard(NULL))
	{
		HANDLE clip;
		clip = GetClipboardData(CF_TEXT);
		//Lock and copy
		copy = (LPSTR)GlobalLock(clip);
		compare = copy;
		//Unlock 
		GlobalUnlock(clip);
		CloseClipboard();
	}

	//Grabs current time
	time_t a = time(nullptr);
	struct tm time_info;

	//Formats the time
	if (localtime_s(&time_info, &a) == 0) strftime(currentTime, sizeof(currentTime), "%H:%M:%S", &time_info);

	//Prints current time
	cout << currentTime;

	//Prints updated clipboard
	cout << " - Clipboard updated: " + copy + " \n" << endl;

	//Loop and check if copy and compare are the same
	while (copy == compare) {

		//Wait for 5 seconds before each check 
		//This can be changed to any amount of time
		Sleep(5000);

		if (OpenClipboard(NULL))
		{
			HANDLE clip;
			clip = GetClipboardData(CF_TEXT);
			//Lock and copy
			compare = (LPSTR)GlobalLock(clip);
			//Unlock 
			GlobalUnlock(clip);
			CloseClipboard();
		}
	}

	//If not, return to main and call recursively 
	main();
}
