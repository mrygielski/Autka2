#ifndef __TGA_GGATE__
#define __TGA_GGATE__

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;

typedef	struct									
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;	

typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

typedef struct					// Structure d'une image TGA
{
	GLubyte	*imageData;				// Données de l'image
	GLuint	bpp;					// Profondeur de la couleur de l'image en bits par pixel
	GLuint	width;					// Largeur de l'image
	GLuint	height;					// Hauteur de l'image
	GLuint	texID;					// Identification de texture pour choisir une texture
} TextureImage;	


TGAHeader tgaheader;									// TGA header
TGA tga;												// TGA image data



GLubyte uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
GLubyte cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed TGA Header
bool LoadUncompressedTGA(Texture *, char *, FILE *);	// Load an Uncompressed file
bool LoadCompressedTGA(Texture *, char *, FILE *);		// Load a Compressed file
bool LoadTGA(Texture * texture, char * filename);				// Load a TGA file




bool LoadTGA(Texture * texture, char * filename)				// Load a TGA file
{
	FILE * fTGA;												// File pointer to texture file
	fTGA = fopen(filename, "rb");								// Open file for reading

	if(fTGA == NULL)											// If it didn't open....
	{
		MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		return false;														// Exit function
	}

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		MessageBox(NULL, "Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
		LoadUncompressedTGA(texture, filename, fTGA);						// If so, jump to Uncompressed TGA loading code
	}
	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)		// See if header matches the predefined header of
	{																		// an RLE compressed TGA image
		LoadCompressedTGA(texture, filename, fTGA);							// If so, jump to Compressed TGA loading code
	}
	else																	// If header matches neither type
	{
		MessageBox(NULL, "TGA file is type 2 or type 10 ", "Invalid Image", MB_OK);	// Display an error
		fclose(fTGA);
		return false;																// Exit function
	}
	return true;															// All went well, continue on
}

