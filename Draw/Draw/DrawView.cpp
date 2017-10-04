
// DrawView.cpp : CDrawView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CDrawView 构造/析构

CDrawView::CDrawView()
{
	// TODO:  在此处添加构造代码

}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawView 绘制

void CDrawView::OnDraw(CDC* pDC)
{	//在视图类中OnDraw函数是WM_PAINT消息的回调函数
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i = 0, nSize = m_ls.GetSize();
	CLayer *pLayer = NULL;
	while (i<nSize) //谁new的对象，基类指针调用抽象函数时就会自动转入谁的派生类
	{
		pLayer = m_ls[i++];
		pLayer->OnDraw(pDC);
	}

	// TODO: add draw code for native data here
}


// CDrawView 打印


void CDrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CDrawView 诊断

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView 消息处理程序


void CDrawView::OnDrawDrag()
{//单击按钮为设置当前类型为拖放
	m_nSelect = ID_DRAW_DRAG;
}

void CDrawView::OnDrawEllip()
{//当前类型为椭圆
	m_nSelect = ID_DRAW_ELLIP;

}

void CDrawView::OnDrawLine()
{//当前为线段
	m_nSelect = ID_DRAW_LINE;
}

void CDrawView::OnDrawPenc()
{//铅笔线
	m_nSelect = ID_DRAW_PENC;

}

void CDrawView::OnUpdateDrawDrag(CCmdUI* pCmdUI)
{//当前按钮是拖放时，该按钮显示选择状态
	pCmdUI->SetRadio(ID_DRAW_DRAG == m_nSelect);
}

void CDrawView::OnUpdateDrawEllip(CCmdUI* pCmdUI)
{//当前按钮是椭圆时，该按钮显示选择状态
	pCmdUI->SetRadio(ID_DRAW_ELLIP == m_nSelect);
}

void CDrawView::OnUpdateDrawLine(CCmdUI* pCmdUI)
{//当前按钮是线段时，该按钮显示选择状态
	pCmdUI->SetRadio(ID_DRAW_LINE == m_nSelect);
}

void CDrawView::OnUpdateDrawPenc(CCmdUI* pCmdUI)
{//当前按钮是铅笔线时，该按钮显示选择状态
	pCmdUI->SetCheck(ID_DRAW_PENC == m_nSelect);
}

//WM_LBUTTONDOWN的消息映射函数
void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CLayer *pLayer = NULL;
	if (ID_DRAW_DRAG == m_nSelect)
	{//将点中图层设为选中状态
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
	//根据指定的类型，在堆空间里申请对应的图层对象
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
	{//根据当前类型创建一个新图层（新图层会覆盖旧图层）
		pLayer->m_clText = m_clText;
		pLayer->OnLButtonDown(nFlags, point);
		m_ls.Add(pLayer);//添加新图层
	}
	CView::OnLButtonDown(nFlags, point);
}
//添加WM_LBUTTONUP映射函数
void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	int nSize = m_ls.GetSize();
	if (!nSize)
		return;
	CLayer* pLayer = NULL;

	if (ID_DRAW_DRAG == m_nSelect)
	{//完成图层绘制
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
	}//完成图层拖放
	pLayer = m_ls[nSize - 1];
	pLayer->OnLButtonUp(nFlags, point);
	Invalidate(FALSE);
	CView::OnLButtonUp(nFlags, point);
}
//添加WM_MOUSEMOVE映射函数
void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{

	int nSize = m_ls.GetSize();
	if (!nSize)
		return;
	CLayer* pLayer = m_ls[nSize - 1];
	if (ID_DRAW_DRAG == m_nSelect)
	{//新绘制图层鼠标光标移动过程使用临时DC避免画面频繁更新
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


//颜色选择
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