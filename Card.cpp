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

void Card::draw(float ang) {
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
			glRotatef(ang, 0.0, 1.0, 0.0);
			glColor3ub(255, 255, 200);
		}
		else if (!show)
		{
			glColor3ub(255, 0, 0);
		}
		else
		{
			glRotatef(ang, 0.0, 1.0, 0.0);
			glColor3ub(255, 255, 255);
		}
		glutSolidCube(2);
		glColor3f(0,0,0);
		glutWireCube(2);
	glPopMatrix();

}

bool Card::inside(float px, float py) {
	if (px < x || px > x + 1.1)
		return false;
	else if (py < y || py > y + 1.95)
		return false;

	return true;
}


bool Card::isSelected() {
	return selected;
}

void Card::setSelected(bool select) {
	selected = select;
}
