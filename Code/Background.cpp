#include "Background.h"


Background::Background(void)
{
	m_colors[0] = 16777215;				// White
	m_colors[1] = 16711935;				// Purple
	m_colors[2] = 255;					// Blue
	m_colors[3] = 65280;				// Green
	m_colors[4] = 16711680;				// Red

	for(int i = 0; i < AMOUNT_OF_STARS; i++)
	{
		m_starPositions[i].x = rand() % SCRWIDTH;
		m_starPositions[i].y = rand() % SCRHEIGHT * 2;
		m_starIsActive[i] = rand() % 50 > 25;
		m_starColor[i] = m_colors[rand() % 5];
	}
	m_position.y = -SCRHEIGHT + 1;
	
}


Background::~Background(void)
{
}

float frameCounter = 0;
void Background::Update(float a_fDeltaTime)
{
	if(m_position.y > 0)
	{
		m_position.y = -SCRHEIGHT + 1;
	}
	m_position.y += a_fDeltaTime * 60;

	frameCounter+= a_fDeltaTime;
	if(frameCounter > 0.7f)
	{
		frameCounter = 0;
		for(int i = 0; i < AMOUNT_OF_STARS; i++)
		{
			m_starIsActive[i] = !m_starIsActive[i];
		}
	}
}

void Background::Draw(Tmpl8::Surface* a_screen)
{
	for(int i = 0; i < AMOUNT_OF_STARS; i++)
	{
		if(m_starIsActive[i])
		{
			a_screen->Plot(m_starPositions[i].x, m_starPositions[i].y + m_position.y, m_starColor[i]);
			a_screen->Plot(m_starPositions[i].x, m_starPositions[i].y+1 + m_position.y, m_starColor[i]);
			a_screen->Plot(m_starPositions[i].x+1, m_starPositions[i].y + m_position.y, m_starColor[i]);
			a_screen->Plot(m_starPositions[i].x+1, m_starPositions[i].y+1 + m_position.y, m_starColor[i]);
		}
	}
}