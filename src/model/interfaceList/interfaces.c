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
#include "Interface/Notification.h"
#include "Interface/OngoingNotification.h"
#include <app_common.h>

#include <badge.h>
#include "model/constants.h"
#include "utils/ui-utils.h"
#include "utils/config.h"
#include "utils/logger.h"
#include <stdio.h>
#include <Eina.h>
#include "Interface/Log.h"
#include <Elementary.h>
#include "components.h"
#include "view/tab-view.h"


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


notification_data *log_component_list_get(int *size)
{
	static notification_data notification_list[] =
	{
			{"LOGERROR", NULL, 0, 0, logerror, },
			{"LOGINFO", NULL,  0, 0, loginfo, },
			{"LOGDEBUG", NULL,  0, 0, logdebug, },
			{"LOGWARNING", NULL,  0, 0, logwarning, },
			{"LOGIF", NULL,  0, 0, logif, }

	};
	*size = sizeof(notification_list) / sizeof(notification_list[0]);
	return notification_list;
}

notification_data *notification_component_list_get(int *size)
{
	static notification_data notification_list[] =
	{

			{"setIcon", NULL, 	 0, 0, setNIcon, },
			{"setTitle", NULL,	 0, 0, setNTitle, },
			{"setText", NULL, 	 0, 0, setNText, },
			{"setSound", NULL,	 0, 0, setNSound, },
			{"update", NULL,	 0,0,	NUpdate, },
			{"Show", NULL, 		 0, 0, NShow, },
			{"Hide", NULL,  	0, 0, NHide, }
	};
	*size = sizeof(notification_list) / sizeof(notification_list[0]);
	return notification_list;
}

notification_data *ongoingnotification_component_list_get(int *size)
{
	static notification_data notification_list[] =
	{
			{"setIcon", NULL,  0, 0, setONIcon, },
			{"setTitle", NULL,  0, 0, setONTitle, },
			{"setText", NULL,  0, 0, setONText, },
			{"setSound", NULL,  0, 0, setONSound, },
			{"setProgress", NULL,  0, 0, setONProgress, },
			{"update", NULL,  0, 0, Onupdate, },

			{"Show", NULL,  0, 0, ONShow, },
			{"Hide", NULL,  0, 0, ONHide, }
	};
	*size = sizeof(notification_list) / sizeof(notification_list[0]);
	return notification_list;
}

notification_data *interface_list_get(int *size)
{
	static notification_data notification_list[] =
	{
			{"LOG", NULL, 0, 0, none, },
			{"NOTIFICATION", NULL,  0, 0, none, },
			{"ONGOINGNOTIFICATION", NULL,  0, 0, none, }
	};
	*size = sizeof(notification_list) / sizeof(notification_list[0]);
	return notification_list;
}

void log_fill_item_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=log_component_list_get(&size);

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

void notification_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=notification_component_list_get(&size);

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

void ongoingnotification_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=ongoingnotification_component_list_get(&size);

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

//get_instance Functions

Notification Notification_get_Instance(){
	static Notification pNotification =NULL;
	if(pNotification==NULL)
		pNotification= NewNotification();

	return pNotification;
}
OngoingNotification OngoingNotification_get_Instance(){
	static OngoingNotification pOngoingNotification =NULL;
	if(pOngoingNotification==NULL){
		pOngoingNotification= NewOngoingNotification();
		notification_set_size(((OngoingNotificationExtend*)pOngoingNotification)->ongoingnotification_handle,0.0);

	}
	return pOngoingNotification;
}


//functions set

void logerror(notification_data* data){
	LOGERROR(LOG_TAG,"this is LOGERROR EXAMPLE");
	snprintf(data->result_text,1024,"please<br>"
			"check LOGERROR at log console");
}
void loginfo(notification_data* data){
	LOGINFO(LOG_TAG,"this is LOGINFO EXAMPLE");
	snprintf(data->result_text,1024,"please<br>"
			"check LOGINFO at log console");
}
void logdebug(notification_data* data){
	LOGDEBUG(LOG_TAG,"this is LOGDEBUG EXAMPLE");
	snprintf(data->result_text,1024,"please<br>"
			"check LOGDEBUG at log console");
}
void logwarning(notification_data* data){
	LOGWARNING(LOG_TAG,"this is LOGWARNING EXAMPLE");
	snprintf(data->result_text,1024,"please<br>"
			"check LOGWARNING at log console");

}
void logif(notification_data* data){
	LOGIF(1==1,LOG_TAG,"this is this LOGIF EXAMPLE");
	snprintf(data->result_text,1024,"please<br>"
			"check LOGIF at log console");

}

