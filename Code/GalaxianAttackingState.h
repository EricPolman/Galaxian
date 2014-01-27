#pragma once
#include "state.h"
#include "GalaxianFormation.h"
#include "Player.h"

class GalaxianAttackingState :
	public State<Galaxian>
{
private:
	GalaxianAttackingState(void);

	Player* m_pPlayer;

    static bool instanceFlag;
    static GalaxianAttackingState *single;
public:
	~GalaxianAttackingState(void);
    static GalaxianAttackingState* getInstance();

	void Enter(Galaxian* a_galaxian);
	void Update(Galaxian* a_galaxian, float a_fDeltaTime);
	void Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen);
	void Hit(Galaxian* a_galaxian, Entity* a_pOther);
	void Exit(Galaxian* a_galaxian);

	void Shoot(Galaxian* a_galaxian);
	
	void SetPlayer(Player* a_pPlayer);

	GalaxianFormation* m_formation;
private:
	std::map<Galaxian*, float> m_deltaTimeMap;
	std::map<Galaxian*, int> m_spriteCounterMap;
	Tmpl8::Surface* m_formationSpriteArray[18];

	Vector2 m_targetPosition, m_directionFromStartToTarget;
};

