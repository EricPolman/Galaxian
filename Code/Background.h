#pragma once
#include "includes.h"

class Background
{
public:
	Background(void);
	~Background(void);

	static const int AMOUNT_OF_STARS = 300;

	Vector2 m_position;
	Vector2 m_starPositions[AMOUNT_OF_STARS];
	bool m_starIsActive[AMOUNT_OF_STARS];
	int m_starColor[AMOUNT_OF_STARS];
	int m_colors[5];

	void Update(float a_fDeltaTime);
	void Draw(Tmpl8::Surface* a_screen);
};

