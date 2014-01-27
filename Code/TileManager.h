#pragma once
#include "includes.h"
#include "TileSurface.h"
#include "TileNode.h"

class TileManager
{
public:
	~TileManager(void);
	static TileManager* getInstance(void);

	void LoadBaseSprite(char* a_sPath);
	void ProcessTileMap();
	void Draw(Tmpl8::Surface* a_screen);

	TileSurface* GetTileSurface(int id);
	
	static int TILE_WIDTH;
	static int TILE_HEIGHT;
private:
	Tmpl8::Surface* surface;

	static bool instanceFlag;
	static TileManager *single;
	TileManager(void);

	Tmpl8::Surface* m_pBaseSprite;
	std::vector<TileSurface*> m_pTileSurfaces;
	TileNode* m_pTiles;

};

#define Tiles TileManager::getInstance()