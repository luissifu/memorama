#include "Card.h"

Card::Card() {
	value = 0;
	show = selected = false;
}

Card::Card(int value) {
	this->value = value;
	show = selected = false;
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
	if (selected)
	{
		glColor3ub(255, 255, 200);
	}
	else
	{
		glColor3ub(255, 255, 255);
	}
	
	glPushMatrix();
	glColor3f(0,0,1);
		glTranslatef(x, y, 0.0);
		glScalef(0.5,1.0,0.02);
		if (selected)
		{
			glColor3ub(255, 255, 200);
		}
		else if (!show)
		{
			glColor3ub(255, 0, 0);
		}
		else
		{
			glColor3ub(255, 255, 255);
		}
		glutSolidCube(2);
		glColor3f(0,0,0);
		glutWireCube(2);
	glPopMatrix();

	/*
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
	*/
}

bool Card::inside(int px, int py) {
	if (px < x || px > x + width)
		return false;
	else if (py < y || py > y + height)
		return false;

	return true;
}


bool Card::isSelected() {
	return selected;
}

void Card::setSelected(bool select) {
	selected = select;
}
