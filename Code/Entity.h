#pragma once
#include "includes.h"

enum EntityType{ENTITY,PLAYER,BULLET,ENEMY};
enum EntityState{ALIVE, DEAD, REMOVED};

class Entity
{
public:
	Entity(Tmpl8::Surface* a_texture,float a_fX = 0, float a_fY = 0); 
	virtual ~Entity(void);
	
	EntityState m_state;
	EntityType m_type;

	virtual void Update(float a_fDeltaTime);
	virtual void Draw(Tmpl8::Surface* a_screen);
	virtual void Hit(Entity* a_pOther);
	virtual void Move(Vector2 a_translation);
	virtual void Move(float a_fX, float a_fY);
	
	void SetPosition(Vector2 a_position){m_position = a_position;}
	inline Vector2 GetPosition(){return m_position;}
	void SetDirection(Vector2 a_direction){m_direction = a_direction;}
	inline Vector2 GetDirection(){return m_direction;}
	
	void SetSprite(Tmpl8::Surface* a_pSprite){m_pSprite = a_pSprite;}
	inline Tmpl8::Surface* GetSprite(){return m_pSprite;}
	
	bool m_bIsVisible;
protected:
	Vector2 m_position;
	Vector2 m_direction;
	Tmpl8::Surface* m_pSprite;

};

