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

#include "model/notification-control.h"
#include <badge.h>
#include "model/constants.h"
#include "utils/ui-utils.h"
#include "utils/config.h"
#include "utils/logger.h"
#include "Interface/Log.h"
#include <stdio.h>
#include <Eina.h>
#include <Elementary.h>
#include "components.h"
#include "view/tab-view.h"
#include "view/layout-view.h"

#include "Device/DeviceStatus.h"
#include "Device/Preference.h"
#include "Device/File.h"
#include "Device/Sensor.h"
#include "Device/MediaRecorder.h"

#define MAX_ATTRIBUTE_NUM 32


static Evas_Object* img=NULL;
static Evas* canvas=NULL;
static Evas_Object* g_eo =NULL;

const char attributeString[][35]={
		"METADATA_DURATION",			/**< Duration */
		"METADATA_VIDEO_BITRATE",			/**< Video Bitrate */
		"METADATA_VIDEO_FPS",				/**< Video FPS */
		"METADATA_VIDEO_WIDTH",			/**< Video Width */
		"METADATA_VIDEO_HEIGHT",			/**< Video Height */
		"METADATA_HAS_VIDEO",				/**< Video stream count */
		"METADATA_AUDIO_BITRATE",			/**< Audio Bitrate */
		"METADATA_AUDIO_CHANNELS",		/**< Audio Channels */
		"METADATA_AUDIO_SAMPLERATE",		/**< Audio Samplerate */
		"METADATA_AUDIO_BITPERSAMPLE",		/**< Audio bit per sample */
		"METADATA_HAS_AUDIO",				/**< Audio stream count */
		"METADATA_ARTIST",					/**< Artist */
		"METADATA_TITLE",					/**< Title */
		"METADATA_ALBUM",					/**< Album */
		"METADATA_ALBUM_ARTIST",			/**< Album_Artist */
		"METADATA_GENRE",					/**< Genre */
		"METADATA_AUTHOR",					/**< Author */
		"METADATA_COPYRIGHT",				/**< Copyright */
		"METADATA_DATE",					/**< Date */
		"METADATA_DESCRIPTION",				/**< Description */
		"METADATA_COMMENT",			/**< Comment */
		"METADATA_TRACK_NUM"	,			/**< Track number info */
		"METADATA_CLASSIFICATION",			/**< Classification */
		"METADATA_RATING"	,				/**< Rating */
		"METADATA_LONGITUDE",				/**< Longitude */
		"METADATA_LATITUDE"	,			/**< Latitude */
		"METADATA_ALTITUDE"	,			/**< Altitude */
		"METADATA_CONDUCTOR",				/**< Conductor */
		"METADATA_UNSYNCLYRICS"	,		/**< Unsynchronized lyric */
		"METADATA_SYNCLYRICS_NUM"	,	/**< Synchronized lyric (time/lyric set) number */
		"METADATA_RECDATE"		,		/**< Recording date */
		"METADATA_ROTATE"					/**< Rotate(Orientation) Information */
};
typedef struct
{
	Evas_Object *navi;
	Elm_Object_Item *navi_item;
	Evas_Object *layout;
	const char *name;
} layout_view_data2;


