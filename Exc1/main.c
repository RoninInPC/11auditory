#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <io.h>
int filesize(FILE* fp)
{	
	int savePos, sizeOfFile;
	savePos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	sizeOfFile = ftell(fp);
	fseek(fp, savePos, SEEK_SET);
	return(sizeOfFile);
}
char* WcharToChar(WCHAR* Name) {
	int k = 0;
	char* Ans = malloc(k*sizeof(char));
	for (int i = 0; i < MAX_PATH; i++) {
		k++;
		Ans = realloc(Ans, k * sizeof(char));
		Ans[k - 1] = (char)Name[i];
	}
	k++;
	Ans[k - 1] = '\0';
	return Ans;
}
int main()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf = FindFirstFile(L"*.txt", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			FILE* fp;
			char* File = WcharToChar(FindFileData.cFileName);
			fopen_s(&fp,File, "r+");
			if (filesize(fp) > 20) {
				wprintf(L"%s\n", FindFileData.cFileName);
			}
			fclose(fp);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	return 0;
}
		