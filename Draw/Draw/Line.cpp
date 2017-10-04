#include "stdafx.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{//初始化成员变量
	m_pe.x = m_pe.y = -1;
}

CLine::~CLine()
{

}

void CLine::OnDraw(CDC* pDC)
{//在WM_PAINT消息回调时绘制出一个从起点m_ps到终点m_pe的线段
	CPen pen(PS_SOLID, 2, m_clText);
	CPen* pPen = pDC->SelectObject(&pen);

	pDC->MoveTo(m_ps);
	pDC->LineTo(m_pe);
	pDC->SelectObject(pPen);

	if (STU_SELECT == m_nStat)
	{//当选段处于选择状态，线段两端显示
		pDC->FillSolidRect(m_ps.x - 5, m_ps.y - 5, 10, 10, GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillSolidRect(m_pe.x - 5, m_pe.y - 5, 10, 10, GetSysColor(COLOR_HIGHLIGHT));
	}
}
void CLine::OnLButtonDown(UINT nFlags, CPoint point)
{//当鼠标按下时赋值给起点
	m_ps = point;
}
void CLine::OnLButtonUp(UINT nFlags, CPoint point)
{//当鼠标释放时赋值给终点
	m_pe = point;
}
void CLine::OnMouseMove(UINT nFlags, CPoint point, CDC *pDC)
{
	if (!pDC)
		return;
	if (nFlags & MK_LBUTTON)
	{
		pDC->SetROP2(R2_NOT);  //绘制新线段时使用反色技术
		if (m_pe.x > -1)
		{//两次反色，对上次留下来的反色线复原
			pDC->MoveTo(m_ps);
			pDC->LineTo(m_pe);
		}
		pDC->MoveTo(m_ps);
		pDC->LineTo(point);
		m_pe = point;
	}
}

BOOL CLine::Track(CPoint point)
{//在鼠标移动过程中判断，鼠标是否掠过某个线段
	CRect rect(m_ps, m_pe);
	rect.NormalizeRect();
	return rect.PtInRect(point);
}

void CLine::Offset(int cx, int cy)
{//将单个线段位置平移
	m_ps.Offset(cx, cy);
	m_pe.Offset(cx, cy);
}