static String getSharedResourceFile(String x){
	String str=calloc(1024,sizeof(char));

	String sharedResRootPath=app_get_shared_resource_path();
	snprintf(str,1024,"%s%s",sharedResRootPath,x);
	free(sharedResRootPath);

	return str;
}
notification_data *device_list_get(int *size){
	static notification_data components[] =
	{
			{ "DeviceStatus", NULL,  0, 0, none, },
			{ "File", NULL,  0, 0, none, },
			{ "Preference", NULL,  0, 0, none, },
			{ "Sensor", NULL,  0, 0, none, },
			{ "MediaRecorder", NULL,  0, 0, none, }
	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *devicestatus_list_get(int *size){
	static notification_data components[] =
	{

			{ "Display", NULL,  0, 0, none, },
			{ "Battery", NULL,  0, 0, none, },
			{ "Flash", NULL,  0, 0, none, },
			{ "Vibrator", NULL,  0, 0, none, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *display_components_get(int *size){
	static notification_data components[] =
	{

			{ "Lock", NULL,  0, 0, Lock, },
			{ "unLock", NULL,  0, 0, unLock, },
			{ "Dim", NULL,  0, 0, Dim, },
			{ "getBright", NULL,  0, 0, getBright, },
			{ "setBright", NULL,  0, 0, setBright, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}
notification_data *battery_components_get(int *size){
	static notification_data components[] =
	{

			{ "getLevel", NULL,  0, 0, getLevel, },
			{ "isCharging", NULL,  0, 0, isCharging, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}
notification_data *flash_components_get(int *size){
	static notification_data components[] =
	{

			{ "On", NULL,  0, 0, onflash, },
			{ "Off", NULL,  0, 0, offflash, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}


notification_data *file_submodules_list_get(int *size){
	static notification_data components[] =
	{
			{ "File", NULL,  0, 0, none, },
			{ "Video", NULL,  0, 0, none, },
			{ "Audio", NULL,  0, 0, none, },
			{ "Image", NULL,  0, 0, none, }
	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *mediarecorder_list_get(int *size){
	static notification_data components[] =
	{
			{ "CameraRecorder", NULL,  0, 0, none, },
			{ "AudioRecorder", NULL,  0, 0, none, }
	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}


notification_data *preference_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "getInt", NULL,  0, 0, preference_int_get, },
			{ "getString", NULL,  0, 0, preference_string_get, },
			{ "getBoolean", NULL,  0, 0, preference_boolean_get, },
			{ "getDouble", NULL,  0, 0, preference_double_get, },
			{ "setInt", NULL,  0, 0, preference_int_set, },
			{ "setString", NULL,  0, 0, preference_string_set, },
			{ "setBoolean", NULL,  0, 0, preference_boolean_set, },
			{ "setDouble", NULL,  0, 0, preference_double_set, },
			{ "remove", NULL,  0, 0, preference__remove, },
			{ "clear", NULL,  0, 0, preference__clear, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *sensor_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "Accelerometer", NULL,  0, 0, none, },
			{ "Gravity", NULL,  0, 0, none, },
			{ "LinearAccelation", NULL,  0, 0, none, },
			{ "MagnetoMeter", NULL,  0, 0, none, },
			{ "RotationVector", NULL,  0, 0, none, },
			{ "Orientation", NULL,  0, 0, none, },
			{ "Gyroscope", NULL,  0, 0, none, },
			{ "Light", NULL,  0, 0, none, },
			{ "Proximity", NULL,  0, 0, none, },
			{ "Pressure", NULL,  0, 0, none, },
			{ "UltraViolet", NULL,  0, 0, none, },
			{ "Temperature", NULL,  0, 0, none, },
			{ "Humidity", NULL,  0, 0, none, }
	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *vibrator_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "Custom", NULL,  0, 0, Custom, },
			{ "short", NULL,  0, 0, Short, },
			{ "Middle", NULL,  0, 0, Middle, },
			{ "Long", NULL,  0, 0, Long, }
	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}


void devicestatus_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=devicestatus_list_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;

	}
	elm_list_item_append(list,notification_list[0].name,NULL,NULL,display_view_layout_fill_cb,&notification_list[0]);
	elm_list_item_append(list,notification_list[1].name,NULL,NULL,battery_view_layout_fill_cb,&notification_list[1]);
	elm_list_item_append(list,notification_list[2].name,NULL,NULL,flash_view_layout_fill_cb,&notification_list[2]);
	elm_list_item_append(list,notification_list[3].name,NULL,NULL,vibrator_item_fill_cb,&notification_list[3]);


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
}

void preference_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=preference_component_list_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void display_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=display_components_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void battery_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=battery_components_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void flash_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=flash_components_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}



void file_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	if(canvas==NULL)
		canvas = evas_object_evas_get(datas->navi);
	if(img==NULL)
	{
		img = evas_object_image_filled_add(canvas);		// Add an image to the given evas
		evas_object_image_file_set(img, "/opt/usr/apps/org.tizen.ditapichecker.shared/res/images/test.jpg", NULL);//Set the source file from where an image object must fetch the real image data
		evas_object_move(img, 240, 108);					// Move the given Evas object to the given location inside its canvas�� viewport
		evas_object_resize(img, 240, 135);				// Change the size of the given Evas object
	}

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=file_submodules_list_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
	}

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,file_view_layout_fill_cb,&notification_list[0]);
	elm_list_item_append(list,notification_list[1].name,NULL,NULL,video_view_layout_fill_cb,&notification_list[1]);
	elm_list_item_append(list,notification_list[2].name,NULL,NULL,audio_view_layout_fill_cb,&notification_list[2]);
	elm_list_item_append(list,notification_list[3].name,NULL,NULL,image_view_layout_fill_cb,&notification_list[3]);




	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}



void sensor_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=sensor_component_list_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;

	}


	elm_list_item_append(list,notification_list[0].name,NULL,NULL,Accelerometer_item_fill_cb,&notification_list[0]);
	elm_list_item_append(list,notification_list[1].name,NULL,NULL,Gravity_item_fill_cb,&notification_list[1]);
	elm_list_item_append(list,notification_list[2].name,NULL,NULL,LinearAccelation_item_fill_cb,&notification_list[2]);
	elm_list_item_append(list,notification_list[3].name,NULL,NULL,MagnetoMeter_item_fill_cb,&notification_list[3]);
	elm_list_item_append(list,notification_list[4].name,NULL,NULL,RotationVector_item_fill_cb,&notification_list[4]);
	elm_list_item_append(list,notification_list[5].name,NULL,NULL,Orientation_item_fill_cb,&notification_list[5]);
	elm_list_item_append(list,notification_list[6].name,NULL,NULL,Gyroscope_item_fill_cb,&notification_list[6]);
	elm_list_item_append(list,notification_list[7].name,NULL,NULL,Light_item_fill_cb,&notification_list[7]);
	elm_list_item_append(list,notification_list[8].name,NULL,NULL,Proximity_item_fill_cb,&notification_list[8]);
	elm_list_item_append(list,notification_list[9].name,NULL,NULL,Pressure_item_fill_cb,&notification_list[9]);
	elm_list_item_append(list,notification_list[10].name,NULL,NULL,UltraViolet_item_fill_cb,&notification_list[10]);
	elm_list_item_append(list,notification_list[11].name,NULL,NULL,Temperature_item_fill_cb,&notification_list[11]);
	elm_list_item_append(list,notification_list[12].name,NULL,NULL,Humidity_item_fill_cb,&notification_list[12]);



	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);

}
void mediarecorder_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
{

	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}

	if(canvas==NULL)
		canvas = evas_object_evas_get(datas->navi);
	if(g_eo==NULL)
	{

		g_eo = evas_object_image_add(canvas);
		evas_object_image_size_set(g_eo, 240, 320);
		evas_object_image_fill_set(g_eo, 0, 320, 240, 320);
		evas_object_move(g_eo, 0,480);
		evas_object_resize(g_eo, 240, 320);
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=mediarecorder_list_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;

	}
	elm_list_item_append(list,notification_list[0].name,NULL,NULL,camerarecorder_view_layout_fill_cb,&notification_list[0]);
	elm_list_item_append(list,notification_list[1].name,NULL,NULL,audiorecorder_view_layout_fill_cb,&notification_list[1]);



	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void vibrator_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=vibrator_component_list_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}
void camerarecorder_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=camerarecorder_component_list_get(&size);


	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}


