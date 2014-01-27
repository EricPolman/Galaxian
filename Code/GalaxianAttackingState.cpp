#include "GalaxianAttackingState.h"
#include "GalaxianDyingState.h"
#include "GalaxianReturnToFormationState.h"
#include "Bullet.h"

bool GalaxianAttackingState::instanceFlag = false;
GalaxianAttackingState* GalaxianAttackingState::single = NULL;
GalaxianAttackingState* GalaxianAttackingState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GalaxianAttackingState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GalaxianAttackingState::~GalaxianAttackingState()
{
	instanceFlag = false;
	delete[] m_formationSpriteArray;
}


GalaxianAttackingState::GalaxianAttackingState(void)
{	
	m_pPlayer = 0;
}


void GalaxianAttackingState::Enter(Galaxian* a_galaxian)
{
	m_targetPosition = m_pPlayer->GetPosition();
	m_targetPosition.y += a_galaxian->GetPositionInFormation().y * 30;
	m_directionFromStartToTarget = m_targetPosition - a_galaxian->GetPosition();
	m_directionFromStartToTarget.Normalize();
	
}

float randomNumber = 0;
void GalaxianAttackingState::Update(Galaxian* a_galaxian, float a_fDeltaTime)
{
	m_deltaTimeMap[a_galaxian] += a_fDeltaTime;

	if(m_deltaTimeMap[a_galaxian] > 0.3f + randomNumber && abs((a_galaxian->GetPosition().x + a_galaxian->GetSprite()->GetWidth()/2) - m_pPlayer->GetPosition().x) < 5)
	{
		randomNumber = ((float)(rand()%3) / 10);
		m_deltaTimeMap[a_galaxian] = 0;
		Shoot(a_galaxian);
	}

	Vector2 target;
	if(a_galaxian->GetPositionInFormation().x >= m_formation->FORMATION_COLUMNS / 2)
	{
		target = Vector2(SCRWIDTH / 2 + cos(max((a_galaxian->GetPosition().y - 200) * PI/180, 0)) * SCRWIDTH / 2 - 80,a_galaxian->GetPosition().y + 100);
	}
	else
	{
		target = Vector2(SCRWIDTH / 2 + sin(max((a_galaxian->GetPosition().y - 200) * PI/180, 0)) * SCRWIDTH / 2 - 80,a_galaxian->GetPosition().y + 100);
	}
	Vector2 direction(target - a_galaxian->GetPosition());
	direction.Normalize();
	a_galaxian->Move(direction * a_fDeltaTime * 200);

	if(a_galaxian->GetPosition().y > SCRHEIGHT - 100)
	{
		a_galaxian->Move(0,250 * a_fDeltaTime);

		if(a_galaxian->GetPosition().y > SCRHEIGHT)
		{
			a_galaxian->SetPosition(Vector2(a_galaxian->GetPosition().x,-20));
			a_galaxian->ChangeState(GalaxianReturnToFormationState::getInstance());
		}
	}
}


void GalaxianAttackingState::Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen)
{
	a_galaxian->GetSprite()->CopyTo(a_screen, a_galaxian->GetPosition().x, a_galaxian->GetPosition().y);
}


void GalaxianAttackingState::Exit(Galaxian* a_galaxian)
{
	
}


void GalaxianAttackingState::Hit(Galaxian* a_galaxian, Entity* a_pOther)
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
		else
		{
			a_galaxian->ChangeState(GalaxianDyingState::getInstance());
		}
	}
}


void GalaxianAttackingState::SetPlayer(Player* a_pPlayer)
{
	m_pPlayer = a_pPlayer;
}


void GalaxianAttackingState::Shoot(Galaxian* a_galaxian)
{
	Bullet* bullet = new Bullet(a_galaxian, a_galaxian->GetPosition().x + GalaxianFormation::SPRITE_WIDTH / 2, a_galaxian->GetPosition().y + GalaxianFormation::SPRITE_HEIGHT + 10);
	Sounds->Play("shoot");
}