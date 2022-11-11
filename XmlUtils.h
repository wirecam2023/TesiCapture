#ifndef _XMLUTILS_H_
#define _XMLUTILS_H_

#include "msxml6.tlh"
#include <iostream>

class CXmlUtils
{
public:

	CXmlUtils();
	~CXmlUtils();

	static CString GetXml(MSXML2::IXMLDOMDocument3Ptr pxmlDocument);
	static std::string bstr2a(const BSTR& cmd);
	static void AddNode(MSXML2::IXMLDOMElementPtr &pXMLChild, MSXML2::IXMLDOMDocument3Ptr pxmlDocument, MSXML2::IXMLDOMElementPtr pParent, CString sName, CString value = "");

	static MSXML2::IXMLDOMNodePtr FindChild(MSXML2::IXMLDOMNodePtr node, LPCTSTR szName, UINT index = 0);
	static CString FindChildValue(MSXML2::IXMLDOMNodePtr node, LPCTSTR szName, UINT index = 0);
};

#endif //_XMLUTILS_H_