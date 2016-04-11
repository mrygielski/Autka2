void Rysuj_dym(float size)
{
	SetTextures(true);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	for (i=ile_dymu;i>=1;i--)
	{
	 if (dym[i].is==true) 
	 {
		ftemp=(255.0f*dym[i].color);
		if (ftemp<0.0f) ftemp=0.0f;
		if (ftemp>=255.0f) ftemp=250.0f;
		BarT(dym[i].x-size,dym[i].y-0.3f-size,dym[i].z,
			  dym[i].x+size,dym[i].y-0.3f-size,dym[i].z,
			  dym[i].x+size,dym[i].y-0.3f+size,dym[i].z,
			  dym[i].x-size,dym[i].y-0.3f+size,dym[i].z,
			  255,255,255,(int)ftemp,textureT[0].texID);
		BarT(dym[i].x,dym[i].y-0.3f-size,dym[i].z-size,
			  dym[i].x,dym[i].y-0.3f-size,dym[i].z+size,
			  dym[i].x,dym[i].y-0.3f+size,dym[i].z+size,
			  dym[i].x,dym[i].y-0.3f+size,dym[i].z-size,
			  255,255,255,(int)ftemp,textureT[0].texID);
		dym[i].color-=0.001f;
		dym[i].y+=0.05f;
		if (dym[i].color<=0.001f) dym[i].is=false;
	 }
	 
	}
	glDisable(GL_BLEND);
	SetTextures(true);	
}

void Rysuj_slad()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glPolygonMode(GL_FRONT,GL_POINT);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glColor4ub(255,255,255,70);
	SetTextures(true);
	glBegin(GL_QUADS);
	for (i=ile_sladow;i>=1;i--)
	{
		glTexCoord2f(0.99f,0.01f);
			glVertex3f(slad[i].x-1,slad[i].y,slad[i].z-1);
		glTexCoord2f(0.99f,0.99f);
			glVertex3f(slad[i].x+1,slad[i].y,slad[i].z-1);
		glTexCoord2f(0.01f,0.01f);
			glVertex3f(slad[i].x+1,slad[i].y,slad[i].z+1);
		glTexCoord2f(0.01f,0.99f);
			glVertex3f(slad[i].x-1,slad[i].y,slad[i].z+1);
	}
	glEnd();
	glDisable(GL_BLEND);
	glPolygonMode(GL_FRONT,GL_FILL);
	SetTextures(true);	
}


void Rysuj_mape()
{
	SetTextures(true);
	
	float x,y,xx,xx2,yy,yy2,a1,a2,a3,a4;
	a1=a2=a3=a4=14;

	/*if (heading<=360.0f && heading>=-360.0f) heading-=3600.0f;

	realkat=(((int)abs(heading)) % 360);

	if (realkat>=45 && realkat<135) {a2=20;a1=1;}
	if (realkat>=225 && realkat<315) {a1=20;a2=1;}
	if (realkat>=135 && realkat<225) {a4=20;a3=1;}
	if (realkat>=0 && realkat<45) {a3=20;a4=1;}
	if (realkat>=315 && realkat<=360) {a3=20;a4=1;}
	*/
	ftemp=xtrans/64;
	xx=(ftemp)-a1; if (xx<0) xx=0;
	xx2=(ftemp)+a2; if (xx2>128) xx2=128;
	ftemp=ztrans/64;
	yy=(ftemp)-a3; if (yy<0) yy=0;
	yy2=(ftemp)+a4; if (yy2>128) yy2=128;

	glPolygonMode(GL_BACK, GL_POINT);
	
	SetTextures(true);
	for (mx=(int)xx;mx<xx2;mx++)
	for (my=(int)yy;my<yy2;my++)
	{
		glBindTexture(GL_TEXTURE_2D,textureIco[mapa[mx][my]]);
		x=(float)(mx<<6);
		y=(float)(my<<6);
		BarT2((x+64),-3,y,
		     (x+64),-3,(y+64),
		     x,-3,(y+64),
		     x,-3,y,
		     255,255,255,255);
	}
	glPolygonMode( GL_BACK, GL_FILL);
/*
	for (mx=xx;mx<xx2;mx++)
	{
		x=mx<<6;
		glPolygonMode( GL_FRONT, GL_POINT);
		BarT(x,61,0,
			 x,-3,0,
		     (x+64),-3,0,
		     (x+64),61,0,
		     255,255,255,255,textureT[1].texID);
		glPolygonMode( GL_FRONT, GL_FILL);
		glPolygonMode( GL_BACK, GL_POINT);
		BarT(x,61,8192,
			 x,-3,8192,
		     (x+64),-3,8192,
		     (x+64),61,8192,
		     255,255,255,255,textureT[1].texID);
		glPolygonMode( GL_BACK, GL_FILL);
	}

	for (mx=yy;mx<yy2;mx++)
	{
		x=mx<<6;
		glPolygonMode( GL_FRONT, GL_POINT);
		BarT(8192,61,x,
			 8192,-3,x,
		     8192,-3,(x+64),
		     8192,61,(x+64),
		     255,255,255,255,textureT[1].texID);
		glPolygonMode( GL_FRONT, GL_FILL);
		
		glPolygonMode( GL_BACK, GL_POINT);
		BarT(0,61,x,
			 0,-3,x,
		     0,-3,(x+64),
		     0,61,(x+64),
		     255,255,255,255,textureT[1].texID);
		glPolygonMode( GL_BACK, GL_FILL);
	}
	SetTextures(true);
	*/
}

