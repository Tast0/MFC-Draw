#pragma once
#include "Layer.h"
class CEllipe : public CLayer
{
	CRect m_rect;
	BOOL Track(CPoint point);
	void OnDraw(CDC* pDC);  //
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC *pDC);
	void Offset(int cx, int cy);
public:
	CEllipe();
	virtual ~CEllipe();

};


