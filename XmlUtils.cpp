#include "stdafx.h"
#include "XmlUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CXmlUtils::CXmlUtils()
{
}

CXmlUtils::~CXmlUtils()
{
}


CString CXmlUtils::GetXml(MSXML2::IXMLDOMDocument3Ptr pxmlDocument)
{
	TCHAR* pBuffer = NULL;

	std::string str = bstr2a(pxmlDocument->xml);
	if (str.length() > 0)
	{
		pBuffer = new TCHAR[str.length() + 1];
		_stprintf(pBuffer, _T("%s"), str.c_str());
	}

	CString ret(pBuffer);
	delete(pBuffer);
	return ret;
}

std::string CXmlUtils::bstr2a(const BSTR& cmd)
{
	int n = SysStringLen(cmd); // length of input
	char* p = NULL;
	char buf[4];
	if (n < 4) {
		p = buf;
		memset(buf, 0, sizeof(buf));
	}
	else {
		p = new char[n + 1];
		p[n] = 0;
	}
	for (int i = 0; i < n; i++) {
		p[i] = (char)cmd[i];
	}

	std::string rv(p);

	if (p != buf) {
		delete p;
	}
	return rv;
}

void CXmlUtils::AddNode(MSXML2::IXMLDOMElementPtr &pXMLChild, MSXML2::IXMLDOMDocument3Ptr pxmlDocument, MSXML2::IXMLDOMElementPtr pParent, CString sName, CString value)
{
	BSTR bstr = sName.AllocSysString();
	pXMLChild = pxmlDocument->createElement(bstr); //Create first child element
	pXMLChild->Puttext(_bstr_t(value));    //Set the element value
	pXMLChild = pParent->appendChild(pXMLChild);
	::SysFreeString(bstr);
}

MSXML2::IXMLDOMNodePtr CXmlUtils::FindChild(MSXML2::IXMLDOMNodePtr node, LPCTSTR szName, UINT index)
{
	if (node->firstChild == NULL)
		return NULL;

	int i = 0;
	MSXML2::IXMLDOMNodePtr tmp = node->firstChild;
	while (tmp)
	{
		std::string str = bstr2a(tmp->GetnodeName()).c_str();
		if (str == szName)
		{
			if (i == index)
				break;
			else
				i++;
		}
		tmp = tmp->nextSibling;
	}
	return tmp;
}

CString CXmlUtils::FindChildValue(MSXML2::IXMLDOMNodePtr node, LPCTSTR szName, UINT index)
{
	CString ret = "";

	if (MSXML2::IXMLDOMNodePtr pTemp = FindChild(node, szName, index))
	{
		if (pTemp->firstChild)
			ret = CString(pTemp->firstChild->nodeValue);

		pTemp.Release();
	}

	return ret;
}
