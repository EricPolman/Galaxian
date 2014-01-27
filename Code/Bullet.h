#pragma once
#include "entity.h"
class Bullet :
	public Entity
{
public:
	Bullet(Entity* a_pOwner, float a_fX = 0, float a_fY = 0); 
	virtual ~Bullet(void);
	
	virtual void Update(float a_fDeltaTime);
	
	void Release();
	virtual void Hit(Entity* a_pOther);
	inline bool GetIsReleased(){return m_bReleased;};
	Entity* GetOwner();
	
	inline bool GetCanKill(){return m_bCanKill;}
	void SetCanKill(bool a_bCanKill){m_bCanKill = a_bCanKill;}
private:
	Entity* m_pOwner;
	bool m_bReleased;
	bool m_bCanKill;
};

