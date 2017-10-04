#pragma once
#include "Layer.h"

class CLine : public CLayer
{
	CPoint m_ps, m_pe;//记录线段的起点 终点
	BOOL Track(CPoint point);//判断鼠标是否点下是否应当一直绘制
	void OnDraw(CDC* pDC);  //
	//在窗口上绘制直线的话，我们需要捕捉两个点
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC *pDC);//使用WM_MOUSEMOVE来捕捉鼠标的不断移动
	void Offset(int cx, int cy);//将单个线段位置平移

public:
	CLine();
	virtual ~CLine();

};

