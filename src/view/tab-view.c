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


#include "view/tab-view.h"
#include <badge.h>
#include "view/layout-view.h"
#include "model/constants.h"
#include "main-app.h"
#include "utils/ui-utils.h"
#include "utils/config.h"
#include "utils/logger.h"
#include <notification.h>
#include <Elementary.h>
#include "Interface/Log.h"
#include "components.h"

enum LIST_STATE
{
	NOT_INITIALIZED,
	STATE_INTERFACE,
	STATE_DEVICE,
	STATE_COMMUNICATION
};

typedef struct
{
	Evas_Object *navi;
	Elm_Object_Item *navi_item;
	Evas_Object *layout;
	Evas_Object *tab;
	enum LIST_STATE state;
	Elm_Object_Item *pressed_toolbar_item;
	Evas_Object *notification_tab;
	Evas_Object *ongoing_notification_tab;
	Evas_Object *communication_tab;

} tab_view_data;


typedef struct
{
	Evas_Object *navi;
	Elm_Object_Item *navi_item;
	Evas_Object *layout;
	const char *name;
} layout_view_data2;

static void _tab_view_destroy(void *data, Evas *e, Evas_Object *obj, void *event_info);
static void _tab_view_fill(tab_view_data *data);
static void _tab_view_select_INTERFACE_cb(void *data, Evas_Object *obj, void *event_info);
static void _tab_view_select_COMMUNICATION_cb(void *data, Evas_Object *obj, void *event_info);
static void _tab_view_select_DEVICE_cb(void *data, Evas_Object *obj, void *event_info);
static void _tab_view_switch_content(Evas_Object *content_to_switch_to, tab_view_data *data);
static Evas_Object *_tab_view_create_tab_content(tab_view_data *data);
static void _tab_view_fill_list(Evas_Object *list, tab_view_data *data);
void _sensorcallback_layout_fill_cb2depth(void *data, Evas_Object *obj, void *event_info);
void _tab_view_layout_fill_cb2depth(void *data, Evas_Object *obj, void *event_info);

void tab_view_add(Evas_Object *parent)
{
	RETM_IF(!parent, "parent is NULL");

	tab_view_data *data = calloc(1, sizeof(tab_view_data));
	data->navi = parent;

	data->layout = ui_utils_layout_add(data->navi, _tab_view_destroy, data);
	if(!data->layout)
	{
		free(data);
		return;
	}

	data->tab = elm_toolbar_add(data->navi);
	if(!data->tab)
	{
		evas_object_del(data->layout);
		return;
	}
	elm_toolbar_shrink_mode_set(data->tab, ELM_TOOLBAR_SHRINK_EXPAND);
	elm_toolbar_transverse_expanded_set(data->tab, EINA_TRUE);
	elm_object_style_set(data->tab, "tabbar");

	_tab_view_fill(data);
	data->navi_item = elm_naviframe_item_push(data->navi, NULL, NULL, NULL, data->layout, "tabbar/notitle");
	elm_object_item_part_content_set(data->navi_item, "tabbar", data->tab);

	/* Create badge */
	int err = badge_new(PACKAGE);
	if(BADGE_ERROR_NONE != err)
	{
		ERR("Badge is not created.");
	}
}
// tab_view_destroy
static void _tab_view_destroy(void *data, Evas *e, Evas_Object *obj, void *event_info)
{

	badge_remove(PACKAGE);
	free(data);
}

static void _tab_view_fill(tab_view_data *data)
{
	Elm_Object_Item *notification_item = NULL;

	RETM_IF(!data, "data is NULL");

	notification_item = elm_toolbar_item_append(data->tab, NULL,
			"INTERFACE", _tab_view_select_INTERFACE_cb, data);
	elm_toolbar_item_append(data->tab, NULL,
			"DEVICE", _tab_view_select_DEVICE_cb, data);
	elm_toolbar_item_append(data->tab, NULL,
			"COMMUNICATION", _tab_view_select_COMMUNICATION_cb, data);


	elm_toolbar_select_mode_set(data->tab, ELM_OBJECT_SELECT_MODE_ALWAYS);
	elm_toolbar_item_selected_set(notification_item, EINA_TRUE);
}

static void _tab_view_select_INTERFACE_cb(void *data, Evas_Object *obj, void *event_info)
{
	RETM_IF(!event_info, "event_info is NULL");
	RETM_IF(!data, "data is NULL");

	tab_view_data *tab_data = (tab_view_data *) data;

	if(event_info != tab_data->pressed_toolbar_item)
	{
		Evas_Object **content_to_switch_to = NULL;
		tab_data->pressed_toolbar_item = event_info;
		if(tab_data->state!=STATE_INTERFACE)
		{
			tab_data->state=STATE_INTERFACE;
			content_to_switch_to = &tab_data->notification_tab;
		}

		if(!*content_to_switch_to)
		{
			*content_to_switch_to = _tab_view_create_tab_content(data);
		}
		_tab_view_switch_content(*content_to_switch_to, tab_data);

	}
}

static void _tab_view_select_DEVICE_cb(void *data, Evas_Object *obj, void *event_info)
{
	RETM_IF(!event_info, "event_info is NULL");
	RETM_IF(!data, "data is NULL");
	tab_view_data *tab_data = (tab_view_data *) data;

	if(event_info != tab_data->pressed_toolbar_item)
	{
		Evas_Object **content_to_switch_to = NULL;
		tab_data->pressed_toolbar_item = event_info;
		if(tab_data->state!=STATE_DEVICE){
			tab_data->state=STATE_DEVICE;
			content_to_switch_to = &tab_data->ongoing_notification_tab;

		}

		if(!*content_to_switch_to)
		{

			*content_to_switch_to = _tab_view_create_tab_content(data);
		}

		_tab_view_switch_content(*content_to_switch_to, tab_data);

	}
}

