#include "darktheme_win.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>

void setDarkTitleBar(WId windowId)
{
    const int DWMWA_USE_IMMERSIVE_DARK_MODE = 20;
    BOOL dark = TRUE;
    DwmSetWindowAttribute(
        (HWND)windowId,
        DWMWA_USE_IMMERSIVE_DARK_MODE,
        &dark,
        sizeof(dark)
    );
}

#else
// 在非Windows平台上，提供一个空函数体
void setDarkTitleBar(WId) {}
#endif