#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
class Switcher  {

public:

    static void setup();
    static void setupAccount();

    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
    {
        char class_name[80];
        char title[80];
        GetWindowTextA(hwnd, title, sizeof(title) / sizeof(char));
        //std::cout << "Window title: " << title << std::endl;

        std::string strTitle = std::string(title);
        //std::cout << "Window title: " << strTitle << std::endl;
        std::string toFind = *reinterpret_cast<std::string*>(lParam);
        if (strTitle.find(toFind) != std::string::npos) {
            //std::cout << "Found the nigga " << toFind << std::endl;
            WINDOWPLACEMENT place;
            GetWindowPlacement(hwnd, &place);

            switch (place.showCmd)
            {
            case SW_SHOWMAXIMIZED:
                ShowWindow(hwnd, SW_SHOWMAXIMIZED);
                break;
            case SW_SHOWMINIMIZED:
                ShowWindow(hwnd, SW_RESTORE);
                break;
            default:
                ShowWindow(hwnd, SW_NORMAL);
                break;
            }
            SetForegroundWindow(hwnd);
            SetActiveWindow(hwnd);
            SetFocus(hwnd);
        }

        return TRUE;
    }
};