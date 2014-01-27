#pragma once
#include "includes.h"
#include "Galaxian.h"

class GalaxianFormation
{
public:
	GalaxianFormation(void);
	~GalaxianFormation(void);

	static const int FORMATION_ROWS = 6;
	static const int FORMATION_COLUMNS = 10;
	static int SPRITE_WIDTH;
	static int SPRITE_HEIGHT;

	void Update(float a_fDeltaTime);
	void Draw(Tmpl8::Surface* a_screen);
	void BoundaryHit(bool a_bNewDirection);

	void SetMovementSpeed(float a_fMovementSpeed){m_fMovementSpeed = a_fMovementSpeed;}
	inline float GetMovementSpeed(){return m_fMovementSpeed;}

	inline bool GetIsGoingRight(){return m_bIsGoingRight;}

	Galaxian* GetFirstGalaxianInFormation();
	Galaxian* GetGalaxian(int a_iCol, int a_iRow);

	void InitializeFormation();
private:
	void ProcessChanges();
	bool m_bIsGoingRight;
	bool m_bBoundaryHit;
	bool m_bNewDirection;

	float m_fMovementSpeed;
	Galaxian* m_galaxians[FORMATION_ROWS][FORMATION_COLUMNS];
};

