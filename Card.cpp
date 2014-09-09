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

void Card::draw() {
	glColor3ub(255,255,255);
	glBegin(GL_POLYGON);
		glVertex2f(       x,        y);
		glVertex2f( x+width,        y);
		glVertex2f( x+width, y+height);
		glVertex2f(       x, y+height);
	glEnd();

	if (!show)
	{
		glColor3ub(255,0,0);
		glBegin(GL_POLYGON);
			glVertex2f(       x+5,        y+5);
			glVertex2f( x+width-5,        y+5);
			glVertex2f( x+width-5, y+height-5);
			glVertex2f(       x+5, y+height-5);
		glEnd();
	}
}

bool Card::inside(int px, int py) {
	if (px < x || px > x + width)
		return false;
	else if (py < y || py > y + height)
		return false;

	return true;
}