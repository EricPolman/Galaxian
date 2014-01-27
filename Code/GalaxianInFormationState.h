#pragma once
#include "state.h"
#include "GalaxianFormation.h"
#include "Player.h"

class GalaxianInFormationState :
	public State<Galaxian>
{
private:
	GalaxianInFormationState(void);

    static bool instanceFlag;
    static GalaxianInFormationState *single;
public:
	~GalaxianInFormationState(void);
    static GalaxianInFormationState* getInstance();

	GalaxianFormation* m_formation;
	Player* m_pPlayer;

	void Enter(Galaxian* a_galaxian);
	void Update(Galaxian* a_galaxian, float a_fDeltaTime);
	void Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen);
	void Hit(Galaxian* a_galaxian, Entity* a_pOther);
	void Exit(Galaxian* a_galaxian);
	
	void SetPlayer(Player* a_pPlayer);

	void SetAttackInProgress(bool a_newValue);
private:
	std::map<Galaxian*, float> m_deltaTimeMap;
	std::map<Galaxian*, int> m_spriteCounterMap;
	Tmpl8::Surface* m_formationSpriteArray[18];
	bool m_bAttackInProgress; 
};

