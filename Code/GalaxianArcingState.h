#pragma once
#include "state.h"
#include "GalaxianFormation.h"
#include "Player.h"

struct ArcProperties
{
	short stepSize;
	short stepCounter;
	float radius;
	float angle;
	Vector2 pivotPoint;
	Vector2 targetPosition;
};

class GalaxianArcingState :
	public State<Galaxian>
{
private:
	GalaxianArcingState(void);

    static bool instanceFlag;
    static GalaxianArcingState *single;
public:
	~GalaxianArcingState(void);
    static GalaxianArcingState* getInstance();

	void Enter(Galaxian* a_galaxian);
	void Update(Galaxian* a_galaxian, float a_fDeltaTime);
	void Draw(Galaxian* a_galaxian, Tmpl8::Surface* a_screen);
	void Hit(Galaxian* a_galaxian, Entity* a_pOther);
	void Exit(Galaxian* a_galaxian);

	GalaxianFormation* m_formation;
private:
	std::map<Galaxian*, float> m_deltaTimeMap;
	std::map<Galaxian*, ArcProperties> m_arcProperties;
	//std::map<Galaxian*, int> m_spriteCounterMap;
	//Tmpl8::Surface* m_formationSpriteArray[18];
};

