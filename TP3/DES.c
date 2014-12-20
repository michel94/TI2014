#include "DES.h"

//função para encriptação
int DES(char* inFileName, unsigned long long key) {
  return DESgeneral(inFileName, key, 0);
}

//funcao para decriptacao
int unDES(char* inFileName, unsigned long long key) {
  return DESgeneral(inFileName, key, 1);
}

//funcao geral para encriptacao (type = 0) e decriptacao (type = 1)
// de um ficheiro
int DESgeneral(char* inFileName, unsigned long long key, int type) {
  FILE* DESInFile;
  unsigned char* inByteArray;
  long inFileSize;
  unsigned char* crpByteArray;
  char* outFileName;
  FILE* DESOutFile;
  char suf[5];

  //abrir ficheiro e ler tamanho
  DESInFile = fopen(inFileName, "rb");

  if (DESInFile == NULL) {
    printf("Error opening file for reading. Exiting...\n");
    return 1;
  }

  fseek(DESInFile, 0L, SEEK_END);
  inFileSize = ftell(DESInFile);  // ignore EOF
  fseek(DESInFile, 0L, SEEK_SET);

  //ler ficheiro inteiro para array inByteArray
  inByteArray = (unsigned char*) calloc(inFileSize, sizeof(unsigned char));
  fread(inByteArray, 1, inFileSize, DESInFile);


  //encriptar dados e assinatura no array
  crpByteArray = encryptDES(inByteArray, inFileSize, key, type);

  //flush do crpByteArray para ficheiro
  //nome do ficheiro de saída
  if (type == 0) {
    outFileName = (char*) calloc(strlen(inFileName) + 5, sizeof(char));
    strcpy(outFileName, inFileName);
    strcat(outFileName, ".DES");
  } else {
    strcpy(suf, &inFileName[strlen(inFileName) - 4]);
    if (strcmp(suf, ".DES") == 0) {
      outFileName = (char*) calloc(strlen(inFileName) + 5, sizeof(char));
      strcpy(outFileName, "DES_");
      strcat(outFileName, inFileName);
      outFileName[strlen(outFileName) - 4] = 0;
    } else {
      outFileName = (char*) calloc(14, sizeof(char));
      strcpy(outFileName, "DES_decrypted");
    }
  }

  DESOutFile = fopen(outFileName, "wb");
  if (DESOutFile == NULL) {
    printf("Error opening file for writing!!! Exiting...\n");
    return -1;
  }

  fwrite(crpByteArray, 1, inFileSize, DESOutFile);
  fclose(DESOutFile);

  // finalizações
  free(inByteArray);
  free(outFileName);
  free(crpByteArray);
  fclose(DESInFile);

  return 0;
}

// função para encriptação/decriptação de dados no array inByteArray,
// de dimensão dim
unsigned char* encryptDES(unsigned char* inByteArray, long dim,
                          unsigned long long key, int type) {
  unsigned long long subKeys[16];
  unsigned char* outByteArray;
  unsigned long long plain, cipher;
  int i, j;

  //obtém sub-keys (16 de comprimento 48)
  DESKeySchedule(key, subKeys);

  if (type == 1) { //decrypt --> inverter subKeys
    for (i = 0; i < 8; i++) {
      unsigned long long temp = subKeys[i];
      subKeys[i] = subKeys[16 - i - 1];
      subKeys[16 - i - 1] = temp;
    }
  }

  outByteArray = (unsigned char*) calloc(dim, sizeof(unsigned char));
  i = 0;
  plain = 0;
  while (i < dim) {
    plain = 0;
    j = i;

    while (j < i + 8 && j < dim) {
      plain = plain | ((unsigned long long)inByteArray[j] <<
                       (64 - 8*(j-i+1)));
      j++;
    }

    //determina cifra
    if (j - i == 8)  //ficheiro múltiplo de 8 bytes
      cipher = encryptDESplain(plain, subKeys);
    else
      cipher = plain;

    //guarda cifra no array de saída
    j = i;
    while (j < i + 8 && j < dim) {
      outByteArray[j] = (unsigned char) (cipher >> (56 - 8*(j-i)) & (0xFF));
      j++;
    }

    i = j;
  }

  return outByteArray;
}


