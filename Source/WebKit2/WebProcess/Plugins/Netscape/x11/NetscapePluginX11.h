/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2010 University of Szeged
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NetscapePluginX11_h
#define NetscapePluginX11_h

#if PLUGIN_ARCHITECTURE(X11) && ENABLE(NETSCAPE_PLUGIN_API)

#include "NetscapePluginUnix.h"
#include <WebCore/XUniqueResource.h>

namespace WebKit {

class NetscapePlugin;

class NetscapePluginX11 final : public NetscapePluginUnix {
public:
    static std::unique_ptr<NetscapePluginX11> create(NetscapePlugin&);
    NetscapePluginX11(NetscapePlugin&, Display*);
#if PLATFORM(GTK)
    NetscapePluginX11(NetscapePlugin&, Display*, uint64_t windowID);
#endif
    virtual ~NetscapePluginX11();

private:
    virtual NPWindowType windowType() const override;
    virtual void* window() const override;
    virtual NPSetWindowCallbackStruct* windowSystemInfo() override { return &m_setWindowCallbackStruct; }
    virtual void geometryDidChange() override;
    virtual void visibilityDidChange() override;
    virtual void paint(WebCore::GraphicsContext&, const WebCore::IntRect&) override;
    virtual bool handleMouseEvent(const WebMouseEvent&) override;
    virtual bool handleWheelEvent(const WebWheelEvent&) override;
    virtual bool handleMouseEnterEvent(const WebMouseEvent&) override;
    virtual bool handleMouseLeaveEvent(const WebMouseEvent&) override;
    virtual bool handleKeyboardEvent(const WebKeyboardEvent&) override;
    virtual void setFocus(bool) override;

    NetscapePlugin& m_plugin;
    Display* m_pluginDisplay { nullptr };
    WebCore::XUniquePixmap m_drawable;
    NPSetWindowCallbackStruct m_setWindowCallbackStruct;
#if PLATFORM(GTK)
    uint64_t m_windowID { 0 };
    unsigned long m_npWindowID { 0 };
    GtkWidget* m_platformPluginWidget { nullptr };
#endif
};
} // namespace WebKit

#endif // PLUGIN_ARCHITECTURE(X11) && ENABLE(NETSCAPE_PLUGIN_API)

#endif // NetscapePluginX11_h
