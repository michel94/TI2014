#include "GIFencoder.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <math.h>

map<string, int> dict;
int buff=0, curnbits=0, ncodes=0;
char towrite[1000000];

// conversão de um objecto do tipo Image numa imagem indexada
imageStruct* GIFEncoder(unsigned char *data, int width, int height) {
	
	imageStruct* image = (imageStruct*)malloc(sizeof(imageStruct));
	image->width = width;
	image->height = height;

	//converter para imagem indexada
	RGB2Indexed(data, image);

	return image;
}
		
//conversão de lista RGB para indexada: máximo de 256 cores
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

	//define o número de cores como potência de 2 (devido aos requistos da Global Color Table)
	image->numColors = nextPower2(colorNum);

	//refine o array de cores com base no número final obtido
	copy = (char*)calloc(image->numColors*3, sizeof(char));
	memset(copy, 0, sizeof(char)*image->numColors*3);
	memcpy(copy, image->colors, sizeof(char)*colorNum*3);
	image->colors = copy;

	image->minCodeSize = numBits(image->numColors - 1);
	if (image->minCodeSize == (char)1)  //imagens binárias --> caso especial (pág. 26 do RFC)
		image->minCodeSize++;
}
	
		
//determinação da próxima potência de 2 de um dado inteiro n
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
	
	
//número de bits necessário para representar n
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
	fprintf(file, "%c", 2*16 + 12); //0x2c
	fprintf(file, "\0\0"); //image left position - 2 bytes
	fprintf(file, "\0\0"); //image top position - 2 bytes
	printBytes(image->width, 2, file); // width - 2 bytes
	printBytes(image->height, 2, file); // width - 2 bytes
	
	//page 12 - GIF.SPEC.PDF

	char lctf = 0 << 7;	// Local Color Table present
	char iflag = 0 << 6;	// Image interlaced
	char sflag = 0 << 5;	// Local Color Table sorted
	//res?
	char s_lct = 0;		//Size of Local Color Table
	
	fprintf(file, "%c", (lctf | iflag | sflag | s_lct) );
	fprintf(file, "%c", numBits(image->numColors));
}

void fillDict(int ncolors){
	for(int i=0; i<ncolors; i++){
		string s(1, i);
		dict[s] = i;
	}
	int CLEARCODE = ncolors+1;
	int ENDOFINF = ncolors+2;
	dict["00000000000000"] = CLEARCODE;
	dict["00000000000001"] = ENDOFINF;
}

bool inDict(string s){
	return dict.find(s) != dict.end();
}

void cleanbuffer(){
	while(curnbits >= 8){
		towrite[ncodes++] = (char) ((buff << 24) >> 24);
		curnbits -= 8;
	}
	
}

void writeBits(int n, int nbits){
	for(int i=0; i<nbits; i++){
		buff = (buff << 1) | (n % 2);
		n = n >> 1;
	}
	curnbits += nbits;
	cleanbuffer();
	//fprintf(file, "%c\n", reverse((char) ((n << 24) >> 24)) );
}

char reverse(char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

void LZWCompress(FILE* file, int minCodeSize, char* pixels, int npixels, int ncolors){
	int imgpos=0;
	char c;
	fillDict(ncolors);

	printf("ncolors: %d\n", ncolors);
	writeBits(ncolors+1, numBits(dict.size()) );

	string s = string(1, pixels[imgpos++]);
	while(imgpos < npixels){
		c = pixels[imgpos++];
		if(inDict(s + c)){
			s += c;
		}else{
			printf("size: %d\n", dict.size());
			writeBits(dict[s], numBits(dict.size()) );
			string s2 = s+c;
			dict[s2] = (int)dict.size();
			for(int o=0; o < s2.size(); o++)
				printf("%d ", s2[o]);
			cout << endl;
			s = string(1, c);
		}
		if(dict.size() == 4096){
			printf("CLEAR DICT\n");
			writeBits(ncolors+1, numBits(dict.size()) );
			dict.clear();
			fillDict(ncolors);
		}

	}
	for(int i=0; i<ncodes; i++){
		printf("%d\n", reverse(towrite[i]));
	}

}

//---- Função para escrever imagem no formato GIF, versão 87a
//// COMPLETAR ESTA FUNÇÃO
void GIFEncoderWrite(imageStruct* image, char* outputFile) {
	
	FILE* file = fopen(outputFile, "wb");
	char trailer;

	//Escrever cabeçalho do GIF
	writeGIFHeader(image, file);
	
	//Escrever cabeçalho do Image Block
	// CRIAR FUN‚ÌO para ESCRITA do IMAGE BLOCK HEADER!!!
	//Sugest‹o da assinatura do mŽtodo a chamar:
	//
	writeImageBlockHeader(image, file);
	
	/////////////////////////////////////////
	//Escrever blocos com 256 bytes no m‡ximo
	/////////////////////////////////////////
	//CODIFICADOR LZW AQUI !!!! 
	//Sugest‹o de assinatura do mŽtodo a chamar:
	//
	// LZWCompress(file, image->minCodeSize, image->pixels, image->width*image->height);
	printf("w:%d h:%d\n", image->width, image->height);
	LZWCompress(file, image->minCodeSize, image->pixels, image->width*image->height, image->numColors);
	
	fprintf(file, "%c", (char)0);
	
	//trailer
	trailer = 0x3b;
	fprintf(file, "%c", trailer);
	
	fclose(file);
}
	
	
//--------------------------------------------------
//gravar cabeçalho do GIF (até global color table)
void writeGIFHeader(imageStruct* image, FILE* file) {

	int i;
	char toWrite, GCTF, colorRes, SF, sz, bgci, par;

	//Assinatura e versão (GIF87a)
	char s[] = "GIF87a";
	for (i = 0; i < (int)strlen(s); i++)
		fprintf(file, "%c", s[i]);

	//Ecrã lógico (igual à da dimensão da imagem) --> primeiro o LSB e depois o MSB
	fprintf(file, "%c", (char)( image->width & 0xFF));
	fprintf(file, "%c", (char)((image->width >> 8) & 0xFF));
	fprintf(file, "%c", (char)( image->height & 0xFF));
	fprintf(file, "%c", (char)((image->height >> 8) & 0xFF));
	
	//GCTF, Color Res, SF, size of GCT
	GCTF = 1;
	colorRes = 7;  //número de bits por cor primária (-1)
	SF = 0;
	sz = numBits(image->numColors - 1) - 1; //-1: 0 --> 2^1, 7 --> 2^8
	toWrite = (char) (GCTF << 7 | colorRes << 4 | SF << 3 | sz);
	fprintf(file, "%c", toWrite);
	
	//Background color index
	bgci = 0;
	fprintf(file, "%c", bgci);
	
	//Pixel aspect ratio
	par = 0; // 0 --> informação sobre aspect ratio não fornecida --> decoder usa valores por omissão
	fprintf(file, "%c",par);

	//Global color table
	for (i = 0; i < image->numColors * 3; i++)
		fprintf(file, "%c", image->colors[i]);


}