unsigned long long int permBase(unsigned long long int input, int inSize,
                                int* table, int outSize) {
  /*unsigned long long int output = 0;

    int i, index;
    unsigned long long int temp_mask;
    unsigned long long int mask = 0x0000000000000001;

    mask = mask << (inSize - 1);

    for (i = 0; i < outSize; i++) {
    index = table[i];
    temp_mask = mask >> (index - 1);
    temp_mask &= input;
    temp_mask >>= (inSize - index);

    output <<= 1;
    output |= temp_mask;
    }

    return output;*/

  unsigned long long int output = 0;
  unsigned long long int bit;
  int i;

  for(i = 0; i < outSize; i++) {
    bit = 1;
    bit = bit << (inSize - table[i]);
    bit = bit & input;
    bit = bit >> (inSize - table[i]);
    bit = bit << (outSize-i-1);

    output |= bit;
  }

  //printf("%llx\n", output);
  return output;
}


// Key generate
void keyPermutation1(unsigned long long int input, unsigned long int* left,
                     unsigned long int* right) {
  *left = permBase(input, 64, PC1[0], 28);
  *right = permBase(input, 64, PC1[1], 28);
}

unsigned long long int keyPermutation2(unsigned long int left,
                                       unsigned long int right) {
  unsigned long long int output = left;
  output = output << 28;
  output |= right;

  return permBase(output, 56, PC2, 48);
}

unsigned long long int leftShift(unsigned long long int input, int n) {
  unsigned long long int bit;

  if (n == 1 || n == 2 || n == 9 || n == 16) n = 1;
  else n = 2;

  int i;
  for (i = 0; i < n; i++) {
    bit = 1;
    bit = bit << 27;
    bit = bit & input;
    bit = bit >> 27;

    input = input << 1;
    input = input | bit;
    input = input & 0xFFFFFFF;
  }

  return input;
}

// função para gerar sub-keys (uma chave para cada uma das 16 iterações)
void DESKeySchedule(unsigned long long key, unsigned long long* subKeys) {
  unsigned long int left, right;
  keyPermutation1(key, &left, &right);

  int i;
  for (i = 0; i < 16; i++) {
    left = leftShift(left, i+1);
    right = leftShift(right, i+1);
    subKeys[i] = keyPermutation2(left, right);
    printf("subKey[%d]->0x%llx\n", i, subKeys[i]);
  }
}

// função para criação de de uma hash a partir dos dados do ficheiro,
// usando MDC-4
unsigned char* signature(unsigned char* inByteArray, long dim,
                         unsigned long long key);

//função para verificação da assinatura: verificar se a hash criada a
// partir dos dados é igual à hash recebida
int checkSignature(unsigned char* inByteArray, unsigned char* hash);

unsigned long long int initPermutation(unsigned long long int input) {
  return permBase(input, 64, IP, 64);
}

unsigned long long int finalPermutation(unsigned long long int input) {
  return permBase(input, 64, FP, 64);
}

unsigned long long int expansion(unsigned long int input) {
  return permBase(input, 32, E, 48);
}

unsigned long int permutation(unsigned long int input) {
  return permBase(input, 32, P, 32);
}

int convert6to4bits(int Sbox, int input) {
  int l = ((input & 32) >> 4) + ((input & 1));
  int c = (input & 30) >> 1;

  return S[Sbox][l][c];
}

//Receives 48(8x6) bits and returns 32(8*4) bits
unsigned long int substitution(unsigned long long int input) {
  unsigned long long int mask = 63; //last 6 bits = 1
  unsigned long long int sixBits;

  unsigned long int output = 0;
  unsigned long int fourBits;

  int i;
  for (i = 0; i < 8; i++) {
    sixBits = (input & mask) >> 6 * i;
    fourBits = convert6to4bits(8 - i - 1, sixBits);
    output += fourBits << 4 * i;
    mask = mask << 6;
  }

  return output;
}

unsigned long long encryptDESplain(unsigned long long plain,
                                   unsigned long long* subKeys) {
  plain = initPermutation(plain);

  unsigned long int left = plain >> 32;
  unsigned long int right = plain << 32 >> 32;
  unsigned long int newLeft, newRight;
  unsigned long long int temp;

  int i;
  for (i = 0; i < 16; i++) {
    temp = expansion(right);

    temp ^= subKeys[i];

    temp = substitution(temp);
    temp = permutation(temp);

    newRight = temp ^ left;
    newLeft = right;

    right = newRight;
    left = newLeft;
  }

  plain = (right << 32) | left;
  plain = finalPermutation(plain);

  printf("res-> %llx\n", plain);

  return plain;
}
