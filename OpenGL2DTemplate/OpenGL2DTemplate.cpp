#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <glut.h>


void drawCircle(int x, int y, float r);
void createWeapon();
void enemyShots();
void Display();
void Key(unsigned char key, int x, int y);
void Anim(void);
void print(int x, int y, char *string);
void TimerEnemyShot(int value);
void Timer(int value);
void TimerPowerUp1(int value);
void TimerPowerUp2(int value);
void TimerDefender(int Value);
void TimerBack(int value);
int* bezier(float t, int* p0, int* p1, int* p2, int* p3);


int pTransX = 0;
int pTransY = 0;
int wTransY = 0;
int eTransX = 0;
int eTransY = 0;
int sTransX = 0;
int sTransY = 0;
int dTransX = 0;
int dShotTransX = 0;
int dShotTransY = 0;
int power1TransY = 0;
int power2TransY = 0;
bool flag1 = false;
bool flag2 = false;
bool wFlag = false;
bool sFlag = false;
bool dFlag = false;
bool sdFlag = false;
bool enemyLevel1 = true;
bool enemyLevel2 = false;
bool enemyLevel3 = false;
bool power1Flag = false;
bool power2Flag = false;
bool endFlagDie = false;
bool endFlagWin = false;

bool background = false;
int back = 600;
float wTransX = 0;
int healthValue = 100;
int scoreValue = 0;
int tx; 
int ty;
double xa;
double ya;
double za;

double xb;
double yb;
double zb;

int p0[2];
int p1[2];
int p2[2];
int p3[2];
int t = 0;


void main(int argc, char** argr) {
  glutInit(&argc, argr);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1000, 600);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Assignment 1");
  glutDisplayFunc(Display);
  glutKeyboardFunc(Key);
  glutIdleFunc(Anim);
  glutTimerFunc(0, TimerEnemyShot, 0);
  glutTimerFunc(0, TimerPowerUp1, 0);
  glutTimerFunc(0, TimerPowerUp2, 0);
  glutTimerFunc(0, TimerDefender, 0);
  glutTimerFunc(0, Timer, 0);
  glutTimerFunc(0, TimerBack, 0);



  p0[0] = 100;
  p0[1] = 450;

  p1[0] = 100;
  p1[1] = 580;

  p2[0] = 250;
  p2[1] = 580;

  p3[0] = 250;
  p3[1] = 450;

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glPointSize(9.0);
  gluOrtho2D(0.0, 1000.0, 0.0, 600.0);
  glutMainLoop();
}

