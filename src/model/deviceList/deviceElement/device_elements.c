
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


typedef struct
{
	Evas_Object *navi;
	Elm_Object_Item *navi_item;
	Evas_Object *layout;
	const char *name;
} layout_view_data2;




notification_data *file_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "deleteFile", NULL,  0, 0, deletefile, },
			{ "copyfile", NULL,  0, 0, copyfile, },
			{ "moveFile", NULL,  0, 0, movefile, },
			{ "searchFile", NULL,  0, 0, searchfile, }


	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *video_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "setEvasObject", NULL,  0, 0, setevasObject, },
			{ "setURI(video)", NULL,  0, 0, setURI_video, },
			{ "playVideo", NULL,  0, 0, playvideo, },
			{ "pauseVideo", NULL,  0, 0, pausevideo, },
			{ "stopVideo", NULL,  0, 0, stopvideo, },
			{ "getVideoinfo", NULL,  0, 0, getvideoinfo, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *audio_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "setURI(audio)", NULL,  0, 0, setURI_audio, },
			{ "playAudio", NULL,  0, 0, playaudio, },
			{ "pauseAudio", NULL,  0, 0, pauseaudio, },
			{ "stopAudio", NULL,  0, 0, stopaudio, },
			{ "getAudioInfo", NULL,  0, 0, getaudioInfo, }


	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *image_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "extractImageInfo", NULL,  0, 0, extractinfo, },
			{ "getimageBurstId", NULL,  0, 0, getimageBurstId, },
			{ "getimageMediaId", NULL,  0, 0, getimageMediaId, },
			{ "getimageDateTaken", NULL,  0, 0, getimageDateTaken, },
			{ "getimageHeight", NULL,  0, 0, getimageHeight, },
			{ "getimageWidth", NULL,  0, 0, getimageWidth, }
	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *camerarecorder_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "Init", NULL,  0, 0, camerarecorderinit, },
			{ "start", NULL,  0, 0, camerarecorderstart, },
			{ "pause", NULL,  0, 0,camerarecorderpause, },
			{ "end", NULL,  0, 0, camerarecorderend, },
			{ "cancel", NULL,  0, 0,camerarecordercancel, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *audiorecorder_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "Init", NULL,  0, 0, audiorecorderinit, },
			{ "start", NULL,  0, 0, audiorecorderstart, },
			{ "pause", NULL,  0, 0,audiorecorderpause, },
			{ "end", NULL,  0, 0, audiorecorderend, },
			{ "cancel", NULL,  0, 0, audiorecordercancel, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}




void file_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=file_component_list_get(&size);


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


void video_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=video_component_list_get(&size);


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
void audio_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=audio_component_list_get(&size);


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
void image_view_layout_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=image_component_list_get(&size);


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



