#pragma once
#include "includes.h"

class TileNode
{
public:
	TileNode(TileNode* a_pPrevious, int a_iRow, int a_iCol);
	~TileNode(void);
	
	int m_iRow, m_iCol;
	int m_iTileId;
	TileNode* m_pPrevious;
	TileNode* m_pNext;

	void Draw(Tmpl8::Surface* a_screen);
};
