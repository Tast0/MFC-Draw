#pragma once
#include "Layer.h"

class CLine : public CLayer
{
	CPoint m_ps, m_pe;//��¼�߶ε���� �յ�
	BOOL Track(CPoint point);//�ж�����Ƿ�����Ƿ�Ӧ��һֱ����
	void OnDraw(CDC* pDC);  //
	//�ڴ����ϻ���ֱ�ߵĻ���������Ҫ��׽������
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC *pDC);//ʹ��WM_MOUSEMOVE����׽���Ĳ����ƶ�
	void Offset(int cx, int cy);//�������߶�λ��ƽ��

public:
	CLine();
	virtual ~CLine();

};

