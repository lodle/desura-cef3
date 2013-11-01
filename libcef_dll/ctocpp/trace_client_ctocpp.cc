// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/ctocpp/trace_client_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

void CefTraceClientCToCpp::OnTraceDataCollected(const char* fragment,
    size_t fragment_size) {
  if (CEF_MEMBER_MISSING(struct_, on_trace_data_collected))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: fragment; type: simple_byaddr
  DCHECK(fragment);
  if (!fragment)
    return;

  // Execute
  struct_->on_trace_data_collected(struct_,
      fragment,
      fragment_size);
}

void CefTraceClientCToCpp::OnTraceBufferPercentFullReply(float percent_full) {
  if (CEF_MEMBER_MISSING(struct_, on_trace_buffer_percent_full_reply))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  struct_->on_trace_buffer_percent_full_reply(struct_,
      percent_full);
}

void CefTraceClientCToCpp::OnEndTracingComplete() {
  if (CEF_MEMBER_MISSING(struct_, on_end_tracing_complete))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  struct_->on_end_tracing_complete(struct_);
}


#ifndef NDEBUG
template<> long CefCToCpp<CefTraceClientCToCpp, CefTraceClient,
    cef_trace_client_t>::DebugObjCt = 0;
#endif

