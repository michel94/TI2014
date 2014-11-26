
#define STBI_FAILURE_USERMSG true

#include "stb_image.c"

#include "GIFencoder.h"

int main(int argc, char *argv[]) {

	char *inputFile;
	char *outputFile;
    int width, height, numComponents;
    unsigned char *data;
	imageStruct* image;
	
	if (argc > 1)
		inputFile = argv[1];
	else
		inputFile = const_cast<char *>("../samples/monica.png");

	if (argc > 2){
		outputFile = argv[2];
		
	}else{
		outputFile = const_cast<char *>("monicaOutput.gif");
	}
	/*for(int i=strlen(outputFile)-1; i>=0; i--){
		printf("%d\n", i);
		if(outputFile[i] == '.'){
			outputFile[i+1] = 'g';
			outputFile[i+2] = 'i';
			outputFile[i+3] = 'f';
			outputFile[i+4] = 0;
			printf("%s\n", outputFile);
			break;
		}
	}*/
	
	printf("Loading file %s\n", inputFile);
	printf("Writing to file %s\n", outputFile);

	data = stbi_load(inputFile, &width, &height, &numComponents, STBI_rgb);

	if (!data && stbi_failure_reason()) {
		printf("Error: %s\n",stbi_failure_reason());
		return 1;
	}

	image = GIFEncoder(data, width, height);
	GIFEncoderWrite(image, outputFile);

	printf("Compressing image...\n");

    stbi_image_free(data);
	printf("Done.\n");

	return 0;
}

