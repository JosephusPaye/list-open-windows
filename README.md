# List Open Windows

A native Node.js module for listing the currently open application windows on Windows. Can be paired with [activate-previous-window](https://github.com/JosephusPaye/activate-previous-window) to create a task switcher.

## Why

It's easy enough to get a list of open windows using the [EnumWindows](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumdesktopwindows) function. The problem is that EnumWindows returns [a lot of other things that are not what you would expect](https://stackoverflow.com/questions/7277366/why-does-enumwindows-return-more-windows-than-i-expected): tooltips, background windows, hidden windows, etc. This module uses a few heuristics to filter the list from EnumWindows to include only what you would see when you press <kbd>Alt</kbd>+<kbd>Tab</kbd>.

## Installation

```
npm install @josephuspaye/list-open-windows --save
```

## Usage

```js
const { listOpenWindows } = require('@josephuspaye/list-open-windows');

// Get the list of open windows
const windows = listOpenWindows();

// Do something with the list
windows.forEach(console.log);
```

`listOpenWindows()` takes no parameter and returns a list of window objects with the following properties:

- `handle` (number) the window handle (HWND)
- `zOrder` (number) the window position in z-order
- `className` (string) the window class name, as retrieved from [GetClassName](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname)
- `caption` (string) the window title/caption, as retrieved from [GetWindowText](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta)
- `processId` (string) the id of the thread that the window belongs to, as retrieved from [GetWindowThreadProcessId](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid)
- `processPath` (string) the path to the executable of the process that the window belongs to, as retrieved from [GetModuleFileNameEx](https://docs.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getmodulefilenameexa)

## Licence

[MIT](LICENCE)
