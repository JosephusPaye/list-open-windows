export interface WindowInfo {
    handle: number;
    zOrder: number;
    className: string;
    caption: string;
    processId: number;
    processPath: string;
}

/**
 * Get the list of currently open windows.
 */
export function listOpenWindows(): WindowInfo[];
