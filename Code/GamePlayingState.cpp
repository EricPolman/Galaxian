#include "GamePlayingState.h"
#include "EntityManager.h"
#include "GalaxianAttackingState.h"
#include "GalaxianInFormationState.h"


bool GamePlayingState::instanceFlag = false;
bool highscoreWritten;

GamePlayingState* GamePlayingState::single = NULL;
GamePlayingState* GamePlayingState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GamePlayingState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GamePlayingState::~GamePlayingState()
{
	instanceFlag = false;
}


GamePlayingState::GamePlayingState(void)
{	
	
}


void GamePlayingState::Enter(Game* a_game)
{
	Stats::LIVES_LEFT = 3;
	Stats::CURRENT_SCORE = 0;
	Stats::ENEMIES_LEFT = 0;
	Stats::ROUND = 0;
	Stats::GAME_OVER = false;
	
	a_game->m_galaxianFormation = new GalaxianFormation();
	
	a_game->player = new Player(a_game->PlayerImage, a_game->m_Screen->GetWidth() / 2, a_game->m_Screen->GetHeight() - 100);
	GalaxianAttackingState::getInstance()->SetPlayer(a_game->player);
	Entities->m_pPlayer = a_game->player;
	GalaxianAttackingState::getInstance()->SetPlayer(a_game->player);
	GalaxianInFormationState::getInstance()->SetPlayer(a_game->player);
	highscoreWritten = false;
	
	Sounds->Add("shoot");
	Sounds->Add("explode");
}


void GamePlayingState::Update(Game* a_game, float a_fDeltaTime)
{
	if(Stats::LIVES_LEFT < 1)
	{
		if(!highscoreWritten)
		{
			if(Stats::CURRENT_SCORE > Stats::HIGH_SCORE)
			{
				Stats::WriteHighscore();
			}
		}
	}
	else
	{
		Entities->Update(a_fDeltaTime);
		a_game->m_galaxianFormation->Update(a_fDeltaTime);
	}
}


void GamePlayingState::Draw(Game* a_game, Tmpl8::Surface* a_screen)
{
	std::ostringstream oss;
	if(Stats::LIVES_LEFT < 1)
	{
		a_game->fontRed->Print(a_screen, "GAME", SCRWIDTH / 2 - 60, SCRHEIGHT / 2);
		a_game->fontGrey->Print(a_screen, "OVER", SCRWIDTH / 2, SCRHEIGHT / 2);
		if(!highscoreWritten)
		{
			highscoreWritten = true;
		}
		a_game->fontGrey->Print(a_screen,"PRESS", SCRWIDTH / 2 - 140, SCRHEIGHT - 120);
		a_game->fontRed->Print(a_screen,"SPACE", SCRWIDTH / 2 - 50, SCRHEIGHT - 120);
		a_game->fontGrey->Print(a_screen,"TO", SCRWIDTH / 2 + 40, SCRHEIGHT - 120);
		a_game->fontGrey->Print(a_screen,"STOP", SCRWIDTH / 2 + 80, SCRHEIGHT - 120);
	}
	else
	{
		Entities->Draw(a_screen);
		a_game->m_galaxianFormation->Draw(a_screen);
	}

	oss.str("");
	oss << Stats::CURRENT_SCORE;
	std::string curScore = "SCORE";
	curScore += oss.str();
	a_game->bigRedFont->Print(a_screen,const_cast<char*>(curScore.c_str()), 5, 25);
	
	for(int i = 0; i < Stats::LIVES_LEFT; i++)
	{
		a_game->PlayerLiveImage->CopyTo(a_screen, 5 + i*34, SCRHEIGHT - 35);
	}
	
	oss.str("");
	oss << Stats::ENEMIES_LEFT;
	std::string enemiesLeft = "ENEMIES";
	enemiesLeft += oss.str();
	a_game->bigRedFont->Print(a_screen,const_cast<char*>(enemiesLeft.c_str()),  SCRWIDTH - 140, 5);
	
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
	
	int tens = Stats::ROUND / 10;
	int remainder = Stats::ROUND - tens * 10 - 1;

	for(int i = 0; i < remainder; i++)
	{
		a_game->FlagOne->CopyTo(a_screen, SCRWIDTH - 25 - 25*i, SCRHEIGHT - 30);
	}
	for(int i = 0; i < tens; i++)
	{
		a_game->FlagTen->CopyTo(a_screen, SCRWIDTH - remainder*25 - (i+1)*35, SCRHEIGHT - 30);
	}
}


void GamePlayingState::Exit(Game* a_game)
{
	ClearEntities();
	std::cout << "lol";
	delete a_game->player;
}


void GamePlayingState::ClearEntities()
{
	Entities->ClearAll();
}