/*
 Luis Sifuentes
 Jose Padilla
 */
#include "includeGL.h"
#include "Card.h"
#include <cstdlib>
#include <ctime>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

const int cardNum = 20;
const int rows = 2;

const int winWidth = 900;
const int winHeight = 600;

const int glWidth = 900;
const int glHeight = 600;

const int cardWidth = 70;
const int cardHeight = 110;

int elapsed_time = 0;
bool started = false;
int turno = 0;
int pares = 0;

Card cards[cardNum];

Card* first;
Card* second;

struct color {
	int r;
	int g;
	int b;
};

color stopped;
color running;

std::stack<int> generatePairs() {
	const int ntg = cardNum/2;

	std::stack<int> data;

	std::srand(std::time(0) + std::clock());

	bool instack[ntg];

	for (int i = 0; i < ntg; i++)
	{
		instack[i] = false;
	}

	for (int i = 0; i < ntg; i++)
	{
		int rndnum = std::rand()%ntg;
		while (instack[rndnum])
		{
			rndnum = std::rand()%ntg;
		}

		instack[rndnum] = true;

		data.push(rndnum);
	}

	//second
	for (int i = 0; i < ntg; i++)
	{
		instack[i] = false;
	}

	for (int i = 0; i < ntg; i++)
	{
		int rndnum = std::rand()%ntg;
		while (instack[rndnum])
		{
			rndnum = std::rand()%ntg;
		}

		instack[rndnum] = true;

		data.push(rndnum);
	}

	return data;
}

void gameInit() {
	std::stack<int> pairs = generatePairs();

	for (int i = 0; i < cardNum; i++)
	{
		cards[i].width = cardWidth;
		cards[i].height = cardHeight;
		cards[i].x = (cardWidth + 10) * (i % (cardNum / rows)) + 50;
		cards[i].y = (cardHeight + 10) * (i / (cardNum / rows)) + 50;
		cards[i].setValue(pairs.top());
		cards[i].setShow(false);
		pairs.pop();
	}

	started = false;
	pares = 0;
	elapsed_time = 0;
	turno = 0;
}


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

void mouse(int button, int state, int x, int y) {
	if (!started)
		started = true;
	
	if (first != NULL && second != NULL)
	{
		if (first->getValue() == second->getValue())
		{
			pares++;
		}
		else
		{
			first->setShow(false);
			second->setShow(false);
		}

		first = NULL;
		second = NULL;
		turno++;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

		for (int i = 0; i < cardNum; i++)
		{
			if (cards[i].inside(x,y) && !cards[i].shouldShow())
			{
				if (first == NULL)
				{
					first = &cards[i];
				}
				else if (second == NULL)
				{
					second = &cards[i];
				}

				cards[i].flip();
			}
		}

	}

	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
		convertTime(elapsed_time);

		for (int i = 0; i < cardNum; i++)
		{
			cards[i].draw();
			if (cards[i].shouldShow())
			{
				drawText(cards[i].x + cardWidth / 2 - 5, cards[i].y + cardHeight / 2, toString(cards[i].getValue()), GLUT_BITMAP_HELVETICA_18, 0, 0, 0);
			}
		}

		drawText(700, 450, "Turnos: ", GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
		drawText(780, 450, toString(turno), GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
		drawText(025, 450, "Tiempo: ", GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
		drawText(250, 500, "I-Iniciar", GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
		drawText(400, 500, "P-Pausar", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(550, 500, "R-Reiniciar", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(800, 580, "Esc-Salir", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(20, 560, "Luis Eduardo Sifuentes a01138688", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(20, 580, "Jose Luis Padilla a01136406", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		
		if (pares == cardNum/2)
		{
			glBegin(GL_POLYGON);
				glVertex3f(60.0f,100.0f,0.0);
				glVertex3f(60.0f,400.0f,0.0f);
				glVertex3f(840.0f,400.0f,0.0f);
				glVertex3f(840.0f,100.0f,0.0f);
			glEnd();

			drawText(250, 250, "Felicidades Ganaste en:", GLUT_BITMAP_HELVETICA_18, stopped.r, stopped.g, stopped.b);
			drawText(450, 250,toString(turno), GLUT_BITMAP_HELVETICA_18, stopped.r, stopped.g, stopped.b);
			drawText(500, 250, "turnos", GLUT_BITMAP_HELVETICA_18, stopped.r, stopped.g, stopped.b);

			started = false;
		}
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case 'I':
		case 'i':
			started = true;
		break;
		case 'P':
		case 'p':
			started = false;
		break;
		case 'R':
		case 'r':
			gameInit();
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
	glutCreateWindow("memorama");
	init();
	gameInit();
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
