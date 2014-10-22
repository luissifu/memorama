#ifndef _CARD_H_
#define _CARD_H_

#include "includeGL.h"

#include <string>

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
		void draw();
		bool inside(int px, int py);
	private:
		int value;
		bool show;
		bool selected;
};

#endif