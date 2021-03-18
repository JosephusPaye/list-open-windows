export interface WindowInfo {
    /**
     * The window handle (HWND)
     */
    handle: number;

    /**
     * The window bounding box minX position
     */
    rectLeft: number;

    /**
     * The window bounding box maxX position
     */
    rectRight: number;

    /**
     * The window bounding box minY position
     */
    rectTop: number;

    /**
     * The window bounding box maxY position
     */
    rectBottom: number;


    /**
     * The window position in z-order
     */
    zOrder: number;

    /**
     * The window class name, as retrieved from [GetClassName](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname)
     */
    className: string;

    /**
     * The window title/caption, as retrieved from [GetWindowText](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta)
     */
    caption: string;

    /**
     * The id of the thread that the window belongs to, as retrieved from [GetWindowThreadProcessId](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid)
     */
    processId: number;

    /**
     * The path to the executable of the process that the window belongs to, as retrieved from [GetModuleFileNameEx](https://docs.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getmodulefilenameexa)
     */
    processPath: string;
}

/**
 * Get the list of currently open windows.
 */
export function listOpenWindows(): WindowInfo[];