String getNotiTitle(){
	static char buffer[50]={0,};
	static int x= 0;
	snprintf(buffer,50,"Title #%d",++x);
	return buffer;
}

String getNotiText(){
	static char buffer[50]={0,};
	static int x= 0;
	snprintf(buffer,50,"Text #%d",++x);
	return buffer;
}

String getONNotiTitle(){
	static char buffer[50]={0,};
	static int x= 0;
	snprintf(buffer,50,"Title #%d",++x);
	return buffer;
}

String getONNotiText(){
	static char buffer[50]={0,};
	static int x= 0;
	snprintf(buffer,50,"Text #%d",++x);
	return buffer;
}


void setNIcon(notification_data* data){

	Notification noti = Notification_get_Instance();
	String str=getSharedResourceFile("images/icon1.png");
	noti->setIcon(noti,str);
	sprintf(data->result_text,"icon set<br>icon path is <br>%s",str);
	free(str);
}
void setNTitle(notification_data* data){

	Notification noti = Notification_get_Instance();
	String titlestr=getNotiTitle();
	noti->setTitle(noti,titlestr);
	sprintf(data->result_text,"notification title is %s",titlestr);
}
void setNText(notification_data* data){
	Notification noti = Notification_get_Instance();
	String textstr=getNotiText();

	noti->setText(noti,textstr);
	sprintf(data->result_text,"notification text is %s",textstr);
}
void setNSound(notification_data* data){
	Notification noti = Notification_get_Instance();
	String str=getSharedResourceFile("sounds/sound.mp3");
	noti->setSound(noti,str);
	sprintf(data->result_text,"notification sound file path is<br> %s",str);

	free(str);
}
void NUpdate(notification_data* data){
	Notification noti = Notification_get_Instance();
	bool b =noti->update(noti);

	sprintf(data->result_text,"%s",b?"Notification status updated":"Notification status update failed");

}
void NShow(notification_data* data){
	Notification noti = Notification_get_Instance();
	if(((NotificationExtend*)noti)->visible==false)
	noti->Show(noti);
}
void NHide(notification_data* data){
	Notification noti = Notification_get_Instance();
	if(((NotificationExtend*)noti)->visible==true)
	noti->Hide(noti);
}


void setONIcon(notification_data* data){
	OngoingNotification on_noti = OngoingNotification_get_Instance();
	String str=getSharedResourceFile("images/icon1.png");
	on_noti->setIcon(on_noti,str);
	sprintf(data->result_text,"ongoingnotification icon path is %s",str);

	free(str);
}
void setONTitle(notification_data* data){
	OngoingNotification on_noti =OngoingNotification_get_Instance();
	String titlestr=getONNotiTitle();
	on_noti->setTitle(on_noti,titlestr);
	sprintf(data->result_text,"ongoingnotification title is %s",titlestr);

}
void setONText(notification_data* data){
	OngoingNotification on_noti = OngoingNotification_get_Instance();
	String textstr=getONNotiText();
	on_noti->setText(on_noti,textstr);
	sprintf(data->result_text,"ongoingnotification text is %s",textstr);


}
void setONSound(notification_data* data){
	OngoingNotification on_noti = OngoingNotification_get_Instance();
	String str=getSharedResourceFile("sounds/sound.mp3");

	on_noti->setSound(on_noti,str);
	sprintf(data->result_text,"ongoingnotification <br>sound file path is<br> %s",str);

	free(str);
}
void setONProgress(notification_data* data){
	OngoingNotification on_noti = OngoingNotification_get_Instance();
	static double progress_rate=0.1;

	on_noti->setProgress(on_noti,progress_rate);
	sprintf(data->result_text,"ongoingnotification <br>progress %.2lf%%",progress_rate*100);

	progress_rate+=0.1;

	if(progress_rate>1.0)
		progress_rate=0.0;

}


void ONShow(notification_data* data){
	OngoingNotification on_noti = OngoingNotification_get_Instance();
	if(((OngoingNotificationExtend*)on_noti)->visible==false)
	{
		on_noti->Show(on_noti);
	}
}
void ONHide(notification_data* data){
	OngoingNotification on_noti = OngoingNotification_get_Instance();
	if(((OngoingNotificationExtend*)on_noti)->visible==true)
	{
	on_noti->Hide(on_noti);
	}
}

void Onupdate(notification_data* data){
	OngoingNotification on_noti = OngoingNotification_get_Instance();
	bool b = on_noti->update(on_noti);
	sprintf(data->result_text,"Ongoing%s",b?"Notification status updated":"Notification status update failed");


}

