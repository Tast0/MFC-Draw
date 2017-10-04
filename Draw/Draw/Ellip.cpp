#include "stdafx.h"
#include "Ellip.h"


CEllipe::CEllipe()
{
	m_rect.SetRect(-1, -1, -1, -1);
}

CEllipe::~CEllipe()
{

}

void CEllipe::OnDraw(CDC* pDC)
{
	CPen pen(PS_SOLID, 2, m_clText);
	CPen* pPen = pDC->SelectObject(&pen);
	pDC->Ellipse(m_rect);
	pDC->SelectObject(pPen);
	if (STU_SELECT == m_nStat)
	{
		CPoint pt = m_rect.CenterPoint();
		COLORREF cl = GetSysColor(COLOR_HIGHLIGHT);
		pDC->FillSolidRect(m_rect.left - 5, pt.y - 5, 10, 10, cl);
		pDC->FillSolidRect(m_rect.right - 5, pt.y - 5, 10, 10, cl);
		pDC->FillSolidRect(pt.x - 5, m_rect.top - 5, 10, 10, cl);
		pDC->FillSolidRect(pt.x - 5, m_rect.bottom - 5, 10, 10, cl);
	}

}
void CEllipe::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_rect.TopLeft() = point;
}
void CEllipe::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
	m_rect.NormalizeRect();
}
void CEllipe::OnMouseMove(UINT nFlags, CPoint point, CDC *pDC)
{
	if (!pDC)
		return;
	if (nFlags & MK_LBUTTON)
	{
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->SetROP2(R2_NOT);
		if (m_rect.right > -1)
			pDC->Ellipse(m_rect);

		m_rect.BottomRight() = point;
		pDC->Ellipse(m_rect);

	}
}
BOOL CEllipe::Track(CPoint point)
{
	return m_rect.PtInRect(point);
}

void CEllipe::Offset(int cx, int cy)
{
	m_rect.OffsetRect(cx, cy);
}