void audiorecorder_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data* notify_info=(notification_data*)data;
	layout_view_data2 *datas = calloc(1, sizeof(layout_view_data2));
	Evas_Object* lists=notify_info->status;

	datas->navi = evas_object_data_get(lists, "view_data");

	datas->name = notify_info->name;
	datas->layout = ui_utils_layout_add(datas->navi, _layout_view_destroy2, datas);

	if(!datas->layout)
	{
		free(datas);
		return ;
	}


	Evas_Object* list= elm_list_add(datas->layout);

	notification_data *notification_list = NULL;
	int size=0;
	//
	notification_list=audiorecorder_component_list_get(&size);


	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
}




//function

Display display_get_instance(){
	static Display pDisplay=NULL;

	if(pDisplay==NULL)
		pDisplay=NewDisplay();

	return pDisplay;
}
Battery battery_get_instance(){
	static Battery pBattery=NULL;

	if(pBattery==NULL)
		pBattery=NewBattery();

	return pBattery;
}

Flash flash_get_instance(){
	static Flash pFlash=NULL;

	if(pFlash==NULL)
		pFlash=NewFlash();

	return pFlash;
}

Vibration vibration_get_instance(){
	static Vibration pVibration = NULL;

	if(pVibration==NULL)
		pVibration = NewVibration();

	return pVibration;
}

