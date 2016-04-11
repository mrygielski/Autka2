#ifndef __GGATE_
#define __GGATE_

#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include "tga.h"

struct font_ttf
{
	int base;
	HFONT font;
};

struct stoper
{
	int StH,StM,StS;
};

struct fpsc
{
	stoper czas;
	unsigned long fr;
};

struct model3D
{
	int model;
	int textura;
};

struct model3Dtga
{
	int model;
	TextureImage textura;
};

// GRUBOŒCI CZCIONKI
#define FONT_1 0
#define FONT_2 100
#define FONT_3 200
#define FONT_4 300
#define FONT_5 400
#define FONT_6 500
#define FONT_7 600
#define FONT_8 700
#define FONT_9 800


// AKCJE ZWI¥ZANE Z MYSZK¥
int mouseX, mouseY;
bool RBM,LBM,MBM;


// Inicjowanie Okna
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
GLvoid ReSizeGLScene(GLsizei,GLsizei);
int InitGL(GLvoid);
GLvoid KillGLWindow(GLvoid);
BOOL CreateGLWindow(char*,int,int,int,bool);

// Tekstury
//GLuint LoadTexture(char*,int);

// Czcionki
font_ttf BuildFont(int,int,int,BOOL,BOOL,BOOL,char*);
GLvoid KillFont(font_ttf czcionka);
GLvoid glPrint(float,float,float,int,int,int,font_ttf,const char*, ...);
//void pisz_tekst(GLfloat x,GLfloat y,GLfloat rozmiar,int numer,GLuint tekstura,char* tablica_stringu,...);


// Perspektywa
void UstawPerspektywe(int typ);

// Mysz
void KursorMyszy();
float MouseX(int mx);
float MouseY(int my);
//

// Inne
void SetTextures(bool tn);
void BarT(float,float,float,float,float,float,float,float,float,float,float,float,int,int,int,int,int);
void Keyboard();

// Stopery i fpsy
stoper Stoper_Start();
unsigned int Stoper_Stop(stoper s);
fpsc FPSC_Start();
float FPSC_Fps(fpsc f);
fpsc FPSC_NextFrame(fpsc ff);

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////




HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool	keys[256], keydown[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
int _i_font,_f_l;
int windowX,windowY,windowX2,windowY2;





void UstawPerspektywe(int typ)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, typ);
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL);

	//BuildFontTexture();

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.5, 1.0, 0.0);	
	glAlphaFunc(GL_GREATER, 0.0f);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	
	return TRUE;										// Initialization Went OK
}


LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}

		// by Tomek
		case WM_MOUSEMOVE:
		{
			mouseX = LOWORD(lParam); 
			mouseY = HIWORD(lParam);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			LBM=true;
			return 0;
		}
		case WM_LBUTTONUP:
		{
			LBM=false;
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			MBM=true;
			return 0;
		}
		case WM_MBUTTONUP:
		{
			MBM=false;
			return 0;
		}	
		case WM_RBUTTONDOWN:
		{
			RBM=true;
			return 0;
		}
		case WM_RBUTTONUP:
		{
			RBM=false;
			return 0;
		}	
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,2500.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	windowX=width;
	windowY=height;
	windowX2=windowX/2;
	windowY2=windowY/2;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"B£¥D #1","Golden Gate Engine ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"B£¥D #2","Golden Gate Engine ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"B£¥D #3","Golden Gate Engine ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"B£¥D #4","Golden Gate Engine ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"B£¥D #5","Golden Gate Engine ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}


/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Nie mo¿na zainicjowaæ okienka","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"Nie ma wybranego trybu pe³noekranowego!\nCzy uruchomiæ program w oknie?","Pytanie?",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program zostanie zakoñczony!","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"B³¹d podczas tworzenia okna!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"B£¥D #6","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"B£¥D #7","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"B£¥D #8","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"B£¥D #9","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"B£¥D #10","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Inicjalizacja nie powiod³a siê!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}


AUX_RGBImageRec *LoadBMP(char *Filename) 
{
	AUX_RGBImageRec* text;
	text=auxDIBImageLoad(Filename);
	return text;
};

