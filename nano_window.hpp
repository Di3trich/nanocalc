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
    const int ROWS = 25;
    const int COLS = 10;
    Calc calc;

public:
    static HWND edit;
    static HWND button;
    static HWND hTrack;
    static HWND vTrack;
    static HWND *hLabel;
    static HWND *vLabel;
    static HWND *values;

    explicit NanoWindow(HWND _hwnd) : hwnd(_hwnd) {}

    void onCreate() {
        CreateWindow("static", "Formula / Valor:", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 10, 120, 20, hwnd,
                     (HMENU) ID_LABEL, NULL, NULL);
        edit = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 120, 10, 570, 20, hwnd,
                            (HMENU) ID_FORMULA,
                            NULL, NULL);
        button = CreateWindow("button", "Insertar", WS_VISIBLE | WS_CHILD, 700, 10, 80, 20, hwnd, (HMENU) ID_INSERT,
                              NULL, NULL);
        vTrack = CreateWindow(TRACKBAR_CLASS, "Trackbar Control", WS_CHILD | WS_VISIBLE | TBS_VERT | TBS_TOP, 755, 50,
                              35, 520,
                              hwnd, (HMENU) ID_VTRACK, NULL, NULL);
        hTrack = CreateWindow(TRACKBAR_CLASS, "Trackbar Control", WS_CHILD | WS_VISIBLE | TBS_TOP, 40, 565, 720, 35,
                              hwnd, (HMENU) ID_VTRACK, NULL, NULL);

        SendMessage(hTrack, TBM_SETRANGE, TRUE, MAKELONG(0, 99));
        SendMessage(vTrack, TBM_SETRANGE, TRUE, MAKELONG(0, 39));

        vLabel = new HWND[ROWS];
        hLabel = new HWND[COLS];
        values = new HWND[ROWS * COLS];

        for (int i = 0; i < ROWS; i++) {
            vLabel[i] = CreateWindow("static", "00", WS_CHILD | WS_VISIBLE | SS_SUNKEN | SS_CENTER | SS_CENTERIMAGE, 10,
                                     i * 20 + 60, 41, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
            for (int j = 0; j < COLS; j++) {
                if (!i) {
                    hLabel[j] = CreateWindow("static", "ABDGH",
                                             WS_CHILD | WS_VISIBLE | SS_SUNKEN | SS_CENTER | SS_CENTERIMAGE,
                                             j * 70 + 50, 41, 71, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
                }
                values[i * COLS + j] = CreateWindow("edit", "",
                                                  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT,
                                                  j * 70 + 50, i * 20 + 60, 71, 21, hwnd, (HMENU) ID_FORMULA, NULL,
                                                  NULL);
            }
        }
        onVTrack();
        onHTrack();

        calc.setCell("a999", "34");
        calc.setCell("a1000", "(5+5)*3+a999");
        auto res = calc.getCellValue("a1000");
        std::cout << res.first << ' ' << res.second << std::endl;
    }

    void executeEvent(int lo, int hi) {
        if (lo == ID_INSERT && hi == BN_CLICKED) return onSetTitle();
    }

    void onSetTitle() {

    }

    void onVTrack() {
        LRESULT pos = SendMessageW(vTrack, TBM_GETPOS, 0, 0);
        char txt[100] = {};
        for (int i = 0; i < ROWS; i++) {
            sprintf(txt, "%d", (int) pos * ROWS + i + 1);
            SetWindowText(vLabel[i], txt);
        }
    }

    void onHTrack() {
        LRESULT pos = SendMessageW(hTrack, TBM_GETPOS, 0, 0);
        char txt[100] = {};
        for (int i = 0; i < COLS; i++) {
            int n = (int) pos * COLS + i + 1, p = 0;
            while (n > 0) {
                txt[p++] = (char) ('A' + --n % 26);
                n /= 26;
            }
            for (int j = 0; j + j < p; j++) {
                char c = txt[j];
                txt[j] = txt[p - j - 1];
                txt[p - j - 1] = c;
            }
            txt[p] = '\0';
            SetWindowText(hLabel[i], txt);
        }
    }
};

HWND NanoWindow::edit = NULL;
HWND NanoWindow::button = NULL;
HWND NanoWindow::vTrack = NULL;
HWND NanoWindow::hTrack = NULL;
HWND *NanoWindow::hLabel = NULL;
HWND *NanoWindow::vLabel = NULL;
HWND *NanoWindow::values = NULL;

#endif