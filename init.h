void Zrob_Granice()
{
	lewo.Triangle[0].x=0;
	lewo.Triangle[0].y=0;
	lewo.Triangle[0].z=0;
	lewo.Triangle[1].x=128*64;
	lewo.Triangle[1].y=0;
	lewo.Triangle[1].z=0;
	lewo.Triangle[2].x=128*32;
	lewo.Triangle[2].y=30;
	lewo.Triangle[2].z=0;

	prawo.Triangle[0].x=0;
	prawo.Triangle[0].y=0;
	prawo.Triangle[0].z=128*64;
	prawo.Triangle[1].x=128*64;
	prawo.Triangle[1].y=0;
	prawo.Triangle[1].z=128*64;
	prawo.Triangle[2].x=128*32;
	prawo.Triangle[2].y=30;
	prawo.Triangle[2].z=128*64;

	dol.Triangle[0].x=0;
	dol.Triangle[0].y=0;
	dol.Triangle[0].z=0;
	dol.Triangle[1].x=0;
	dol.Triangle[1].y=0;
	dol.Triangle[1].z=128*64;
	dol.Triangle[2].x=0;
	dol.Triangle[2].y=30;
	dol.Triangle[2].z=128*32;

	gora.Triangle[0].x=128*64;
	gora.Triangle[0].y=0;
	gora.Triangle[0].z=0;
	gora.Triangle[1].x=128*64;
	gora.Triangle[1].y=0;
	gora.Triangle[1].z=128*64;
	gora.Triangle[2].x=128*64;
	gora.Triangle[2].y=30;
	gora.Triangle[2].z=128*32;

}

void LoadMap(char* pl)
{
/*	plik=fopen(pl,"r");
	fread(&mapa,sizeof(mapa),1,plik);
	fread(&ilosc_band,sizeof(ilosc_band),1,plik);
	
	
	for (i=1;i<=ilosc_band;i++)
	{
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i].Triangle[0].x=(ftemp+1)*64;
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i].Triangle[0].z=(ftemp+1)*64;
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i].Triangle[1].x=(ftemp+1)*64;
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i].Triangle[1].z=(ftemp+1)*64;
		bandy[i].Triangle[2].x=bandy[i].Triangle[0].x;
		bandy[i].Triangle[0].y=-0;
		bandy[i].Triangle[1].y=-0;
		bandy[i].Triangle[2].y=30;
		bandy[i].Triangle[2].z=bandy[i].Triangle[0].z;	
	}

	fread(&ilosc_modeli,sizeof(ilosc_modeli),1,plik);

	
	fread(&modele,sizeof(modele),1,plik);

	for (i=1;i<=ilosc_modeli;i++)
	{
		modele[i].x=(modele[i].x+1)*64;
		modele[i].y=(modele[i].y+1)*64;
	}


	fclose(plik);*/

	plik=fopen("mapa.dat","r");
	fread(&mapa,sizeof(mapa),1,plik);
	
	fread(&ilosc_band,sizeof(ilosc_band),1,plik);
	//ilosc_band++;
	
	for (i=1;i<=1000;i++)
	{
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i-1].Triangle[0].x=(ftemp+1)*64;
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i-1].Triangle[0].z=(ftemp+1)*64;
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i-1].Triangle[1].x=(ftemp+1)*64;
		fread(&ftemp,sizeof(ftemp),1,plik);bandy[i-1].Triangle[1].z=(ftemp+1)*64;
		bandy[i].Triangle[2].x=bandy[i].Triangle[0].x;
		bandy[i].Triangle[0].y=-0;
		bandy[i].Triangle[1].y=-0;
		bandy[i].Triangle[2].y=30;
		bandy[i].Triangle[2].z=bandy[i].Triangle[0].z;	
	}
	
	fread(&ilosc_modeli,sizeof(ilosc_modeli),1,plik);
	fread(&modele,sizeof(modele),1,plik);

	for (i=0;i<=ilosc_modeli;i++)
	{
		modele[i].x=modele[i].x*64+64;
		modele[i].y=modele[i].y*64+64;
	}

	modele_y[1]=26;
	modele_y[2]=2;
	modele_y[3]=0;

	fclose(plik);
}

void dodaj_ikone(char* path)
{
	textureIco[iloscicon]=LoadTexture(path,1,true,false);
	iloscicon+=1;	
}

void LoadTextures()
{
	LoadTGAFile(&fonttexture,"textures/courier.tga",false,1,false);

    texture[0]=LoadTexture("textures/sky.bmp",1,1,false);
	texture[1]=LoadTexture("textures/a.bmp",1,1,true);
	texture[2]=LoadTexture("textures/slad.bmp",1,1,true);


 	modele3dTGA[0]=LoadModel3DTGA("modele/maluch/malec.dat","modele/maluch/karoseria.tga",2,false,1,true);
	modele3dTGA[1]=LoadModel3DTGA("modele/maluch/wnetrze.dat","modele/maluch/karoseria.tga",2,false,1,false);
	modele3dTGA[2]=LoadModel3DTGA("modele/kierownica/kierownica.dat","modele/kierownica/kierownica.tga",2,false,1,false);
	modele3d[1]=LoadModel3D("modele/maluch/kolo.dat","modele/maluch/kolo.bmp",2,false,1,false);
	/*
 	modele3dTGA[0]=LoadModel3DTGA("modele/tico/tico.dat","modele/tico/karoseria.tga",2,false,1,true);
	modele3dTGA[1]=LoadModel3DTGA("modele/tico/wnetrze.dat","modele/tico/karoseria.tga",2,false,1,false);
	modele3dTGA[2]=LoadModel3DTGA("modele/kierownica/kierownica.dat","modele/kierownica/kierownica.tga",2,false,1,false);
	modele3d[1]=LoadModel3D("modele/tico/kolo.dat","modele/tico/kolo.bmp",2,false,1,false);
	*/
	
	LoadTGAFile(&textureT[0],"textures/dym.tga",false,2,false);
	LoadTGAFile(&textureT[1],"textures/sciana.tga",false,2,false);

}