void Key(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		if (pTransX < 377) {
			pTransX += 8;
			break;
		}
	case 'a':
		if (pTransX > -377) {
			pTransX -= 8;
			break;
		}
	case ' ':
		wFlag = true;
		
		
		break;
	}
	
	glutPostRedisplay();

}
void Anim(void) {
	
	//translation of weapon
	if (wFlag == true && wTransY <400) {
		wTransY += 3;
	}
	else {
		wFlag = false;
		wTransY = 0;
	}


	/*if (t >= 1) {
		p1[0] = rand() % 900 + 100;
		p1[1] = rand() % 500 + 100;
		p2[0] = rand() % 900 + 100;
		p2[1] = rand() % 500 + 100;
		
		int p5[2];
		p5[0] = p0[0];
		p0[0] = p3[0];
		p3[0] = p0[0];

		p5[1] = p0[1];
		p0[1] = p3[1];
		p3[1] = p0[1];

		t = 0;
	}
	else {
		t += 0.5;
		int* p = bezier(t, p0, p1, p2, p3);
		eTransX = p[0];
		eTransY = p[1];
	}*/
	
	//translation in x for enemy
	if (eTransX < 900 && flag1 == false) {
		//eTransX += rand() % 5 + 1;
		eTransX += 2;
	}
	if (eTransX > -800 && flag1 == true) {
		//eTransX -= rand() % 5 + 1;
		eTransX -= 2;
	}
	if (eTransX == 900) {
		flag1 = true;
	}
	if (eTransX == -800) {
		flag1 = false;
	}

	//translation in y for enemy
	if (eTransY < 200 && flag2 == false) {
		//eTransY += rand() % 5 + 1;
		eTransY += 2;
	}
	if (eTransY > -200 && flag2 == true) {
		//eTransY -= rand() % 5 + 1;
		eTransY -= 2;
	}
	if (eTransY == 200) {
		flag2 = true;
	}
	if (eTransY == -200) {
		flag2 = false;
	}

	//translation of enemy shot in y
	if (sFlag == true && sTransY >-1100) {
		//sTransY -= rand() % 5 + 1;
		sTransY -= 4;
	}
	else {
		sTransY = 0;
		sFlag = false;

	}

	//translation of first poewrup
	if (power1Flag == true && power1TransY >-800) {
		//sTransY -= rand() % 5 + 1;
		power1TransY -= 1;
	}
	else {
		xa = rand() % 900 + 10;
		ya = xa + 50;
		za = (ya + xa) / 2;
		power1TransY = 0;
		power1Flag = false;
	}

	//translation of second powerup 
	if (power2Flag == true && power2TransY >-800) {
		//sTransY -= rand() % 5 + 1;
		power2TransY -= 1;
	}
	else {
		xb = rand() % 900 + 10;
		yb = xb + 20;
		zb = (yb + xb) / 2;
		power2TransY = 0;
		power2Flag = false;
	}

	//translation of defender
	if (dFlag == true && dTransX < 1140) {
		dTransX += 1;
	}
	else {
		dFlag = false;
		dTransX = 0;
	}

	//Background Movement
	if (background == true && back < 1000) {
		back += 2;
	}
	else {
		background = false;
		back = 0;
	}


	//translation of defender shot in y
	if (sdFlag == true && dShotTransY >-1100) {
		//sTransY -= rand() % 5 + 1;
		dShotTransY -= 2;
	}
	else {
		dShotTransY = 0;
		sdFlag = false;

	}

	//collision of player's weapon with enemy
	tx = eTransX*0.45;
	ty = eTransY*0.45;
	int wTipX = 600 +pTransX;
	int wTipY = 190+ wTransY;
	int eUpBorderY = ty + 460;
	int eLeftBorderX = tx + 283;
	int eRightBorderX = tx + 630;
	if (wTipY == 460
		&& wTipX >= eLeftBorderX
		&& wTipX <= eRightBorderX
		&& wFlag == true) {
		healthValue -= 25;
	}

	//collision of powerups with player
	int pLeftBorderX = pTransX + 340;
	int pRightBorderX = pTransX + 633;

	int power1TipX = za;
	int power1TipY = 550 + power1TransY;
	if (power1TipX >= pLeftBorderX 
		&& power1TipX <= pRightBorderX
		&& power1TipY == 130
		&& power1Flag) {
		scoreValue += 25;
	}
	int power2TipX = zb;
	int power2TipY = 570 + power2TransY;
	if (power2TipX >= pLeftBorderX
		&& power2TipX <= pRightBorderX
		&& power2TipY == 130
		&& power2Flag) {
		healthValue -= 25;
	}

	//collision of enemy shot with player
	int eShotX = 600+ (sTransX*0.45);
	int eShotY = 500 + (sTransY*0.45);
	if (eShotY == 100
		&& eShotX >= pLeftBorderX
		&& eShotX <= pRightBorderX
		&& sFlag == true) {
		pTransY = 600;
		endFlagDie = true;
	}
	/*if (eShotY <= eUpBorderY-200) {
		test = true;
	}
	if (sTransY == -1100) {
		test = false;
	}*/

	//collision of weapon with defender
	int dLeftBorderX = -140 + dTransX;
	int dRightBorderX = 0 + dTransX;
	int dBorderY = 300;
	int w = 190 + wTransY;
	if (wTipX >= dLeftBorderX
		&& wTipX <= dRightBorderX
		&& wFlag == true
		) {
		wFlag = false;
	}

	//collision of defender shot with enemy
	int sdBorderY = 330 + dShotTransY;
	if (sdFlag
		&& sdBorderY == 130
		&& eShotX >= pLeftBorderX
		&& eShotX <= pRightBorderX
		) {
		pTransY = 600;
		endFlagDie = true;
	}


	//handling enemy levels
	if (healthValue == 0 && enemyLevel1 ==true && enemyLevel2 == false && enemyLevel3 == false) {
		enemyLevel2 = true;
		enemyLevel1 = false;
		healthValue = 200;
	}
	if (healthValue == 0 && enemyLevel1 == false && enemyLevel2 == true && enemyLevel3 == false) {
		enemyLevel2 = false;
		enemyLevel3 = true;
		healthValue = 300;
	}
	if (healthValue == 0 && enemyLevel1 == false && enemyLevel2 == false && enemyLevel3 == true) {
		endFlagWin = true;
	}

	glutPostRedisplay();

}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

  //glBegin(GL_POINTS);
  //for (float t = 0;t<1;t += 0.001)
  //{
	 // int* p = bezier(t, p0, p1, p2, p3);
	 // glVertex3f(p[0], p[1], 0);
  //}
  //glEnd();

  //Background
  if (background == true) {
	  glPushMatrix();
	  glTranslatef(0,back,0);
	  glColor3f(1.0f, 0.0f, 0.0f);
	  
	  glBegin(GL_QUADS);
	  
	  glVertex3f(100.0f, 100.0f, 0.0f);
	  glVertex3f(150.0f, 100.0f, 0.0f);
	  glVertex3f(150.0f, 150.0f, 0.0f);
	  glVertex3f(100.0f, 150.0f, 0.0f);
	  
	  glVertex3f(160.0f, 100.0f, 0.0f);
	  glVertex3f(210.0f, 100.0f, 0.0f);
	  glVertex3f(210.0f, 150.0f, 0.0f);
	  glVertex3f(160.0f, 150.0f, 0.0f);

	  glVertex3f(220.0f, 100.0f, 0.0f);
	  glVertex3f(280.0f, 100.0f, 0.0f);
	  glVertex3f(280.0f, 150.0f, 0.0f);
	  glVertex3f(220.0f, 150.0f, 0.0f);
	  
	  glVertex3f(290.0f, 100.0f, 0.0f);
	  glVertex3f(350.0f, 100.0f, 0.0f);
	  glVertex3f(350.0f, 150.0f, 0.0f);
	  glVertex3f(290.0f, 150.0f, 0.0f);

	  glVertex3f(360.0f, 100.0f, 0.0f);
	  glVertex3f(420.0f, 100.0f, 0.0f);
	  glVertex3f(420.0f, 150.0f, 0.0f);
	  glVertex3f(360.0f, 150.0f, 0.0f);

	  glVertex3f(430.0f, 100.0f, 0.0f);
	  glVertex3f(490.0f, 100.0f, 0.0f);
	  glVertex3f(490.0f, 150.0f, 0.0f);
	  glVertex3f(430.0f, 150.0f, 0.0f);

	  glVertex3f(500.0f, 100.0f, 0.0f);
	  glVertex3f(560.0f, 100.0f, 0.0f);
	  glVertex3f(560.0f, 150.0f, 0.0f);
	  glVertex3f(500.0f, 150.0f, 0.0f);

	  glVertex3f(570.0f, 100.0f, 0.0f);
	  glVertex3f(630.0f, 100.0f, 0.0f);
	  glVertex3f(630.0f, 150.0f, 0.0f);
	  glVertex3f(570.0f, 150.0f, 0.0f);

	  glVertex3f(640.0f, 100.0f, 0.0f);
	  glVertex3f(700.0f, 100.0f, 0.0f);
	  glVertex3f(700.0f, 150.0f, 0.0f);
	  glVertex3f(640.0f, 150.0f, 0.0f);

	  glVertex3f(710.0f, 100.0f, 0.0f);
	  glVertex3f(770.0f, 100.0f, 0.0f);
	  glVertex3f(770.0f, 150.0f, 0.0f);
	  glVertex3f(710.0f, 150.0f, 0.0f);

	  glVertex3f(780.0f, 100.0f, 0.0f);
	  glVertex3f(840.0f, 100.0f, 0.0f);
	  glVertex3f(840.0f, 150.0f, 0.0f);
	  glVertex3f(780.0f, 150.0f, 0.0f);

	  glVertex3f(850.0f, 100.0f, 0.0f);
	  glVertex3f(910.0f, 100.0f, 0.0f);
	  glVertex3f(910.0f, 150.0f, 0.0f);
	  glVertex3f(850.0f, 150.0f, 0.0f);


	  glEnd();
	  glPopMatrix();
  }

  //Enemy Border
  glPushMatrix();
  glTranslatef(tx, ty, 0);
  glBegin(GL_QUADS);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex3f(283.0f, 450.0f, 0.0f);
  glVertex3f(630.0f, 450.0f, 0.0f);
  glVertex3f(630.0f, 520.0f, 0.0f);
  glVertex3f(283.0f, 520.0f, 0.0f);
  glEnd();
  glPopMatrix();

  //Enemy
  glPushMatrix();
  glTranslatef(300,485,0);
  glScalef(0.45, 0.45, 0.0);
  glTranslatef(-300,-485, 0);
  glTranslatef(250,0,0);

  glTranslatef(eTransX, eTransY, 0);
  glBegin(GL_TRIANGLES);
  if (enemyLevel1 == true) {
	  glColor3f(0.419608f, 0.137255f, 0.556863f);
  }
  if (enemyLevel2 == true) {
	  glColor3f(0.329412f, 0.329412f, 0.329412f);
  }
  if (enemyLevel3 == true) {
	  glColor3f(0.372549f, 0.623529f, 0.623529f);
  }
  glVertex3f(250.0f, 475.0f, 0.0f);
  glVertex3f(100.0f, 440.0f, 0.0f);
  glVertex3f(100.0f, 540.0f, 0.0f);

  glVertex3f(600.0f, 450.0f, 0.0f);
  glVertex3f(600.0f, 550.0f, 0.0f);
  glVertex3f(700.0f, 500.0f, 0.0f);

  glVertex3f(600.0f, 450.0f, 0.0f);
  glVertex3f(600.0f, 500.0f, 0.0f);
  glVertex3f(200.0f, 475.0f, 0.0f);

  glVertex3f(600.0f, 550.0f, 0.0f);
  glVertex3f(600.0f, 500.0f, 0.0f);
  glVertex3f(200.0f, 475.0f, 0.0f);
  glEnd();

  glBegin(GL_QUADS);
  glVertex3f(375.0f, 400.0f, 0.0f);
  glVertex3f(575.0f, 500.0f, 0.0f);
  glVertex3f(475.0f, 500.0f, 0.0f);
  glVertex3f(275.0f, 400.0f, 0.0f);

  glVertex3f(375.0f, 570.0f, 0.0f);
  glVertex3f(575.0f, 500.0f, 0.0f);
  glVertex3f(475.0f, 500.0f, 0.0f);
  glVertex3f(275.0f, 570.0f, 0.0f);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(1.0f, 0.0f, 1.0f);
  glVertex3f(560.0f, 485.0f, 0.0f);
  glVertex3f(560.0f, 515.0f, 0.0f);
  glVertex3f(585.0f, 515.0f, 0.0f);
  glVertex3f(585.0f, 485.0f, 0.0f);

  glVertex3f(530.0f, 485.0f, 0.0f);
  glVertex3f(530.0f, 515.0f, 0.0f);
  glVertex3f(555.0f, 515.0f, 0.0f);
  glVertex3f(555.0f, 485.0f, 0.0f);

  glVertex3f(500.0f, 485.0f, 0.0f);
  glVertex3f(500.0f, 515.0f, 0.0f);
  glVertex3f(525.0f, 515.0f, 0.0f);
  glVertex3f(525.0f, 485.0f, 0.0f);

  glVertex3f(470.0f, 485.0f, 0.0f);
  glVertex3f(470.0f, 515.0f, 0.0f);
  glVertex3f(495.0f, 515.0f, 0.0f);
  glVertex3f(495.0f, 485.0f, 0.0f);

  glVertex3f(440.0f, 485.0f, 0.0f);
  glVertex3f(440.0f, 515.0f, 0.0f);
  glVertex3f(465.0f, 515.0f, 0.0f);
  glVertex3f(465.0f, 485.0f, 0.0f);
  glEnd();

  glColor3f(1.0f, 0.0f, 1.0f);
  drawCircle(650,500 ,10);

  glPopMatrix();

  //Enemy Shots
  glPushMatrix();
  glTranslatef(300, 485, 0);
  glScalef(0.45, 0.45, 0.0);
  glTranslatef(-300, -485, 0);
  glTranslatef(250, 0, 0);

  if (sFlag == true) {
	glTranslatef(sTransX, sTransY, 0);
	enemyShots();
  }
  glPopMatrix();

  //defender shots
  glColor3f(1.0f, 1.0f, 1.0f);
  glPushMatrix();
  if (sdFlag) {
	  glTranslatef(dShotTransX, dShotTransY, 0);
	  drawCircle(-100, 350, 20);
  }
  glPopMatrix();


  //first Power-Up
  glPushMatrix();
  glTranslatef(0, power1TransY, 0);
  if (power1Flag == true) {
	  glColor3f(1.0f, 1.0f, 0.0f);
	  glBegin(GL_TRIANGLES);
	  glVertex3f(xa, 600.0f, 0.0f);
	  glVertex3f(ya, 600.0f, 0.0f);
	  glVertex3f(za, 550.0f, 0.0f);
	  glEnd();
	  glBegin(GL_QUADS);
	  glVertex3f(xa, 600.0f, 0.0f);
	  glVertex3f(ya, 600.0f, 0.0f);
	  glVertex3f(ya, 620.0f, 0.0f);
	  glVertex3f(xa, 620.0f, 0.0f);
	  glEnd();
	  glColor3f(0.0f, 0.0f, 1.0f);
	  int d = (ya + xa) / 2;
	  drawCircle(d,600,15);
  }
  glPopMatrix();

  
  //Second Power-Up
  glPushMatrix();
  glTranslatef(0, power2TransY, 0);
  if (power2Flag == true) {
	  glColor3f(1.0f, 0.5f, 0.0f);
	  glBegin(GL_QUADS);
	  glVertex3f(xb, 600.0f, 0.0f);
	  glVertex3f(yb, 600.0f, 0.0f);
	  glVertex3f(yb, 642.0f, 0.0f);
	  glVertex3f(xb, 642.0f, 0.0f);
	  glEnd();
	  glBegin(GL_TRIANGLES);
	  glVertex3f(xb, 600.0f, 0.0f);
	  glVertex3f(yb, 600.0f, 0.0f);
	  glVertex3f(zb, 570.0f, 0.0f);
	  glEnd();
	  glColor3f(0.0f, 0.0f, 0.0f);
	  drawCircle(zb,635,7);
	  drawCircle(zb,621,7);
	  drawCircle(zb,607,7);

  }
  glPopMatrix();

  //Defender of the enemy
  glPushMatrix();
  glTranslatef(dTransX, 0, 0);
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-140.0f, 300.0f, 0.0f);
  glVertex3f(0.0f, 300.0f, 0.0f);
  glVertex3f(0.0f, 340.0f, 0.0f);
  glVertex3f(-140.0f, 340.0f, 0.0f);
  glEnd();
  glPopMatrix();

  //Player
  glPushMatrix();
  glTranslatef(pTransX,pTransY,0);

  //Player's Body
  glBegin(GL_QUADS); 
  glColor3f(0.419608f, 0.137255f, 0.556863f);
  glVertex3f(425.0f, 50.0f, 0.0f);
  glVertex3f(450.0f, 200.0f, 0.0f);
  glVertex3f(550.0f, 200.0f, 0.0f);
  glVertex3f(575.0f, 50.0f, 0.0f);
  glEnd();

  //Player's Eye
  drawCircle(540, 210, 25);
  drawCircle(460, 210, 25);

  glColor3f(1.0f, 1.0f, 1.0f);
  drawCircle(539, 210, 18);
  drawCircle(462, 210, 18);

  glColor3f(0.0f, 1.0f, 0.498039f);
  drawCircle(536, 208, 9);
  drawCircle(465, 208, 9);

  glColor3f(0.0f, 0.0f, 0.0f);
  drawCircle(536, 208, 5);
  drawCircle(465, 208, 5);

  //Player's mouth
  glBegin(GL_TRIANGLES); 
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex3f(500.0f, 120.0f, 0.0f);
  glVertex3f(450.0f, 150.0f, 0.0f);
  glVertex3f(550.0f, 150.0f, 0.0f);

  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(515.0f, 130.0f, 0.0f);
  glVertex3f(515.0f, 140.0f, 0.0f);
  glVertex3f(530.0f, 138.0f, 0.0f);

  glVertex3f(485.0f, 130.0f, 0.0f);
  glVertex3f(485.0f, 140.0f, 0.0f);
  glVertex3f(470.0f, 138.0f, 0.0f);
  glEnd();

  //Player's legs
  glBegin(GL_QUADS); 
  glColor3f(0.419608f, 0.137255f, 0.556863f);
  glVertex3f(465.0f, 50.0f, 0.0f);
  glVertex3f(465.0f, 20.0f, 0.0f);
  glVertex3f(450.0f, 20.0f, 0.0f);
  glVertex3f(450.0f, 50.0f, 0.0f);

  glVertex3f(465.0f, 20.0f, 0.0f);
  glVertex3f(430.0f, 20.0f, 0.0f);
  glVertex3f(430.0f, 30.0f, 0.0f);
  glVertex3f(465.0f, 30.0f, 0.0f);

  glVertex3f(550.0f, 50.0f, 0.0f);
  glVertex3f(550.0f, 20.0f, 0.0f);
  glVertex3f(535.0f, 20.0f, 0.0f);
  glVertex3f(535.0f, 50.0f, 0.0f);

  glVertex3f(535.0f, 20.0f, 0.0f);
  glVertex3f(570.0f, 20.0f, 0.0f);
  glVertex3f(570.0f, 30.0f, 0.0f);
  glVertex3f(535.0f, 30.0f, 0.0f);
  glEnd();

  //Player's hands
  glBegin(GL_QUADS); 
  glColor3f(0.419608f, 0.137255f, 0.556863f);
  glVertex3f(550.0f, 130.0f, 0.0f);
  glVertex3f(550.0f, 115.0f, 0.0f);
  glVertex3f(600.0f, 115.0f, 0.0f);
  glVertex3f(600.0f, 130.0f, 0.0f);

  glColor3f(0.419608f, 0.137255f, 0.556863f);
  glVertex3f(450.0f, 130.0f, 0.0f);
  glVertex3f(450.0f, 115.0f, 0.0f);
  glVertex3f(400.0f, 115.0f, 0.0f);
  glVertex3f(400.0f, 130.0f, 0.0f);
  glEnd();

  drawCircle(610, 122.5, 13);
  drawCircle(390, 122.5, 13);
  glPopMatrix();

  //Player's Weapon

  if (wFlag == true) {
	  /*glPushMatrix();
	  glTranslatef(wTransX, wTransY, 0);
	  glBegin(GL_QUADS);
	  glColor3f(0.329412f, 0.329412f, 0.329412f);
	  glVertex3f(600.0f, 135.0f, 0.0f);
	  glVertex3f(620.0f, 135.0f, 0.0f);
	  glVertex3f(620.0f, 170.0f, 0.0f);
	  glVertex3f(600.0f, 170.0f, 0.0f);
	  glEnd();

	  drawCircle(610, 135, 10);

	  glBegin(GL_TRIANGLES);
	  glVertex3f(600.0f, 170.0f, 0.0f);
	  glVertex3f(620.0f, 170.0f, 0.0f);
	  glVertex3f(610.0f, 190.0f, 0.0f);
	  glEnd();

	  glBegin(GL_QUADS);
	  glColor3f(1.0f, 1.0f, 0.0f);
	  glVertex3f(620.0f, 147.5f, 0.0f);
	  glVertex3f(620.0f, 160.0f, 0.0f);
	  glVertex3f(650.0f, 160.0f, 0.0f);
	  glVertex3f(650.0f, 147.5f, 0.0f);

	  glColor3f(1.0f, 1.0f, 0.0f);
	  glVertex3f(600.0f, 147.5f, 0.0f);
	  glVertex3f(600.0f, 160.0f, 0.0f);
	  glVertex3f(570.0f, 160.0f, 0.0f);
	  glVertex3f(570.0f, 147.5f, 0.0f);
	  glEnd();
	  glPopMatrix();
	  */
	  createWeapon();
  }
  
  
  glColor3f(1.0f, 1.0f, 0.0f);
  print(100, 475, "Score: ");
  char score[100] = { "0" };
  sprintf(score, "%d", scoreValue);
  print(175, 475, score);

  glColor3f(1.0f, 1.0f, 0.0f);
  print(100, 500, "Health: ");
  char health[100] = { "0" };
  sprintf(health, "%d", healthValue);
  print(175, 500, health);

  if (endFlagDie == true) {
	  glColor3f(1.0f, 1.0f, 0.0f);
	  print(450, 300, "You are such a loser");
  }
  if (endFlagWin == true) {
	  glColor3f(1.0f, 1.0f, 0.0f);
	  print(450, 300, "You are a Winner");
  }

  glFlush();

}

