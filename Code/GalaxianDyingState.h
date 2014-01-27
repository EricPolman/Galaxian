#pragma once
#include "state.h"
#include "GalaxianFormation.h"

class GalaxianDyingState :
	public State<Galaxian>
{
private:
	GalaxianDyingState(void);

    static bool instanceFlag;
    static GalaxianDyingState *single;
public:
	~GalaxianDyingState(void);
    static GalaxianDyingState* getInstance();
	
	GalaxianFormation* m_formation;

	void Enter(Galaxian* a_galaxian);
	void Update(Galaxian* a_galaxian, float a_fDeltaTime);
	void Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen);
	void Hit(Galaxian* a_galaxian, Entity* a_pOther);
	void Exit(Galaxian* a_galaxian);

private:
	std::map<Galaxian*, float> m_killTimerMap;
	std::map<Galaxian*, int> m_spriteCounterMap;
	Tmpl8::Surface* m_explodingSpriteArray[16];
};

