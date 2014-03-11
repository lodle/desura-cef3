///////////// Copyright 2010 DesuraNet. All rights reserved. /////////////
//
//   Project     : desura_libcef_dll_wrapper
//   File        : MenuInfo.h
//   Description :
//      [TODO: Write the purpose of MenuInfo.h.]
//
//   Created On: 9/18/2010 10:01:48 AM
//   Created By:  <mailto:>
////////////////////////////////////////////////////////////////////////////

#ifndef DESURA_MENUINFO_H
#define DESURA_MENUINFO_H
#ifdef _WIN32
#pragma once
#endif

#include "ChromiumBrowserI.h"
//#include "include/cef.h"
#include "include/cef_menu_model.h"

class ChromiumMenuItem : public ChromiumDLL::ChromiumMenuItemI
{
public:
	ChromiumMenuItem(CefMenuModel::MenuItemType item);

	virtual int getAction();
	virtual int getType();
	virtual const char* getLabel();

	virtual bool isEnabled();
	virtual bool isChecked();

private:
	CefMenuModel::MenuItemType m_MenuItem;
};





#ifdef OS_WIN
	typedef HWND MenuHandle_t;
#else
	typedef void* MenuHandle_t;
#endif

/*==========================================================================*|
class ChromiumMenuInfo : public ChromiumDLL::ChromiumMenuInfoI
{
public:
	ChromiumMenuInfo(CefMenuModel::MenuInfo info, MenuHandle_t hwnd);

	virtual ChromiumDLL::ChromiumMenuInfoI::TypeFlags getTypeFlags();
	virtual ChromiumDLL::ChromiumMenuInfoI::EditFlags getEditFlags();

	virtual void getMousePos(int* x, int* y);

	virtual const char* getLinkUrl();
	virtual const char* getImageUrl();
	virtual const char* getPageUrl();
	virtual const char* getFrameUrl();
	virtual const char* getSelectionText();
	virtual const char* getMisSpelledWord();
	virtual const char* getSecurityInfo();

	virtual int getCustomCount();
	virtual ChromiumDLL::ChromiumMenuItemI* getCustomItem(size_t index);

	virtual int* getHWND();

private:
	std::vector<ChromiumMenuItem> m_vMenuItems;
	CefMenuModel::MenuInfo m_MenuInfo;
	MenuHandle_t m_Hwnd;
};
|*==========================================================================*/

#endif //DESURA_MENUINFO_H
