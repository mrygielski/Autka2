#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
/////////////////MODU£Y///////
#include "..\files.h"
#include "..\ggate.h"
#include "..\cameraGG.h"
#include "..\3DMath.h"	
//////////////////////////////
void BarT2(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,int r,int g, int b,int a){glColor4ub(r,g,b,a);glBegin(GL_TRIANGLE_STRIP);glTexCoord2f(0.99f,0.01f);glVertex3f(x2,y2,z2);glTexCoord2f(0.99f,0.99f);glVertex3f(x1,y1,z1);glTexCoord2f(0.01f,0.01f);glVertex3f(x3,y3,z3);glTexCoord2f(0.01f,0.99f);glVertex3f(x4,y4,z4);glEnd();}
//////////////////////////////
#include "vars.h"

#include "rysowanie_sam.h"
#include "rysowanie_swiat.h"
#include "kolizje.h"
#include "fizyka.h"
#include "init.h"

//////////////////////////////
#pragma comment( lib, "winmm.lib" )



void Get_FPS(int &fPs)
{
	static float framesPerSecond    = 0.0f;	// This will store our fps
	static float lastTime			= 0.0f;	// This will hold the time from the last frame
	float currentTime = GetTickCount() * 0.001f;				
	framesPerSecond+=2;
	if( currentTime - lastTime >= 0.5f )
	{
		lastTime = currentTime;
		fPs=(int)framesPerSecond;
		framesPerSecond = 0;
	}
}

void Rysuj_modele()
{
	SetTextures(true);
	glPolygonMode(GL_BACK,GL_POINT);
	for (i=1;i<=ilosc_modeli;i++)
	{
		glPushMatrix();       ////// to naprawiæ - nie pokazuje modeli
		glColor3ub(255,255,255);
		glTranslatef(modele[i].x,modele_y[modele[i].numer],modele[i].y);
		glRotatef(-90,1,0,0);
		glRotatef(modele[i].rot,0,0,1);
		glScalef(64,64,64);
		glBindTexture(GL_TEXTURE_2D, modele3dTGA_ed[modele[i].numer].textura.texID);
		glCallList(modele3dTGA_ed[modele[i].numer].model);
		glPopMatrix();
	}
	SetTextures(true);
	glPolygonMode(GL_BACK,GL_FILL);
}


void DrawGLScene()
{
	glClear(/*GL_COLOR_BUFFER_BIT |*/ GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	g_Camera.Look();
	
	Zrob_Sam_Linie(13);
	Wykryj_kolizje();

	Rysuj_Linie_TEST();

	Rysuj_niebo();
	Rysuj_mape();	
	Rysuj_modele();
	Rysuj_slad();


	glPushMatrix();
	Rysuj_Malucha();
	glPopMatrix();

	
	Rysuj_dym(2);

	
	

	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	glTranslatef(0,0,-1);
	piszTXT(-0.54f,0.40f,0.015f,0.03f,0.03f,255,255,0,fonttexture.texID, "PREDKOSC= %f",predkosc);
	piszTXT(-0.54f,0.37f,0.015f,0.03f,0.03f,255,255,0,fonttexture.texID, "K:%d H:%f KS:%f KC:%f",realkat,heading,katskret,katcam);
	piszTXT(-0.54f,0.34f,0.015f,0.03f,0.03f,255,255,0,fonttexture.texID, "FPS= %d",fps);
	glEnable(GL_DEPTH_TEST);
}


int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	if (CreateGLWindow("GG CAR_ENGINE",640,480,16,fullscreen)==FALSE)
	{
		return 0;
	}


	dodaj_ikone("textures/teren/trawa.bmp");
	dodaj_ikone("textures/teren/ulica1.bmp");
	dodaj_ikone("textures/teren/ulica2.bmp");
	dodaj_ikone("textures/teren/rog1.bmp");
	dodaj_ikone("textures/teren/rog2.bmp");
	dodaj_ikone("textures/teren/rog3.bmp");
	dodaj_ikone("textures/teren/rog4.bmp");
	dodaj_ikone("textures/teren/asfalt2.bmp");
	iloscicon-=1;


	xpos=-100;
	zpos=-100;
	heading=180;
	KAMERA=3;

	LoadMap("mapa.dat");
	LoadTextures();

	Zrob_Granice();

	sky=gluNewQuadric();
	gluQuadricNormals(sky,GLU_NONE);
	gluQuadricTexture(sky,GL_TRUE);

	modele3dTGA_ed[1]=LoadModel3DTGA("modele/swiat/tree.dat","modele/swiat/tree.tga",1,true,1,false);
	modele3dTGA_ed[2]=LoadModel3DTGA("modele/swiat/banda.dat","modele/swiat/banda.tga",true,1,4,false);
	modele3dTGA_ed[3]=LoadModel3DTGA("modele/swiat/opony.dat","modele/swiat/opony.tga",true,1,4,false);



	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=TRUE;
			}
 			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			obrt_prz+=predkosc*7.5f;
			if (KAMERA!=5) headingRAD=(heading+katskret+katcam)*RAD;
			else headingRAD=(heading+katskret)*RAD;


			if (KAMERA==1) g_Camera.PositionCamera(480,40,384, xtrans,ytrans,ztrans,0,1,0); // kamera a'la colin
			if (KAMERA==2) g_Camera.PositionCamera((xtrans)+((float)sin(headingRAD)*40),ytrans+20,(ztrans)+((float)cos(headingRAD)*40),xtrans,ytrans+10,ztrans,0,1,0); //camera z bliska
		    if (KAMERA==3) g_Camera.PositionCamera((xtrans)+((float)sin(headingRAD)*80),ytrans+20,(ztrans)+((float)cos(headingRAD)*80),xtrans,ytrans+10,ztrans,0,1,0); //camera z daleka
			if (KAMERA==4) g_Camera.PositionCamera((xtrans)+((float)sin(headingRAD)*4),ytrans+350,(ztrans)+((float)cos(headingRAD)*4),xtrans,ytrans,ztrans,0,1,0);// GTA
		    if (KAMERA==5) g_Camera.PositionCamera((xtrans)+((float)sin(headingRAD)*((max_predkosc-predkosc)+0.05f)),ytrans+7,(ztrans)+((float)cos(headingRAD)*((max_predkosc-predkosc)+0.05f)),xtrans,ytrans+7,ztrans,0,1,0); // ze œrodka

			headingRAD=heading*RAD;


			DrawGLScene();
			Sleep(5);
			Get_FPS(fps);
			SwapBuffers(hDC);

			if (keys['1']) KAMERA=1;
			if (keys['2']) KAMERA=2;
			if (keys['3']) KAMERA=3;
			if (keys['4']) KAMERA=4;
			if (keys['5']) KAMERA=5;

			if (keys['V'])
			{
					PlaySound("q\\g.wav",NULL,SND_ASYNC);
			}
			if (keys['B'])
			{
					PlaySound("q\\a.wav",NULL,SND_ASYNC);
			}
			if (keys['N'])
			{
					PlaySound("q\\l.wav",NULL,SND_ASYNC);
			}



			Fizyka_gry();

			if (keys[VK_ESCAPE])
			{
				done=TRUE;
			}
		}
	}


	KillGLWindow();

	return (msg.wParam);
} 

