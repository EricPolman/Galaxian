#pragma once
#include "Player.h"

class EntityManager
{
public:
	~EntityManager(void);
	static EntityManager* GetInstance(void);

	void Update(float a_fDeltaTime);
	void Draw(Tmpl8::Surface* a_screen);
	void Remove(Entity* a_pEntity);
	void Add(Entity* a_pEntity);
	void ClearAll();
	Player* m_pPlayer;
private:
	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_toBeRemoved;
	static bool instanceFlag;

	static EntityManager *single;
	EntityManager(void){}
};


#define Entities EntityManager::GetInstance()