Image image_get_instance(){
	static Image pImage = NULL;

	if(pImage==NULL)
		pImage = NewImage();

	return pImage;
}


Video video_get_instance(){
	static Video pVideo = NULL;

	if(pVideo==NULL)
		pVideo = NewVideo();

	return pVideo;
}

Audio audio_get_instance(){
	static Audio pAudio = NULL;

	if(pAudio==NULL)
		pAudio = NewAudio();

	return pAudio;
}

Preference Preference_get_instance(){
	static Preference pPreference =NULL;
	if(pPreference ==NULL)
		pPreference = NewPreference();

	return pPreference;
}

void Lock(notification_data* data){
	Display x= display_get_instance();
	x->Lock(x);

	sprintf(data->result_text,"Screen Lock");
}
void unLock(notification_data* data){
	Display x= display_get_instance();
	x->Unlock(x);

	sprintf(data->result_text,"Screen Unlock");
}
void Dim(notification_data* data){
	Display x= display_get_instance();
	x->Dim(x);

	sprintf(data->result_text,"Dimmed");
}
void getBright(notification_data* data){
	Display x= display_get_instance();
	snprintf(data->result_text,1024,"BrightLev: %d", x->getBright(x));
}
void setBright(notification_data* data){
	Display x= display_get_instance();
	static int k =0;
	x->setBright(x,k);
	snprintf(data->result_text,1024,"BrightLev: %d",k);
	k=k%100+10;
	if(k>100){
		k=10;
	}

}

void getLevel(notification_data* data){
	Battery battery= battery_get_instance();
	int level=battery->getLevel(battery);
	snprintf(data->result_text,1024,"Batterypercent: %d%%",level);
}

void isCharging(notification_data* data){
	Battery battery= battery_get_instance();
	bool charging = battery->isCharging(battery);
	snprintf(data->result_text,1024,"%s",(charging)?"charging":"not charging");


}

void onflash(notification_data* data){
	Flash flash = flash_get_instance();
	flash->On();
	snprintf(data->result_text,1024,"flash on");

}

void offflash(notification_data* data){
	Flash flash = flash_get_instance();
	flash->Off();
	snprintf(data->result_text,1024,"flash off");

}

void Custom(notification_data* data){
	Vibration v=vibration_get_instance();
	v->Custom(v, 5000);
	snprintf(data->result_text,1024,"vibrate 5 sec");

}
void Short(notification_data* data){
	Vibration v=vibration_get_instance();
	v->Short(v);
	snprintf(data->result_text,1024,"vibrate 0.1 sec");

}
void Middle(notification_data* data){
	Vibration v=vibration_get_instance();
	v->Middle(v);
	snprintf(data->result_text,1024,"vibrate 0.5 sec");

}
void Long(notification_data* data){
	Vibration v=vibration_get_instance();
	v->Long(v);
	snprintf(data->result_text,1024,"vibrate 1.5 sec");

}



void extractinfo(notification_data* data){

	Image image= image_get_instance();
	image->setURI(image,"/opt/usr/media/Downloads/1.jpg");
	snprintf(data->result_text,1024,"image <br>/opt/usr/media/Downloads/1.jpg<br>metadata extract complete");
}


void  getimageMediaId (notification_data* data){
	Image image= image_get_instance();
	if(((ImageExtends*)image)->imageMetaHandle){
		String str =image->getMediaId(image);
		snprintf(data->result_text,1024,"MeiaID: %s",str?str:"(none)");

	}
	else{
		snprintf(data->result_text,1024,"press extractImageInfo button first");
	}


}
void  getimageDateTaken (notification_data* data){
	Image image= image_get_instance();
	if(((ImageExtends*)image)->imageMetaHandle){
		String str = image->getDate(image);
		snprintf(data->result_text,1024,"MeiaID: %s",str?str:"(none)");

	}
	else{
		snprintf(data->result_text,1024,"press extractImageInfo button first");
	}

}
void	getimageWidth(notification_data* data){

	Image image= image_get_instance();
	int  width = image->getWidth(image);
	if(width != -1)
	{
		snprintf(data->result_text,1024,"image width: %d",width);
	}
	else
	{
		snprintf(data->result_text,1024,"press extractImageInfo button first");

	}

}
void	getimageHeight(notification_data* data){
	Image image= image_get_instance();
	int  height = image->getHeight(image);
	if(height!=-1)
	{
		snprintf(data->result_text,1024,"image width: %d",height);
	}
	else
	{
		snprintf(data->result_text,1024,"press extractImageInfo button first");

	}

}

