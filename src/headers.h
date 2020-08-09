#pragma once

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0601
#define MAX_STRING_LENGTH 256

#include <dwmapi.h>
#include <node_api.h>
#include <psapi.h>
#include <stdint.h>
#include <vector>
#include <windows.h>
#pragma comment(lib, "dwmapi.lib")

using Hwnds = std::vector<HWND>;

typedef struct {
  HWND handle;
  int zOrder;
  wchar_t className[MAX_STRING_LENGTH];
  wchar_t caption[MAX_STRING_LENGTH];
  DWORD processId;
  wchar_t processPath[MAX_STRING_LENGTH];
} window_info_t;

using WindowList = std::vector<window_info_t>;

extern WindowList listWindows();
extern napi_value jsListWindows(napi_env env, napi_callback_info info);
