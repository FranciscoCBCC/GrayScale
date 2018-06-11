#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER {  
	unsigned short      bfType;                 // Specifies the type of file. This member must be BM. (0x4D42)
	unsigned int        bfSize;                 // Specifies the size of the file, in bytes.
	short               bfReserved1;            // Reserved; must be set to zero.
	short               bfReserved2;            // Reserved; must be set to zero.
	unsigned int        bfOffBits;              // Specifies the byte offset from the BITMAPFILEHEADER structure to the actual bitmap data in the file.
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {  
	unsigned int        biSize;                 // Specifies the number of bytes required by the BITMAPINFOHEADER structure.
	int                 biWidth;                // Specifies the width of the bitmap, in pixels.
	int                 biHeight;               // Specifies the height of the bitmap, in pixels.
	unsigned short      biPlanes;               // Specifies the number of planes for the target device. This member must be set to 1.
	unsigned short      biBitCount;             // Specifies the number of bits per pixel. This value must be 1,4, 8, or 24.
	unsigned int        biCompression;          // Specifies the type of compression for a compressed bitmap. Itcan be one of the following values: BI_RGB, BI_RLE8, BI_RLE4   
	unsigned int        biSizeImage;            // Specifies the size, in bytes, of the image. It is valid to set this member to zero if the bitmap is in the BI_RGB format.
	int                 biXPelsPerMeter;        // Specifies the horizontal resolution, in pixels per meter, of the target device for the bitmap.
	int                 biYPelsPerMeter;        // Specifies the vertical resolution, in pixels per meter, of the target device for the bitmap.
	unsigned int        biClrUsed;              // Specifies the number of color indexes in the color table actually used by the bitmap.
	unsigned int        biClrImportant;         // Specifies the number of color indexes that are considered important for displaying the bitmap. If this value is zero, all colors are important.
} BITMAPINFOHEADER;  


typedef struct tagRGBPIXEL{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} rgbPIXEL;

#pragma pack(pop)

typedef struct tagBITMAP{
	BITMAPFILEHEADER FILEHEADER;
	BITMAPINFOHEADER INFOHEADER;
	rgbPIXEL*    IMAGEDATA;
}BITMAP;
