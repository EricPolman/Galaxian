#include "Galaxian.h"


Galaxian::Galaxian(Tmpl8::Surface* a_texture,float a_fX, float a_fY, Rank a_rank)
	: Entity(a_texture, a_fX, a_fY)
{
	m_rank = a_rank;
	m_type = ENEMY;
	Stats::ENEMIES_LEFT++;
}


Galaxian::~Galaxian(void)
{
	Entity::~Entity();
}


void Galaxian::Update(float a_fDeltaTime)
{
	m_pCurrentState->Update(this, a_fDeltaTime);
}


void Galaxian::Draw(Tmpl8::Surface* a_screen)
{
	m_pCurrentState->Draw(this, a_screen); 
}


void Galaxian::Hit(Entity* a_pOther)
{
	m_pCurrentState->Hit(this, a_pOther);
}


void Galaxian::SetState(State<Galaxian>* a_state)
{
	m_pCurrentState = a_state;
	a_state->Enter(this);
}


State<Galaxian>* Galaxian::GetState()
{
	return m_pCurrentState;
}


void Galaxian::ChangeState(State<Galaxian>* a_newState)
{
	m_pCurrentState->Exit(this);

	m_pCurrentState = a_newState;
	m_pCurrentState->Enter(this);
}