void deletefile(notification_data* data){
	File file = NewFile();

	if(file->Delete("/opt/usr/media/Downloads/copied.jpg")==true){

		sprintf(data->result_text,"/opt/usr/media/Downloads/copied.jpg<br>deleted");
	}
	else
	{
		sprintf(data->result_text,"delete target File:<br>/opt/usr/media/Downloads/copied.jpg<br>doesn't exist");
	}
	DestroyFile(file);
}
void copyfile(notification_data* data){
	File file = NewFile();
	String srcfilepath=getSharedResourceFile("images/test.jpg");

	if(file->Copy(srcfilepath,"/opt/usr/media/Downloads/copied.jpg")==true){

		sprintf(data->result_text,"%s"
				"<br><br>copied to<br><br>"
				"/opt/usr/media/Downloads/copied.jpg",srcfilepath);

	}else{
		sprintf(data->result_text,"copy source file:<br>%s doesn't exist",srcfilepath);
	}
	free(srcfilepath);
	DestroyFile(file);

}
void movefile(notification_data* data){
	File file = NewFile();
	if(file->Move("/opt/usr/media/Downloads/copied.jpg","/opt/usr/media/Downloads/moved.jpg")){
		;
		sprintf(data->result_text,"/opt/usr/media/Downloads/copied.jpg<br><br>moved to<br><br>/opt/usr/media/Downloads/moved.jpg");
	}
	else
	{
		sprintf(data->result_text,"/opt/usr/media/Downloads/copied.jpg doesn't exist");

	}
	DestroyFile(file);

}


void searchfile(notification_data* data){
	File v= NewFile();

	GList* file_list=v->Search("/opt/usr/media","2.mp3");

	char buff[1024]={0,};
	for (int i = 0; i < g_list_length(file_list); i++)
	{
		strcat(buff,(String)g_list_nth_data(file_list, i));
		strcat(buff,"<br>");
	}
	snprintf(data->result_text,1024,"find 2.mp3 in /opt/usr/media<br>result"
			":<br>%s",buff);
	v->deleteSearchedList(file_list);
	DestroyFile(v);

}

void playvideo(notification_data* data){
	Video v= video_get_instance();

	if(((VideoExtends*)v)->uri&&((VideoExtends*)v)->EvasObject)
	{
		evas_object_show(img);
		v->Play(v);
		sprintf(data->result_text,"video play");

	}
	else{
		sprintf(data->result_text,"press<br>setEvasObject button<br>setURI(Video) button<br>first");
	}
}
void pausevideo(notification_data* data){
	Video v= video_get_instance();

	if(((VideoExtends*)v)->uri&&((VideoExtends*)v)->EvasObject)
	{
		v->Pause(v);
		sprintf(data->result_text,"video pause");

	}
	else{
		sprintf(data->result_text,"press<br>setEvasObject button<br>setURI(Video) button<br>first");
	}
}
void stopvideo(notification_data* data){
	Video v= video_get_instance();

	if(((VideoExtends*)v)->uri&&((VideoExtends*)v)->EvasObject)
	{
		v->Stop(v);
		evas_object_hide(img);
		sprintf(data->result_text,"video stop and hide");

	}
	else{
		sprintf(data->result_text,"press<br>setEvasObject button<br>setURI(Video) button<br>first");
	}
}

void getvideoinfo(notification_data* data){
	Video v= video_get_instance();
	if(((VideoExtends*)v)->uri){
		String pstr=NULL;

		memset(data->result_text,0,1024);

		char str[10]={0};
		for(int i=0;i<MAX_ATTRIBUTE_NUM;i++){
			pstr= v->getInfo(v,i);
			snprintf(str,10,"%d",i);
			if(pstr!=NULL){
				strcat(data->result_text,attributeString[i]);
				strcat(data->result_text,": ");

				strcat(data->result_text,pstr);
				strcat(data->result_text,"<br>");
				LOGINFO(LOG_TAG,"%s: %s",attributeString[i],pstr);
				free(pstr);
			}
			pstr=NULL;
		}
	}
	else
	{
		sprintf(data->result_text,"press setURI(video)button first");
	}
}
void setURI_video(notification_data* data){
	Video v= video_get_instance();

	String videofilepath =getSharedResourceFile("videos/Samsung Galaxy S3 Theme song.mp4");
	v->setURI(v,videofilepath);
	sprintf(data->result_text,"VideoURI set:<br>%s",videofilepath);
	free(videofilepath);
}

