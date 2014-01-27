#include "TileNode.h"
#include "TileManager.h"

TileNode::TileNode(TileNode* a_pPrevious, int a_iRow, int a_iCol)
{
	m_pPrevious = a_pPrevious;
	m_iRow = a_iRow;
	m_iCol = a_iCol;
	m_pNext = 0;
}


TileNode::~TileNode(void)
{
}


void TileNode::Draw(Tmpl8::Surface* a_screen)
{
	Tiles->GetTileSurface(m_iTileId)->m_pTileSurface->CopyTo
		(a_screen, Tiles->TILE_WIDTH * m_iCol, Tiles->TILE_HEIGHT * m_iRow);
	if(m_pNext != 0)
	{
		m_pNext->Draw(a_screen);
	}
}