GLuint LoadTexture(char* plik,int jakosc,bool mipmaps, bool metal)
{
	AUX_RGBImageRec *TextureImage[1];
	GLuint textura[1];
	if (TextureImage[0]=LoadBMP(plik))
	{
		glGenTextures(1, &textura[0]);
		glBindTexture(GL_TEXTURE_2D, textura[0]);
		if (mipmaps==false)
		{
		 glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
			 TextureImage[0]->sizeX,TextureImage[0]->sizeY,
			 0,GL_RGB,
			 GL_UNSIGNED_BYTE,TextureImage[0]->data);
		 if ((jakosc==1)||(jakosc==2))
		 {
		   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,jakosc+9727);
			 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,jakosc+9727);
		 }
		}
		if (mipmaps==true)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D,3,TextureImage[0]->sizeX,TextureImage[0]->sizeY,GL_RGB,GL_UNSIGNED_BYTE,TextureImage[0]->data);
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


	}
	if (metal==true)
	{
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	}
	free(TextureImage[0]);
	return textura[0];
}

font_ttf BuildFont(int wysokosc,int szerokosc,int styl,
			  BOOL podkreslenie,BOOL przekreslenie,BOOL kursywa,
			  char* nazwa)
{
	font_ttf cz;
	cz.base = glGenLists(255);								// Storage For 96 Characters
	cz.font = CreateFont(	wysokosc,							// Height Of Font
						szerokosc,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						styl,						// Font Weight
						kursywa,							// Italic
						podkreslenie,							// Underline
						przekreslenie,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						nazwa);					// Font Name
	SelectObject(hDC, cz.font);							// Selects The Font We Want
	wglUseFontBitmaps(hDC, 1, 255, cz.base);				// Builds 96 Characters Starting At Character 32
	return cz;
}

GLvoid KillFont(font_ttf czcionka)
{
	glDeleteLists(czcionka.base, 255);
}

