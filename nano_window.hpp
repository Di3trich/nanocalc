#ifndef __NANO_WINDOW_HPP__
#define __NANO_WINDOW_HPP__

#include <windows.h>
#include <commctrl.h>
#include <iostream>

#include "resource.hpp"
#include "calc.hpp"

class NanoWindow {
private:
    HWND hwnd;

public:
    static HWND edit;
    static HWND button;
    static HWND hTrack;
    static HWND vTrack;

    explicit NanoWindow(HWND _hwnd) : hwnd(_hwnd) {}

    void onCreate() {
        CreateWindow("static", "Formula / Valor:", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 10, 120, 20, hwnd,
                     (HMENU) ID_LABEL, NULL, NULL);
        edit = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 10, 570, 20, hwnd, (HMENU) ID_FORMULA,
                            NULL, NULL);
        button = CreateWindow("button", "Insertar", WS_VISIBLE | WS_CHILD, 700, 10, 80, 20, hwnd, (HMENU) ID_INSERT,
                              NULL, NULL);
        vTrack = CreateWindow(TRACKBAR_CLASS, "Trackbar Control", WS_CHILD | WS_VISIBLE | TBS_VERT, 0, 30, 30, 520,
                              hwnd, (HMENU) ID_VTRACK, NULL, NULL);
        hTrack = CreateWindow(TRACKBAR_CLASS, "Trackbar Control", WS_CHILD | WS_VISIBLE | TBS_TOP, 20, 540, 770, 30,
                              hwnd, (HMENU) ID_VTRACK, NULL, NULL);

        SendMessage(hTrack, TBM_SETRANGE, TRUE, MAKELONG(0, 200));
        SendMessage(hTrack, TBM_SETPAGESIZE, 0, 10);
        SendMessage(hTrack, TBM_SETTICFREQ, 10, 0);
        SendMessage(hTrack, TBM_SETPOS, FALSE, 0);

        Calc c;
        c.setCell(0, "2+3/3+1");
        auto res = c.evaluateSingle(0);
        std::cout<<res.second<<std::endl;
        auto other = c.evaluateSingle(0);
        std::cout<<other.second<<std::endl;
    }

    void executeEvent(int lo, int hi) {
        if (lo == ID_INSERT && hi == BN_CLICKED) return onSetTitle();
    }

    void onSetTitle() {

    }

    void onVTrack() {
        LRESULT pos = SendMessageW(vTrack, TBM_GETPOS, 0, 0);
        std::cout << pos << std::endl;
    }

    void onHTrack() {
        LRESULT pos = SendMessageW(hTrack, TBM_GETPOS, 0, 0);
        std::cout << pos << std::endl;
    }

    void paint() {

    }
};

HWND NanoWindow::edit = NULL;
HWND NanoWindow::button = NULL;
HWND NanoWindow::vTrack = NULL;
HWND NanoWindow::hTrack = NULL;

#endif