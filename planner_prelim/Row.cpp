#include "stdafx.h"
#include "Row.h"

CRow::CRow(CString String1, CString String2, CString String3, CString String4,
	CString String5, CString String6, CString String7)
{

	m_Strings[0] = String1;
	m_Strings[1] = String2;
	m_Strings[2] = String3;
	m_Strings[3] = String4;
	m_Strings[4] = String5;
	m_Strings[5] = String6;
	m_Strings[6] = String7;


}


CString* CRow::ReturnDataOfIndex(int Index)
{

	return &m_Strings[Index];

}