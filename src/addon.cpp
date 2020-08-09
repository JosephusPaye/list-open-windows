#include "headers.h"

/**
 * Initialize the Node module by registering all native functions wrappers.
 *
 * @param  env     The napi env
 * @param  exports The module exports object, for population
 * @return         The populated exports object
 */
napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value listWindowsFn, switchToWindowFn;

  // Create the module.listWindows() function
  status =
      napi_create_function(env, NULL, 0, jsListWindows, NULL, &listWindowsFn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL,
                     "Failed to wrap native function 'jsListWindows'");
  }

  // Export the module.listWindows()
  status = napi_set_named_property(env, exports, "listWindows", listWindowsFn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to export function 'listWindows'");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
