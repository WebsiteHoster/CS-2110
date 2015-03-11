// Jesse Chen

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// This is the array into which you will load the raw data from the file
unsigned char data_arr[0x36 + 240 * 160 * 4];

int main(int argc, char *argv[]) {

	// 1. Make sure the user passed in the correct number of arguments
	if (argc != 2) {
		printf("Invalid number of arguments.\n");
		return -1;
	}

	// 2. Open the file; if it doesn't exist, tell the user and then exit
	FILE *fileIn = fopen(argv[1],  "rb");
	if (fileIn == NULL) {
		printf("File not found.\n");
		return -1;
	}

	// 3. Read the file into the buffer then close it when you are done
	int bytesRead = fread(data_arr, 1, sizeof(data_arr), fileIn);
	for (int i = 0x36 + 1; i <= bytesRead; i += 4) {
		data_arr[i - 1] /= 8;
		printf("B=0x%02X, ", data_arr[i - 1]);
		data_arr[i] /= 8;
		printf("G=0x%02X, ", data_arr[i]);
		data_arr[i + 1] /= 8;
		printf("R=0x%02X, ", data_arr[i + 1]);

		if ((i - 0x36) % 16 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	fclose(fileIn);

	// 4. Get the width and height of the image
	int width, height;

	int* pdata_arr = (int*) (data_arr + 0x12);
	width = *pdata_arr;

	pdata_arr = (int*) (data_arr + 0x16);
	height = *pdata_arr;

	// 5. Create header file, and write header contents; close it
	char* fileName = argv[1];
	char shortName[100];
	int length = strlen(fileName);

	fileName[length - 4] = '\0';
	strcpy(shortName, fileName);
	strcat(fileName, ".h");
	FILE *headerFile = fopen(fileName, "w");

	length = strlen(shortName);
	char caps[length];
	for (int  i = 0; i <= length; i++) {
		caps[i] = toupper(shortName[i]);
	}

	fprintf(headerFile, "#define %s_WIDTH %i\n", caps, width);
	fprintf(headerFile, "#define %s_HEIGHT %i\n", caps, height);
	fprintf(headerFile, "const unsigned short %s_data[%i];", shortName, width * height);

	fclose(headerFile);

	// 6. Create c file, and write pixel data; close it
	fileName[length] = '\0';
	strcat(fileName, ".c");
	FILE *dataFile = fopen(fileName, "w");

	printf("\n");
	unsigned short colorData[sizeof(data_arr) - 0x36];
	for (int i = 0; i < bytesRead; i++) {
		colorData[i] = (data_arr[i + 0x36] << 10) | (data_arr[i + 0x37] << 5) | data_arr[i + 0x38];
		printf("0x%04X, ", colorData[i]);
	}
	printf("\n");

	fprintf(dataFile, "const unsigned short %s_data[%i] = {", shortName, width * height);

	unsigned short gbaData[sizeof(data_arr)];
	int k = 0;
	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			unsigned short gbaPixel = gbaData[width * i + j];
			gbaPixel = colorData[k];
			k++;

			if ((width * i + j) % 10 == 0) {
				fprintf(dataFile, "\n\t");
			}
			fprintf(dataFile, "0x%04X, ", gbaPixel);
		}
	}

	/*for (int i = 0x36; i < bytesRead; i += 4) {
		if ((i - 0x36) % 40 == 0) {
			fprintf(dataFile, "\n\t");
		}

		unsigned short gbaPixel = (gbaData[i] << 10) | (gbaData[i + 1] << 5) | gbaData[i + 2];
		fprintf(dataFile, "0x%04X, ", gbaPixel);
	}*/

	fprintf(dataFile, "\n};");

	fclose(dataFile);

	return 0;
}