static void _tab_view_select_COMMUNICATION_cb(void *data, Evas_Object *obj, void *event_info)
{
	RETM_IF(!event_info, "event_info is NULL");
	RETM_IF(!data, "data is NULL");

	tab_view_data *tab_data = (tab_view_data *) data;

	if(event_info != tab_data->pressed_toolbar_item)
	{
		Evas_Object **content_to_switch_to = NULL;
		tab_data->pressed_toolbar_item = event_info;

		if(tab_data->state!=STATE_COMMUNICATION){
			tab_data->state=STATE_COMMUNICATION;

			content_to_switch_to = &tab_data->communication_tab;
		}
		if(!*content_to_switch_to)
		{
			*content_to_switch_to = _tab_view_create_tab_content(data);
		}
		_tab_view_switch_content(*content_to_switch_to, tab_data);
	}
}

static void _tab_view_switch_content(Evas_Object *content_to_switch_to, tab_view_data *data)
{
	RETM_IF(!content_to_switch_to, "content_to_switch_to is NULL");
	RETM_IF(!data, "data is NULL");
	Evas_Object *content_to_switch_from = NULL;

	content_to_switch_from = elm_object_part_content_unset(data->layout, "elm.swallow.content");
	evas_object_hide(content_to_switch_from);
	elm_object_part_content_set(data->layout, "elm.swallow.content", content_to_switch_to);
	evas_object_show(content_to_switch_to);
}

static Evas_Object *_tab_view_create_tab_content(tab_view_data *data)
{
	RETVM_IF(!data, NULL, "data is NULL");

	Evas_Object *list = elm_list_add(data->layout);
	if(!list)
	{
		return NULL;
	}
	_tab_view_fill_list(list, data);

	return list;
}

//1click
static void _tab_view_fill_list(Evas_Object *list, tab_view_data *data)
{
	RETM_IF(!list, "list is NULL");
	RETM_IF(!data, "data is NULL");

	int size = 0;
	evas_object_data_set(list , "view_data", data->navi);

	notification_data *notification_list = NULL;

	if (STATE_INTERFACE == data->state)
	{
		notification_list = interface_list_get(&size);
		int i = 0;
			for (; i < size; i++)
			{	notification_list[i].status=list;
			}
			elm_list_item_append(list, notification_list[0].name, NULL, NULL, log_fill_item_cb, &notification_list[0]);
			elm_list_item_append(list, notification_list[1].name, NULL, NULL, notification_item_fill_cb, &notification_list[1]);
			elm_list_item_append(list, notification_list[2].name, NULL, NULL, ongoingnotification_item_fill_cb, &notification_list[2]);

	}
	else if (STATE_DEVICE == data->state)
	{
		notification_list = device_list_get(&size);
		int i = 0;
			for (; i < size; i++)
			{
				notification_list[i].status=list;
			}
			elm_list_item_append(list, notification_list[0].name, NULL, NULL, devicestatus_item_fill_cb, &notification_list[0]);
			elm_list_item_append(list, notification_list[1].name, NULL, NULL, file_item_fill_cb, &notification_list[1]);
			elm_list_item_append(list, notification_list[2].name, NULL, NULL, preference_item_fill_cb, &notification_list[2]);
			elm_list_item_append(list, notification_list[3].name, NULL, NULL, sensor_item_fill_cb, &notification_list[3]);
			elm_list_item_append(list, notification_list[4].name, NULL, NULL, vibrator_item_fill_cb, &notification_list[4]);

	}
	else if(STATE_COMMUNICATION == data->state)
	{
		notification_list = communication_list_get(&size);
		int i = 0;
			for (; i < size; i++)
			{
				notification_list[i].status=list;
			}
			elm_list_item_append(list, notification_list[0].name, NULL, NULL, bouetooth_fill_item_cb, &notification_list[0]);
			elm_list_item_append(list, notification_list[1].name, NULL, NULL, gps_fill_item_cb, &notification_list[1]);
			elm_list_item_append(list, notification_list[2].name, NULL, NULL, http_fill_item_cb, &notification_list[2]);
			elm_list_item_append(list, notification_list[3].name, NULL, NULL, nfc_fill_item_cb, &notification_list[3]);
			elm_list_item_append(list, notification_list[4].name, NULL, NULL, socket_fill_item_cb, &notification_list[4]);

	}


}





//2depth
 void _sensorcallback_layout_fill_cb2depth(void *data, Evas_Object *obj, void *event_info)
{
	RETM_IF(!obj, "obj is NULL");
	RETM_IF(!data, "data is NULL");


    elm_list_item_selected_set(event_info, EINA_FALSE);
    notification_data *notification_info = (notification_data *)data;




    Evas_Object *navi = evas_object_data_get(notification_info->status, "view_data");

    RETM_IF(!navi, "navi is NULL");

    notification_info->callback(notification_info);
    layout_view_add2(navi, notification_info);
}
 void _tab_view_layout_fill_cb2depth(void *data, Evas_Object *obj, void *event_info)
{
	RETM_IF(!obj, "obj is NULL");
	RETM_IF(!data, "data is NULL");


    elm_list_item_selected_set(event_info, EINA_FALSE);
    notification_data *notification_info = (notification_data *)data;




    Evas_Object *navi = evas_object_data_get(notification_info->status, "view_data");

    RETM_IF(!navi, "navi is NULL");

    notification_info->callback(notification_info);
    layout_view_add(navi, notification_info);
}



 void _layout_view_destroy2(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	layout_view_data2 *layout_data = (layout_view_data2 *)data;
	if (layout_data)
	{
		evas_object_data_del(layout_data->navi, LAYOUT);
		free(layout_data);
	}
}
