#if !defined(AFX_OBSCRIPTERRORVIEW_H__41F19D94_176A_4B70_95D1_E8B10A776D10__INCLUDED_)
#define AFX_OBSCRIPTERRORVIEW_H__41F19D94_176A_4B70_95D1_E8B10A776D10__INCLUDED_


class CObScptView;


class CObScriptErrorView : public CFormView {
  DECLARE_DYNCREATE(CObScriptErrorView);

protected:

  CObScptView*	m_pScriptView;
  bool          m_HasDblClick;


protected:

  CObScriptErrorView();
  virtual ~CObScriptErrorView();



public:

  void ClearErrors (void);
  void AddError    (CObScriptError* pError);
  void AddErrors   (CObScriptErrorArray& Errors);
  void AddMessage  (const char* pString, ...);

  CObScriptError* FindErrorFromLine (const int Line);

  void SetScriptView (CObScptView* pView) { m_pScriptView = pView; }

  //{{AFX_DATA(CObScriptErrorView)
  enum { IDD = IDD_SCRIPTERROR_VIEW };
  CRichEditCtrl	m_ErrorText;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObScriptErrorView)
public:
  virtual void OnInitialUpdate();
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL


protected:
	
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObScriptErrorView)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDblclkErrortext(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnMsgfilterErrortext(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
