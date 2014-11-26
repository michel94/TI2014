
#include "GIFencoder.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <math.h>
#include <iostream>

using namespace std;

map<string, int> dict;
int ncodes=0, bit_position = 0;
char towrite[1000000];
int CLEARCODE, ENDOFINF;

// convers�o de um objecto do tipo Image numa imagem indexada
imageStruct* GIFEncoder(unsigned char *data, int width, int height) {

	imageStruct* image = (imageStruct*)malloc(sizeof(imageStruct));
	image->width = width;
	image->height = height;

	//converter para imagem indexada
	RGB2Indexed(data, image);

	return image;
}

//convers�o de lista RGB para indexada: m�ximo de 256 cores
void RGB2Indexed(unsigned char *data, imageStruct* image) {
	int x, y, colorIndex, colorNum = 0;
	char *copy;

	image->pixels = (char*)calloc(image->width*image->height, sizeof(char));
	image->colors = (char*)calloc(MAX_COLORS * 3, sizeof(char));


	for (x = 0; x < image->width; x++) {
		for (y = 0; y < image->height; y++) {
			for (colorIndex = 0; colorIndex < colorNum; colorIndex++) {
				if (image->colors[colorIndex * 3] == (char)data[(y * image->width + x)*3] &&
					image->colors[colorIndex * 3 + 1] == (char)data[(y * image->width + x)*3 + 1] &&
					image->colors[colorIndex * 3 + 2] == (char)data[(y * image->width + x)*3 + 2])
					break;
			}

			if (colorIndex >= MAX_COLORS) {
				printf("Demasiadas cores...\n");
				exit(1);
			}

			image->pixels[y * image->width + x] = (char)colorIndex;

			if (colorIndex == colorNum)
			{
				image->colors[colorIndex * 3]	  = (char)data[(y * image->width + x)*3];
				image->colors[colorIndex * 3 + 1] = (char)data[(y * image->width + x)*3 + 1];
				image->colors[colorIndex * 3 + 2] = (char)data[(y * image->width + x)*3 + 2];
				colorNum++;
			}
		}
	}

	//define o n�mero de cores como pot�ncia de 2 (devido aos requistos da Global Color Table)
	image->numColors = nextPower2(colorNum);

	//refine o array de cores com base no n�mero final obtido
	copy = (char*)calloc(image->numColors*3, sizeof(char));
	memset(copy, 0, sizeof(char)*image->numColors*3);
	memcpy(copy, image->colors, sizeof(char)*colorNum*3);
	image->colors = copy;

	image->minCodeSize = numBits(image->numColors - 1);
	if (image->minCodeSize == (char)1)  //imagens bin�rias --> caso especial (p�g. 26 do RFC)
		image->minCodeSize++;
}


//determina��o da pr�xima pot�ncia de 2 de um dado inteiro n
int nextPower2(int n) {
	int ret = 1, nIni = n;

	if (n == 0)
		return 0;

	while (n != 0) {
		ret *= 2;
		n /= 2;
	}

	if (ret % nIni == 0)
		ret = nIni;

	return ret;
}


//n�mero de bits necess�rio para representar n
char numBits(int n) {
	char nb = 0;

	if (n == 0)
		return 0;

	while (n != 0) {
		nb++;
		n /= 2;
	}

	return nb;
}

int printBytes(int a, int n, FILE* file){
	if(n < 0 || n > 4)
		return 1;

	int i;
	for(i=0; i<n; i++){
		fprintf(file, "%d\n", (a << 24) >> 24);
		a = a >> 8;
	}
	return 0;

}

void writeImageBlockHeader(imageStruct* image, FILE* file){
	fprintf(file, "%c", (2 << 4) + 12); //0x2c
	fprintf(file, "%c%c", 0, 0); //image left position - 2 bytes
	fprintf(file, "%c%c", 0, 0); //image top position - 2 bytes

	fprintf(file, "%c", (char)( image->width & 0xFF));
	fprintf(file, "%c", (char)((image->width >> 8) & 0xFF));
	fprintf(file, "%c", (char)( image->height & 0xFF));
	fprintf(file, "%c", (char)((image->height >> 8) & 0xFF));

	//page 12 - GIF.SPEC.PDF

	char lctf = 0 << 7;	// Local Color Table present
	char iflag = 0 << 6;	// Image interlaced
	char sflag = 0 << 5;	// Local Color Table sorted
	//res?
	char s_lct = 0;		//Size of Local Color Table

	fprintf(file, "%c", (lctf | iflag | sflag | s_lct) );
	fprintf(file, "%c", numBits(image->numColors - 1));
}

