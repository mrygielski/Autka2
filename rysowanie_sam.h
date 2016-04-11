void Rysuj_Malucha()
{
	xtrans = -xpos;
	ztrans = -zpos;
	glTranslatef(xtrans, ytrans, ztrans);
	glRotatef(heading+katskret,0,1,0);
	glRotatef(90,0,1,0);
	glRotatef(-90,1,0,0);
	glPolygonMode(GL_BACK,GL_POINT);
	glColor3ub(255,255,255);
	glBindTexture(GL_TEXTURE_2D,modele3d[1].textura);
	//kolo tyl
	glPushMatrix();
	glTranslatef(-6.7f,5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(obrt_tyl,0,1,0);
	glCallList(modele3d[1].model);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.7f,-5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(obrt_tyl,0,1,0);
	glCallList(modele3d[1].model);
	glPopMatrix();

	//kolo przod
	glPushMatrix();
	glTranslatef(6.7f,5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(skret,0,0,1);
	glRotatef(obrt_prz,0,1,0);	
	glCallList(modele3d[1].model);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.7f,-5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(skret,0,0,1);
	glRotatef(obrt_prz,0,1,0);
	glCallList(modele3d[1].model);
	glPopMatrix();

	//samochod
	// wnêtrze
	glPushMatrix();
	glTranslatef(-0.5f,0,3.5f);
	glScalef(20,21.9f,20);
	glRotatef(odchyl,1,0,0);
	glRotatef(podnies,0,1,0);
	glBindTexture(GL_TEXTURE_2D,modele3dTGA[1].textura.texID);
	glCallList(modele3dTGA[1].model);
	glPopMatrix();
	glPolygonMode(GL_BACK,GL_FILL);

	// kierownica
	glPushMatrix();
	glTranslatef(3.0f,3,4.5f+(-podnies/20));
	glScalef(3,3,3);
	glRotatef(20*odchyl,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(-90,0,1,0);
	glBindTexture(GL_TEXTURE_2D,modele3dTGA[2].textura.texID);
	glCallList(modele3dTGA[2].model);
	glPopMatrix();
	glPolygonMode(GL_BACK,GL_FILL);


	// karoseria
	glPolygonMode(GL_BACK,GL_FILL);
	glPushMatrix();
	glTranslatef(-0.5f,0,4.8f);
	glScalef(22,22,22);
	glRotatef(odchyl,1,0,0);
	glRotatef(podnies,0,1,0);
	glBindTexture(GL_TEXTURE_2D,modele3dTGA[0].textura.texID);
	glCallList(modele3dTGA[0].model);
 	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glColor4ub(255,255,255,100);
	glCallList(modele3dTGA[0].model);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_BLEND);

	glPopMatrix();
	glPolygonMode(GL_BACK,GL_FILL);
}

void Rysuj_Tico()
{
	xtrans = -xpos;
	ztrans = -zpos;
	glTranslatef(xtrans, ytrans, ztrans);
	glRotatef(heading+katskret,0,1,0);
	glRotatef(90,0,1,0);
	glRotatef(-90,1,0,0);
	glPolygonMode(GL_BACK,GL_POINT);
	glColor3ub(255,255,255);
	glBindTexture(GL_TEXTURE_2D,modele3d[1].textura);
	
	//kolo tyl
	glPushMatrix();
	glTranslatef(-9.2f,5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(obrt_tyl,0,1,0);
	glCallList(modele3d[1].model);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9.2f,-5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(obrt_tyl,0,1,0);
	glCallList(modele3d[1].model);
	glPopMatrix();

	//kolo przod
	glPushMatrix();
	glTranslatef(7.5f,5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(skret,0,0,1);
	glRotatef(obrt_prz,0,1,0);	
	glCallList(modele3d[1].model);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5f,-5.0f,0);
	glScalef(3.5f,3.f,4.f);
	glRotatef(skret,0,0,1);
	glRotatef(obrt_prz,0,1,0);
	glCallList(modele3d[1].model);
	glPopMatrix();



	//samochod
	// wnêtrze
	glPushMatrix();
	glTranslatef(-0.5f,0,4.0f);
	glScalef(20,21.9f,20);
	glRotatef(odchyl,1,0,0);
	glRotatef(podnies,0,1,0);
	glBindTexture(GL_TEXTURE_2D,modele3dTGA[1].textura.texID);
	glCallList(modele3dTGA[1].model);
	glPopMatrix();
	glPolygonMode(GL_BACK,GL_FILL);


	// kierownica
	glPushMatrix();
	glTranslatef(3.2f,3,5+(-podnies/20));
	glScalef(3,3,3);
	glRotatef(20*odchyl,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(-90,0,1,0);
	glBindTexture(GL_TEXTURE_2D,modele3dTGA[2].textura.texID);
	glCallList(modele3dTGA[2].model);
	glPopMatrix();
	glPolygonMode(GL_BACK,GL_FILL);



	// karoseria
	glPolygonMode(GL_BACK,GL_FILL);
	glPushMatrix();
	glTranslatef(-0.5f,0,4.8f);
	glScalef(22,22,22);
	glRotatef(odchyl,1,0,0);
	glRotatef(podnies,0,1,0);
	glBindTexture(GL_TEXTURE_2D,modele3dTGA[0].textura.texID);
	glCallList(modele3dTGA[0].model);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glColor4ub(255,255,255,100);
	glCallList(modele3dTGA[0].model);
	glPopMatrix();
	glPolygonMode(GL_BACK,GL_FILL);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_BLEND);
	glPopMatrix();
	glPolygonMode(GL_BACK,GL_FILL);

	
	
}