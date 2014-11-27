#ifndef GIFENCODER_HEADER
#define GIFENCODER_HEADER

#define MAX_COLORS 256

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cmath>
#include <map>
#include <string.h>

using namespace std;

typedef struct _imageStruct {
  int width;
  int height;
  char *pixels;
  char *colors;
  int numColors;
  char minCodeSize;
} imageStruct;

imageStruct* GIFEncoder(unsigned char *data, int width, int height);
void RGB2Indexed(unsigned char *data, imageStruct* image);
int nextPower2(int n);
char numBits(int n);
void GIFEncoderWrite(imageStruct* image, char* outputFile);
void writeGIFHeader(imageStruct* image, FILE* file);
void writeImageBlockHeader(imageStruct* image, FILE* file);

#endif
