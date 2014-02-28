///////////// Copyright 2010 DesuraNet. All rights reserved. /////////////
//
//   Project     : desura_libcef_dll_wrapper
//   File        : ChromiumBrowserEvents.h
//   Description :
//      [TODO: Write the purpose of ChromiumBrowserEvents.h.]
//
//   Created On: 7/1/2010 11:35:47 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

#ifndef DESURA_CHROMIUMBROWSEREVENTS_H
#define DESURA_CHROMIUMBROWSEREVENTS_H
#ifdef _WIN32
#pragma once
#endif

//#include "include/cef.h"
#include "ChromiumBrowserI.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_client.h"
#include "include/cef_browser.h"
#include "include/cef_load_handler.h"
#include "include/cef_menu_model.h"
#include "include/cef_request_handler.h"
#include "include/cef_display_handler.h"
#include "include/cef_jsdialog_handler.h"
#include "include/cef_keyboard_handler.h"
#include "include/cef_life_span_handler.h"

class ChromiumBrowser;


class ChromiumEventInfoI
{
public:
	virtual ChromiumDLL::ChromiumBrowserEventI* GetCallback()=0;
	virtual void SetBrowser(CefRefPtr<CefBrowser> browser)=0;
	virtual CefRefPtr<CefBrowser> GetBrowser()=0;
	virtual void setContext(CefRefPtr<CefV8Context> context)=0;
};

/////////////////////////////////////////////////////////////////////////////////////////////
/// LifeSpanHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class LifeSpanHandler : public CefLifeSpanHandler, public virtual ChromiumEventInfoI
{
public:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> parentBrowser,
                               CefRefPtr<CefFrame> frame,
                               const CefString& target_url,
                               const CefString& target_frame_name,
                               const CefPopupFeatures& popupFeatures,
                               CefWindowInfo& windowInfo,
                               CefRefPtr<CefClient>& client,
                               CefBrowserSettings& settings,
                               bool* no_javascript_access);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// LifeSpanHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class LoadHandler : public CefLoadHandler, public virtual ChromiumEventInfoI
{
public:
	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);
	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode);
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             ErrorCode errorCode,
                             const CefString& errorText,
                             const CefString& failedUrl);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// RequestHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class RequestHandler : public CefRequestHandler, public virtual ChromiumEventInfoI
{
public:
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool isRedirect);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// DisplayHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class DisplayHandler : public CefDisplayHandler, public virtual ChromiumEventInfoI
{
public:
	virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// KeyboardHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class KeyboardHandler : public CefKeyboardHandler, public virtual ChromiumEventInfoI
{
public:
	virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser,
                            const CefKeyEvent& event,
                            CefEventHandle os_event);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// JSDialogHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class JSDialogHandler : public CefJSDialogHandler, public virtual ChromiumEventInfoI
{
public:
	virtual bool OnJSAlert(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& message);
	virtual bool OnJSConfirm(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& message, bool& retval);
	virtual bool OnJSPrompt(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& message, const CefString& defaultValue, bool& retval, CefString& result);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// ChromiumBrowserEvents
/////////////////////////////////////////////////////////////////////////////////////////////

class ChromiumBrowserEvents : 
	public CefClient
	, public virtual ChromiumEventInfoI
	, public LifeSpanHandler
	, public LoadHandler
	, public RequestHandler
	, public DisplayHandler
	, public KeyboardHandler
	, public JSDialogHandler
{
public:
	ChromiumBrowserEvents(ChromiumBrowser* pParent);

	void setCallBack(ChromiumDLL::ChromiumBrowserEventI* cbe);
	void setParent(ChromiumBrowser* parent);

	virtual ChromiumDLL::ChromiumBrowserEventI* GetCallback();
	virtual void SetBrowser(CefRefPtr<CefBrowser> browser);
	virtual CefRefPtr<CefBrowser> GetBrowser();
	virtual void setContext(CefRefPtr<CefV8Context> context);

	virtual CefRefPtr<CefLifeSpanHandler>	GetLifeSpanHandler()	{ return (CefLifeSpanHandler*)this; }
	virtual CefRefPtr<CefLoadHandler>		GetLoadHandler()		{ return (CefLoadHandler*)this; }
	virtual CefRefPtr<CefRequestHandler>	GetRequestHandler()		{ return (CefRequestHandler*)this; }
	virtual CefRefPtr<CefDisplayHandler>	GetDisplayHandler()		{ return (CefDisplayHandler*)this; }
	virtual CefRefPtr<CefKeyboardHandler>	GetKeyboardHandler()	{ return (CefKeyboardHandler*)this; }
	virtual CefRefPtr<CefJSDialogHandler>	GetJSDialogHandler()	{ return (CefJSDialogHandler*)this; }

private:
	CefRefPtr<CefBrowser> m_Browser;
	ChromiumBrowser* m_pParent;
	ChromiumDLL::ChromiumBrowserEventI *m_pEventCallBack;

	IMPLEMENT_REFCOUNTING(ChromiumBrowserEvents);
};


#endif //DESURA_CHROMIUMBROWSEREVENTS_H
