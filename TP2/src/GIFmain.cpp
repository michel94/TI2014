#include "GIFmain.h"
#include "stb_image.c"

int main(int argc, char *argv[]) {
  char *inputFile;
  char *outputFile;
  int width, height, numComponents;
  unsigned char *data;
  imageStruct* image;

  if (argc > 1) {
    inputFile = argv[1];
  } else {
    inputFile = const_cast<char *>("../samples/monica.png");
  }

  if (argc > 2) {
    outputFile = argv[2];
  } else {
    outputFile = const_cast<char *>("output.gif");
  }

  printf("Loading file %s\n", inputFile);
  printf("Writing to file %s\n", outputFile);

  data = stbi_load(inputFile, &width, &height, &numComponents, STBI_rgb);

  if (!data && stbi_failure_reason()) {
    printf("Error: %s\n", stbi_failure_reason());
    return 1;
  }

  image = GIFEncoder(data, width, height);
  GIFEncoderWrite(image, outputFile);

  printf("Compressing image...\n");

  stbi_image_free(data);
  printf("Done.\n");

  return 0;
}
