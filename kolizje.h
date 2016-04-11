void Zrob_Sam_Linie(float dl)
{
	headingRAD=(heading+katskret+27)*RAD;
	vLine[0].x=xtrans-((float)sin(headingRAD)*(dl-1+predkosc));
	vLine[0].y=ytrans;
	vLine[0].z=ztrans-((float)cos(headingRAD)*(dl-1+predkosc));
	vLine2[0].x=xtrans+((float)sin(headingRAD)*(dl-predkosc));
	vLine2[0].y=ytrans;
	vLine2[0].z=ztrans+((float)cos(headingRAD)*(dl-predkosc));
	vLine3[0].x=xtrans+((float)sin(headingRAD)*(dl-predkosc));
	vLine3[0].y=ytrans;
	vLine3[0].z=ztrans+((float)cos(headingRAD)*(dl-predkosc));
	vLine4[0].x=xtrans-((float)sin(headingRAD)*(dl-1+predkosc));
	vLine4[0].y=ytrans;
	vLine4[0].z=ztrans-((float)cos(headingRAD)*(dl-1+predkosc));
	
	headingRAD=(heading+katskret-27)*RAD;
	vLine[1].x=xtrans-((float)sin(headingRAD)*(dl-1+predkosc));
	vLine[1].y=ytrans;
	vLine[1].z=ztrans-((float)cos(headingRAD)*(dl-1+predkosc));
	vLine2[1].x=xtrans+((float)sin(headingRAD)*(dl-predkosc));
	vLine2[1].y=ytrans;
	vLine2[1].z=ztrans+((float)cos(headingRAD)*(dl-predkosc));
	vLine3[1].x=xtrans-((float)sin(headingRAD)*(dl-1+predkosc));
	vLine3[1].y=ytrans;
	vLine3[1].z=ztrans-((float)cos(headingRAD)*(dl-1+predkosc));
	vLine4[1].x=xtrans+((float)sin(headingRAD)*(dl-predkosc));
	vLine4[1].y=ytrans;
	vLine4[1].z=ztrans+((float)cos(headingRAD)*(dl-predkosc));
	
	headingRAD=heading*RAD;
}

bool Colission(SCIANA wall_)
{
	bCollided = IntersectedPolygon(wall_.Triangle, vLine, 3),
	bCollided2 = IntersectedPolygon(wall_.Triangle, vLine2, 3),
	bCollided3 = IntersectedPolygon(wall_.Triangle, vLine3, 3),
	bCollided4 = IntersectedPolygon(wall_.Triangle, vLine4, 3);

	if (bCollided||bCollided2||bCollided3||bCollided4) return true; else return false;
}


void Wykryj_kolizje()
{
	kolizja = Colission(lewo);
	if (kolizja==false) kolizja = Colission(dol);
	if (kolizja==false) kolizja = Colission(prawo);
	if (kolizja==false) kolizja = Colission(gora);
	if (kolizja==false) 
	{
		for (i=1;i<=ilosc_band;i++)
		{
			kolizja = Colission(bandy[i]);
			if (kolizja) break;
		}
	}
}