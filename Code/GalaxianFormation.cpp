#include "GalaxianFormation.h"
#include "GalaxianInFormationState.h"
#include "GalaxianArcingState.h"
#include "GalaxianReturnToFormationState.h"
#include "GalaxianAttackingState.h"

Tmpl8::Surface* GalaxianBlue = new Tmpl8::Surface("assets/enemies/galaxian_blue1.png");
Tmpl8::Surface* GalaxianPurple = new Tmpl8::Surface("assets/enemies/galaxian_purple1.png");
Tmpl8::Surface* GalaxianRed = new Tmpl8::Surface("assets/enemies/galaxian_red1.png");
Tmpl8::Surface* GalaxianYellow = new Tmpl8::Surface("assets/enemies/galaxian_yellow1.png");

int GalaxianFormation::SPRITE_WIDTH;
int GalaxianFormation::SPRITE_HEIGHT;

GalaxianFormation::GalaxianFormation(void)
{

	GalaxianInFormationState::getInstance()->m_formation = this;
	GalaxianArcingState::getInstance()->m_formation = this;
	GalaxianReturnToFormationState::getInstance()->m_formation = this;
	GalaxianAttackingState::getInstance()->m_formation = this;

	InitializeFormation();
}


void GalaxianFormation::InitializeFormation()
{
	Stats::ROUND++;
	m_bIsGoingRight = true;
	m_bBoundaryHit = false;
	m_fMovementSpeed = 35;

	std::ifstream formationTxt("assets/formation.txt");
	std::string formationTxtRows[FORMATION_ROWS];
	
	SPRITE_WIDTH = GalaxianBlue->GetWidth();
	SPRITE_HEIGHT = GalaxianBlue->GetHeight();
	int offset = (SCRWIDTH - (FORMATION_COLUMNS * SPRITE_WIDTH * 1.5)) * 0.5;
	
	if (formationTxt.is_open())
	{
		int row = 0;
		while ( std::getline(formationTxt,formationTxtRows[row]) || row < FORMATION_ROWS )
		{
			row++;
		}
		formationTxt.close();
	}

	for(int rows = 0; rows < FORMATION_ROWS; rows++)
	{
		for(int cols = 0; cols < FORMATION_COLUMNS; cols++)
		{
			char numberAsChar = formationTxtRows[rows][cols];
			const char* constPtrToCharForCasting = &numberAsChar;
			int x = offset + cols * (SPRITE_WIDTH + 12);
			int y = 60 + rows * (SPRITE_HEIGHT + 6);
			switch (atoi(constPtrToCharForCasting))
			{
			case 1:
				m_galaxians[rows][cols] = new Galaxian(GalaxianBlue, x, y);
				break;
			case 2:
				m_galaxians[rows][cols] = new Galaxian(GalaxianPurple, x, y);
				break;
			case 3:
				m_galaxians[rows][cols] = new Galaxian(GalaxianRed, x, y);
				break;
			case 4:
				m_galaxians[rows][cols] = new Galaxian(GalaxianYellow, x, y);
				break;
			case 0:
			default:
				m_galaxians[rows][cols] = 0;
				break;
			}
			if(m_galaxians[rows][cols])
			{
				m_galaxians[rows][cols]->SetPositionInFormation(cols, rows);
				m_galaxians[rows][cols]->SetRank((Rank)atoi(constPtrToCharForCasting));
				
				m_galaxians[rows][cols]->SetState(GalaxianInFormationState::getInstance());
			}
		}
	}
}


GalaxianFormation::~GalaxianFormation(void)
{
	/*for(int rows = 0; rows < FORMATION_ROWS; rows++)
	{
		for(int cols = 0; cols < FORMATION_COLUMNS; cols++)
		{
			if(m_galaxians[rows][cols] != 0)
			{
				/delete m_galaxians[rows][cols];
			}
		}
	}*/
	//delete[] m_galaxians;
}


float respawnTimer = 0;
void GalaxianFormation::Update(float a_fDeltaTime)
{
	ProcessChanges();
	if(Stats::ENEMIES_LEFT == 0)
	{
		respawnTimer += a_fDeltaTime;
		if(respawnTimer > 2.5f)
		{
			respawnTimer = 0;
			InitializeFormation();
		}
	}
}


void GalaxianFormation::Draw(Tmpl8::Surface* a_screen)
{
	
}


void GalaxianFormation::BoundaryHit(bool a_bNewDirection)
{
	m_bBoundaryHit = true;
	m_bNewDirection = a_bNewDirection;
}


void GalaxianFormation::ProcessChanges()
{
	if(m_bBoundaryHit)
	{
		m_bIsGoingRight = m_bNewDirection;
		m_bBoundaryHit = false;
	}
}


Galaxian* GalaxianFormation::GetFirstGalaxianInFormation()
{
	for(int rows = 0; rows < FORMATION_ROWS; rows++)
	{
		for(int cols = 0; cols < FORMATION_COLUMNS; cols++)
		{
			if(m_galaxians[rows][cols] && m_galaxians[rows][cols]->GetState() == GalaxianInFormationState::getInstance())
			{
				return m_galaxians[rows][cols];
			}
		}
	}
	return 0;
}


Galaxian* GalaxianFormation::GetGalaxian(int a_iRow, int a_iCol)
{
	if(m_galaxians[a_iCol][a_iRow] && m_galaxians[a_iCol][a_iRow]->GetState() == GalaxianInFormationState::getInstance())
	{
		return m_galaxians[a_iCol][a_iRow];
	}
	else
	{
		return 0;
	}
}