
// DrawView.cpp : CDrawView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"
#include "Layer.h"
#include "Line.h"
#include "Ellip.h"
#include "Penc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DRAW_DRAG, &CDrawView::OnDrawDrag)
	ON_COMMAND(ID_DRAW_ELLIP, &CDrawView::OnDrawEllip)
	ON_COMMAND(ID_DRAW_LINE, &CDrawView::OnDrawLine)
	ON_COMMAND(ID_DRAW_PENC, &CDrawView::OnDrawPenc)
	ON_UPDATE_COMMAND_UI(ID_DRAW_DRAG, &CDrawView::OnUpdateDrawDrag)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIP, &CDrawView::OnUpdateDrawEllip)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CDrawView::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PENC, &CDrawView::OnUpdateDrawPenc)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_COLOR, &CDrawView::OnDrawColor)
END_MESSAGE_MAP()

// CDrawView ����/����

CDrawView::CDrawView()
{
	// TODO:  �ڴ˴���ӹ������

}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDrawView ����

void CDrawView::OnDraw(CDC* pDC)
{	//����ͼ����OnDraw������WM_PAINT��Ϣ�Ļص�����
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i = 0, nSize = m_ls.GetSize();
	CLayer *pLayer = NULL;
	while (i<nSize) //˭new�Ķ��󣬻���ָ����ó�����ʱ�ͻ��Զ�ת��˭��������
	{
		pLayer = m_ls[i++];
		pLayer->OnDraw(pDC);
	}

	// TODO: add draw code for native data here
}


// CDrawView ��ӡ


void CDrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

//void CDrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CDrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDrawView ���

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView ��Ϣ�������


void CDrawView::OnDrawDrag()
{//������ťΪ���õ�ǰ����Ϊ�Ϸ�
	m_nSelect = ID_DRAW_DRAG;
}

void CDrawView::OnDrawEllip()
{//��ǰ����Ϊ��Բ
	m_nSelect = ID_DRAW_ELLIP;

}

void CDrawView::OnDrawLine()
{//��ǰΪ�߶�
	m_nSelect = ID_DRAW_LINE;
}

void CDrawView::OnDrawPenc()
{//Ǧ����
	m_nSelect = ID_DRAW_PENC;

}

void CDrawView::OnUpdateDrawDrag(CCmdUI* pCmdUI)
{//��ǰ��ť���Ϸ�ʱ���ð�ť��ʾѡ��״̬
	pCmdUI->SetRadio(ID_DRAW_DRAG == m_nSelect);
}

void CDrawView::OnUpdateDrawEllip(CCmdUI* pCmdUI)
{//��ǰ��ť����Բʱ���ð�ť��ʾѡ��״̬
	pCmdUI->SetRadio(ID_DRAW_ELLIP == m_nSelect);
}

void CDrawView::OnUpdateDrawLine(CCmdUI* pCmdUI)
{//��ǰ��ť���߶�ʱ���ð�ť��ʾѡ��״̬
	pCmdUI->SetRadio(ID_DRAW_LINE == m_nSelect);
}

void CDrawView::OnUpdateDrawPenc(CCmdUI* pCmdUI)
{//��ǰ��ť��Ǧ����ʱ���ð�ť��ʾѡ��״̬
	pCmdUI->SetCheck(ID_DRAW_PENC == m_nSelect);
}

//WM_LBUTTONDOWN����Ϣӳ�亯��
void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CLayer *pLayer = NULL;
	if (ID_DRAW_DRAG == m_nSelect)
	{//������ͼ����Ϊѡ��״̬
		int i = 0, nSize = m_ls.GetSize();
		while (i<nSize)
		{
			pLayer = m_ls[i++];
			pLayer->m_nStat = pLayer->Track(point);
		}
		m_ptDrag = point;
		Invalidate(TRUE);
		return;
	}
	//����ָ�������ͣ��ڶѿռ��������Ӧ��ͼ�����
	switch (m_nSelect)
	{
	case ID_DRAW_LINE:
		pLayer = new CLine;
		break;
	case ID_DRAW_ELLIP:
		pLayer = new CEllipe;
		break;
	case ID_DRAW_PENC:
		pLayer = new CPenc;
		break;
	}
	if (pLayer)
	{//���ݵ�ǰ���ʹ���һ����ͼ�㣨��ͼ��Ḳ�Ǿ�ͼ�㣩
		pLayer->m_clText = m_clText;
		pLayer->OnLButtonDown(nFlags, point);
		m_ls.Add(pLayer);//�����ͼ��
	}
	CView::OnLButtonDown(nFlags, point);
}
//���WM_LBUTTONUPӳ�亯��
void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	int nSize = m_ls.GetSize();
	if (!nSize)
		return;
	CLayer* pLayer = NULL;

	if (ID_DRAW_DRAG == m_nSelect)
	{//���ͼ�����
		int i = 0;
		int cx = point.x - m_ptDrag.x;
		int cy = point.y - m_ptDrag.y;

		while (i<nSize)
		{
			pLayer = m_ls[i++];
			if (STU_SELECT == pLayer->m_nStat)
				pLayer->Offset(cx, cy);
		}
		Invalidate(TRUE);
		return;
	}//���ͼ���Ϸ�
	pLayer = m_ls[nSize - 1];
	pLayer->OnLButtonUp(nFlags, point);
	Invalidate(FALSE);
	CView::OnLButtonUp(nFlags, point);
}
//���WM_MOUSEMOVEӳ�亯��
void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{

	int nSize = m_ls.GetSize();
	if (!nSize)
		return;
	CLayer* pLayer = m_ls[nSize - 1];
	if (ID_DRAW_DRAG == m_nSelect)
	{//�»���ͼ��������ƶ�����ʹ����ʱDC���⻭��Ƶ������
		int i = 0;
		while (i<nSize)
		{
			pLayer = m_ls[i];
			if (pLayer->Track(point))
			{
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
				return;
			}

			++i;
		}
		return;
	}
	CClientDC dc(this);

	pLayer->OnMouseMove(nFlags, point, &dc);

	CView::OnMouseMove(nFlags, point);
}


//��ɫѡ��
void CDrawView::OnDrawColor()
{
	CColorDialog dlg;
	if (IDCANCEL == dlg.DoModal())
		return;
	CLayer* pLayer = NULL;
	int i = 0, nSize = m_ls.GetSize();
	COLORREF cl = dlg.GetColor();
	while (i<nSize)
	{
		pLayer = m_ls[i++];
		if (STU_SELECT == pLayer->m_nStat)
			pLayer->m_clText = cl;

	}
	m_clText = cl;
	Invalidate();
}