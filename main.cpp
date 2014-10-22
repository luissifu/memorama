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

const int cardNum = 27;
const int rows = 3;

int winWidth = 900;
int winHeight = 600;

const int glWidth = 900;
const int glHeight = 600;

const float cardWidth = 1.3;
const float cardHeight = 2.2;

int elapsed_time = 0;
bool started = false;
bool showHelp = true;
int turno = 0;
int pares = 0;

float angle = 0;

Card cards[cardNum];

Card* first;
Card* second;
Card* third;

struct color {
	int r;
	int g;
	int b;
};

color stopped;
color running;

std::stack<int> generateTriples() {
	const int ntg = cardNum/3;

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

	//third
	for (int i = 0; i < ntg; i++)
	{
		instack[i] = false;
	}

	for (int i = 0; i < ntg; i++)
	{
		int rndnum = std::rand() % ntg;
		while (instack[rndnum])
		{
			rndnum = std::rand() % ntg;
		}

		instack[rndnum] = true;

		data.push(rndnum);
	}

	return data;
}

void gameInit() {
	std::stack<int> triples = generateTriples();

	for (int i = 0; i < cardNum; i++)
	{
		cards[i].width = cardWidth;
		cards[i].height = cardHeight;
		cards[i].x = (cardWidth) * (i % (cardNum / rows)) - 5;
		cards[i].y = (cardHeight + 0.001) * (i / (cardNum / rows));
		cards[i].setValue(triples.top());
		cards[i].setShow(false);
		triples.pop();
	}

	started = false;
	pares = 0;
	elapsed_time = 0;
	turno = 0;

	first = second = third = NULL;
}


void init() {
	glClearColor(0.011, 0.75, 0.23, 1.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8, 8, -6.4, 6.4, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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

	angle += 5;

	if (angle >= 180.0)
		angle = -180.0;
}

void drawText(float x, float y, std::string text, void* font, int r, int g, int b) {
	glColor3ub(r, g, b);
	glRasterPos3f(x, y, 0);

	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

std::string convertTime(int t) {
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

    return timedisp;
}

void mouse(int button, int state, int mx, int my) {
	printf("%d:%d\n", mx, my);
	
	float x = (mx * 16.0) / winWidth - 8.0;
	float y = (winHeight - my) * 12.8 / winHeight - 6.4;

	printf("%f:%f\n", x, y);


	if (!started)
		started = true;

	if (first != NULL && second != NULL && third != NULL)
	{
		if (first->getValue() == second->getValue() && second->getValue() == third->getValue())
		{
			pares++;
		}
		else
		{
			first->setShow(false);
			second->setShow(false);
			third->setShow(false);
		}

		first->setSelected(false);
		second->setSelected(false);
		third->setSelected(false);

		first = NULL;
		second = NULL;
		third = NULL;
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
				else if (third == NULL)
				{
					third = &cards[i];
				}

				cards[i].flip();
				cards[i].setSelected(true);
			}
		}

		if (pares == (cardNum/3)-1 && first != NULL && second != NULL && third != NULL)
		{
			pares++;

			first->setSelected(false);
			second->setSelected(false);
			third->setSelected(false);

			first = NULL;
			second = NULL;
			third = NULL;
			turno++;
		}

	}

	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

        if (started)
        {
            drawText(-6, -4, convertTime(elapsed_time), GLUT_BITMAP_TIMES_ROMAN_24, running.r, running.g, running.b);
        }
        else
        {
			drawText(-6, -4, convertTime(elapsed_time), GLUT_BITMAP_TIMES_ROMAN_24, stopped.r, stopped.g, stopped.b);
        }

		for (int i = 0; i < cardNum; i++)
		{
			cards[i].draw(angle);
			if (cards[i].shouldShow())
			{
				drawText(cards[i].x + 0.05, cards[i].y + 0.05, toString(cards[i].getValue()), GLUT_BITMAP_HELVETICA_18, 0, 0, 0);
			}

			if (showHelp)
			{
				drawText(cards[i].x, cards[i].y, toString(cards[i].getValue()), GLUT_BITMAP_HELVETICA_18, 0, 0, 255);
			}
		}

		drawText(-6, -5, "Turnos: ", GLUT_BITMAP_HELVETICA_18,running.r, running.g, running.b);
		drawText(-6, -5, toString(turno), GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(-6, -5, "Tiempo: ", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(-6, -5, "I-Iniciar", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(-6, -5, "P-Pausar", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(-6, -5, "R-Reiniciar", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(-6, -5, "A-Mostrar/Ocultar Ayuda", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(-6, -5, "Esc-Salir", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(20, 560, "Luis Eduardo Sifuentes a01138688", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);
		drawText(20, 580, "Jose Luis Padilla a01136406", GLUT_BITMAP_HELVETICA_18, running.r, running.g, running.b);

		if (pares == cardNum/3)
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
			drawText(250, 300, "Tu tiempo fue:", GLUT_BITMAP_HELVETICA_18, stopped.r, stopped.g, stopped.b);
			drawText(500, 300, convertTime(elapsed_time), GLUT_BITMAP_HELVETICA_18, stopped.r, stopped.g, stopped.b);

			started = false;
		}

		glPopMatrix();

	glFlush();
}

typedef enum {autor1,autor2,menuiniciar,menureiniciar,menupausar,menuayuda,menuexit}
opcionesMenu;

void onMenu(int opcion) {
    switch(opcion)
    {
		case autor1:
        break;
		case autor2:
        break;
		case menupausar:
			started=false;
        break;
		case menuiniciar:
			started=true;
        break;
		case menureiniciar:
			gameInit();
        break;
        case menuayuda:
			showHelp=!showHelp;
        break;
		case menuexit:
			exit(0);
        break;
    }
    glutPostRedisplay();
}

void creacionMenu(void) {
    int menuAutores, menuPrincipal;

    menuAutores = glutCreateMenu(onMenu);
    glutAddMenuEntry("Luis Eduardo Sifuentes A01138688", autor1);
    glutAddMenuEntry("Jose Luis Padilla A01136406", autor2);

    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Autores ", menuAutores);
    glutAddMenuEntry("Iniciar", menuiniciar);
    glutAddMenuEntry("Pausar", menupausar);
    glutAddMenuEntry("Reiniciar", menureiniciar);
    glutAddMenuEntry("Ayuda",menuayuda);
    glutAddMenuEntry("Salir", menuexit);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
		case 'a':
		case 'A':
			showHelp=!showHelp;
		break;
		 case 'O':
    case 'o':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-8, 8, -6.4, 6.4, 0, 1);
        break;
		  case 'F':
    case 'f':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-8, 8, -6.4, 6.4, 1, 10);
        gluLookAt(0, 0, 1.2, 0, 0, 0, 0, 1,0);
        break;

		default:
		break;
	}

	glutPostRedisplay();
}

void reshape(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
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
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	creacionMenu( );
	glutMainLoop();
	return 0;
}
