// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009
#include "GamePlayingState.h"
#include "GameMenuState.h"
#include "Stats.h"
#include "TileManager.h"

using namespace Tmpl8;

float fFrameTimer = 0;
const float FRAMES_PER_SECOND = 1.f/60.f;

Game::~Game()
{	
	delete PlayerImage;
	delete PlayerLiveImage;
	delete FlagOne;
	delete FlagTen;
	delete bigRedFont;
	delete fontRed;
	delete fontGrey;
	delete player;
	delete m_galaxianFormation;
	delete m_background;
}

void Game::Init()
{
	srand(time(NULL));
	m_background = new Background();
	PlayerImage = new Surface("assets/player.png");
	PlayerLiveImage = new Surface("assets/player_live.png");
	FlagOne = new Surface("assets/flag_1.png");
	FlagTen = new Surface("assets/flag_10.png");
	bigRedFont = new Font("assets/fonts/main_font_2x.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-"); 
	fontRed = new Font("assets/fonts/font_red_2x.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-"); 
	fontGrey = new Font("assets/fonts/font_grey_2x.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-"); 

	SetState(GameMenuState::getInstance());
	
	Tiles->LoadBaseSprite("assets/backgrounds/light_world-1.png");
	Tiles->ProcessTileMap();
}

void Game::Tick( float a_fDeltaTime )
{
	if(a_fDeltaTime > FRAMES_PER_SECOND)
	{
		a_fDeltaTime = FRAMES_PER_SECOND;
	}

	Update(a_fDeltaTime);
	Draw();
}

void Game::Update(float a_fDeltaTime)
{
	m_background->Update(a_fDeltaTime);

	m_pCurrentState->Update(this, a_fDeltaTime);
	
}

void Game::Draw()
{
	m_Screen->Clear(0);
	
//	Tiles->Draw(m_Screen);
	m_background->Draw(m_Screen);

	m_pCurrentState->Draw(this, m_Screen);	

}


void Game::KeyDown( unsigned int code )
{
	if(m_pCurrentState == GamePlayingState::getInstance())
	{
		player->KeyDown(code);
		if(Stats::LIVES_LEFT < 1)
		{
			if(code == 57)
			{
				Stats::GAME_OVER = true;
			}
		}
	}
	else
	{
		if(code == 57)
		{
			SetState(GamePlayingState::getInstance());
		}
	}
}

void Game::KeyUp( unsigned int code )
{
	if(m_pCurrentState == GamePlayingState::getInstance())
	{
		player->KeyUp(code);
	}
	else
	{

	}
}


void Game::SetState(State<Game>* a_state)
{
	m_pCurrentState = a_state;
	a_state->Enter(this);
}


State<Game>* Game::GetState()
{
	return m_pCurrentState;
}


void Game::ChangeState(State<Game>* a_newState)
{
	m_pCurrentState->Exit(this);

	m_pCurrentState = a_newState;
	m_pCurrentState->Enter(this);
}