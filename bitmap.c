#include <stdio.h>
#include <stdlib.h>
#include "bitmapHeader.h"
//Feito com o auxilio do site: https://stackoverflow.com/questions/19624159/strange-values-when-reading-pixels-from-24-bit-bitmap

int main(){
	
	BITMAP imagemBitmap;
	FILE *imagemEntrada, *imagemSaida;
	unsigned int ImagePixelAmount = 0;
	
	imagemEntrada = fopen("image.bmp", "rb");
	fseek(imagemEntrada, 0, SEEK_SET);	
	fread(&imagemBitmap.FILEHEADER, sizeof(BITMAPFILEHEADER), 1, imagemEntrada); //FILE READER
	
	/*
	printf("<<Bitmap File Header Data Values>> \n");
	printf("Tamanho imagem:  %d\n", imagemBitmap.FILEHEADER.bfSize);
	printf("Byte Offset:  %d\n", imagemBitmap.FILEHEADER.bfOffBits);
	*/
	
	fread(&imagemBitmap.INFOHEADER, sizeof(BITMAPINFOHEADER), 1, imagemEntrada); //INFO READER
	
	/*
	printf("\n<<Bitmap Info Header Data Values>>\n");
	printf("Size of Bitmap Info Header: %d\n", imagemBitmap.INFOHEADER.biSize);
	printf("Width of Bitmap: %d\n", imagemBitmap.INFOHEADER.biWidth);
	printf("Height of Bitmap: %d\n", imagemBitmap.INFOHEADER.biHeight);
	printf("Bit Count: %d\n", imagemBitmap.INFOHEADER.biBitCount);
	printf("Amount of color indexes: %d\n", imagemBitmap.INFOHEADER.biClrUsed);   
	*/ 
	
	ImagePixelAmount = imagemBitmap.INFOHEADER.biHeight * imagemBitmap.INFOHEADER.biWidth; 
	
	//Create space in memory and read in pixel data from the image
	imagemBitmap.IMAGEDATA = (rgbPIXEL*)malloc(sizeof(rgbPIXEL) * ImagePixelAmount);	
	fseek(imagemEntrada, imagemBitmap.FILEHEADER.bfOffBits, SEEK_SET);
	fread(imagemBitmap.IMAGEDATA, ImagePixelAmount * sizeof(rgbPIXEL), 1, imagemEntrada);
	
	//Conver para escala de cinza, 0.3*R +0.59*G +0.11*B
	for(int y = 0; y < imagemBitmap.INFOHEADER.biHeight; y++){
    	for(int x = 0; x < imagemBitmap.INFOHEADER.biWidth; x++){
			char buffer;
			buffer = ((imagemBitmap.IMAGEDATA[y * imagemBitmap.INFOHEADER.biWidth + x].r)+ //Vermelho
					 (imagemBitmap.IMAGEDATA[y * imagemBitmap.INFOHEADER.biWidth + x].g)+ //Verde
					 (imagemBitmap.IMAGEDATA[y * imagemBitmap.INFOHEADER.biWidth + x].b))/3; //Azul
			imagemBitmap.IMAGEDATA[y * imagemBitmap.INFOHEADER.biWidth + x].r = buffer;
			imagemBitmap.IMAGEDATA[y * imagemBitmap.INFOHEADER.biWidth + x].g = buffer;
			imagemBitmap.IMAGEDATA[y * imagemBitmap.INFOHEADER.biWidth + x].b = buffer;
    	}
	}
	
	//Imagem de saida
	imagemSaida = fopen("gray.bmp", "wb");
	fseek(imagemSaida, 0, SEEK_SET);	
	fwrite(&imagemBitmap.FILEHEADER, sizeof(BITMAPFILEHEADER), 1, imagemSaida);
	fwrite(&imagemBitmap.INFOHEADER, sizeof(BITMAPINFOHEADER), 1, imagemSaida);
	fseek(imagemSaida, imagemBitmap.FILEHEADER.bfOffBits, SEEK_SET);
	fwrite(imagemBitmap.IMAGEDATA, ImagePixelAmount * sizeof(rgbPIXEL), 1, imagemSaida);
	
	fclose(imagemEntrada);
	fclose(imagemSaida);
	return 0;
}
