#ifndef _CARD_H_
#define _CARD_H_

#include "includeGL.h"

#include <string>

const GLubyte tres[] = {
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x01, 0x37, 0xFF, 0xFF,
	0x01, 0x37, 0xFF, 0xFF,
	0x01, 0x37, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x01, 0x37, 0xFF, 0xFF,
	0x01, 0x37, 0xFF, 0xFF,
	0x01, 0x37, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x01, 0x37, 0xFF, 0xFF,
	0x01, 0x37, 0xFF, 0xFF,
	0x01, 0x37, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

const GLubyte seis[] = {
	0xF0, 0x00, 0x00, 0x0F,
	0xC0, 0x00, 0x00, 0x03,
	0x80, 0x01, 0x80, 0x01,
	0x80, 0x07, 0xE0, 0x01,
	0x00, 0x1E, 0x78, 0x00,
	0x00, 0x18, 0x18, 0x00,
	0x00, 0x30, 0x0C, 0x00,
	0x00, 0x30, 0x0C, 0x00,
	0x00, 0x60, 0x06, 0x00,
	0x00, 0x60, 0x06, 0x00,
	0x00, 0x30, 0x0F, 0x00,
	0x00, 0x30, 0x0F, 0x00,
	0x00, 0x18, 0x1B, 0x00,
	0x00, 0x1E, 0x7B, 0x00,
	0x00, 0x07, 0xE3, 0x00,
	0x00, 0x01, 0x83, 0x00,
	0x00, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x03, 0x00,
	0x00, 0x60, 0x07, 0x00,
	0x00, 0x60, 0x06, 0x00,
	0x00, 0x30, 0x0C, 0x00,
	0x00, 0x30, 0x0C, 0x00,
	0x00, 0x18, 0x18, 0x00,
	0x00, 0x1E, 0x78, 0x00,
	0x00, 0x07, 0xE0, 0x00,
	0x80, 0x01, 0x80, 0x01,
	0x80, 0x00, 0x00, 0x01,
	0xC0, 0x00, 0x00, 0x03,
	0xF0, 0x00, 0x00, 0x0F
};

class Card {
	public:
		Card();
		Card(int value);
		//
		float x;
		float y;
		float width;
		float height;
		//
		void flip();
		bool shouldShow();
		void setShow(bool show);
		bool isSelected();
		void setSelected(bool select);
		int getValue();
		void setValue(int value);
		void draw(float ang);
		bool inside(float px, float py);
	private:
		int value;
		bool show;
		bool selected;
};

#endif
