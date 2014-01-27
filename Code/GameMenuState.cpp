#include "GameMenuState.h"
#include "EntityManager.h"
#include "GalaxianAttackingState.h"
#include "GalaxianInFormationState.h"


bool GameMenuState::instanceFlag = false;

GameMenuState* GameMenuState::single = NULL;
GameMenuState* GameMenuState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GameMenuState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GameMenuState::~GameMenuState()
{
	instanceFlag = false;
}


GameMenuState::GameMenuState(void)
{	
	
}


void GameMenuState::Enter(Game* a_game)
{
	Stats::LoadHighscore();
	m_enemyExamples[0] = new Tmpl8::Surface("assets/enemies/galaxian_blue1.png");
	m_enemyExamples[1] = new Tmpl8::Surface("assets/enemies/galaxian_purple1.png");
	m_enemyExamples[2] = new Tmpl8::Surface("assets/enemies/galaxian_red1.png");
	m_enemyExamples[3] = new Tmpl8::Surface("assets/enemies/galaxian_yellow1.png");
	
	m_enemyPoints[0] = "60";
	m_enemyPoints[1] = "80";
	m_enemyPoints[2] = "100";
	m_enemyPoints[3] = "300";

	for(int i = 0; i < 4; i++)
	{
		m_enemyExamplePositions[i] = Vector2(-10 - 60 * i, SCRHEIGHT / 2 - 100 + 70*i);
		m_enemyPointsPositions[i] = Vector2(SCRWIDTH + 10 + 60 * i, SCRHEIGHT / 2 - 93 + 70*i);
	}
}

float scoreTimer = 0;
void GameMenuState::Update(Game* a_game, float a_fDeltaTime)
{
	for(int i = 0; i < 4; i++)
	{
		if(m_enemyExamplePositions[i].x < 200)
		{
			m_enemyExamplePositions[i].x += a_fDeltaTime * 200;
		}
	}
	scoreTimer += a_fDeltaTime;

	if(scoreTimer > 1.5f)
	{
		for(int i = 0; i < 4; i++)
		{
			if(m_enemyPointsPositions[i].x > 280)
			{
				m_enemyPointsPositions[i].x -= a_fDeltaTime * 200;
			}
		}
	}
}


void GameMenuState::Draw(Game* a_game, Tmpl8::Surface* a_screen)
{
	for(int i = 0; i < 4; i++)
	{
		m_enemyExamples[i]->CopyTo(a_screen, m_enemyExamplePositions[i].x, m_enemyExamplePositions[i].y);
		a_game->fontRed->Print(a_screen,m_enemyPoints[i], m_enemyPointsPositions[i].x, m_enemyPointsPositions[i].y, true);
	}
	a_game->fontGrey->Print(a_screen,"POINTS", 280 - 70, SCRHEIGHT - SCRHEIGHT / 2 - 150);
	

	std::ostringstream oss;
	oss.str("");
	if(Stats::CURRENT_SCORE > Stats::HIGH_SCORE)
	{
		oss << Stats::CURRENT_SCORE;
	}
	else
	{
		oss << Stats::HIGH_SCORE;
	}
	std::string highscore = "HIGHSCORE";
	highscore += oss.str();
	a_game->bigRedFont->Print(a_screen,const_cast<char*>(highscore.c_str()), 5, 5);
	
	a_game->fontGrey->Print(a_screen,"PRESS", SCRWIDTH / 2 - 140, SCRHEIGHT - 120);
	a_game->fontRed->Print(a_screen,"SPACE", SCRWIDTH / 2 - 50, SCRHEIGHT - 120);
	a_game->fontGrey->Print(a_screen,"TO", SCRWIDTH / 2 + 40, SCRHEIGHT - 120);
	a_game->fontGrey->Print(a_screen,"START", SCRWIDTH / 2 + 80, SCRHEIGHT - 120);
}