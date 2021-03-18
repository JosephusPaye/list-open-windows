#include "headers.h"

/**
 * An N-API function which wraps the native listWindows() function for use in
 * JS.
 *
 * @param  env  The napi environment
 * @param  info The napi arguments and callback info
 * @return      napi_value array, of currently open window objects
 */
napi_value jsListWindows(napi_env env, napi_callback_info info) {
  // The array of windows, a single window object and properties
  napi_value jsWindows, jsWindow, jsHandle, jsZOrder, jsClassName, jsCaption, jsRectLeft, jsRectBottom, jsRectRight, jsRectTop,
      jsProcessId, jsProcessPath;
  napi_status status;

  // Get list of open windows
  WindowList windows = listWindows();

  // const jsWindows = [];
  status = napi_create_array(env, &jsWindows);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to create array 'jsWindows'");
  }

  int i = 0;
  for (const window_info_t window : windows) {
    // const jsWindow = {}
    status = napi_create_object(env, &jsWindow);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create object 'jsWindow'");
    }

    // const jsHandle = ...
    status = napi_create_int32(env, (uint32_t)window.handle, &jsHandle);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create int 'jsHandle'");
    }

    // const jsZOrder = ...
    status = napi_create_int32(env, (uint32_t)window.zOrder, &jsZOrder);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create int 'jsZOrder'");
    }

  // const jsRectLeft = ...
    status = napi_create_int32(env, (uint32_t)window.rectLeft, &jsRectLeft);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create int 'jsRectLeft'");
    }
  // const jsRectRight = ...
    status = napi_create_int32(env, (uint32_t)window.rectRight, &jsRectRight);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create int 'jsRectRight'");
    }
  // const jsRectTop = ...
    status = napi_create_int32(env, (uint32_t)window.rectTop, &jsRectTop);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create int 'jsRectTop'");
    }
  // const jsRectBottom = ...
    status = napi_create_int32(env, (uint32_t)window.rectBottom, &jsRectBottom);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create int 'jsRectBottom'");
    }


    // const jsClassName = '...'
    status = napi_create_string_utf16(env, (char16_t *)window.className,
                                      NAPI_AUTO_LENGTH, &jsClassName);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create string 'jsClassName'");
    }

    // const jsCaption = '...'
    status = napi_create_string_utf16(env, (char16_t *)window.caption,
                                      NAPI_AUTO_LENGTH, &jsCaption);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create string 'jsCaption'");
    }

    // const jsProcessId = ...
    status = napi_create_int32(env, (uint32_t)window.processId, &jsProcessId);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create int 'jsProcessId'");
    }

    // const jsProcessPath = '...'
    status = napi_create_string_utf16(env, (char16_t *)window.processPath,
                                      NAPI_AUTO_LENGTH, &jsProcessPath);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Failed to create string 'jsProcessPath'");
    }

    // jsWindow.handle = jsHandle
    status = napi_set_named_property(env, jsWindow, "handle", jsHandle);
    if (status != napi_ok) {
      napi_throw_error(env, NULL,
                       "Failed to set property 'handle' on object 'jsWindow'");
    }

    // jsWindow.zOrder = jsZOrder
    status = napi_set_named_property(env, jsWindow, "zOrder", jsZOrder);
    if (status != napi_ok) {
      napi_throw_error(env, NULL,
                       "Failed to set property 'zOrder' on object 'jsWindow'");
    }

    status = napi_set_named_property(env, jsWindow, "rectLeft", jsRectLeft);
    if (status != napi_ok) {
        napi_throw_error(env, NULL,
                    "Failed to set property 'rectLeft' on object 'jsWindow'");
      }
    status = napi_set_named_property(env, jsWindow, "rectRight", jsRectRight);
      if (status != napi_ok) {
          napi_throw_error(env, NULL,
                      "Failed to set property 'rectRight' on object 'jsWindow'");
        }
    status = napi_set_named_property(env, jsWindow, "rectTop", jsRectTop);
      if (status != napi_ok) {
          napi_throw_error(env, NULL,
                      "Failed to set property 'rectTop' on object 'jsWindow'");
        }
    status = napi_set_named_property(env, jsWindow, "rectBottom", jsRectBottom);
        if (status != napi_ok) {
            napi_throw_error(env, NULL,
                        "Failed to set property 'rectBottom' on object 'jsWindow'");
          }
    // jsWindow.className = jsClassName
    status = napi_set_named_property(env, jsWindow, "className", jsClassName);
    if (status != napi_ok) {
      napi_throw_error(
          env, NULL, "Failed to set property 'className' on object 'jsWindow'");
    }

    // jsWindow.caption = jsCaption
    status = napi_set_named_property(env, jsWindow, "caption", jsCaption);
    if (status != napi_ok) {
      napi_throw_error(env, NULL,
                       "Failed to set property 'caption' on object 'jsWindow'");
    }

    // jsWindows[i] = jsWindow
    status = napi_set_element(env, jsWindows, i, jsWindow);
    if (status != napi_ok) {
      napi_throw_error(
          env, NULL,
          "Failed to insert object 'jsWindow' into array 'jsWindows'");
    }

    // jsWindow.processId = jsProcessId
    status = napi_set_named_property(env, jsWindow, "processId", jsProcessId);
    if (status != napi_ok) {
      napi_throw_error(
          env, NULL, "Failed to set property 'processId' on object 'jsWindow'");
    }

    // jsWindow.processPath = jsProcessPath
    status =
        napi_set_named_property(env, jsWindow, "processPath", jsProcessPath);
    if (status != napi_ok) {
      napi_throw_error(
          env, NULL,
          "Failed to set property 'processPath' on object 'jsWindow'");
    }

    i++;
  }

  return jsWindows;
}
