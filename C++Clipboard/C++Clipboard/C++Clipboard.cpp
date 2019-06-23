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
		// lock and copy
		copy = (LPSTR)GlobalLock(clip);
		compare = copy;
		// unlock 
		GlobalUnlock(clip);
		CloseClipboard();
	}

	//Grabs current time
	time_t a = time(nullptr);
	struct tm time_info;
	if (localtime_s(&time_info, &a) == 0) strftime(currentTime, sizeof(currentTime), "%H:%M:%S", &time_info);

	//Prints current time
	cout << currentTime;

	//Prints updated clipboard
	cout << " - Clipboard updated: " + copy + " \n" << endl;

	//Loop and check if copy and compare are the same
	while (copy == compare) {
		Sleep(1000);

		if (OpenClipboard(NULL))
		{
			HANDLE clip;
			clip = GetClipboardData(CF_TEXT);
			// lock and copy
			compare = (LPSTR)GlobalLock(clip);
			// unlock 
			GlobalUnlock(clip);
			CloseClipboard();
		}
	}

	//if not, return to main and call recursively 
	main();
}