bool LoadUncompressedTGA(Texture * texture, char * filename, FILE * fTGA)	// Load an uncompressed TGA (note, much of this code is based on NeHe's 
{																			// TGA Loading code nehe.gamedev.net)
	if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Read TGA header
	{										
		MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display error
		if(fTGA != NULL)													// if file is still open
		{
			fclose(fTGA);													// Close it
		}
		return false;														// Return failular
	}	

	texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	texture->bpp	= tga.header[4];										// Determine the bits per pixel
	tga.Width		= texture->width;										// Copy width into local structure						
	tga.Height		= texture->height;										// Copy height into local structure
	tga.Bpp			= texture->bpp;											// Copy BPP into local structure

	if((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp !=32)))	// Make sure all information is valid
	{
		MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);	// Display Error
		if(fTGA != NULL)													// Check if file is still open
		{
			fclose(fTGA);													// If so, close it
		}
		return false;														// Return failed
	}

	if(texture->bpp == 24)													//If the BPP of the image is 24...
	{
		texture->type	= GL_RGB;											// Set Image type to GL_RGB
	}
	else																	// Else if its 32 BPP
	{
		texture->type	= GL_RGBA;											// Set image type to GL_RGBA
	}

	tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute the number of BYTES per pixel
	tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute the total amout ofmemory needed to store data
	texture->imageData	= (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory

	if(texture->imageData == NULL)											// If no space was allocated
	{
		MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		fclose(fTGA);														// Close the file
		return false;														// Return failed
	}

	if(fread(texture->imageData, 1, tga.imageSize, fTGA) != tga.imageSize)	// Attempt to read image data
	{
		MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// Display Error
		if(texture->imageData != NULL)										// If imagedata has data in it
		{
			free(texture->imageData);										// Delete data from memory
		}
		fclose(fTGA);														// Close file
		return false;														// Return failed
	}

	// Byte Swapping Optimized By Steve Thomas
	for(GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
	{
		texture->imageData[cswap] ^= texture->imageData[cswap+2] ^=
		texture->imageData[cswap] ^= texture->imageData[cswap+2];
	}

	fclose(fTGA);															// Close file
	return true;															// Return success
}

bool LoadCompressedTGA(Texture * texture, char * filename, FILE * fTGA)		// Load COMPRESSED TGAs
{ 
	if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Attempt to read header
	{
		MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display Error
		if(fTGA != NULL)													// If file is open
		{
			fclose(fTGA);													// Close it
		}
		return false;														// Return failed
	}

	texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	texture->bpp	= tga.header[4];										// Determine Bits Per Pixel
	tga.Width		= texture->width;										// Copy width to local structure
	tga.Height		= texture->height;										// Copy width to local structure
	tga.Bpp			= texture->bpp;											// Copy width to local structure

	if((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp !=32)))	//Make sure all texture info is ok
	{
		MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);	// If it isnt...Display error
		if(fTGA != NULL)													// Check if file is open
		{
			fclose(fTGA);													// Ifit is, close it
		}
		return false;														// Return failed
	}

	tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute BYTES per pixel
	tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute amout of memory needed to store image
	texture->imageData	= (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory

	if(texture->imageData == NULL)											// If it wasnt allocated correctly..
	{
		MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		fclose(fTGA);														// Close file
		return false;														// Return failed
	}

	GLuint pixelcount	= tga.Height * tga.Width;							// Nuber of pixels in the image
	GLuint currentpixel	= 0;												// Current pixel being read
	GLuint currentbyte	= 0;												// Current byte 
	GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);			// Storage for 1 pixel

	do
	{
		GLubyte chunkheader = 0;											// Storage for "chunk" header

		if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)				// Read in the 1 byte header
		{
			MessageBox(NULL, "Could not read RLE header", "ERROR", MB_OK);	// Display Error
			if(fTGA != NULL)												// If file is open
			{
				fclose(fTGA);												// Close file
			}
			if(texture->imageData != NULL)									// If there is stored image data
			{
				free(texture->imageData);									// Delete image data
			}
			return false;													// Return failed
		}

		if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
		{																	// that follow the header
			chunkheader++;													// add 1 to get number of following color values
			for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
			{
				if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) // Try to read 1 pixel
				{
					MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// IF we cant, display an error

					if(fTGA != NULL)													// See if file is open
					{
						fclose(fTGA);													// If so, close file
					}

					if(colorbuffer != NULL)												// See if colorbuffer has data in it
					{
						free(colorbuffer);												// If so, delete it
					}

					if(texture->imageData != NULL)										// See if there is stored Image data
					{
						free(texture->imageData);										// If so, delete it too
					}

					return false;														// Return failed
				}
																						// write to memory
				texture->imageData[currentbyte		] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
				texture->imageData[currentbyte + 1	] = colorbuffer[1];
				texture->imageData[currentbyte + 2	] = colorbuffer[0];

				if(tga.bytesPerPixel == 4)												// if its a 32 bpp image
				{
					texture->imageData[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
				}

				currentbyte += tga.bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
				currentpixel++;															// Increase current pixel by 1

				if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
				{
					MessageBox(NULL, "Too many pixels read", "ERROR", NULL);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
		else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
		{
			chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
			if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)		// Attempt to read following color values
			{	
				MessageBox(NULL, "Could not read from file", "ERROR", MB_OK);			// If attempt fails.. Display error (again)

				if(fTGA != NULL)														// If thereis a file open
				{
					fclose(fTGA);														// Close it
				}

				if(colorbuffer != NULL)													// If there is data in the colorbuffer
				{
					free(colorbuffer);													// delete it
				}

				if(texture->imageData != NULL)											// If thereis image data
				{
					free(texture->imageData);											// delete it
				}

				return false;															// return failed
			}

			for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
			{																			// by the header
				texture->imageData[currentbyte		] = colorbuffer[2];					// switch R and B bytes areound while copying
				texture->imageData[currentbyte + 1	] = colorbuffer[1];
				texture->imageData[currentbyte + 2	] = colorbuffer[0];

				if(tga.bytesPerPixel == 4)												// If TGA images is 32 bpp
				{
					texture->imageData[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
				}

				currentbyte += tga.bytesPerPixel;										// Increase current byte by the number of bytes per pixel
				currentpixel++;															// Increase pixel count by 1

				if(currentpixel > pixelcount)											// Make sure we havent written too many pixels
				{
					MessageBox(NULL, "Too many pixels read", "ERROR", NULL);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
	}

	while(currentpixel < pixelcount);													// Loop while there are still pixels left
	fclose(fTGA);																		// Close the file
	return true;																		// return success
}



bool LoadTGAFile(TextureImage* Texture, char* filename, bool mipmaps, int jakosc, bool metal)
{
	GLubyte		TGAheader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};	// En-tête de TGA non-compressé
	GLubyte		TGAcompare[12];								// Pour comparer l'en-tête du TGA
	GLubyte		header[6];									// 6 er bits de l'en-tête
	GLuint		bytesPerPixel;								// Garde le nombre de bits par pixel utilisé dans un TGA
	GLuint		imageSize;									// Utilisé pour stocker l'image quand les réglages sont dans la RAM
	GLuint		temp;										// Variable temporaire
	GLuint		type=GL_RGBA;								// Mode par défaut RBGA (32 BPP)
	FILE *file = fopen(filename, "rb");						// Ouverture du TGA
	if(	file==NULL ||										// Il existe ?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Ce sont les 12 bits à lire ?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// L'en-tête est correct ?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// Oui, donc on lit les 6 bits suivants de l'en-tête
		{
			if (file == NULL)		// Le fichier existe ?
				{
					// Le fichier indiqué n'existe pas ...
					MessageBox(NULL, filename, "B£¥D W PLIKU!", MB_ICONERROR); 
					return false;
				}
			else
				{
					fclose(file);		// Une erreur et on ferme le fichier
					MessageBox(NULL, filename, "B£¥D W PLIKU! #2", MB_ICONERROR);
					return false;		// Retourne false
				}
		}
	Texture->width  = header[1] * 256 + header[0];		// Détermine la largeur du TGA (highbyte*256+lowbyte)
	Texture->height = header[3] * 256 + header[2];		// Détermine la hauteur du TGA (highbyte*256+lowbyte)
 	if(	Texture->width	<=0	||					// La largeur est <= 0 ?
		Texture->height	<=0	||					// La hauteur est <= 0 ?
		(header[4]!=24 && header[4]!=32))		// TGA de 24 ou 32 bits ?
		{
			fclose(file);						// Une erreur et on ferme le fichier
			MessageBox(NULL, filename, "B£¥D W PLIKU! #3", MB_ICONERROR);
			return false;						// Retourne false
		}
	Texture->bpp	= header[4];				// Bits par pixel du TGA (24 ou 32)
	bytesPerPixel	= Texture->bpp/8;			// Divise par ! pour avoir le nombre de bits par pixel
	imageSize		= Texture->width*Texture->height*bytesPerPixel;	// Calcule l'espace mémoire requis pour le TGA
	Texture->imageData=(GLubyte *)malloc(imageSize);	// Réserve la mémoire pour stocker le TGA
	if(	Texture->imageData==NULL ||						// L'espace mémoire existe ?
		fread(Texture->imageData, 1, imageSize, file)!=imageSize)	// La taille de l'image est la même que l'espace mémoire réservé ?
		{
			if(Texture->imageData!=NULL)			// L'image a été chargée ?
				{
				  free(Texture->imageData);			// Oui, donc on libère les données de l'image
				}

			fclose(file);							// Ferme le fichier
			MessageBox(NULL, filename, "B£¥D W PLIKU! #4", MB_ICONERROR);
			return false;							// Retourne false
		}
	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Boucle passant les donées de l'image
		{													// Inverse le 1 er et le 3 ème bits ('R'ouge et 'B'eu)
			temp = Texture->imageData[i];					// Stockage temporaire de la donnée de l'image 'i'
			Texture->imageData[i] = Texture->imageData[i + 2];		// Met le 1 er bit à la valeur du 3 ème
			Texture->imageData[i + 2] = temp;						// Met le 3 ème bit à la valeur de 'temp'
		}
	fclose (file);	// Ferme le fichier
	glGenTextures(1, &Texture[0].texID);			// Génère l'identification de la texture OpenGL
	if (Texture[0].bpp == 24)		// TGA 24 bits ?
		{
			type = GL_RGB;				// Oui, donc met à To GL_RGB
		}

	glBindTexture(GL_TEXTURE_2D, Texture[0].texID);		// Attache notre texture
	if (mipmaps==false)
		{
		 glTexImage2D(GL_TEXTURE_2D,0,type,Texture[0].width,Texture[0].height,0,type,GL_UNSIGNED_BYTE,Texture[0].imageData);
		 if ((jakosc==1)||(jakosc==2))
		 {
		   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,jakosc+9727);
			 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,jakosc+9727);
		 }
		}
	if (mipmaps==true)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D,type,
				Texture[0].width,Texture[0].height,
				type,GL_UNSIGNED_BYTE,Texture[0].imageData);
			if (jakosc==1) 
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); //filtrowanie dwuliniowe
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			}
			if (jakosc==2) 
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); //filtrowanie trójliniowe
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			}
		}
	if (metal==true)
	{
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	}
	
	return true;
}


#endif