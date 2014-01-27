#include "Bullet.h"

static Tmpl8::Surface* bulletImage = new Tmpl8::Surface("assets/bullet.png");

Bullet::Bullet(Entity* a_pOwner, float a_fX, float a_fY)
	: Entity(bulletImage, a_fX, a_fY)
{
	m_pOwner = a_pOwner;
	m_bReleased = false;
	m_bCanKill = true;
	m_type = BULLET;
}


Bullet::~Bullet(void)
{
	Entity::~Entity();
}


void Bullet::Update(float a_fDeltaTime)
{
	if(m_pOwner->m_type == PLAYER)
	{
		if(m_state == EntityState::ALIVE && m_bReleased)
		{
			m_position.y -= a_fDeltaTime * 600;
		}
	}
	else
	{
		m_position.y += a_fDeltaTime * 600;
	}

	if(m_position.y < -20 || m_position.y > SCRHEIGHT + 20)
	{
		if(m_pOwner->m_type == EntityType::PLAYER)
		{
			m_state = EntityState::DEAD;
		}
		else
		{
			m_state = EntityState::REMOVED;
		}
	}
}


void Bullet::Release()
{
	m_bReleased = true;
}


void Bullet::Hit(Entity* a_pOther)
{
	if(a_pOther != m_pOwner && a_pOther->m_type != m_pOwner->m_type & a_pOther->m_type != m_type)
	{
		if(m_pOwner->m_type == EntityType::PLAYER)
		{
			m_state = EntityState::DEAD;
		}
		else
		{
			m_state = EntityState::REMOVED;
		}
	}
}


Entity* Bullet::GetOwner()
{
	return m_pOwner;
}