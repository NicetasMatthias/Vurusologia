#include <fileapi.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fileapi.h>

int main(int argc, char* argv[])
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char path[MAX_PATH];
	char pathExe[MAX_PATH];
	char pathBak[MAX_PATH];
	
	bool flag = false;

	// выясняем текущую директорию
	if (GetCurrentDirectory (sizeof (path), path))
    {
		strcpy (pathExe, path);
        lstrcat (pathExe, "\\*.exe");
    }
	else
	{
        printf ("error while recieving path %s\n", GetLastError ());
		return 1;
	}
		
	hFind = FindFirstFile(pathExe, &FindFileData);
	
	if (hFind == INVALID_HANDLE_VALUE)
    {
		printf ("Invalid file handle. Error is %u.\n", GetLastError ());
		return 2;
	}
	if (strstr (FindFileData.cFileName, argv[0]))
	{
		printf ("find myself || skip\n");
	}
	else
	{
		printf ("\n\nFind \"%s\"\n", FindFileData.cFileName);
		char tmpTxtName[MAX_PATH];
		char tmpExeName[MAX_PATH];
		char *isStr = strtok (FindFileData.cFileName, ".");
		strcpy (tmpTxtName, isStr);
		strcat (tmpTxtName, ".txt");
		strcpy (tmpExeName, isStr);
		strcat (tmpExeName, ".exe");
		
		if (GetFileAttributes(tmpTxtName) != DWORD(-1))
		{
			flag = true;
			SetFileAttributes (tmpTxtName, FILE_ATTRIBUTE_NORMAL);
			
			printf ("File \"%s\" set unhidden.\n", tmpTxtName);
			
			if (DeleteFile (tmpExeName) == 0)
			{
				printf ("File \"%s\" deletion error. Error is %u.\n", tmpExeName, GetLastError ());
			}
			else
			{
				printf ("File \"%s\" deleted.\n", tmpExeName);
			}
		}
	}
	while (FindNextFile(hFind, &FindFileData) != 0)
	{
		if (strstr (FindFileData.cFileName, argv[0]))
		{
			printf ("find myself || skip\n");
		}
		else
		{
		printf ("\n\nFind \"%s\"\n", FindFileData.cFileName);
			char tmpTxtName[MAX_PATH];
			char tmpExeName[MAX_PATH];
			char *isStr = strtok (FindFileData.cFileName, ".");
			strcpy (tmpTxtName, isStr);
			strcat (tmpTxtName, ".txt");
			strcpy (tmpExeName, isStr);
			strcat (tmpExeName, ".exe");
			
			if (GetFileAttributes(tmpTxtName) != DWORD(-1))
			{
				flag = true;
				SetFileAttributes (tmpTxtName, FILE_ATTRIBUTE_NORMAL);
				
				printf ("File \"%s\" set unhidden.\n", tmpTxtName);
				
				if (DeleteFile (tmpExeName) == 0)
				{
					printf ("File \"%s\" deletion error. Error is %u.\n", tmpExeName, GetLastError ());
				}
				else
				{
					printf ("File \"%s\" deleted.\n", tmpExeName);
				}
			}
		}
	}	
	
	if (flag)
	{
		printf ("\n\nBak files:\n");
		DeleteFile ("bat.bat");
		DeleteFile ("vbs.vbs");
		
		
		hFind = INVALID_HANDLE_VALUE;
		strcpy (pathBak, path);
        lstrcat (pathBak, "\\*.bak*");
		
		hFind = FindFirstFile(pathBak, &FindFileData);

		if (hFind == INVALID_HANDLE_VALUE)
		{
			return 0;
		}
		else
		{
			DeleteFile(FindFileData.cFileName);
			printf ("\t- %s\n", FindFileData.cFileName);
		}
		
		while (FindNextFile(hFind, &FindFileData) != 0)		
		{
			DeleteFile(FindFileData.cFileName);
			printf ("\t- %s\n", FindFileData.cFileName);
		}		
		printf ("Deleted.\n");
	}
	FindClose(hFind);
	return 0;
}