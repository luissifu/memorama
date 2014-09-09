/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <sstream>


struct color {
	int r;
	int g;
	int b;
};


color stopped;
color running;

const int winWidth = 900;
const int winHeight = 600;

const int glWidth = 900;
const int glHeight = 600;

int elapsed_time = 0;
bool started = false;

void init() {
	glClearColor(0.54,0.73,0.05,1.0);
	gluOrtho2D(0, glWidth, glHeight, 0);

	stopped.r = 48;
	stopped.g = 98;
	stopped.b = 48;

	running.r = 15;
	running.g = 56;
	running.b = 15;
}

std::string toString(int value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

void timer(int value) {
	if (started)
	{
		elapsed_time++;
		glutPostRedisplay();
	}
	glutTimerFunc(100,timer,0);
}

void drawText(int x, int y, std::string text, void* font, int r, int g, int b) {
	glColor3ub(r, g, b);
	glRasterPos2i(x, y);

	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

void convertTime(int t) {
	int ms = t % 10;
	int nt = t / 10;
	int s = nt % 60;
	int m = nt / 60;

	std::string timedisp = "";
	timedisp += toString(m);
	timedisp += ":";
	if (s < 10)
	{
		timedisp += "0";
		timedisp += toString(s);
	}
	else
		timedisp += toString(s);

	timedisp += ".";
	timedisp += toString(ms);


	if (started)
	{
		drawText(100, 451, timedisp, GLUT_BITMAP_TIMES_ROMAN_24, running.r, running.g, running.b);
	}
	else
	{
		drawText(100, 451, timedisp, GLUT_BITMAP_TIMES_ROMAN_24, stopped.r, stopped.g, stopped.b);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
		convertTime(elapsed_time);

    drawText(700, 450, "Turnos: ", GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
    drawText(025, 450, "Tiempo: ", GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
	drawText(250, 500, "S-Start", GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
	drawText(400, 500, "D-Detener", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
	drawText(550, 500, "R-Reiniciar", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
	drawText(800, 580, "Esc-Salir", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
    drawText(20, 560, "Luis Eduardo Sifuentes a01138688", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
    drawText(20, 580, "Jose Luis Padilla a01136406", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);




	glFlush();
}
/*
void draw3dString (void *font, char *s, float x, float y, float z)
{
unsigned int i;
glMatrixMode(GL_MODELVIEW);

glPushMatrix();
glTranslatef(x, y, z);
if (opcion == 1)
glScaled(0.005, 0.005, 0.0002);
else
glScaled(0.0009, 0.0009, 0.0009);

// if (!dibujaPortada && opcion ==1) glRotatef(45, 1, 0, 0);
for (i = 0; i < s[i] != '\0'; i++)
glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
glPopMatrix();
}
*/
void keyboard(unsigned char key, int x, int y) {
	switch(key)
	{
	    case 27:
	        exit(0);
	        break;
		case 'S':
		case 's':
			started = true;
		break;
		case 'D':
		case 'd':
			started = false;
		break;
		case 'R':
		case 'r':
			elapsed_time = 0;
			started = false;
		break;
		default:
		break;
	}

	//printf("%c", key);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("memorama");
	//glutReshapeFunc(handleResize);
	init();
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
