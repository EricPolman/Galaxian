#pragma once
#include "state.h"
#include "GalaxianFormation.h"
#include "GalaxianDyingState.h"

class GalaxianReturnToFormationState :
	public State<Galaxian>
{
private:
	GalaxianReturnToFormationState(void);

    static bool instanceFlag;
    static GalaxianReturnToFormationState *single;
public:
	~GalaxianReturnToFormationState(void);
    static GalaxianReturnToFormationState* getInstance();

	void Enter(Galaxian* a_galaxian);
	void Update(Galaxian* a_galaxian, float a_fDeltaTime);
	void Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen);
	void Hit(Galaxian* a_galaxian, Entity* a_pOther);
	void Exit(Galaxian* a_galaxian);

	GalaxianFormation* m_formation;
private:
	std::map<Galaxian*, float> m_deltaTimeMap;
	std::map<Galaxian*, Galaxian*> m_referanceMap;
};

