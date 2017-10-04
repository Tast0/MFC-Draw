#include "stdafx.h"
#include "Penc.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPenc::CPenc()
{

}

CPenc::~CPenc()
{

}

void CPenc::OnDraw(CDC* pDC)
{
	int nSize = m_arr.GetSize();
	if (!nSize)
		return;
	CPen pen(PS_SOLID, 2, m_clText);
	CPen* pPen = pDC->SelectObject(&pen);

	pDC->Polyline(m_arr.GetData(), nSize);
	pDC->SelectObject(pPen);

	if (STU_SELECT == m_nStat)
	{
		CPoint pt = m_arr[0];
		pDC->FillSolidRect(pt.x - 5, pt.y - 5, 10, 10, GetSysColor(COLOR_HIGHLIGHT));
		pt = m_arr[nSize - 1];
		pDC->FillSolidRect(pt.x - 5, pt.y - 5, 10, 10, GetSysColor(COLOR_HIGHLIGHT));
	}

}
void CPenc::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_arr.Add(point);
}
void CPenc::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_arr.Add(point);
}
void CPenc::OnMouseMove(UINT nFlags, CPoint point, CDC *pDC)
{
	int nSize = m_arr.GetSize();
	if (!nSize)
		return;
	if (nFlags & MK_LBUTTON)
	{
		//两点之间的距离尽量大于3以上再添加
		CPoint &pt = m_arr[nSize - 1];
		int cx = pt.x - point.x;
		int cy = pt.y - point.y;
		//		TRACE("pt.x=%d,pt.y=%d\n",pt.x,pt.y);
		pDC->MoveTo(pt);
		pDC->LineTo(point);
		if (sqrt((double)cx*cx + (double)cy*cy) > 5)
			m_arr.Add(point);

	}
}

BOOL CPenc::Track(CPoint point)
{
	int i = 0, nSize = m_arr.GetSize();
	while (i<nSize)
	{
		CPoint& pt = m_arr[i];
		int cx = pt.x - point.x;
		int cy = pt.y - point.y;
		if (sqrt((double)cx*cx + (double)cy*cy)<15)
			return TRUE;
		++i;
	}
	return FALSE;
}

void CPenc::Offset(int cx, int cy)
{
	int i = 0, nSize = m_arr.GetSize();
	while (i<nSize)
		m_arr[i++].Offset(cx, cy);
}

