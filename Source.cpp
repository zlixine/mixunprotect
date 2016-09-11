/**
*	C&C mix unprotector.
*   Originally By: Askaledd
*   Modified By Zlixine
*	Drag-n-drop mix files on mixunprotect.exe to unprotect them.
*
*	Based on instructions given at:
*	http://www.modenc.renegadeprojects.com/Unprotecting_a_protected_MIX
*/
#include <iostream>

#define PACKED
#pragma pack(push,1)

typedef struct mix_header 
{
	unsigned int flags;
	unsigned short file_count;
	unsigned int body_size;
}mix_header PACKED;

int main(int argc, char** argv)
{
	printf("---Starting Un-Scrambler\n");
	printf("----------------\n C&C mix unprotector V.2.\n Originally By : Askaledd\n Modified By Zlixine\n Drag and drop mix files on mixunprotect.exe to unprotect them. \n Based on instructions given at : \n http ://www.modenc.renegadeprojects.com/Unprotecting_a_protected_MIX \n ----------------\n");
	FILE* mix;
	int i, file_size;
	mix_header header;

	if (argc < 2)
	{

		printf("ERROR: NO ARGUMENT FOUND!!!\n");
		system("pause");
		return 0;
	}

	for (i = 1; i < argc; ++i)
	{
		if (!(mix = fopen(argv[i], "rb+")))
		{
			printf("ERROR: FILE DOESN'T EXIST\n", argv[i]);
			system("pause");
			return 0;
		}

		fseek(mix, 0, SEEK_END);
		file_size = ftell(mix);

		fseek(mix, 0, SEEK_SET);
		fread(&header, sizeof(header), 1, mix);

		if (header.flags & 0x00020000)
		{
			printf("ERROR: MIX FILE IS ENCRYPTED!\n", argv[i]);
			system("pause");
			return 0;
		}
		else
		{
			header.flags = 0;
			header.body_size = file_size - (12 * header.file_count) - 10;

			fseek(mix, 0, SEEK_SET);
			fwrite(&header, sizeof(header), 1, mix);
		}

		
		fclose(mix);
	}
	printf("Done!! Check Your Mix File!\n");
	system("pause");
	return 0;
}