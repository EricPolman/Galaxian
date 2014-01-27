#include "GalaxianInFormationState.h"
#include "GalaxianDyingState.h"
#include "GalaxianArcingState.h"

bool GalaxianInFormationState::instanceFlag = false;
GalaxianInFormationState* GalaxianInFormationState::single = NULL;
GalaxianInFormationState* GalaxianInFormationState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GalaxianInFormationState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GalaxianInFormationState::~GalaxianInFormationState()
{
	instanceFlag = false;
	delete[] m_formationSpriteArray;
}


GalaxianInFormationState::GalaxianInFormationState(void)
{	
	m_formationSpriteArray[0] = new Tmpl8::Surface("assets/enemies/galaxian_blue1.png");
	m_formationSpriteArray[1] = new Tmpl8::Surface("assets/enemies/galaxian_blue2.png");
	m_formationSpriteArray[2] = new Tmpl8::Surface("assets/enemies/galaxian_blue3.png");
	m_formationSpriteArray[3] = new Tmpl8::Surface("assets/enemies/galaxian_blue4.png");
	m_formationSpriteArray[4] = new Tmpl8::Surface("assets/enemies/galaxian_blue5.png");
	m_formationSpriteArray[5] = new Tmpl8::Surface("assets/enemies/galaxian_blue6.png");
	m_formationSpriteArray[6] = new Tmpl8::Surface("assets/enemies/galaxian_purple1.png");
	m_formationSpriteArray[7] = new Tmpl8::Surface("assets/enemies/galaxian_purple2.png");
	m_formationSpriteArray[8] = new Tmpl8::Surface("assets/enemies/galaxian_purple3.png");
	m_formationSpriteArray[9] = new Tmpl8::Surface("assets/enemies/galaxian_purple4.png");
	m_formationSpriteArray[10] = new Tmpl8::Surface("assets/enemies/galaxian_purple5.png");
	m_formationSpriteArray[11] = new Tmpl8::Surface("assets/enemies/galaxian_purple6.png");
	m_formationSpriteArray[12] = new Tmpl8::Surface("assets/enemies/galaxian_red1.png");
	m_formationSpriteArray[13] = new Tmpl8::Surface("assets/enemies/galaxian_red2.png");
	m_formationSpriteArray[14] = new Tmpl8::Surface("assets/enemies/galaxian_red3.png");
	m_formationSpriteArray[15] = new Tmpl8::Surface("assets/enemies/galaxian_red4.png");
	m_formationSpriteArray[16] = new Tmpl8::Surface("assets/enemies/galaxian_red5.png");
	m_formationSpriteArray[17] = new Tmpl8::Surface("assets/enemies/galaxian_red6.png");
}


void GalaxianInFormationState::Enter(Galaxian* a_galaxian)
{
	a_galaxian->SetDirection(Vector2(0,1));
	m_bAttackInProgress = false;
}


void GalaxianInFormationState::Update(Galaxian* a_galaxian, float a_fDeltaTime)
{
	m_deltaTimeMap[a_galaxian] += a_fDeltaTime;
	if(a_galaxian->GetRank() != Rank::GENERAL)
	{
		if(m_deltaTimeMap[a_galaxian] > 0.3f)
		{
			if(m_spriteCounterMap[a_galaxian] == 6)
			{
				m_spriteCounterMap[a_galaxian] = 0;
			}
			m_deltaTimeMap[a_galaxian] = 0;
			a_galaxian->SetSprite(m_formationSpriteArray[(a_galaxian->GetRank()-1) * 6 + m_spriteCounterMap[a_galaxian]]);
			m_spriteCounterMap[a_galaxian]++;
		}
	}
	else
	{
		if(m_deltaTimeMap[a_galaxian] > max((4 + rand() % 8) - Stats::ROUND / 3,3))
		{
			m_deltaTimeMap[a_galaxian] = 0;
			if(!m_bAttackInProgress)
			{
				a_galaxian->ChangeState(GalaxianArcingState::getInstance());
				m_bAttackInProgress = true;
			}
		}
	}

	if(m_formation->GetIsGoingRight())
	{
		a_galaxian->Move(m_formation->GetMovementSpeed() * a_fDeltaTime, 0);
	}
	else
	{
		a_galaxian->Move(-m_formation->GetMovementSpeed() * a_fDeltaTime, 0);
	}

	if(a_galaxian->GetPosition().x > SCRWIDTH - a_galaxian->GetSprite()->GetWidth() || a_galaxian->GetPosition().x < 0)
	{
		m_formation->BoundaryHit(a_galaxian->GetPosition().x < 0);
	}
}


void GalaxianInFormationState::Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen)
{
	a_galaxian->GetSprite()->CopyTo(a_screen, a_galaxian->GetPosition().x, a_galaxian->GetPosition().y);
}


void GalaxianInFormationState::Exit(Galaxian* a_galaxian)
{
	
}


void GalaxianInFormationState::Hit(Galaxian* a_galaxian, Entity* a_pOther)
{
	if(a_pOther->m_type != EntityType::ENEMY)
	{
		if(a_pOther->m_type == EntityType::BULLET)
		{
			if(((Bullet*)(a_pOther))->GetOwner()->m_type != a_galaxian->m_type && ((Bullet*)(a_pOther))->GetCanKill())
			{
				((Bullet*)(a_pOther))->SetCanKill(false);
				a_galaxian->ChangeState(GalaxianDyingState::getInstance());
			}
		}
	}
}


void GalaxianInFormationState::SetPlayer(Player* a_pPlayer)
{
	m_pPlayer = a_pPlayer;
}


void GalaxianInFormationState::SetAttackInProgress(bool a_newValue)
{
	m_bAttackInProgress = a_newValue;
}