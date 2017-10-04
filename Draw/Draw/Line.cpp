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
{//��ʼ����Ա����
	m_pe.x = m_pe.y = -1;
}

CLine::~CLine()
{

}

void CLine::OnDraw(CDC* pDC)
{//��WM_PAINT��Ϣ�ص�ʱ���Ƴ�һ�������m_ps���յ�m_pe���߶�
	CPen pen(PS_SOLID, 2, m_clText);
	CPen* pPen = pDC->SelectObject(&pen);

	pDC->MoveTo(m_ps);
	pDC->LineTo(m_pe);
	pDC->SelectObject(pPen);

	if (STU_SELECT == m_nStat)
	{//��ѡ�δ���ѡ��״̬���߶�������ʾ
		pDC->FillSolidRect(m_ps.x - 5, m_ps.y - 5, 10, 10, GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillSolidRect(m_pe.x - 5, m_pe.y - 5, 10, 10, GetSysColor(COLOR_HIGHLIGHT));
	}
}
void CLine::OnLButtonDown(UINT nFlags, CPoint point)
{//����갴��ʱ��ֵ�����
	m_ps = point;
}
void CLine::OnLButtonUp(UINT nFlags, CPoint point)
{//������ͷ�ʱ��ֵ���յ�
	m_pe = point;
}
void CLine::OnMouseMove(UINT nFlags, CPoint point, CDC *pDC)
{
	if (!pDC)
		return;
	if (nFlags & MK_LBUTTON)
	{
		pDC->SetROP2(R2_NOT);  //�������߶�ʱʹ�÷�ɫ����
		if (m_pe.x > -1)
		{//���η�ɫ�����ϴ��������ķ�ɫ�߸�ԭ
			pDC->MoveTo(m_ps);
			pDC->LineTo(m_pe);
		}
		pDC->MoveTo(m_ps);
		pDC->LineTo(point);
		m_pe = point;
	}
}

BOOL CLine::Track(CPoint point)
{//������ƶ��������жϣ�����Ƿ��ӹ�ĳ���߶�
	CRect rect(m_ps, m_pe);
	rect.NormalizeRect();
	return rect.PtInRect(point);
}

void CLine::Offset(int cx, int cy)
{//�������߶�λ��ƽ��
	m_ps.Offset(cx, cy);
	m_pe.Offset(cx, cy);
}