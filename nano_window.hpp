#ifndef __NANO_WINDOW_HPP__
#define __NANO_WINDOW_HPP__

#include <windows.h>
#include <map>

#include "resource.hpp"

class NanoWindow {
private:
    HWND hwnd;

public:
    static HWND edit;
    static HWND button;

    NanoWindow(HWND _hwnd) : hwnd(_hwnd) {}

    void onCreate() {
        CreateWindow("static", "Formula / Valor:", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 10, 120, 20, hwnd,
                     (HMENU) ID_LABEL, NULL, NULL);
        edit = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 10, 570, 20, hwnd, (HMENU) ID_FORMULA,
                            NULL, NULL);
        button = CreateWindow("button", "Insertar", WS_VISIBLE | WS_CHILD, 700, 10, 80, 20, hwnd, (HMENU) ID_INSERT,
                              NULL, NULL);
    }

    void executeEvent(int lo, int hi) {
        if (lo == ID_INSERT && hi == BN_CLICKED) return onSetTitle();
    }

    void onSetTitle() {
        char text[100];
        //GetWindowText(edit, text, 100);
        SetWindowText(edit, "hola mundo");
    }
};

HWND NanoWindow::edit = NULL;
HWND NanoWindow::button = NULL;

#endif