void setevasObject(notification_data* data){

	Video v= video_get_instance();
	v->setObject(v,img);
	sprintf(data->result_text,"video panel set complete");

}

void playaudio(notification_data* data){
	Audio a=audio_get_instance();
	if(	((AudioExtends*) a)->uri){
		a->Play(a);
		sprintf(data->result_text,"play audio");

	}
	else{
		sprintf(data->result_text,"press<br>setURI(audio)butten<br>first");

	}
}
void pauseaudio(notification_data* data){
	Audio a=audio_get_instance();

	if(	((AudioExtends*) a)->uri){
		a->Pause(a);
		sprintf(data->result_text,"pause audio");

	}
	else
	{
		sprintf(data->result_text,"press<br>setURI(audio)butten<br>first");

	}
}
void stopaudio(notification_data* data){
	Audio a=audio_get_instance();

	if(	((AudioExtends*) a)->uri){
		a->Stop(a);
		sprintf(data->result_text,"stop audio");

	}
	else
	{
		sprintf(data->result_text,"press<br>setURI(audio)butten<br>first");
	}
}

void getaudioInfo(notification_data* data){

	Audio a= audio_get_instance();
	if(((AudioExtends*)a)->uri){
		String pstr=NULL;

		memset(data->result_text,0,1024);

		char str[10]={0};
		for(int i=0;i<MAX_ATTRIBUTE_NUM;i++){
			pstr= a->getInfo(a,i);
			snprintf(str,10,"%d",i);
			if(pstr!=NULL){
				strcat(data->result_text,attributeString[i]);
				strcat(data->result_text,": ");

				strcat(data->result_text,pstr);
				strcat(data->result_text,"<br>");
				LOGINFO(LOG_TAG,"%s: %s",attributeString[i],pstr);
				free(pstr);
			}
			pstr=NULL;
		}
	}
	else{
		sprintf(data->result_text,"press setURI(audio) button first");
	}
}
void setURI_audio(notification_data* data){
	Audio a=audio_get_instance();
	String audiofilepath= getSharedResourceFile("music/Over the Horizon.mp3");
	a->setURI(a,audiofilepath);
	sprintf(data->result_text,"AudioURI set: <br>%s<br>",audiofilepath);
	free(audiofilepath);
}

void preference_int_get(notification_data* data){
	Preference pref= Preference_get_instance();

	int a =pref->getInt("int",-1);
	sprintf(data->result_text," %d get by<br>keyword:\"int\" at preference",a);
}
void preference_string_get(notification_data* data){
	Preference pref= Preference_get_instance();
	String x=NULL;
	x=pref->getString("string","(none)");
	sprintf(data->result_text," %s get by<br>keyword:\"String\" at preference",x);
	free(x);
	x=NULL;

}
void preference_boolean_get(notification_data* data){
	Preference pref= Preference_get_instance();
	bool b =pref->getBoolean("Boolean",false);
	sprintf(data->result_text,"\"%s\" get by<br>keyword:\"boolean\" at preference",b?"true":"false");
}
void preference_double_get(notification_data* data){
	Preference pref= Preference_get_instance();
	double d =pref->getDouble("double",-100.0);
	sprintf(data->result_text," %lf get by<br>keyword:\"double\" at preference",d);
}
void preference_int_set(notification_data* data){
	static int a=0;
	Preference pref= Preference_get_instance();
	pref->setInt("int",++a);
	sprintf(data->result_text,"&lt;\"int\",%d&gt;<br> saved at preference",a);

}
void preference_string_set(notification_data* data){
	static int a=0;
	char buffer[50]={0,};
	sprintf(buffer,"%s:%d","count",++a);
	Preference pref= Preference_get_instance();
	pref->setString("string",buffer);
	sprintf(data->result_text,"&lt;\"%s\",\"%s\"&gt;<br> saved at preference","string",buffer);

}
void preference_boolean_set(notification_data* data){
	bool b= true;
	Preference pref= Preference_get_instance();
	pref->setBoolean("Boolean",true);
	sprintf(data->result_text," &lt; \"%s\",\"%s\"&gt;<br> saved at preference","boolean",b?"true":"false");


}
void preference_double_set(notification_data* data){
	static double d=0.0;
	Preference pref= Preference_get_instance();
	pref->setDouble("double",d+=0.5);
	sprintf(data->result_text,"&lt;double,%lf&gt;<br> saved at preference",d);
}
void preference__remove(notification_data* data){
	Preference pref= Preference_get_instance();
	pref->Remove("int");
	pref->Remove("double");
	sprintf(data->result_text,"\"int\" and \"double\" are removed");

}
void preference__clear(notification_data* data){

	Preference pref= Preference_get_instance();
	pref->Clear();

	sprintf(data->result_text,"all datas are remove at preference");
}


