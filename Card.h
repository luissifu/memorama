#ifndef _CARD_H_
#define _CARD_H_

#include "includeGL.h"

#include <string>

class Card {
	public:
		Card();
		Card(int value);
		//
		int x;
		int y;
		int width;
		int height;
		//
		void flip();
		bool shouldShow();
		void setShow(bool show);
		int getValue();
		void setValue(int value);
		void draw();
		bool inside();
	private:
		int value;
		bool show;
};

#endif