
void Dodaj_dymek(float x, float y, float z)
{
	for (i=1;i<ile_dymu;i++)
		if (dym[i].is==false)
		{
			dym[i].x=x;
			dym[i].y=y;
			dym[i].z=z;
			dym[i].is=true;
			dym[i].color=0.1f; 
			return;
		}
}

void Dodaj_slad(float x, float y, float z)
{
		tslad+=1;
		if (tslad==1)
		{
			
		sladow+=1;
		if (sladow>ile_sladow) sladow=0;
		slad[sladow].x=x;
		slad[sladow].y=y-0.5f;
		slad[sladow].z=z;
		
		tslad=0;
		return;
		}
}




void Forward(float szybkosc_chodzenia)
{
	xpos += ((float)sin(headingRAD)*szybkosc_chodzenia);
	zpos += ((float)cos(headingRAD)*szybkosc_chodzenia);
	
}


void AddBackSmoke()
{
	headingRAD=(heading+katskret+35)*RAD;
	Dodaj_dymek((xtrans)+((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans+((float)cos(headingRAD)*8));

	Dodaj_slad((xtrans)+((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans+((float)cos(headingRAD)*8));

	headingRAD=(heading+katskret-35)*RAD;
	Dodaj_dymek((xtrans)+((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans+((float)cos(headingRAD)*8));
	Dodaj_slad((xtrans)+((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans+((float)cos(headingRAD)*8));


	headingRAD=heading*RAD;
}

void AddFrontSmoke()
{
	headingRAD=(heading+katskret+35)*RAD;
	Dodaj_dymek((xtrans)-((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans-((float)cos(headingRAD)*8));

	Dodaj_slad((xtrans)-((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans-((float)cos(headingRAD)*8));

	headingRAD=(heading+katskret-35)*RAD;
	Dodaj_dymek((xtrans)-((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans-((float)cos(headingRAD)*8));

	Dodaj_slad((xtrans)-((float)sin(headingRAD)*8),
				ytrans-2,
				ztrans-((float)cos(headingRAD)*8));

	headingRAD=heading*RAD;
}

void Fizyka_gry()
{
	if (kolizja==true) {predkosc=-0.5f;Forward(predkosc);}

	if (predkosc<0.5f) heading -= (odchyl*(predkosc))/6;
	else               heading -= (odchyl)/6;

	if (keys[VK_RIGHT])
	{
		yrot = heading;
		if (skret>-21) skret-=0.5f;
		if (predkosc!=0) {
		if (odchyl<5) odchyl+=0.2f;
		if (katcam<max_cam) katcam+=0.2f;
		if (predkosc>2) AddFrontSmoke();
		if (predkosc>0) predkosc-=0.001f;}
	} 
	else 
	{
		if (katcam>0) katcam-=0.2f;
		if (skret<0) skret+=0.5f;
		if (odchyl>0) odchyl-=0.1f;				
	}

	if (keys[VK_LEFT])
	{
		yrot = heading;
		if (skret<21) skret+=0.5f;
		if (predkosc!=0) {
		if (odchyl>-5) odchyl-=0.2f;
		if (predkosc>0) predkosc-=0.001f;
		if (predkosc>2) AddFrontSmoke();
		if (katcam>-max_cam) katcam-=0.2f;}
	} 
	else
	{
		if (katcam<0) katcam+=0.2f;
		if (skret>0) skret-=0.5f;
		if (odchyl<0) odchyl+=0.1f;
	}


	if (keys[VK_UP]) 
	{
		Forward(predkosc);
		if (predkosc<max_predkosc) predkosc+=acceleration;
		if (podnies>-5) podnies-=0.2f;
	} 
	else 
	{
		if (predkosc>0) predkosc-=0.001f;
		if (predkosc<0) predkosc=0;
		Forward(predkosc);
		if (podnies<0) podnies+=0.1f;
	}

	if (keys[VK_DOWN]) 
	{
		if (predkosc>acceleration) AddBackSmoke();
		if (predkosc>0) predkosc-=hamulec;
		if (podnies<5) podnies+=0.2f;
	} 
	else
	{
		if (podnies>0) podnies-=0.1f;
	}



	if (keys[VK_SPACE])
	{
		if (predkosc>acceleration) AddBackSmoke();
		if (keys[VK_RIGHT]) 
		{
			if (predkosc>0.5f) katskret-=0.25f; else {katskret-=predkosc*0.5f;}
			if (predkosc>0) predkosc-=acceleration+(abs(katskret)*0.00001f);
		} else
		if (keys[VK_LEFT]) 
		{
			if (predkosc>0.5f) katskret+=0.25f; else {katskret+=predkosc*0.5f;}
			if (predkosc>0) predkosc-=acceleration+(abs(katskret)*0.00001f);
		}else
		if (keys[VK_UP]) 
		{
			if (predkosc>0) predkosc-=acceleration*2;
		}
		else
		if (predkosc>0) predkosc-=acceleration;
		reczny=true;
		max_cam=40;
		obrt_tyl=0;
	} 
	else 
	{
		reczny=false;
		obrt_tyl=obrt_prz;
		max_cam=15;
	}

	if (katskret!=0 && reczny==false) 
	{
		if (katskret<0) {heading-=1.0f;katskret+=1.0f;}
		if (katskret>0) {heading+=1.0f;katskret-=1.0f;}
		
	}
}