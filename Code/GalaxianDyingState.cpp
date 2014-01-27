#include "GalaxianDyingState.h"
#include "GalaxianAttackingState.h"
#include "GalaxianInFormationState.h"

bool GalaxianDyingState::instanceFlag = false;
GalaxianDyingState* GalaxianDyingState::single = NULL;
GalaxianDyingState* GalaxianDyingState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GalaxianDyingState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GalaxianDyingState::~GalaxianDyingState()
{
	instanceFlag = false;
	m_spriteCounterMap.clear();
	m_killTimerMap.clear();
	delete[] m_explodingSpriteArray;
}


GalaxianDyingState::GalaxianDyingState(void)
{
	m_explodingSpriteArray[0] = new Tmpl8::Surface("assets/enemies/galaxian_blue_exploding1.png");
	m_explodingSpriteArray[1] = new Tmpl8::Surface("assets/enemies/galaxian_blue_exploding2.png");
	m_explodingSpriteArray[2] = new Tmpl8::Surface("assets/enemies/galaxian_blue_exploding3.png");
	m_explodingSpriteArray[3] = new Tmpl8::Surface("assets/enemies/galaxian_blue_exploding4.png");
	m_explodingSpriteArray[4] = new Tmpl8::Surface("assets/enemies/galaxian_purple_exploding1.png");
	m_explodingSpriteArray[5] = new Tmpl8::Surface("assets/enemies/galaxian_purple_exploding2.png");
	m_explodingSpriteArray[6] = new Tmpl8::Surface("assets/enemies/galaxian_purple_exploding3.png");
	m_explodingSpriteArray[7] = new Tmpl8::Surface("assets/enemies/galaxian_purple_exploding4.png");
	m_explodingSpriteArray[8] = new Tmpl8::Surface("assets/enemies/galaxian_red_exploding1.png");
	m_explodingSpriteArray[9] = new Tmpl8::Surface("assets/enemies/galaxian_red_exploding2.png");
	m_explodingSpriteArray[10] = new Tmpl8::Surface("assets/enemies/galaxian_red_exploding3.png");
	m_explodingSpriteArray[11] = new Tmpl8::Surface("assets/enemies/galaxian_red_exploding4.png");
	m_explodingSpriteArray[12] = new Tmpl8::Surface("assets/enemies/galaxian_yellow_exploding1.png");
	m_explodingSpriteArray[13] = new Tmpl8::Surface("assets/enemies/galaxian_yellow_exploding2.png");
	m_explodingSpriteArray[14] = new Tmpl8::Surface("assets/enemies/galaxian_yellow_exploding3.png");
	m_explodingSpriteArray[15] = new Tmpl8::Surface("assets/enemies/galaxian_yellow_exploding4.png");
}


void GalaxianDyingState::Enter(Galaxian* a_galaxian)
{
	Stats::AddScore(a_galaxian->GetRank());
	a_galaxian->m_state = EntityState::DEAD;
	m_killTimerMap[a_galaxian] = 0;
	m_spriteCounterMap[a_galaxian] = 0;
	Stats::ENEMIES_LEFT--;
}

void GalaxianDyingState::Update(Galaxian* a_galaxian, float a_fDeltaTime)
{
	m_killTimerMap[a_galaxian] += a_fDeltaTime;
	if(m_killTimerMap[a_galaxian] > 0.07f)
	{
		if(m_spriteCounterMap[a_galaxian] == 0)
		{
			Vector2 newSpritePosition;
			newSpritePosition.x = a_galaxian->GetPosition().x - ((m_explodingSpriteArray[0]->GetWidth() - a_galaxian->GetSprite()->GetWidth()) * 0.5);
			newSpritePosition.y = a_galaxian->GetPosition().y - ((m_explodingSpriteArray[0]->GetHeight() - a_galaxian->GetSprite()->GetHeight()) * 0.5);
			a_galaxian->SetPosition(newSpritePosition);

			Sounds->Play("explode");

			if(a_galaxian->GetRank() == Rank::GENERAL)
			{
				GalaxianInFormationState::getInstance()->SetAttackInProgress(false);
			}
		}
		if(m_spriteCounterMap[a_galaxian] == 4)
		{
			a_galaxian->m_state = EntityState::REMOVED;
			return;
		}
		m_killTimerMap[a_galaxian] = 0;
		a_galaxian->SetSprite(m_explodingSpriteArray[(a_galaxian->GetRank()-1) * 4 + m_spriteCounterMap[a_galaxian]]);
		m_spriteCounterMap[a_galaxian]++;
	}
}


void GalaxianDyingState::Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen)
{
	a_galaxian->GetSprite()->CopyTo(a_screen, a_galaxian->GetPosition().x, a_galaxian->GetPosition().y);
}


void GalaxianDyingState::Exit(Galaxian* a_galaxian)
{
	
}


void GalaxianDyingState::Hit(Galaxian* a_galaxian, Entity* a_pOther)
{

}