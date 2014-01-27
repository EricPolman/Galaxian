#include "TileManager.h"

int TileManager::TILE_WIDTH = 16;
int TileManager::TILE_HEIGHT = 16;

TileManager::TileManager(void)
{
	m_pTileSurfaces.reserve(768);
}

TileManager::~TileManager(void)
{
	instanceFlag = false;
	delete m_pBaseSprite;
}

bool TileManager::instanceFlag = false;
TileManager* TileManager::single = NULL;
TileManager* TileManager::getInstance()
{
    if(! instanceFlag)
    {
        single = new TileManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


void TileManager::LoadBaseSprite(char* a_sPath)
{
	m_pBaseSprite = new Tmpl8::Surface(a_sPath);
}


void TileManager::ProcessTileMap()
{
	int rows = m_pBaseSprite->GetHeight() / TILE_HEIGHT;
	int columns = m_pBaseSprite->GetWidth() / TILE_WIDTH;
	int idCounter = 0;
	
	int id = 0;
	TileNode* previous = 0;
	TileNode* next = 0;

	for(int row = 0; row < rows; row++)
	{
		for(int col = 0; col < columns; col++)
		{
			TileNode* tileNode = new TileNode(previous, row, col);
			if(previous != 0)
			{
				previous->m_pNext = tileNode;
			}
			Tmpl8::Surface* surface = new Tmpl8::Surface(TILE_WIDTH, TILE_HEIGHT);
			m_pBaseSprite->CopyPartTo(surface, 0, 0, col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

			if(row == 0 && col == 0)
			{
				m_pTiles = tileNode;
				TileSurface* tileSurface = new TileSurface(idCounter,surface);
				m_pTileSurfaces.push_back(tileSurface);
				tileNode->m_iTileId = 0;
				idCounter++;
				previous = tileNode;
				continue;
			}
			bool isUnique = true;
			for(std::vector<TileSurface*>::iterator iter = m_pTileSurfaces.begin(); iter != m_pTileSurfaces.end();)
			{
				if(!(*iter)->CompareSurfaces(surface))
				{
					isUnique = false;
					id = (*iter)->m_iTileId;
					iter = m_pTileSurfaces.end();
				}
				else
				{
					iter++;
				}
			}

			if(isUnique)
			{
				TileSurface* tileSurface = new TileSurface(idCounter,surface);
				m_pTileSurfaces.push_back(tileSurface);
				id = idCounter;
				idCounter++;
			}
			else
			{
				delete surface;
			}
			tileNode->m_iTileId = id;
			previous = tileNode;
		}
	}
}


void TileManager::Draw(Tmpl8::Surface* a_screen)
{
	int counter = 0;
	//m_pTiles->Draw(a_screen);
	for(std::vector<TileSurface*>::iterator iter = m_pTileSurfaces.begin(); iter != m_pTileSurfaces.end(); iter++)
	{
		(*iter)->m_pTileSurface->CopyTo(a_screen, TILE_WIDTH * (counter % (SCRWIDTH/TILE_WIDTH)),counter / (SCRWIDTH/TILE_WIDTH) * TILE_HEIGHT);
		counter++;
	}
}


TileSurface* TileManager::GetTileSurface(int id)
{
	return m_pTileSurfaces[id];
}