GLvoid glPrint(float x,float y,float z,int r,int g,int b,font_ttf czcionka,const char *fmt, ...)
{
	glColor3ub(r,g,b);
	glRasterPos3f(x,y,z);
	
	char text[256];
	va_list	ap;
	if (fmt == NULL) return;
	va_start(ap, fmt);
	    vsprintf(text, fmt, ap);
	va_end(ap);
	_f_l=strlen(text);
	for (_i_font=0;_i_font<_f_l;_i_font++) text[_i_font]--;
	glPushAttrib(GL_LIST_BIT);
	glListBase(czcionka.base);
	glCallLists(_f_l, GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

void KursorMyszy()
{
	glLoadIdentity();
	glTranslatef(0,0,-3);
}

float MouseX(int mx)
{
	float mxx=(float)mx;
	mxx=mxx/195;
	mxx=mxx-1.65f;
	return mxx;
}
float MouseY(int my)
{
	float myy=(float)my;
	myy=myy/195;
	myy=myy+1.2f;
	return myy;
}
void SetTextures(bool tn)
{
	if (tn==true) 
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
}

int hour()
{
	tm timer;
	int i;
	_getsystime(&timer);
	i=timer.tm_hour;
	return i;
}

int minute()
{
	tm timer;
	int i;
	_getsystime(&timer);
	i=timer.tm_min;
	return i;
}

int second()
{
	tm timer;
	int i;
	_getsystime(&timer);
	i=timer.tm_sec;
	return i;
}



stoper Stoper_Start()
{
	stoper s;
	s.StH=hour();
	s.StM=minute();
	s.StS=second();
	return s;
}

unsigned int Stoper_Stop(stoper s)
{
	unsigned int h=0,m=0,sec=0,wynik=0;
	h=hour();
	m=minute();
	sec=second();
	wynik=((h-s.StH)/3600) + ((m-s.StM)/60) + (sec-s.StS);
	return wynik;
}

fpsc FPSC_Start()
{
	fpsc f;
	f.czas=Stoper_Start();
	f.fr=0;
	return f;
}

float FPSC_Fps(fpsc f)
{
	float wynik=0,stop;
	stop=Stoper_Stop(f.czas);
	if (stop<=0) stop++;
	wynik=f.fr/stop;
	return wynik;
}

fpsc FPSC_NextFrame(fpsc ff)
{
	fpsc f=ff;
	f.fr++;
	return f;
}

void BarT(float x1,float y1,float z1,
		  float x2,float y2,float z2,
		  float x3,float y3,float z3,
		  float x4,float y4,float z4,int r,int g, int b,int a,int text)
{
	SetTextures(true);
	glColor4ub(r,g,b,a);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.99f,0.01f);glVertex3f(x2,y2,z2);
		glTexCoord2f(0.99f,0.99f);glVertex3f(x1,y1,z1);
		glTexCoord2f(0.01f,0.01f);glVertex3f(x3,y3,z3);
		glTexCoord2f(0.01f,0.99f);glVertex3f(x4,y4,z4);
	glEnd();
	SetTextures(false);
}

void Keyboard()
{

	for (int i=0;i<=255;i++)
				if (keys[i]==false) keydown[i]=false;
					else 
					keydown[i]=true;

}

void napisz_litere(int jaki_znak,GLfloat gdzie_x,
				   GLfloat gdzie_y,GLfloat rozmiar,int numer,GLuint textura,int r, int g, int b)
{
	GLfloat x1=0,x2=16,y1=(float)(numer<<7),y2=(float)(numer<<7)+16;
	int znak=0;
	do
	{
		if (x2 != 256)
		{
			x1+=16;
			x2+=16;
			znak=znak+1;
		}
		else
		{
			x1=0;x2=16;
			y1+=16;
			y2+=16;
			znak=znak+1;
		};
	}
	while(znak!=jaki_znak);
    glColor3ub(r,g,b);
	glBindTexture(GL_TEXTURE_2D, textura);// Tekstura z fontem
	glBegin(GL_QUADS);
		glTexCoord2f(x1/256, y2/256); glVertex2f(gdzie_x, gdzie_y-rozmiar);
		glTexCoord2f(x2/256, y2/256); glVertex2f(gdzie_x+rozmiar, gdzie_y -rozmiar);
		glTexCoord2f(x2/256, y1/256); glVertex2f(gdzie_x+rozmiar, gdzie_y);
		glTexCoord2f(x1/256, y1/256); glVertex2f(gdzie_x, gdzie_y);
	glEnd();
}

char* makestring(char* control, ...)
{
    char buf[1000];
    va_list args;
    va_start(args, control);
		vsprintf(buf,control,args);
    va_end(args);
    return buf;
}

void pisz_tekst(GLfloat x,GLfloat y,GLfloat rozmiar,int r, int g, int b,
				int numer,GLuint tekstura,char* control,...)
{
	char buf[1000];
    va_list args;
    va_start(args, control);
	vsprintf(buf,control,args);
    va_end(args);
	char *str=buf;
    

	GLfloat XXX = x;

	while(*str!=0)
	{
		napisz_litere(*str,XXX,y,rozmiar,numer,tekstura,r,g,b);
		XXX+=(rozmiar+(rozmiar/12));
		str++;
	}
}

int Change_Resolution(int x, int y, int bpp, char* title)
{
		KillGLWindow();
	  if (CreateGLWindow(title,x,y,bpp,fullscreen)==FALSE)
		{
			return -1;
		}
		return 0;
}

int Random(int min,int max)
{
	int i;
	i=rand()%(max-min+1)+min;
	return i;
}

void randomize()
{
	tm timer;
	int i=0,a=0,b;
	_getsystime(&timer);
	i=timer.tm_sec+100;
	while (a!=i)
	{
		b=rand()%100;
		a++;
	}
}


void litera(int jaki_znak,GLfloat gdzie_x,
				   GLfloat gdzie_y,GLfloat rozmiarx,float rozmiary,GLuint textura,int r, int g, int b)
{
	if (jaki_znak<0) return;
	
	GLfloat x1=0,x2=16,y1=0,y2=16.0f;
	//float x1,x2,y1,y2;
	int znak=0,jaki_znak2=jaki_znak-32;
	if (jaki_znak2>0)
	do
	{
		if (x2 != 256)
		{
			x1+=16;
			x2+=16;
			znak=znak+1;
		}
		else
		{
			x1=0;x2=16;
			y1+=16;
			y2+=16;
			znak=znak+1;
		};
	}
	while(znak!=jaki_znak2);
	y1=256-y1;
	y2=256-y2;
	//x1=256-x1;
	//x2=256-x2;
    glColor3ub(r,g,b);
	glBindTexture(GL_TEXTURE_2D, textura);// Tekstura z fontem
	glBegin(GL_QUADS);
		glTexCoord2f(x1/256, y2/256); glVertex2f(gdzie_x, gdzie_y-rozmiary);
		glTexCoord2f(x2/256, y2/256); glVertex2f(gdzie_x+rozmiarx, gdzie_y -rozmiary);
		glTexCoord2f(x2/256, y1/256); glVertex2f(gdzie_x+rozmiarx, gdzie_y);
		glTexCoord2f(x1/256, y1/256); glVertex2f(gdzie_x, gdzie_y);
	glEnd();
}
void piszTXT(GLfloat x,GLfloat y,float odleglosc,GLfloat rozmiarx,float rozmiary,int r, int g, int b,
				GLuint tekstura,char* control,...)
{
	char buf[1000];
    va_list args;
    va_start(args, control);
	vsprintf(buf,control,args);
    va_end(args);
	char *str=buf;
	GLfloat XXX = x;
	while(*str!=0)
	{
		litera(*str,XXX,y,rozmiarx,rozmiary,tekstura,r,g,b);
		XXX+=odleglosc;
		str++;
	}
}

model3D LoadModel3D(char* filename,char* texture,int jakosc,bool mipmapy,int numer, bool metal)
{
 int i,j;
 int plik=Assign(filename);
 int vert,text,norm,face,size;
 short face_i[5000][9];
 float vert_i[5000][3];
 float norm_i[5000][3];
 float text_i[5000][2];

 read(plik,&face,4);
 read(plik,&vert,4);
 read(plik,&norm,4);
 read(plik,&text,4);
 read(plik,&size,4);
 for (i=0;i<face;i++)
 for (j=0;j<9;j++)
 {
	read(plik,&face_i[i][j],2);
 }
 for (i=0;i<vert;i++)
 for (j=0;j<3;j++)
 {
	read(plik,&vert_i[i][j],4);
 }
 for (i=0;i<norm;i++)
 for (j=0;j<3;j++)
 {
	read(plik,&norm_i[i][j],4);
 }
 for (i=0;i<text;i++)
 for (j=0;j<2;j++)
 {
	read(plik,&text_i[i][j],4);
 }


 int vi,ti,ni;
 int lid;
 model3D mdl;
 lid=glGenLists(numer);
 glNewList(lid, GL_COMPILE);
 glBegin (GL_TRIANGLES);
   for(i=0;i<size;i++)
   {
    for(j=0;j<3;j++)
    {
      vi=face_i[i][j];
      ni=face_i[i][j+3];//Normal index
      ti=face_i[i][j+6];//Texture index
      glNormal3f (norm_i[ni][0],norm_i[ni][1],norm_i[ni][2]);
      glTexCoord2f(text_i[ti][0],text_i[ti][1]);
      glVertex3f (vert_i[vi][0],vert_i[vi][1],vert_i[vi][2]);
    }
   }
 glEnd ();
 glEndList();
 close(plik);
 
 mdl.model=lid;
 mdl.textura=LoadTexture(texture,jakosc,mipmapy,metal);
 return mdl;
};

model3Dtga LoadModel3DTGA(char* filename,char* texture,int jakosc,bool mipmapy,int numer, bool metal)
{
 int i,j;
 int plik=Assign(filename);
 int vert,text,norm,face,size;
 short face_i[5000][9];
 float vert_i[5000][3];
 float norm_i[5000][3];
 float text_i[5000][2];

 read(plik,&face,4);
 read(plik,&vert,4);
 read(plik,&norm,4);
 read(plik,&text,4);
 read(plik,&size,4);
 for (i=0;i<face;i++)
 for (j=0;j<9;j++)
 {
	read(plik,&face_i[i][j],2);
 }
 for (i=0;i<vert;i++)
 for (j=0;j<3;j++)
 {
	read(plik,&vert_i[i][j],4);
 }
 for (i=0;i<norm;i++)
 for (j=0;j<3;j++)
 {
	read(plik,&norm_i[i][j],4);
 }
 for (i=0;i<text;i++)
 for (j=0;j<2;j++)
 {
	read(plik,&text_i[i][j],4);
 }


 int vi,ti,ni;
 int lid;
 model3Dtga mdl;
 lid=glGenLists(numer);
 glNewList(lid, GL_COMPILE);
 glBegin (GL_TRIANGLES);
   for(i=0;i<size;i++)
   {
    for(j=0;j<3;j++)
    {
      vi=face_i[i][j];
      ni=face_i[i][j+3];//Normal index
      ti=face_i[i][j+6];//Texture index
      glNormal3f (norm_i[ni][0],norm_i[ni][1],norm_i[ni][2]);
      glTexCoord2f(text_i[ti][0],text_i[ti][1]);
      glVertex3f (vert_i[vi][0],vert_i[vi][1],vert_i[vi][2]);
    }
   }
 glEnd ();
 glEndList();
 close(plik);
 
 mdl.model=lid;
 LoadTGAFile(&mdl.textura,texture,mipmapy,jakosc,metal);
 return mdl;
};

#endif