void Rysuj_niebo()
{
	SetTextures(true);
	glPushMatrix();
	glTranslatef(xtrans,ytrans,ztrans);
	glRotatef(90,1,0,0);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glColor4ub(255,255,255,255);
	glPolygonMode(GL_FRONT,GL_POINT);	
	gluSphere(sky,1750,8,8);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPopMatrix();
}

void Rysuj_Linie_TEST()
{
	glColor3ub(255,255,0);
	SetTextures(false);
	glBegin(GL_QUADS);
	for (i=1;i<=ilosc_band;i++)
	{
		glVertex3f(bandy[i].Triangle[0].x,bandy[i].Triangle[0].y,bandy[i].Triangle[0].z);
		glVertex3f(bandy[i].Triangle[1].x,bandy[i].Triangle[1].y,bandy[i].Triangle[1].z);

	/**/glVertex3f(bandy[i].Triangle[1].x,bandy[i].Triangle[1].y-3,bandy[i].Triangle[1].z);
	/**/glVertex3f(bandy[i].Triangle[0].x,bandy[i].Triangle[0].y-3,bandy[i].Triangle[0].z);

		
		/*glVertex3f(bandy[i].Triangle[1].x,bandy[i].Triangle[1].y,bandy[i].Triangle[1].z);
		glVertex3f(bandy[i].Triangle[2].x,bandy[i].Triangle[2].y,bandy[i].Triangle[2].z);
		
		glVertex3f(bandy[i].Triangle[0].x,bandy[i].Triangle[0].y,bandy[i].Triangle[0].z);
		glVertex3f(bandy[i].Triangle[2].x,bandy[i].Triangle[2].y,bandy[i].Triangle[2].z);*/
	}
	glEnd();
	glBegin(GL_LINES);
	if(bCollided) glColor3ub(0, 255, 0); else glColor3ub(255, 255, 0);				
	glVertex3f(vLine[1].x,vLine[1].y,vLine[1].z);
	glVertex3f(vLine[0].x,vLine[0].y,vLine[0].z);
	if(bCollided2) glColor3ub(0, 255, 0); else glColor3ub(255, 255, 0);				
	glVertex3f(vLine2[1].x,vLine2[1].y,vLine2[1].z);
	glVertex3f(vLine2[0].x,vLine2[0].y,vLine2[0].z);
	if(bCollided3) glColor3ub(0, 255, 0); else glColor3ub(255, 255, 0);		
	glVertex3f(vLine3[1].x,vLine3[1].y,vLine3[1].z);
	glVertex3f(vLine3[0].x,vLine3[0].y,vLine3[0].z);
	if(bCollided4) glColor3ub(0, 255, 0); else glColor3ub(255, 255, 0);
	glVertex3f(vLine4[1].x,vLine4[1].y,vLine4[1].z);
	glVertex3f(vLine4[0].x,vLine4[0].y,vLine4[0].z);
	glEnd();
	
	SetTextures(true);
}

