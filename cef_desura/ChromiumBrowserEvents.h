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

#ifdef WIN32
#define OVERRIDE override
#else
#define OVERRIDE
#endif


class ChromiumEventInfoI
{
public:
	virtual ChromiumDLL::ChromiumBrowserEventI* GetCallback()=0;
	virtual ChromiumDLL::ChromiumRendererEventI* GetRenderCallback()=0;
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
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> parentBrowser,
                               CefRefPtr<CefFrame> frame,
                               const CefString& target_url,
                               const CefString& target_frame_name,
                               const CefPopupFeatures& popupFeatures,
                               CefWindowInfo& windowInfo,
                               CefRefPtr<CefClient>& client,
                               CefBrowserSettings& settings,
							   bool* no_javascript_access) OVERRIDE;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// LifeSpanHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class LoadHandler : public CefLoadHandler, public virtual ChromiumEventInfoI
{
public:
	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) OVERRIDE;
	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) OVERRIDE;
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             ErrorCode errorCode,
                             const CefString& errorText,
							 const CefString& failedUrl) OVERRIDE;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// RequestHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class RequestHandler : public CefRequestHandler, public virtual ChromiumEventInfoI
{
public:
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool isRedirect) OVERRIDE;

	//TODO
	//virtual bool GetDownloadHandler(CefRefPtr<CefBrowser> browser, const CefString& mimeType, const CefString& fileName, int64 contentLength, CefRefPtr<CefDownloadHandler>& handler, const CefString& url) OVERRIDE;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// DisplayHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class DisplayHandler : public CefDisplayHandler, public virtual ChromiumEventInfoI
{
public:
	virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line) OVERRIDE;
	virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value) OVERRIDE;
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;
	virtual bool OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text) OVERRIDE;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// KeyboardHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class KeyboardHandler : public CefKeyboardHandler, public virtual ChromiumEventInfoI
{
public:
	virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser,
                            const CefKeyEvent& event,
							CefEventHandle os_event) OVERRIDE;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// JSDialogHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class JSDialogHandler : public CefJSDialogHandler, public virtual ChromiumEventInfoI
{
public:

};

/////////////////////////////////////////////////////////////////////////////////////////////
/// RenderHandler
/////////////////////////////////////////////////////////////////////////////////////////////

class RenderHandler : public CefRenderHandler, public virtual ChromiumEventInfoI
{
public:
	virtual void OnPaint(CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList& dirtyRects,
		const void* buffer,
		int width, int height) OVERRIDE;

	virtual void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor) OVERRIDE;
	virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE;
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
	, public RenderHandler
{
public:
	ChromiumBrowserEvents(ChromiumBrowser* pParent);

	void setCallBack(ChromiumDLL::ChromiumBrowserEventI* cbe);
	void setCallBack(ChromiumDLL::ChromiumRendererEventI* cbe);

	void setParent(ChromiumBrowser* parent);

	virtual ChromiumDLL::ChromiumBrowserEventI* GetCallback();
	virtual ChromiumDLL::ChromiumRendererEventI* GetRenderCallback();

	virtual void SetBrowser(CefRefPtr<CefBrowser> browser);
	virtual CefRefPtr<CefBrowser> GetBrowser();
	virtual void setContext(CefRefPtr<CefV8Context> context);

	virtual CefRefPtr<CefLifeSpanHandler>	GetLifeSpanHandler()	{ return (CefLifeSpanHandler*)this; }
	virtual CefRefPtr<CefLoadHandler>		GetLoadHandler()		{ return (CefLoadHandler*)this; }
	virtual CefRefPtr<CefRequestHandler>	GetRequestHandler()		{ return (CefRequestHandler*)this; }
	virtual CefRefPtr<CefDisplayHandler>	GetDisplayHandler()		{ return (CefDisplayHandler*)this; }
	virtual CefRefPtr<CefKeyboardHandler>	GetKeyboardHandler()	{ return (CefKeyboardHandler*)this; }
	virtual CefRefPtr<CefJSDialogHandler>	GetJSDialogHandler()	{ return (CefJSDialogHandler*)this; }
	virtual CefRefPtr<CefRenderHandler>		GetRenderHandler()		{ return (RenderHandler*)this; }

private:
	CefRefPtr<CefBrowser> m_Browser;
	ChromiumBrowser* m_pParent;
	ChromiumDLL::ChromiumBrowserEventI* m_pEventCallBack;
	ChromiumDLL::ChromiumRendererEventI* m_pRendereEventCallBack;

	IMPLEMENT_REFCOUNTING(ChromiumBrowserEvents);
};


#endif //DESURA_CHROMIUMBROWSEREVENTS_H
