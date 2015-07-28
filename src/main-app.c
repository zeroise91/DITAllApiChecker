/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "main-app.h"

#include "utils/ui-utils.h"
#include "view/layout-view.h"
#include "view/tab-view.h"
#include "utils/logger.h"
#include "model/constants.h"
#include <stdlib.h>
#include "model/notification-control.h"
#include <notification.h>
#include <Elementary.h>
#include <app.h>
#include "utils/config.h"
#include <efl_extension.h>

// app event callbacks
static bool _on_create_cb(void *user_data);
static void _on_terminate_cb(void *user_data);
static void _on_pause_cb(void *user_data);
static void _on_resume_cb(void *user_data);
static void _on_app_control_cb(app_control_h app_control, void *user_data);

static Evas_Object *_add_naviframe(app_data *app);
static void _app_navi_back_cb(void *data, Evas_Object *obj, void *event_info);
app_data *app_create()
{
    app_data *app = calloc(1, sizeof(app_data));
    return app;
}

void app_destroy(app_data *app)
{
    if(app)
    {
        free(app);
    }
}

int app_run(app_data *app, int argc, char **argv)
{
    if(!app)
    {
        return -1;
    }

    ui_app_lifecycle_callback_s cbs =
    {
        .create = _on_create_cb,
        .terminate = _on_terminate_cb,
        .pause = _on_pause_cb,
        .resume = _on_resume_cb,
        .app_control = _on_app_control_cb
    };

    return ui_app_main(argc, argv, &cbs, app);
}

static Evas_Object *_add_naviframe(app_data *app)
{
    Evas_Object *navi = ui_utils_navi_add(win_get_host_layout(app->win));
    RETVM_IF(!navi, NULL, "navi is NULL");
    eext_object_event_callback_add(navi, EEXT_CALLBACK_BACK, _app_navi_back_cb, app);
    win_set_layout(app->win, navi);
    return navi;
}

static bool _on_create_cb(void *user_data)
{
    app_data *ad = user_data;
    RETVM_IF(!ad, false, "ad is NULL");

    ad->win = win_create();
    RETVM_IF(!ad->win, false, "ad->win is NULL");

    ad->navi = _add_naviframe(ad);
    RETVM_IF(!ad->navi, false, "ad->navi is NULL");

    tab_view_add(ad->navi);
    return true;
}

static void _app_navi_back_cb(void *data, Evas_Object *obj, void *event_info)
{
    RETM_IF(!data, "data is NULL");
    app_data *app = data;

    if(elm_naviframe_top_item_get(app->navi)
            == elm_naviframe_bottom_item_get(app->navi))
    {
        win_lower(app->win);
    }
    else
    {
        elm_naviframe_item_pop(app->navi);
    }
}

static void _on_terminate_cb(void *user_data)
{
    app_data *app = user_data;

    if(!app)
    {
        return;
    }

    win_destroy(app->win);
    app->win = NULL;
}

static void _on_pause_cb(void *user_data)
{
}

static void _on_resume_cb(void *user_data)
{
}

static void _on_app_control_cb(app_control_h app_control, void *user_data)
{
    app_data *app = (app_data *)user_data;
    if(app)
    {
        char *argument= NULL;
        app_control_get_extra_data(app_control, MESSAGE_POST, &argument);
        if(argument)
        {
            char *uri_data = NULL;
            app_control_get_uri(app_control, &uri_data);
            if(uri_data)
            {

                notification_data* notify_data = (notification_data *) malloc(sizeof(notification_data));
                if(!notify_data)
                {
                    free(argument);
                    free(uri_data);
                    return;
                }

                snprintf(notify_data->name, TEXT_SHORT_LEN, "%s", app_control_request);

                char *operation_data = NULL;
                app_control_get_operation(app_control, &operation_data);

                char *mime_data = NULL;
                app_control_get_mime(app_control, &mime_data);

                char **result_service_data = NULL;
                int length = 0;
                char extra_data_text[TEXT_SHORT_LEN] = {'\0'};
                int err = app_control_get_extra_data_array(app_control, SERVICE_DATA_TEXT, &result_service_data, &length);
                if(err == APP_CONTROL_ERROR_NONE)
                {
                    snprintf(extra_data_text, TEXT_SHORT_LEN, "# 1%s (%s | %s)<br>", key_value, SERVICE_DATA_TEXT, result_service_data[0]);
                    int i = 0;
                    for(; i != length; i++)
                    {
                        free(result_service_data[i]);
                    }
                    free(result_service_data);
                }

                char **result_service_data_to = NULL;
                char extra_data_to[TEXT_SHORT_LEN] = { '\0'};
                err = app_control_get_extra_data_array(app_control, SERVICE_DATA_TO, &result_service_data_to, &length);
                if(err == APP_CONTROL_ERROR_NONE)
                {
                    snprintf(extra_data_to, TEXT_SHORT_LEN, "# 2%s (%s | %s)", key_value, SERVICE_DATA_TEXT, result_service_data_to[0]);
                    int i = 0;
                    for(; i != length; i++)
                    {
                        free(result_service_data_to[i]);
                    }
                    free(result_service_data_to);
                }

                snprintf(notify_data->result_text, TEXT_MAX_LEN, "%s %i<br>%s %s<br>%s %s<br>%s %s<br><br>%s<br># 0%s (%s | %s)<br>%s%s",
                        req_id, ++app->service_request_count,operation_id,operation_data,uri_data_text,uri_data
                        ,mime_type, mime_data,extra_data, key_value, extra_data_tizen_org, argument, extra_data_text, extra_data_to);

                layout_view_add(app->navi, notify_data);

                free(operation_data);
                free(uri_data);
                free(mime_data);
                free(argument);
                free(notify_data);
            }
        }
        win_raise(app->win);
    }
}

