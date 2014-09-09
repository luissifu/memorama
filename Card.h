#ifndef _CARD_H_
#define _CARD_H_

#include "includeGL.h"

class Card {
	public:
		Card();
		Card(int value);
		//
		void flip();
		bool shouldShow();
		void setShow(bool show);
		int getValue();
		void setValue(int value);
		void draw(int x, int y);
	private:
		int value;
		bool show;
};

#endif