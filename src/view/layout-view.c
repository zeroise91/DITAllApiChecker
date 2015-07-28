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


#include "view/layout-view.h"
#include "utils/ui-utils.h"
#include "utils/config.h"
#include "utils/logger.h"
#include <Elementary.h>


typedef struct
{
    Evas_Object *navi;
    Elm_Object_Item *navi_item;
    Evas_Object *layout;
    const char *name;
} layout_view_data;
Evas_Object* content;

Evas_Object* _get_title(){return content;}

static void _layout_view_destroy(void *data, Evas *e, Evas_Object *obj, void *event_info);
static void _layout_view_fill(Evas_Object *layout, notification_data *notify_info);
void _layout_view_fill2(Evas_Object *layout, notification_data *notify_info);

#define ENTRY_TITLE_STYLE "DEFAULT='align=left font=Tizen:style=Roman text_class=tizen font_size=30'"
#define ENTRY_CONTENT_STYLE "DEFAULT='align=left font=Tizen:style=Roman text_class=tizen font_size=45'"
#define LAYOUT_TITLE "Notify result"
#define LAYOUT "layout"

Evas_Object *layout_view_add(Evas_Object *parent, notification_data *notify_info)
{
    if(!parent)
    {
        return NULL;
    }

    layout_view_data *data = calloc(1, sizeof(layout_view_data));
    if(!data)
    {
        return NULL;
    }

    data->navi = parent;
    data->name = notify_info->name;
    data->layout = ui_utils_layout_add(data->navi, _layout_view_destroy, data);

    if(!data->layout)
    {
        free(data);
        return NULL;
    }

    _layout_view_fill(data->layout, notify_info);
    data->navi_item = elm_naviframe_item_push(data->navi, data->name, NULL, NULL, data->layout, NULL);
    return data->layout;
}

Evas_Object *layout_view_add2(Evas_Object *parent, notification_data *notify_info)
{
    if(!parent)
    {
        return NULL;
    }

    layout_view_data *data = calloc(1, sizeof(layout_view_data));
    if(!data)
    {
        return NULL;
    }

    data->navi = parent;
    data->name = notify_info->name;
    data->layout = ui_utils_layout_add(data->navi, _layout_view_destroy, data);

    if(!data->layout)
    {
        free(data);
        return NULL;
    }

    _layout_view_fill2(data->layout, notify_info);
    data->navi_item = elm_naviframe_item_push(data->navi, data->name, NULL, NULL, data->layout, NULL);
    return data->layout;
}
static void _layout_view_destroy(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
    layout_view_data *layout_data = (layout_view_data *)data;
    if (layout_data)
    {
        evas_object_data_del(layout_data->navi, LAYOUT);
        free(layout_data);
    }
}

static void _layout_view_fill(Evas_Object *layout, notification_data *notify_info)
{
    if(!layout)
    {
        return;
    }
    elm_layout_file_set(layout, LAYOUTEDJ, "layout");

    Evas_Object *title = elm_label_add(layout);
    if(title)
    {
        elm_label_ellipsis_set(title, EINA_TRUE);
        elm_label_line_wrap_set(title, ELM_WRAP_MIXED);
        elm_object_text_set(title, notify_info->name);
        evas_object_size_hint_weight_set(title, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(title, EVAS_HINT_FILL, EVAS_HINT_FILL);
        elm_object_part_content_set(layout, "title_part", title);
        evas_object_show(title);
    }

    Evas_Object *scroller = elm_scroller_add(layout);
   if (scroller)
    {
        elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
        elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
        elm_scroller_content_min_limit(scroller, EINA_TRUE, EINA_TRUE);
        elm_object_part_content_set(layout, "content_part", scroller);
        evas_object_show (scroller);

        Evas_Object *box = elm_box_add(scroller);
        if (box)
        {
            elm_object_content_set(scroller, box);
            evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
            evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
            elm_box_horizontal_set(box, EINA_FALSE);
            evas_object_show(box);

            Evas_Object* content = elm_label_add(layout);
            if(content)
            {
                elm_label_line_wrap_set(content, ELM_WRAP_MIXED);
                elm_object_text_set(content, notify_info->result_text);
                evas_object_size_hint_weight_set(content, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
                evas_object_size_hint_align_set(content, EVAS_HINT_FILL, EVAS_HINT_FILL);
                elm_box_pack_start(box, content);
                evas_object_show(content);
            }
        }
    }
  }

 void _layout_view_fill2(Evas_Object *layout, notification_data *notify_info)
{
    if(!layout)
    {
        return;
    }
    elm_layout_file_set(layout, LAYOUTEDJ, "layout");

    Evas_Object *title = elm_label_add(layout);
    if(title)
    {
        elm_label_ellipsis_set(title, EINA_TRUE);
        elm_label_line_wrap_set(title, ELM_WRAP_MIXED);
        elm_object_text_set(title, notify_info->name);
        evas_object_size_hint_weight_set(title, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(title, EVAS_HINT_FILL, EVAS_HINT_FILL);
        elm_object_part_content_set(layout, "title_part", title);
        evas_object_show(title);
    }

    Evas_Object *scroller = elm_scroller_add(layout);
   if (scroller)
    {
        elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
        elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
        elm_scroller_content_min_limit(scroller, EINA_TRUE, EINA_TRUE);
        elm_object_part_content_set(layout, "content_part", scroller);
        evas_object_show (scroller);

        Evas_Object *box = elm_box_add(scroller);
        if (box)
        {
            elm_object_content_set(scroller, box);
            evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
            evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
            elm_box_horizontal_set(box, EINA_FALSE);
            evas_object_show(box);

             content = elm_label_add(layout);
            if(content)
            {
                elm_label_line_wrap_set(content, ELM_WRAP_MIXED);
                elm_object_text_set(content, notify_info->result_text);
                evas_object_size_hint_weight_set(content, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
                evas_object_size_hint_align_set(content, EVAS_HINT_FILL, EVAS_HINT_FILL);
                elm_box_pack_start(box, content);
                evas_object_show(content);
            }
        }
    }
  }
