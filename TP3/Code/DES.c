/*Author: Rui Pedro Paiva
Teoria da Informa��o, LEI, 2008/2009*/

#include "DES.h"

//fun��o para encripta��o
int DES (char* inFileName, unsigned long long key)
{
	return DESgeneral(inFileName, key, 0);
}


//fun��o para decripta��o
int unDES (char* inFileName, unsigned long long key)
{
	return DESgeneral(inFileName, key, 1);
}


//fun��o geral para encripta��o (type = 0) e decripta��o (type = 1) de um ficheiro 
int DESgeneral (char* inFileName, unsigned long long key, int type)
{
	FILE* DESInFile;
	unsigned char* inByteArray;
	long inFileSize;
	unsigned char* crpByteArray;
	char* outFileName;
	int write;
	char response;
	struct stat stFileInfo;
	FILE* DESOutFile;
	char suf[5];


	//abrir ficheiro e ler tamanho
	DESInFile = fopen(inFileName, "rb");
	if (DESInFile == NULL)
	{
		printf("Error opening file for reading. Exiting...\n");
		return 1;
	}
	fseek(DESInFile, 0L, SEEK_END);
	inFileSize = ftell(DESInFile);  //ignore EOF
	fseek(DESInFile, 0L, SEEK_SET);


	//ler ficheiro inteiro para array inByteArray	
	inByteArray = (unsigned char*) calloc(inFileSize, sizeof(unsigned char)); 
	fread(inByteArray, 1, inFileSize, DESInFile);


	//criar assinatura
	if (type == 0)  //encripta��o
	{
		/******* ADICIONAR C�DIGO: 
		 implementar � fun��o:
		 unsigned char* signature(unsigned char* inByteArray, long dim, unsigned long long key)  // ver abaixo
		 e adicionar hash aos dados
		 ***********************/
	}
	
	
	//encriptar dados e assinatura no array
	crpByteArray = encryptDES(inByteArray, inFileSize, key, type);
		
	//flush do crpByteArray para ficheiro
	//nome do ficheiro de sa�da
	if (type == 0)  //encripta��o
	{
		outFileName = (char*) calloc(strlen(inFileName) + 5, sizeof(char)); 
		strcpy(outFileName, inFileName);
		strcat(outFileName, ".DES");
	}
	else  //decripta��o
	{
		strcpy(suf, &inFileName[strlen(inFileName) - 4]);
		if (strcmp(suf, ".DES") == 0)
		{		
			outFileName = (char*) calloc(strlen(inFileName) + 5, sizeof(char)); 
			strcpy(outFileName, "DES_");
			strcat(outFileName, inFileName);
			outFileName[strlen(outFileName) - 4] = 0;
		}
		else
		{
			outFileName = (char*) calloc(14, sizeof(char));
			strcpy(outFileName, "DES_decrypted");
		}

	}
	
	
	//verificar assinatura
	if (type == 1)
	{
		/******* ADICIONAR C�DIGO: 
		 implementar � fun��o:
		 int checkSignature(unsigned char* inByteArray, unsigned char* hash)  // ver abaixo
		 e retirar hash aos dados
		 abortar desencripta��o caso a verifica��o da assinatura n�o passe no teste
		 ***********************/		
	}
	
	//criar ficheiro
	write = 1;
	if(stat(outFileName, &stFileInfo) == 0) //see if file already exists
	{
		printf ("File already exists. Overwrite (y/n)?: ");
		response = getchar();
		if (response == 'n')
			write = 0;
		printf("\n");
		fflush(stdin);
	}

	if (write)
	{
		DESOutFile = fopen(outFileName, "wb");
		if (DESOutFile == NULL)
		{
			printf("Error opening file for writing!!! Exiting...\n");
			return -1;
		}
		fwrite(crpByteArray, 1, inFileSize, DESOutFile);
		fclose(DESOutFile);
	}
	
	//finaliza��es
	free(inByteArray);
	free(outFileName);
	free(crpByteArray);
	fclose(DESInFile);

	return 0;	
}


// fun��o para encripta��o/decripta��o de dados no array inByteArray, de dimens�o dim
unsigned char* encryptDES(unsigned char* inByteArray, long dim, unsigned long long key, int type)
{
	unsigned long long subKeys[16];
	unsigned char* outByteArray;
	unsigned long long plain, cipher, aux1, aux2;
	int i, j;

	
	//obt�m sub-keys (16 de comprimento 48)
	/**** ADICIONAR C�DIGO PARA A FUN��O DESKEYSCHEDULE (ABAIXO) ********/
	DESKeySchedule(key, subKeys);


	if (type == 1) //decrypt --> inverter subKeys
	{
		/**************** ADICIONAR C�DIGO ****************************/
	}

	outByteArray = (unsigned char*) calloc(dim, sizeof(unsigned char)); 
	i = 0;
	plain = 0;
	while (i < dim)
	{
		plain = 0;
		j = i;
		while (j < i + 8 && j < dim)
		{
 			plain = plain | ((unsigned long long)inByteArray[j] << (64 - 8*(j-i+1)));
			j++;
		}

		//determina cifra
		if (j - i == 8)  //ficheiro � m�ltiplo de 8 bytes
			/**** ADICIONAR C�DIGO PARA A FUN��O ENCRYPTDESPLAIN (ABAIXO) ********/
			cipher = encryptDESplain(plain, subKeys);
		else
			cipher = plain;


		//guarda cifra no array de sa�da
		j = i;
		while (j < i + 8 && j < dim)
		{
			outByteArray[j] = (unsigned char) (cipher >> (56 - 8*(j-i)) & (0xFF));
			j++;
		}

		i = j;		
	}

	return outByteArray;
}


/************************************************************************************/
/***************************** ADICIONAR C�DIGO *************************************/
/************************************************************************************/


// fun��o para encripta��o de uma mensagem de 64 bits (plain), com base nas subKeys
//devolve a mensagem cifrada
unsigned long long encryptDESplain(unsigned long long plain, unsigned long long* subKeys)
{


}


// fun��o para gerar sub-keys (uma chave para cada uma das 16 itera��es)
void DESKeySchedule(unsigned long long key, unsigned long long* subKeys)
{

}


// fun��o para cria��o de de uma hash a partir dos dados do ficheiro, usando MDC-4
unsigned char* signature(unsigned char* inByteArray, long dim, unsigned long long key){

}


//fun��o para verifica��o da assinatura: verificar se a hash criada a partir dos dados � igual � hash recebida
int checkSignature(unsigned char* inByteArray, unsigned char* hash){
	
}
