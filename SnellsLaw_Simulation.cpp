#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(deg) (deg * 180 / PI)

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawSlab(float len);
void drawRay(float r1x, float r1y, float r2x, float  r2y);
void drawNormal(float ax, float ay);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
float RI = 1.2f;
float box_len = 4.0f;
float slab_len = 3.0f;
float f1x=-2.5f,f1y=-1.125f,f2x,f2y;
float r1x,r1y,r2x,r2y;
float b1x,b1y,b2x,b2y;
float c1x,c1y,c2x,c2y;
float len=3.0f;
float theta = 45.0f; 
float theta2,theta3; 
float tmp_len=0.5f;
float tmp_len2=0.1f;
float tmp_len3=0.1f;
//Flags to shift controls:
int rf=0,gf=0,bf=1;

int rflag=0,eflag=0;

int lf=0;//flag to ensure the recharging of spider.

int main(int argc, char **argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;
	r1x = r2x = f1x - len*sin(DEG2RAD(theta));
	r1y = r2y = f1y - len*cos(DEG2RAD(theta));

	/*cout<<f1x<<' '<<f1y<<"\n";
	cout<<r1x<<' '<<sin(DEG2RAD(theta))<<"\n";*/
	


	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);

	glutMainLoop();
	return 0;
}

// Function to draw objects on the screen
void drawScene() {
	//cout<<theta<<" deg\n";
/*	glRasterPos2i(100, 120);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, "text to render");*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -15.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(-len*20, -len*20);
	glVertex2f(len*20, -len*20);
	glVertex2f(len*20, len*20);
	glVertex2f(-len*20, len*20);
	glEnd();
	glPopMatrix();
	// Draw Box
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawBox(box_len);

	// Draw Slab
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	drawSlab(slab_len);
	glPopMatrix();
	//Draw  ray
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawRay(r1x,r1y,r2x,r2y);
	if(rflag)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		drawRay(b1x,b1y,b2x,b2y);
		drawNormal(f1x,f1y);
	}
	if(eflag)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		drawRay(c1x,c1y,c2x,c2y);
		drawNormal(f2x,f2y);
	}
	glPopMatrix();




	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {

//	if(r2y<(-(slab_len*0.75)/2))
	if(r2y<-((slab_len*0.75)/2))
	{
		r2x = r1x+ tmp_len*sin(DEG2RAD(theta));
		r2y = r1y+ tmp_len*cos(DEG2RAD(theta));
		tmp_len += 0.1;
	}
	else if(rflag==0)
	{
		rflag=1;
		b1x=b2x=r2x;
		b1y=b2y=r2y;
	}
	else if(rflag && b2y<((slab_len*0.75)/2))
	{
		theta2 = RAD2DEG(asin(sin(DEG2RAD(theta))/RI));
		b2x = b1x+ tmp_len2*sin(DEG2RAD(theta2));
		b2y = b1y+ tmp_len2*cos(DEG2RAD(theta2));
		tmp_len2 += 0.1;
	}
	else if(eflag==0)
	{
		eflag=1;
		c1x=c2x=b2x;
		f2x=b2x;
		c1y=c2y=b2y;
		f2y=b2y;
	}
	else if(eflag)
	{
//		theta3 = theta;//asin(RI*sin(DEG2RAD(theta2)));
		theta3 = RAD2DEG(asin(RI*sin(DEG2RAD(theta2))));
		c2x = c1x+ tmp_len3*sin(DEG2RAD(theta3));
		c2y = c1y+ tmp_len3*cos(DEG2RAD(theta3));
		tmp_len3 += 0.1;
	}


	glutTimerFunc(10, update, 0);
}

void drawBox(float len) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(-len*0.95 / 2, -len*0.95 / 2);
	glVertex2f(len*0.95 / 2, -len*0.95 / 2);
	glVertex2f(len*0.95 / 2, len*0.95 / 2);
	glVertex2f(-len*0.95 / 2, len*0.95 / 2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawRay(float r1x, float r1y, float r2x, float r2y)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_LINES);
	glVertex2f(r1x, r1y);
	glVertex2f(r2x, r2y);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawNormal(float ax,float ay)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_LINES);
		glVertex2f(ax, ay-1.0f);
		glVertex2f(ax, ay+1.0f);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void drawSlab(float len) {

	glBegin(GL_QUADS);
	glVertex2f(-len , -(len*0.75) / 2);
	glVertex2f(len , -(len*0.75) / 2);
	glVertex2f(len , (len*0.75) / 2);
	glVertex2f(-len , (len*0.75) / 2);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
}

void handleKeypress2(int key, int x, int y) {

	if (key == GLUT_KEY_UP || key==GLUT_KEY_DOWN)
	{
		theta -= 5.0f;
		cout<<"Incident Angle = "<<theta<<"\n";
		if(key==GLUT_KEY_DOWN)
			theta+= 10.0f;
		r1x = r2x = f1x - len*sin(DEG2RAD(theta));
		r1y = r2y = f1y - len*cos(DEG2RAD(theta));
		rflag=0;
		eflag=0;
		tmp_len=tmp_len2=tmp_len3=0.1f;
	}


/*	if(bf){
		if (key == GLUT_KEY_LEFT)
			tri_x -= 0.1;
		if (key == GLUT_KEY_RIGHT)
			tri_x += 0.1;
		if (key == GLUT_KEY_UP)
			tri_y += 0.1;
		if (key == GLUT_KEY_DOWN)
			tri_y -= 0.1;
	}*/

}

void handleMouseclick(int button, int state, int x, int y) {
/*	if(bf)
	{

		if (state == GLUT_DOWN)
		{
			if (button == GLUT_LEFT_BUTTON)
				theta += 15;
			else if (button == GLUT_RIGHT_BUTTON)
				theta -= 15;
		}
	}*/
}
