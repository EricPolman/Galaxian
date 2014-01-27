#pragma once
#include "Bullet.h"

class Player : public Entity
{
public:
	Player(Tmpl8::Surface* a_texture,float a_fX = 0, float a_fY = 0);
	virtual ~Player();
	
	virtual void Update(float a_fDeltaTime);

	void KeyDown( unsigned int code );
	void KeyUp( unsigned int code );
	void MouseMove( unsigned int x, unsigned int y ) {}
	void MouseUp( unsigned int button ) {}
	void MouseDown( unsigned int button ) {}
	void Hit(Entity* a_pOther);
private:
	Bullet* m_pBullet;
	bool m_bLeftKeyPressed, m_bRightKeyPressed, m_bSpaceKeyPressed;
	int m_iExplodingSpritesCounter;
	float m_fExplodingTimer;
	Tmpl8::Surface* m_explodingSprites[4];
	Tmpl8::Surface* m_pNormalSprite;
};
