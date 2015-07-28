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


#include "utils/ui-utils.h"
#include <Elementary.h>
#include <app.h>

Evas_Object *ui_utils_navi_add(Evas_Object *parent)
{
    if(!parent)
    {
        return NULL;
    }
    Evas_Object *navi = elm_naviframe_add(parent);
    elm_naviframe_prev_btn_auto_pushed_set(navi, EINA_FALSE);

    return navi;
}

Evas_Object *ui_utils_layout_add(Evas_Object *parent, Evas_Object_Event_Cb destroy_cb, void *cb_data)
{
    Evas_Object *layout = elm_layout_add(parent);
    if(!layout)
    {
        return NULL;
    }

    elm_layout_theme_set(layout, "layout", "application", "default");
    evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_event_callback_add(layout, EVAS_CALLBACK_FREE, destroy_cb, cb_data);

    return layout;
}
