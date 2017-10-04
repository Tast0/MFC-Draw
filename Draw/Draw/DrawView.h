
// DrawView.h : CDrawView 类的接口
//

#pragma once
#include "Layer.h"

class CDrawView : public CView
{
protected: // 仅从序列化创建
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// 特性
public:

	CDrawDoc* GetDocument() const;

// 操作
public:
	int m_nSelect;  //当前要绘制图层的种类
	CArray<CLayer*,CLayer*> m_ls;
	CPoint m_ptDrag;
	COLORREF m_clText, m_clBack;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawDrag();
	afx_msg void OnDrawEllip();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPenc();
	afx_msg void OnUpdateDrawDrag(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawEllip(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawPenc(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawColor();
};

#ifndef _DEBUG  // DrawView.cpp 中的调试版本
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }
#endif

