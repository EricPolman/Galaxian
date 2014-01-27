#include "GalaxianArcingState.h"
#include "GalaxianDyingState.h"
#include "GalaxianAttackingState.h"

bool GalaxianArcingState::instanceFlag = false;
GalaxianArcingState* GalaxianArcingState::single = NULL;
GalaxianArcingState* GalaxianArcingState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GalaxianArcingState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GalaxianArcingState::~GalaxianArcingState()
{
	instanceFlag = false;
	//delete[] m_formationSpriteArray;
}


GalaxianArcingState::GalaxianArcingState(void)
{	
	
}


void GalaxianArcingState::Enter(Galaxian* a_galaxian)
{
	m_arcProperties[a_galaxian].stepSize = 18;
	m_arcProperties[a_galaxian].stepCounter = 0;
	m_arcProperties[a_galaxian].radius = 90;
	if(a_galaxian->GetPositionInFormation().x < m_formation->FORMATION_COLUMNS / 2)
	{
		m_arcProperties[a_galaxian].pivotPoint = a_galaxian->GetPosition() - Vector2(m_arcProperties[a_galaxian].radius,0);
		m_arcProperties[a_galaxian].angle = 0;
	}
	else
	{
		m_arcProperties[a_galaxian].pivotPoint = a_galaxian->GetPosition() + Vector2(m_arcProperties[a_galaxian].radius,0);
		m_arcProperties[a_galaxian].angle = 180;
	}
	
	m_arcProperties[a_galaxian].targetPosition = a_galaxian->GetPosition()+Vector2(0,1);
	if(a_galaxian->GetRank() == Rank::GENERAL)
	{
		Galaxian* first = m_formation->GetGalaxian((int)a_galaxian->GetPositionInFormation().x, (int)a_galaxian->GetPositionInFormation().y+1);
		Galaxian* second = m_formation->GetGalaxian((int)a_galaxian->GetPositionInFormation().x-1, (int)a_galaxian->GetPositionInFormation().y+1);
		Galaxian* third = m_formation->GetGalaxian((int)a_galaxian->GetPositionInFormation().x+1, (int)a_galaxian->GetPositionInFormation().y+1);

		if(first)
		{
			first->ChangeState(this);
		}
		if(second)
		{
			second->ChangeState(this);
		}
		if(third && (!first || !second))
		{
			third->ChangeState(this);
		}
	}
}


void GalaxianArcingState::Update(Galaxian* a_galaxian, float a_fDeltaTime)
{
	if(a_galaxian->GetPosition().Distance(m_arcProperties[a_galaxian].targetPosition) < 4)
	{
		m_arcProperties[a_galaxian].stepCounter++;
		if(a_galaxian->GetPositionInFormation().x < m_formation->FORMATION_COLUMNS / 2)
		{
			m_arcProperties[a_galaxian].angle = 0 - m_arcProperties[a_galaxian].stepSize * m_arcProperties[a_galaxian].stepCounter;
		}
		else
		{
			m_arcProperties[a_galaxian].angle = 180 + m_arcProperties[a_galaxian].stepSize * m_arcProperties[a_galaxian].stepCounter;
		}
		m_arcProperties[a_galaxian].angle *= PI / 180;
		float x = cos(m_arcProperties[a_galaxian].angle);
		float y = sin(m_arcProperties[a_galaxian].angle);
		x *= m_arcProperties[a_galaxian].radius;
		y *= m_arcProperties[a_galaxian].radius;

		m_arcProperties[a_galaxian].targetPosition = m_arcProperties[a_galaxian].pivotPoint + Vector2(x,y);
	}
	
	Vector2 direction = m_arcProperties[a_galaxian].targetPosition - a_galaxian->GetPosition();
	direction.Normalize();
	a_galaxian->Move(direction * 250 * a_fDeltaTime);

	if(m_arcProperties[a_galaxian].stepCounter == 10)
	{
		a_galaxian->ChangeState(GalaxianAttackingState::getInstance());
	}
}


void GalaxianArcingState::Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen)
{
	a_galaxian->GetSprite()->CopyTo(a_screen, a_galaxian->GetPosition().x, a_galaxian->GetPosition().y);
}


void GalaxianArcingState::Exit(Galaxian* a_galaxian)
{
	
}


void GalaxianArcingState::Hit(Galaxian* a_galaxian, Entity* a_pOther)
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