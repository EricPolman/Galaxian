#pragma once
#include "entity.h"
#include "state.h";
#include "Bullet.h"

enum Rank{
	PRIVATE = 1,
	CORPORAL,
	SERGEANT,
	GENERAL
};

class Galaxian :
	public Entity
{
public:
	Galaxian(Tmpl8::Surface* a_texture,float a_fX = 0, float a_fY = 0, Rank a_rank = Rank::PRIVATE);
	virtual ~Galaxian(void);

	void ChangeState(State<Galaxian>* a_newState);
	void SetState(State<Galaxian>* a_state);
	State<Galaxian>* GetState();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw(Tmpl8::Surface* a_screen);
	virtual void Hit(Entity* a_pOther);
	
	void SetRank(Rank a_rank){m_rank = a_rank;}
	inline Rank GetRank(){return m_rank;}

	void SetPositionInFormation(int a_iX, int a_iY){m_positionInFormation.x = a_iX;m_positionInFormation.y = a_iY;}
	inline Vector2 GetPositionInFormation(){return m_positionInFormation;}
protected:
	State<Galaxian>* m_pCurrentState;
	Vector2 m_positionInFormation;
	Rank m_rank;
};

