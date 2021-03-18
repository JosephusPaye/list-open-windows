#include "headers.h"

int getProcessName(int pid, wchar_t *name) {
  HANDLE processHandle = NULL;

  processHandle =
      OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

  if (processHandle != NULL) {
    if (GetModuleFileNameEx(processHandle, NULL, name, MAX_STRING_LENGTH) ==
        0) {
      return 1;
    } else {
      return 0;
    }

    CloseHandle(processHandle);
  } else {
    return 0;
  }

  return 0;
}

/**
 * Get the handle of the last visible active popup of the window with the given
 * handle.
 *
 * @param  hwnd The window handle
 * @return      The handle of the last visible active popup, or NULL
 */
static HWND getLastVisibleActivePopUpOfWindow(HWND hwnd) {
  while (true) {
    const HWND h = GetLastActivePopup(hwnd);

    if (IsWindowVisible(h)) {
      return h;
    } else if (h == hwnd) {
      return NULL;
    }

    hwnd = h;
  }
}

/**
 * Check if the window with the given handle is cloaked. Cloaked windows are
 * invisible background UWP apps, apps on other virtual desktops, etc.
 *
 * See https://stackoverflow.com/a/43959512,
 * https://stackoverflow.com/a/33577647
 *
 * @param  hwnd The window handle
 * @return      true if the window is cloaked, false otherwise
 */
static bool isCloakedWindow(HWND hwnd) {
  int CloakedVal;
  HRESULT hRes = DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &CloakedVal,
                                       sizeof(CloakedVal));

  if (hRes != S_OK) {
    CloakedVal = 0;
  }

  return CloakedVal ? true : false;
}

/**
 * Determine if the window with the given handle would appear in the Alt+Tab
 * list.
 *
 * @param  hwnd The window handle
 * @return      true if the window would appear in Alt+Tab list, false otherwise
 */
static bool isAltTabWindow(HWND hwnd) {
  if (GetShellWindow() == hwnd) {
    return false;
  }

  if (isCloakedWindow(hwnd)) {
    return false;
  }

  const LONG ex = GetWindowLong(hwnd, GWL_EXSTYLE);

  if (ex & WS_EX_TOOLWINDOW) {
    return false;
  }

  const HWND hRoot = GetAncestor(hwnd, GA_ROOTOWNER);
  const HWND hLast = getLastVisibleActivePopUpOfWindow(hRoot);

  if (hLast != hwnd) {
    return false;
  }

  return true;
}

/**
 * Get a list of handles of open windows that would appear in the Alt+Tab list.
 * The list is sorted by z-order, which is the order in which the windows
 * would appear in the Alt+Tab list.
 *
 * @return A list of open windows that would appear in Alt+Tab.
 */
static Hwnds enumAltTabWindows() {
  Hwnds hwnds;

  EnumWindows(
      [](HWND h, LPARAM lParam) -> BOOL {
        Hwnds &hs = *reinterpret_cast<Hwnds *>(lParam);

        if (isAltTabWindow(h)) {
          hs.push_back(h);
        }

        return TRUE;
      },
      reinterpret_cast<LPARAM>(&hwnds));

  return hwnds;
}

/**
 * Get the z-order of the window with the given handle.
 *
 * @param  hwnd The window handle
 * @return      The z-order, or 0
 */
static int getZorder(HWND hwnd) {
  int z = 0;

  for (auto h = hwnd; h != NULL; h = GetWindow(h, GW_HWNDPREV)) {
    ++z;
  }

  return z;
}

static RECT getRect(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    return rect;
}

/**
 * Get a list of currently open windows. The list holds structs of type of
 * window_info_t.
 *
 * @return The list of currently open windows.
 */
WindowList listWindows() {
  const Hwnds hwnds = enumAltTabWindows();
  WindowList windows;

  for (const HWND hwnd : hwnds) {
    window_info_t window;
    window.handle = hwnd;
    window.zOrder = getZorder(hwnd);
    RECT rect = getRect(hwnd);
    window.rectLeft = rect.left;
    window.rectRight = rect.right;
    window.rectTop = rect.top;
    window.rectBottom = rect.bottom;
    GetClassName(hwnd, window.className, MAX_STRING_LENGTH);
    GetWindowText(hwnd, window.caption, MAX_STRING_LENGTH);
    GetWindowThreadProcessId(hwnd, &window.processId);
    getProcessName(window.processId, window.processPath);

    windows.push_back(window);
  }

  return windows;
}
