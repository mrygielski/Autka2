MSG	msg;
BOOL done=FALSE;
void DrawGLScene();
const float RAD = 0.017453292519943295769236907684886f;
const float max_predkosc = 2.0f;
float acceleration = 0.01f;
float hamulec = 0.0125f;
float max_cam;
///////////////////ZMIENNE////
CCamera g_Camera;


int texture[50],textureIco[50];
int textureL[50];
TextureImage textureT[50];
TextureImage fonttexture,fonttexture2;


model3D modele3d[20];
model3Dtga modele3dTGA[5];


GLUquadricObj *sky;

// CHODZENIE
float xpos,zpos,heading,yrot,headingRAD;
int realkat;
float xtrans,ytrans,ztrans;
bool reczny;

float obrt_tyl, obrt_prz, predkosc, skret, podnies, odchyl;
float carX, carY, kat, katskret, katcam;
int fps;

struct XYdym
{
	float x;
	float y;
	float z;
	bool is;
	float color;
};

struct XYslad
{
	float x;
	float y;
	float z;
};

struct SCIANA
{
  CVector2 Triangle[3];
};

int ile_dymu=1000,max_dym;
XYdym dym[1001];

int ile_sladow=1000,sladow,tslad;
XYslad slad[1001];

int i,itemp;
float ftemp;

int KAMERA;


bool bCollided, bCollided2, bCollided3, bCollided4, kolizja;

SCIANA lewo,prawo,gora,dol;
int ilosc_band;
SCIANA bandy[1000];

CVector2 vLine[2],vLine2[2],vLine3[2],vLine4[2];





unsigned short mapa[129][129];
FILE* plik;
int iloscicon;
int mx,my;


model3Dtga modele3dTGA_ed[255];
struct Tmodel
{
	float x,y,rot;
	unsigned short numer;
};
Tmodel modele[10000];
int nrmodelu=1,ilosc_modeli=1;
float modele_y[10000];