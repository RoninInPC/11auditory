#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <string.h>
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
IMAGE_NT_HEADERS* GetHeader(LPBYTE pBase) {
	if (pBase == NULL)
		return NULL;
	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)pBase;
	if (IsBadReadPtr(pDosHeader, sizeof(IMAGE_DOS_HEADER)))
		return NULL;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return NULL;
	IMAGE_NT_HEADERS* pHeader = (IMAGE_NT_HEADERS*)(pBase + pDosHeader->e_lfanew);
	if (IsBadReadPtr(pHeader, sizeof(IMAGE_NT_HEADERS)))
		return NULL;
	if (pHeader->Signature != IMAGE_NT_SIGNATURE)
		return NULL;
	return pHeader;
}
int main()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf = FindFirstFile(L"*.*", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			FILE* fp;
			char* File = WcharToChar(FindFileData.cFileName);
			if (File[0] == '.') {
				continue;
			}
			int t = 1;
			for (int i = 0; i < strlen(File); i++) {
				if (File[i] == '.') {
					t = 0;
				}
			}
			if (t == 1) {
				continue;
			}
			
			fopen_s(&fp, File, "r+");
			char c;
			fscanf_s(fp,"%c", &c);
			char c1;
			fscanf_s(fp,"%c", &c1);
			char c2;
			fscanf_s(fp,"%c", &c2);
			char c3;
			fscanf_s(fp,"%c", &c3);
			if (c == 'M' && c1 == 'Z' || c == '0' && c1 == 'x' && c2 == '3' && c3 == 'C') {
				printf("%s\n", File);
			}
			fclose(fp);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	return 0;
}
