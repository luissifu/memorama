#include "Card.h"

Card::Card() {
	value = 0;
	show = false;
}

Card::Card(int value) {
	this->value = value;
	show = false;
}

void Card::flip() {
	show = !show;
}

bool Card::shouldShow() {
	return show;
}

void Card::setShow(bool show) {
	this->show = show;
}

int Card::getValue() {
	return value;
}

void Card::setValue(int value) {
	this->value = value;
}

void Card::draw(int x, int y) {
	glColor3ub(255,255,255);
	glBegin(GL_POLYGON);
		glVertex2f(    x,   y);
		glVertex2f( x+50,   y);
		glVertex2f( x+50, y+50);
		glVertex2f(    x, y+50);
	glEnd();

	if (show)
	{
		glColor3ub(0,255,0);
		glBegin(GL_POLYGON);
			glVertex2f(  x+5,  y+5);
			glVertex2f( x+45,  y+5);
			glVertex2f( x+45, y+45);
			glVertex2f(  x+5, y+45);
		glEnd();
	}
}