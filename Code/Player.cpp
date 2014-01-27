#include "Player.h"

Player::Player(Tmpl8::Surface* a_texture,float a_fX, float a_fY)
	: Entity(a_texture, a_fX, a_fY)
{
	m_bLeftKeyPressed = m_bRightKeyPressed = m_bSpaceKeyPressed = false;
	m_pBullet = 0;
	m_type = PLAYER;
	
	m_pNormalSprite = a_texture;

	m_fExplodingTimer = 0;
	m_iExplodingSpritesCounter = 0;

	std::ostringstream oss;
	for(int i = 0; i < 4; i++)
	{
		std::string path = "assets/player_exploding";
		oss << i;
		path += oss.str();
		oss.str("");
		path += ".png";
		m_explodingSprites[i] = new Tmpl8::Surface(const_cast<char*>(path.c_str()));
	}
}

Player::~Player()
{
	if(m_pBullet)
		delete m_pBullet;

	delete m_pNormalSprite;
	delete[] m_explodingSprites;
	Entity::~Entity();
}

void Player::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	
	if(m_state == EntityState::ALIVE)
	{
		if(m_bLeftKeyPressed && m_position.x > 300.f * a_fDeltaTime)
		{
			Move(-200.f * a_fDeltaTime, 0);
		}
		if(m_bRightKeyPressed && m_position.x < SCRWIDTH - m_pSprite->GetWidth() - 300.f * a_fDeltaTime)
		{
			Move(200.f * a_fDeltaTime, 0);
		}
	}
	else
	{
		// Dem' player be dead.
		// Play exploding animation.
		m_fExplodingTimer += a_fDeltaTime;
		if(m_fExplodingTimer > 0.12f)
		{
			if(m_iExplodingSpritesCounter == 4)
			{
				m_bIsVisible = false;
				SetSprite(m_pNormalSprite);
				if(m_fExplodingTimer > 1.12f)
				{
					m_bIsVisible = true;
					m_iExplodingSpritesCounter = 0;
					SetPosition(Vector2(SCRWIDTH / 2 - m_pSprite->GetWidth()/2, SCRHEIGHT - 100));
					m_state = EntityState::ALIVE;
					m_bLeftKeyPressed = m_bRightKeyPressed = m_bSpaceKeyPressed = false;
				}
				return;
			}
			if(m_iExplodingSpritesCounter == 0)
			{
				
				Sounds->Play("explode");
				if(m_pBullet)
				{
					m_pBullet->m_state = EntityState::REMOVED;
					m_pBullet->m_bIsVisible = false;
					m_pBullet = 0;
				}

				Vector2 newSpritePosition;
				newSpritePosition.x = GetPosition().x - ((m_explodingSprites[0]->GetWidth() - m_pSprite->GetWidth()) * 0.5);
				newSpritePosition.y = GetPosition().y - ((m_explodingSprites[0]->GetHeight() - m_pSprite->GetHeight()) * 0.5);
				SetPosition(newSpritePosition);
			}
			m_fExplodingTimer = 0;
			SetSprite(m_explodingSprites[m_iExplodingSpritesCounter]);
			m_iExplodingSpritesCounter++;
		}
	}
	if(m_pBullet)
	{
		if(!m_pBullet->GetIsReleased())
		{
			Vector2 bulletPosition;
			bulletPosition.x = m_position.x + m_pSprite->GetWidth() * 0.5f - 1;
			bulletPosition.y = m_position.y - 8;
			m_pBullet->SetPosition(bulletPosition);
		}
		if(m_pBullet->m_state == EntityState::DEAD)
		{
			m_pBullet->m_state = EntityState::REMOVED;
			m_pBullet->m_bIsVisible = false;
			m_pBullet = 0;
		}
	}
}

void Player::KeyDown( unsigned int code )
{
	if(m_state == EntityState::ALIVE)
	{
		//std::cout << code;
		if(code == 30) //A
		{
			m_bLeftKeyPressed = true;
		}
		if(code == 32) //D
		{
			m_bRightKeyPressed = true;		
		}
		if(code == 57) //Space
		{
			m_bSpaceKeyPressed = true;
			if(!m_pBullet)
			{
				m_pBullet = new Bullet(this, m_position.x + m_pSprite->GetWidth() * 0.5f - 1, m_position.y - 8);
			}
		}
	}
}

void Player::KeyUp( unsigned int code )
{
	if(m_state == EntityState::ALIVE)
	{
		if(code == 30) //A
		{
			m_bLeftKeyPressed = false;
		}
		if(code == 32) //D
		{
			m_bRightKeyPressed = false;		
		}
		if(code == 57) //SPace
		{
			m_bSpaceKeyPressed = false;
			if(m_pBullet && !m_pBullet->GetIsReleased())
			{
				m_pBullet->Release();
				Sounds->Play("shoot");
			}
		}
	}
}


void Player::Hit(Entity* a_pOther)
{
	if(m_state == EntityState::ALIVE)
	{
		if(a_pOther->m_type != EntityType::BULLET)
		{
			Stats::LIVES_LEFT--;
			m_state = EntityState::DEAD;
		}
		else
		{
			Bullet* bullet = (Bullet*)a_pOther;
			if(bullet->GetOwner() != this)
			{
				Stats::LIVES_LEFT--;
				m_state = EntityState::DEAD;
			}
		}
	}
}