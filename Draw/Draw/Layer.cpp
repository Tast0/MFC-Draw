#include "stdafx.h"
#include "Layer.h"


CLayer::CLayer()
{
	m_nStat = STU_NORMAL;
	m_clText = 0;//RGB(0,0,0);
	m_clBack = 0xffffff;//RGB(255,255,255);
}

CLayer::~CLayer()
{

}
