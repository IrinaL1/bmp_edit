#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int64_t LONG;

typedef struct tagBITMAPFILEHEADER
{
	WORD bfTYPE;
	DWORD bfSIZE;
	WORD bfRes1;
	WORD bfRes2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
   DWORD  biSize;
   LONG   biWidth;
   LONG   biHeight;
   WORD   biPlanes;
   WORD   biBitCount;
   DWORD  biCompression;
   DWORD  biSizeImage;
   LONG   biXPelsPerMeter;
   LONG   biYPelsPerMeter;
   DWORD  biClrUsed;
   DWORD  biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
   BYTE    rgbBlue;
   BYTE    rgbGreen;
   BYTE    rgbRed;
   BYTE    rgbReserved;
} RGBQUAD;

RGBQUAD * read_bmp (DWORD * pbfSIZE, const char * fin_name);

RGBQUAD * read_bmp (DWORD * pbfSIZE, const char * fin_name){
	
	FILE * fin = fopen(fin_name, "rb");
	
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	if (fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fin) != sizeof(BITMAPFILEHEADER)){
		perror("fread bfh: ");
		return NULL;
	}
	
	if (bfh.bfTYPE != 0x424D){
		printf("Wrong type of file\n");
		return NULL;
	}

	*pbfSIZE = bfh.bfSIZE;
		
	if (fread(&bih, sizeof(BITMAPINFOHEADER), 1, fin) != sizeof(BITMAPINFOHEADER)){
		perror("fread bih: ");
		return NULL;
	}

	if (fseek(fin, bfh.bfOffBits, SEEK_SET) == -1){
		perror("fseek :");
		return NULL;
	}

	long long int numPix = 0;
	numPix = bih.biWidth * bih.biHeight;
	RGBQUAD * inBuf = calloc(numPix, sizeof(RGBQUAD));

	for (int i = 0; i < numPix; i++)
		if (fread(inBuf + i, sizeof(RGBQUAD), 1, fin) != sizeof(RGBQUAD)){
			perror("fread RGBQUAD: ");
			return NULL;
		}
	
	return inBuf;
}

