//
// Created by trida on 11/19/25.
//

#ifndef HERION_HERO_COLORS_HPP
#define HERION_HERO_COLORS_HPP


class COLORS {
private:

public:
	typedef struct Color {
		int r;
		int g;
		int b;
		int a;
	}Color;

	static const Color BLACK;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color MAGENTA;
	static const Color CYAN;
	static const Color ORANGE;
	static const Color PURPLE;
	static const Color LIGHT_GRAY;
	static const Color DARK_GRAY;

};


#endif //HERION_HERO_COLORS_HPP