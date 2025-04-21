#pragma once

#include "pch.h"
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>  // For CListView

class CPhoneNumbersView : public CListView
{
protected:
    CPhoneNumbersView();

public:
    // Document accessor (optional if you're using Doc/View)
    class CPhoneBookDoc* GetDocument();

    // Overrides
public:
    virtual void OnInitialUpdate();     // Called first time after creation
    virtual void DoDataExchange(CDataExchange* pDX); // If you plan to bind controls
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual void OnDraw(CDC* pDC);      // Drawing code (optional)

    // Implementation
public:
    virtual ~CPhoneNumbersView();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()
};
