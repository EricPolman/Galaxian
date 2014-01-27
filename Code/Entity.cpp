#include "Entity.h"
#include "EntityManager.h"


Entity::Entity(Tmpl8::Surface* a_texture,float a_fX, float a_fY)
{
	m_pSprite = a_texture;
	m_position.x = a_fX;
	m_position.y = a_fY;
	m_state = ALIVE;
	m_type = ENTITY;
	m_direction.y = -1;
	m_bIsVisible = true;
	Entities->Add(this);
}


Entity::~Entity(void)
{
	Entities->Remove(this);
}


void Entity::Update(float a_fDeltaTime)
{

}


void Entity::Hit(Entity* a_pOther)
{

}


void Entity::Draw(Tmpl8::Surface* a_screen)
{
	if(m_bIsVisible)
	{
		m_pSprite->CopyTo(a_screen, m_position.x, m_position.y);
	}
}


void Entity::Move(float a_fX, float a_fY)
{
	m_position.x += a_fX;
	m_position.y += a_fY;
}


void Entity::Move(Vector2 a_translation)
{
	m_position.x += a_translation.x;
	m_position.y += a_translation.y;
}
