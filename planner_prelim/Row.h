#pragma once


class CRow
{
	CString m_Strings[7];
	int m_RowNumber;

public:

	CString* ReturnDataOfIndex(int Index);

	CRow(CString String1, CString String2, CString String3, CString String4, 
		CString String5, CString String6, CString String7);

	CRow() {}
	~CRow() {}
};

