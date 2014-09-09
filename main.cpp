/*
 Luis Sifuentes
 Jose Padilla
 */
#include "includeGL.h"
#include "Card.h"

#include <stdlib.h>
#include <sstream>

const int cardNum = 18;
const int rows = 3;

const int winWidth = 500;
const int winHeight = 500;

const int glWidth = 500;
const int glHeight = 500;

const int cardWidth = 50;
const int cardHeight = 80;


int elapsed_time = 0;
bool started = false;

Card cards[cardNum];

void init() {
	glClearColor(0.54,0.73,0.05,1.0);
	gluOrtho2D(0, glWidth, glHeight, 0);

	for (int i = 0; i < cardNum; i++)
	{
		cards[i].width = cardWidth;
		cards[i].height = cardHeight;
		cards[i].x = (cardWidth + 10) * (i % (cardNum / rows)) + 10;
		cards[i].y = (cardHeight + 10) * (i / (cardNum / rows)) + 10;
		cards[i].setValue(1);
	}
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
}

void mouse() {

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
		convertTime(elapsed_time);

		for (int i = 0; i < cardNum; i++)
		{
			cards[i].draw();
		}

	glFlush();
}

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

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cronometro");
	init();
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