void enemyShots(){
	drawCircle(600, 550,20);
	glBegin(GL_TRIANGLES);
	glVertex3f(620.0f, 550.0f, 0.0f);
	glVertex3f(580.0f, 550.0f, 0.0f);
	glVertex3f(600.0f, 500.0f, 0.0f);
	glEnd();
	glColor3f(0.419608f, 0.137255f, 0.556863f);
	drawCircle(600, 550, 10);
}

void createWeapon() {
	wTransX = pTransX;
	glPushMatrix();
	glTranslatef(wTransX, wTransY, 0);
	glBegin(GL_QUADS);
	glColor3f(0.329412f, 0.329412f, 0.329412f);
	glVertex3f(600.0f, 135.0f, 0.0f);
	glVertex3f(620.0f, 135.0f, 0.0f);
	glVertex3f(620.0f, 170.0f, 0.0f);
	glVertex3f(600.0f, 170.0f, 0.0f);
	glEnd();

	drawCircle(610, 135, 10);

	glBegin(GL_TRIANGLES);
	glVertex3f(600.0f, 170.0f, 0.0f);
	glVertex3f(620.0f, 170.0f, 0.0f);
	glVertex3f(610.0f, 190.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(620.0f, 147.5f, 0.0f);
	glVertex3f(620.0f, 160.0f, 0.0f);
	glVertex3f(650.0f, 160.0f, 0.0f);
	glVertex3f(650.0f, 147.5f, 0.0f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(600.0f, 147.5f, 0.0f);
	glVertex3f(600.0f, 160.0f, 0.0f);
	glVertex3f(570.0f, 160.0f, 0.0f);
	glVertex3f(570.0f, 147.5f, 0.0f);
	glEnd();
	glPopMatrix();
}

void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void print(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void TimerEnemyShot(int value) {
	sFlag = true;
	sTransX = eTransX;
	sTransY = sTransY + eTransY;
	glutPostRedisplay();
	glutTimerFunc(2.5 * 1000, TimerEnemyShot, 0);
}

void TimerBack(int value) {
	background = true;
	glutPostRedisplay();
	glutTimerFunc(1 * 1000, TimerBack, 0);
}


void Timer(int value) {
	sdFlag = true;
	dShotTransX = dTransX;
	glutPostRedisplay();
	int ran = rand() % 3 + 1;
	glutTimerFunc(ran * 1000, Timer, 0);
}
void TimerPowerUp1(int value) {
	power1Flag = true;
	glutPostRedisplay();
	int ran = rand() % 10 + 1;
	glutTimerFunc(ran * 1000, TimerPowerUp1, 0);
}
void TimerPowerUp2(int value) {
	power2Flag = true;
	glutPostRedisplay();
	int ran = rand() % 10 + 1;
	glutTimerFunc(ran * 1000, TimerPowerUp2, 0);
}
void TimerDefender(int Value) {
	dFlag = true;
	glutPostRedisplay();
	glutTimerFunc(5 * 1000, TimerDefender, 0);
}
int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}