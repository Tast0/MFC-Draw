#pragma once
enum { STU_NORMAL, STU_SELECT };
class CLayer
{
public:
	int m_nStat;  //ͼ��״̬
	COLORREF m_clText, m_clBack;
	//ͼ���϶����̣�ѡ��ƽ�ƺ͸���
	virtual void Offset(int cx, int cy) = 0;
	virtual BOOL Track(CPoint point) = 0;
	//��꼰��ʾ�¼�����
	virtual void OnDraw(CDC* pDC) = 0;
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC = NULL) = 0;

	CLayer();
	virtual ~CLayer();

};
