#include "GalaxianReturnToFormationState.h"
#include "GalaxianInFormationState.h"
#include "GalaxianArcingState.h"

bool GalaxianReturnToFormationState::instanceFlag = false;
GalaxianReturnToFormationState* GalaxianReturnToFormationState::single = NULL;
GalaxianReturnToFormationState* GalaxianReturnToFormationState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GalaxianReturnToFormationState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GalaxianReturnToFormationState::~GalaxianReturnToFormationState()
{
	instanceFlag = false;
	m_deltaTimeMap.clear();
	m_referanceMap.clear();
}


GalaxianReturnToFormationState::GalaxianReturnToFormationState(void)
{
}


void GalaxianReturnToFormationState::Enter(Galaxian* a_galaxian)
{
	m_referanceMap[a_galaxian] = m_formation->GetFirstGalaxianInFormation();
	if(!m_referanceMap[a_galaxian])
	{
		a_galaxian->ChangeState(GalaxianArcingState::getInstance());
	}
}

void GalaxianReturnToFormationState::Update(Galaxian* a_galaxian, float a_fDeltaTime)
{
	m_deltaTimeMap[a_galaxian] += a_fDeltaTime;
	if(m_referanceMap[a_galaxian]->m_state == EntityState::REMOVED)
	{
		m_referanceMap[a_galaxian] = m_formation->GetFirstGalaxianInFormation();
	}
	Vector2 referancePosition = m_referanceMap[a_galaxian]->GetPosition();
	int xOffset = a_galaxian->GetPositionInFormation().x - m_referanceMap[a_galaxian]->GetPositionInFormation().x;
	int yOffset = a_galaxian->GetPositionInFormation().y - m_referanceMap[a_galaxian]->GetPositionInFormation().y;
	Vector2 targetPosition = referancePosition + Vector2(xOffset * (GalaxianFormation::SPRITE_WIDTH+12), yOffset * (GalaxianFormation::SPRITE_HEIGHT+6));

	if(a_galaxian->GetPosition().Distance(targetPosition) > 5)
	{
		Vector2 direction = targetPosition - a_galaxian->GetPosition();
		direction.Normalize();
		a_galaxian->Move(direction * a_fDeltaTime * 200);
	}
	else
	{
		a_galaxian->SetPosition(targetPosition);
		a_galaxian->SetDirection(Vector2(0,1));
		a_galaxian->ChangeState(GalaxianInFormationState::getInstance());
	}
}


void GalaxianReturnToFormationState::Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen)
{
	a_galaxian->GetSprite()->CopyTo(a_screen, a_galaxian->GetPosition().x, a_galaxian->GetPosition().y);
}


void GalaxianReturnToFormationState::Exit(Galaxian* a_galaxian)
{
	
}


void GalaxianReturnToFormationState::Hit(Galaxian* a_galaxian, Entity* a_pOther)
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