void fillDict(int ncolors){
	for(int i=0; i<ncolors; i++){
		string s(1, i);
		dict[s] = i;
	}
	CLEARCODE = ncolors;
	ENDOFINF = ncolors+1;
	dict[string(1, CLEARCODE)] = CLEARCODE;
	dict[string(1, ENDOFINF)] = ENDOFINF;
}

bool inDict(string s){
	return dict.find(s) != dict.end();
}

void writeBits(int n, int nbits,  FILE* file){

	int bit;
	for(int i=0; i<nbits; i++, n = n >> 1){

		bit = 1 & n;
		bit = bit << bit_position;
		towrite[ncodes] = towrite[ncodes] | bit;

		bit_position++;
		if(bit_position == 8){
			printf("%d\n", towrite[ncodes]);
			fprintf(file, "%c", towrite[ncodes]);

			ncodes++;
			bit_position = 0;

			if(ncodes % 256 == 0)
				writeBits(255, 8, file);
		}
	}
}


void LZWCompress(FILE* file, int minCodeSize, char* pixels, int npixels, int ncolors){
	int imgpos=0;
	char c;

	fillDict(ncolors);

	//first block size and clearcode
	writeBits(255, 8, file); //sub-block size
	writeBits(CLEARCODE, (int)numBits(dict.size() - 1), file);  //clearcode

	string s = string(1, pixels[imgpos++]);
	while(imgpos < npixels){

		c = pixels[imgpos++];
		if(inDict(s + c)){
			s += c;
		}
		else{

			writeBits(dict[s], (int)numBits(dict.size() - 1), file);
			dict[s+c] = (int)dict.size() - 1;
			s = string(1, c);

		}
		if(dict.size() == 4096){
			printf("CLEAR DICT\n");
			writeBits(CLEARCODE, numBits(dict.size() - 1), file);
			dict.clear();
			fillDict(ncolors);
		}
	}

	//end of information
	writeBits(ENDOFINF, (int)numBits(dict.size() - 1), file);

	//escrever o byte que está em buffer
	//if(bit_position != 0)
		
		//writeBits(ENDOFINF, (int)numBits(dict.size() - 1), file);
		
		//fprintf(file, "%c", towrite[ncodes]);


	printf("towrite %d\n", towrite[ncodes - ncodes % 256]);
	towrite[ncodes - ncodes % 256] = ncodes % 256;

	for(int i = ncodes - ncodes % 256; i < ncodes; i++){
		fprintf(file, "%c", towrite[i]);
	}
}


void GIFEncoderWrite(imageStruct* image, char* outputFile) {

	FILE* file = fopen(outputFile, "wb");
	char trailer, terminator, eoi;

	writeGIFHeader(image, file);
	writeImageBlockHeader(image, file);


	LZWCompress(file, image->minCodeSize, image->pixels, image->width*image->height, image->numColors);

	//block terminator
	terminator = 0x00;
	fprintf(file, "%c", terminator);

	//trailer
	trailer = 0x3b;
	fprintf(file, "%c", trailer);

	fclose(file);
}


//--------------------------------------------------
//gravar cabe�alho do GIF (at� global color table)
void writeGIFHeader(imageStruct* image, FILE* file) {

	int i;
	char toWrite, GCTF, colorRes, SF, sz, bgci, par;

	//Assinatura e vers�o (GIF87a)
	char s[] = "GIF87a";
	for (i = 0; i < (int)strlen(s); i++)
		fprintf(file, "%c", s[i]);

	//Ecr� l�gico (igual � da dimens�o da imagem) --> primeiro o LSB e depois o MSB
	fprintf(file, "%c", (char)( image->width & 0xFF));
	fprintf(file, "%c", (char)((image->width >> 8) & 0xFF));
	fprintf(file, "%c", (char)( image->height & 0xFF));
	fprintf(file, "%c", (char)((image->height >> 8) & 0xFF));

	//GCTF, Color Res, SF, size of GCT
	GCTF = 1;
	colorRes = 7;  //n�mero de bits por cor prim�ria (-1)
	SF = 0;
	sz = numBits(image->numColors - 1) - 1; //-1: 0 --> 2^1, 7 --> 2^8
	toWrite = (char) (GCTF << 7 | colorRes << 4 | SF << 3 | sz);
	fprintf(file, "%c", toWrite);

	//Background color index
	bgci = 0;
	fprintf(file, "%c", bgci);

	//Pixel aspect ratio
	par = 0; // 0 --> informa��o sobre aspect ratio n�o fornecida --> decoder usa valores por omiss�o
	fprintf(file, "%c",par);

	//Global color table
	for (i = 0; i < image->numColors * 3; i++)
		fprintf(file, "%c", image->colors[i]);


}