CameraRecorder CameraRecorder_get_instance(){

	static CameraRecorder cr =NULL;
	if(cr==NULL)
		cr=  NewCameraRecorder();
	return cr;
}


void camerarecorderinit(notification_data* data){
	CameraRecorder cr = CameraRecorder_get_instance();
	bool b=cr->Init(cr,"/opt/usr/media/Videos/VIDEO_RECORDED.mp4", CAMERA_BACK, g_eo);

	sprintf(data->result_text,"%s",b?"video will recorded at <br>/opt/usr/media/Videos/VIDEO_RECORDED.mp4":"init failed");
}
void camerarecorderstart(notification_data* data){
	CameraRecorder cr = CameraRecorder_get_instance();
	bool b =cr->Start(cr);
	sprintf(data->result_text,"%s",b?"start ok":"start fail");
	if (b==true)
		evas_object_show(g_eo);

}
void camerarecorderpause(notification_data* data){
	CameraRecorder cr = CameraRecorder_get_instance();
	bool b= cr->Pause(cr);
	sprintf(data->result_text,"%s",b?"pause ok":"pause fail");
}
void camerarecorderend(notification_data* data){

	CameraRecorder cr = CameraRecorder_get_instance();
	bool b= cr->End(cr);
	sprintf(data->result_text,"%s",b?"CameraRecorder recorded at"
			"<br>opt/usr/media/Videos/VIDEO_RECORDED.mp4"
			:
			"CameraRecorder end fail");

	if (b == true)
	{
		evas_object_hide(g_eo);
	}

}
void camerarecordercancel(notification_data* data){
	CameraRecorder cr = CameraRecorder_get_instance();
	bool b = cr->Cancel(cr);

	sprintf(data->result_text,"%s",b?"cancel sucess<br>VIDEO will not recorded":"cancel fail");
	if( b == true)
	{
		evas_object_hide(g_eo);

	}
}

AudioRecorder audiorec_get_instance(){
	static AudioRecorder pa=NULL;
	if(pa==NULL)
	{
		pa=NewAudioRecorder();
	}
	return pa;
}

void audiorecorderinit(notification_data* data){

	AudioRecorder pa=audiorec_get_instance();
	bool b = pa->Init(pa,"/opt/usr/media/Sounds/AUDIO_RECORDED.mp4");
	sprintf(data->result_text,"%s",b?"AUDIO will recorded at <br>/opt/usr/media/Sounds/AUDIO_RECORDED.mp4":"init failed");

}
void audiorecorderstart(notification_data* data){
	AudioRecorder pa=audiorec_get_instance();
	bool b =pa->Start(pa);
	sprintf(data->result_text,"%s",b?"start ok":"start fail");

}
void audiorecorderpause(notification_data* data){
	AudioRecorder pa=audiorec_get_instance();
	bool b = pa->Pause(pa);
	sprintf(data->result_text,"%s",b?"pause ok":"pause fail");


}
void audiorecorderend(notification_data* data){
	AudioRecorder pa=audiorec_get_instance();
	bool b = pa->End(pa);
	sprintf(data->result_text,"%s",b?"AUDIO recorded at<br>/opt/usr/media/Sounds/AUDIO_RECORDED.mp4":"AudioRecorder  end fail");

}
void audiorecordercancel(notification_data* data){
	AudioRecorder pa=audiorec_get_instance();
	bool b = pa->Cancel(pa);
	sprintf(data->result_text,"%s",b?"cancel sucess<br>AUDIO will not recorded":"cancel fail");

}


