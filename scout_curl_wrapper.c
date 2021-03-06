/*
 * Scout APM extension for PHP
 *
 * Copyright (C) 2019-
 * For license information, please see the LICENSE file.
 */

#include "zend_scoutapm.h"

#if HAVE_SCOUT_CURL
#include <curl/curl.h>
#include "scout_extern.h"

ZEND_NAMED_FUNCTION(scoutapm_curl_setopt_handler)
{
    zval *zid, *zvalue;
    zend_long options;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_RESOURCE(zid)
            Z_PARAM_LONG(options)
            Z_PARAM_ZVAL(zvalue)
    ZEND_PARSE_PARAMETERS_END();

    if (options == CURLOPT_URL) {
        record_arguments_for_call(unique_resource_id(SCOUT_WRAPPER_TYPE_CURL, zid), 1, zvalue);
    }

    SCOUT_INTERNAL_FUNCTION_PASSTHRU();
}

ZEND_NAMED_FUNCTION(scoutapm_curl_exec_handler)
{
    int handler_index;
    double entered = scoutapm_microtime();
    zval *resource_id;
    const char *called_function;
    zend_long recorded_arguments_index;

    called_function = determine_function_name(execute_data);

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_RESOURCE(resource_id)
    ZEND_PARSE_PARAMETERS_END();

    handler_index = handler_index_for_function(called_function);

    recorded_arguments_index = find_index_for_recorded_arguments(unique_resource_id(SCOUT_WRAPPER_TYPE_CURL, resource_id));

    if (recorded_arguments_index < 0) {
        scoutapm_default_handler(INTERNAL_FUNCTION_PARAM_PASSTHRU);
        return;
    }

    original_handlers[handler_index](INTERNAL_FUNCTION_PARAM_PASSTHRU);

    record_observed_stack_frame(
        called_function,
        entered,
        scoutapm_microtime(),
        SCOUTAPM_G(disconnected_call_argument_store)[recorded_arguments_index].argc,
        SCOUTAPM_G(disconnected_call_argument_store)[recorded_arguments_index].argv
    );
}
#endif
