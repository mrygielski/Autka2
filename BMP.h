#ifndef __BMP_GGATE
#define __BMP_GGATE

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SaveBMP(char *FileName,int width,int height);
int write8BitBmpFile(char *filename,unsigned int width,unsigned int height,unsigned char *image,unsigned int numPaletteEntries,RGBQUAD *palette);
int write24BitBmpFile(char *filename,unsigned int width,unsigned int height,unsigned char *image);
int writeGrayScaleDataToBmpFile(char *filename,unsigned int width,unsigned int height,unsigned char *image);


////////////////////////////////////////////////////////////////////
void SaveBMP(char *FileName,int width,int height)
{ 
  int LightMapWidth = width;  
  int LightMapHeight =height;
  unsigned char *LightMapImage;
  LightMapImage = new unsigned char[(LightMapWidth*LightMapHeight)*3];

  int y,off,i;
	unsigned char *kolorki;
	kolorki=new unsigned char[LightMapWidth*3];

	for (y=0;y<height;y++)
	{
		off=(( ( (height-1)-y) *width))*3;
		glReadPixels(0,y,width,1,GL_RGB,0x1401,kolorki);
		for (i=0;i<width*3;i++) LightMapImage[off+i]=kolorki[i];
	}

  write24BitBmpFile(FileName, LightMapWidth, LightMapHeight, LightMapImage);
  delete [] LightMapImage;
	delete [] kolorki;
}

