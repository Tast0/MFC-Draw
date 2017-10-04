#pragma once
#include "Layer.h"
class CPenc : public CLayer
{
	CArray<CPoint, CPoint> m_arr;
	void OnDraw(CDC* pDC);  //
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC *pDC);
	BOOL Track(CPoint point);
	void Offset(int cx, int cy);
public:
	CPenc();
	virtual ~CPenc();

};

