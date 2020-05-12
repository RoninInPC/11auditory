#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <io.h>
int IsBinare(char* Name) {
	int ans = 0;
	int j = 0;
	while (1) {
		if (Name[j] == '.') {
			break;
		}
		j++;
	}
	j++;
	if (strlen(Name) - j == 3) {
		if (Name[j] == 'b' && Name[j+1] == 'i' && Name[j+2] == 'n') {
			ans = 1;
		}
		if (Name[j] == 'd' && Name[j+1] == 'a' && Name[j+2] == 't') {
			ans = 1;
		}
	}
	return ans;
}
char* WcharToChar(WCHAR* Name) {
	int k = 0;
	char* Ans = malloc(k * sizeof(char));
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
			fopen_s(&fp, File, "r+");
			if (IsBinare(File)==1) {
				wprintf(L"%s\n", FindFileData.cFileName);
			}
			fclose(fp);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	return 0;
}