int write8BitBmpFile(char *filename, unsigned int width, unsigned int height, 
							unsigned char *image, unsigned int numPaletteEntries, RGBQUAD *palette)
{
	BITMAPINFOHEADER bmpInfoHeader;
	BITMAPFILEHEADER bmpFileHeader;
	FILE *filep;
	unsigned int row;
	unsigned int extrabytes, bytesize;
	unsigned char *paddedImage = NULL;
  extrabytes = (4 - width % 4) % 4;
	bytesize = (width + extrabytes) * height;
	bmpFileHeader.bfType = 'MB';   // Bitmap header
	bmpFileHeader.bfSize = 0;      // This can be 0 for BI_RGB bitmaps
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * numPaletteEntries;
	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfoHeader.biWidth = width;
	bmpInfoHeader.biHeight = height;
	bmpInfoHeader.biPlanes = 1;
	bmpInfoHeader.biBitCount = 8;            // 8 - bit bitmap
	bmpInfoHeader.biCompression = BI_RGB;
	bmpInfoHeader.biSizeImage = bytesize;     // includes padding for 4 byte alignment
	bmpInfoHeader.biXPelsPerMeter = 2952;
	bmpInfoHeader.biYPelsPerMeter = 2952;
	bmpInfoHeader.biClrUsed = numPaletteEntries;
	bmpInfoHeader.biClrImportant = 0;
	if ((filep = fopen(filename, "wb")) == NULL) {
		printf("Error opening file %s\n", filename);
		return FALSE;
	}
	if (fwrite(&bmpFileHeader, 1, sizeof(BITMAPFILEHEADER), filep) < sizeof(BITMAPFILEHEADER)) {
		printf("Error writing bitmap file header\n");
		fclose(filep);
		return FALSE;
	}
	if (fwrite(&bmpInfoHeader, 1, sizeof(BITMAPINFOHEADER), filep) < sizeof(BITMAPINFOHEADER)) {
		printf("Error writing bitmap info header\n");
		fclose(filep);
		return FALSE;
	}
	if (fwrite(palette, 1, numPaletteEntries * sizeof(RGBQUAD), filep) < numPaletteEntries * sizeof(RGBQUAD)) {
		printf("Error writing bitmap palette\n");
		fclose(filep);
		return FALSE;
	}
	paddedImage = (unsigned char *)calloc(sizeof(unsigned char), bytesize);
	if (paddedImage == NULL) {
		printf("Error allocating memory \n");
		fclose(filep);
		return FALSE;
	}
	for (row = 0; row < height; row++)
		memcpy(&paddedImage[row * (width + extrabytes)], &image[(height - 1 - row) * width], width);
	if (fwrite(paddedImage, 1, bytesize, filep) < bytesize) {
		printf("Error writing bitmap data\n");
		free(paddedImage);
		fclose(filep);
		return FALSE;
	}
	fclose(filep);
	free(paddedImage);
	return TRUE;
}
int write24BitBmpFile(char *filename, unsigned int width, unsigned int height, unsigned char *image)
{
	BITMAPINFOHEADER bmpInfoHeader;
	BITMAPFILEHEADER bmpFileHeader;
	FILE *filep;
	unsigned int row, column;
	unsigned int extrabytes, bytesize;
	unsigned char *paddedImage = NULL, *paddedImagePtr, *imagePtr;
  extrabytes = (4 - (width * 3) % 4) % 4;
	bytesize = (width * 3 + extrabytes) * height;
	bmpFileHeader.bfType = 'MB';   // Bitmap header
	bmpFileHeader.bfSize = 0;      // This can be 0 for BI_RGB bitmaps
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfoHeader.biWidth = width;
	bmpInfoHeader.biHeight = height;
	bmpInfoHeader.biPlanes = 1;
	bmpInfoHeader.biBitCount = 24;            // 8 - bit bitmap
	bmpInfoHeader.biCompression = BI_RGB;
	bmpInfoHeader.biSizeImage = bytesize;     // includes padding for 4 byte alignment
	bmpInfoHeader.biXPelsPerMeter = 2952;
	bmpInfoHeader.biYPelsPerMeter = 2952;
	bmpInfoHeader.biClrUsed = 0;
	bmpInfoHeader.biClrImportant = 0;
	if ((filep = fopen(filename, "wb")) == NULL) {
		printf("Error opening file %s\n", filename);
		return FALSE;
	}
	if (fwrite(&bmpFileHeader, 1, sizeof(BITMAPFILEHEADER), filep) < sizeof(BITMAPFILEHEADER)) {
		printf("Error writing bitmap file header\n");
		fclose(filep);
		return FALSE;
	}
	if (fwrite(&bmpInfoHeader, 1, sizeof(BITMAPINFOHEADER), filep) < sizeof(BITMAPINFOHEADER)) {
		printf("Error writing bitmap info header\n");
		fclose(filep);
		return FALSE;
	}
	paddedImage = (unsigned char *)calloc(sizeof(unsigned char), bytesize);
	if (paddedImage == NULL) {
		printf("Error allocating memory \n");
		fclose(filep);
		return FALSE;
	}
	for (row = 0; row < height; row++) {
		imagePtr = image + (height - 1 - row) * width * 3;
		paddedImagePtr = paddedImage + row * (width * 3 + extrabytes);
		for (column = 0; column < width; column++) {
			*paddedImagePtr = *(imagePtr + 2);
			*(paddedImagePtr + 1) = *(imagePtr + 1);
			*(paddedImagePtr + 2) = *imagePtr;
			imagePtr += 3;
			paddedImagePtr += 3;
		}
	}
	if (fwrite(paddedImage, 1, bytesize, filep) < bytesize) {
		printf("Error writing bitmap data\n");
		free(paddedImage);
		fclose(filep);
		return FALSE;
	}
	fclose(filep);
	free(paddedImage);
	return TRUE;
}
int writeGrayScaleDataToBmpFile(char *filename, unsigned int width, unsigned int height, unsigned char *image)
{
	RGBQUAD palette[256];
	unsigned int i;
   unsigned int numPaletteEntries = 256;
	for (i = 0; i < numPaletteEntries; i++) {
		palette[i].rgbRed = i;
		palette[i].rgbGreen = i;
		palette[i].rgbBlue = i;
		palette[i].rgbReserved = 0;
	}
   return write8BitBmpFile(filename, width, height, image, numPaletteEntries, palette);
}





#endif