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
		glBindTexture(GL_TEXTURE_2D, selectedId);
	}
	else
	{    
		glBindTexture(GL_TEXTURE_2D, showId);
	}

	glPushMatrix();
		glTranslatef(x, y, 0.0);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, 1.5f, 0);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0f, 1.5f, 0);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.0f, 0.0f, 0);
		glEnd();
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
