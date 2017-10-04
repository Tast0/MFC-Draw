#pragma once
enum { STU_NORMAL, STU_SELECT };
class CLayer
{
public:
	int m_nStat;  //图层状态
	COLORREF m_clText, m_clBack;
	//图层拖动过程，选择，平移和跟踪
	virtual void Offset(int cx, int cy) = 0;
	virtual BOOL Track(CPoint point) = 0;
	//鼠标及显示事件处理
	virtual void OnDraw(CDC* pDC) = 0;
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC = NULL) = 0;

	CLayer();
	virtual ~CLayer();

};
