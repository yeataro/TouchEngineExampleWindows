#pragma once

#include <string>
#include <atomic>
#include <TouchPlugIn/TouchPlugIn.h>
#include "Device.h"

class DocumentWindow
{
public:
    static HRESULT registerClass(HINSTANCE hInstance);
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    DocumentWindow(std::wstring path);
    ~DocumentWindow();
    const std::wstring getPath() const;
    void openWindow(HWND parent);
    HWND getWindow() const { return myWindow; };
    void didLoad() { myDidLoad = true; };
    void propertyLayoutDidChange();
    void render();
    void cancelFrame();
private:
    static wchar_t *WindowClassName;
    static void eventCallback(TPInstance *instance, TPEvent event, TPError error, int64_t time_value, int32_t time_scale, void * info);
    static void propertyValueCallback(TPInstance *instance, TPScope scope, int32_t group, int32_t index, void *info);
    void endFrame(int64_t time_value, int32_t time_scale, TPError error);
    TPInstance *myInstance;
    HWND myWindow;
    Device myDevice;
    std::atomic<bool> myDidLoad;
    std::atomic<bool> myInFrame;
    float myLastStreamValue;
};

