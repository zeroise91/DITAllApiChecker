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


#define MAX_ATTRIBUTE_NUM 32

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



notification_data *device_list_get(int *size){
	static notification_data components[] =
	{
			{ "DeviceStatus", NULL,  0, 0, none, },
			{ "File", NULL,  0, 0, none, },
			{ "Preference", NULL,  0, 0, none, },
			{ "Sensor", NULL,  0, 0, none, },
			{ "Vibrator", NULL,  0, 0, none, }
	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *devicestatus_list_get(int *size){
	static notification_data components[] =
	{
			{ "Lock", NULL,  0, 0, Lock, },
			{ "unLock", NULL,  0, 0, unLock, },
			{ "Dim", NULL,  0, 0, Dim, },

			{ "getBright", NULL,  0, 0, getBright, },
			{ "setBright", NULL,  0, 0, setBright, },

			{ "getLevel", NULL,  0, 0, getLevel, },
			{ "isCharging", NULL,  0, 0, isCharging, },

			{ "On(flash)", NULL,  0, 0, onflash, },
			{ "Off(flash)", NULL,  0, 0, offflash, },

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *file_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "deleteFile", NULL,  0, 0, deletefile, },
			{ "copyfile", NULL,  0, 0, copyfile, },
			{ "moveFile", NULL,  0, 0, movefile, },
			{ "searchFile", NULL,  0, 0, searchfile, },

			{ "setEvasObject", NULL,  0, 0, setevasObject, },
			{ "setURI(video)", NULL,  0, 0, setURI_video, },
			{ "getVideoinfo", NULL,  0, 0, getvideoinfo, },
			{ "playVideo", NULL,  0, 0, playvideo, },
			{ "pauseVideo", NULL,  0, 0, pausevideo, },
			{ "stopVideo", NULL,  0, 0, stopvideo, },
			{ "recordVideo", NULL,  0, 0, recordvideo, },

			{ "setURI(audio)", NULL,  0, 0, setURI_audio, },
			{ "playAudio", NULL,  0, 0, playaudio, },
			{ "pauseAudio", NULL,  0, 0, pauseaudio, },
			{ "stopAudio", NULL,  0, 0, stopaudio, },
			{ "recordAudio", NULL,  0, 0, recordaudio, },
			{ "getAudioInfo", NULL,  0, 0, getaudioInfo, },

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
			{ "Gravity", NULL,  0, 0, none, },
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
void _tab_view_layout_fill_act(void *data, Evas_Object *obj, void *event_info);


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
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}
Evas_Object* img=NULL;
Evas* canvas=NULL;


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
		evas_object_image_file_set(img, "/opt/usr/media/Downloads/1.jpg", NULL);//Set the source file from where an image object must fetch the real image data
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
void _tab_view_layout_fill_act(void *data, Evas_Object *obj, void *event_info){

	elm_list_item_selected_set(event_info, EINA_FALSE);
	notification_data *notification_info = (notification_data *)data;
	notification_info->callback(notification_info);

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

	Accelerometer a=NewAccelerometer();
	Gravity b=NewGravity();
	LinearAccelation c = NewLinearAccelation();
	Magnetometer d= NewMagnetometer();
	RotationVector e= NewRotationVector();
	Orientation f= NewOrientation();
	Gyroscope g= NewGyroscope();
	Light h= NewLight();
	Proximity i = NewProximity();
	Pressure j= NewPressure();
	UltraViolet k= NewUltraViolet();
	Temperature l = NewTemperature();
	Humidity m = NewHumidity();

	if(a!=NULL)
		elm_list_item_append(list,notification_list[0].name,NULL,NULL,Accelerometer_item_fill_cb,&notification_list[0]);
	if(b!=NULL)
		elm_list_item_append(list,notification_list[1].name,NULL,NULL,Gravity_item_fill_cb,&notification_list[1]);
	if(c!=NULL)
		elm_list_item_append(list,notification_list[2].name,NULL,NULL,LinearAccelation_item_fill_cb,&notification_list[2]);
	if(d!=NULL)
		elm_list_item_append(list,notification_list[3].name,NULL,NULL,MagnetoMeter_item_fill_cb,&notification_list[3]);
	if(e!=NULL)
		elm_list_item_append(list,notification_list[4].name,NULL,NULL,RotationVector_item_fill_cb,&notification_list[4]);
	if(f!=NULL)
		elm_list_item_append(list,notification_list[5].name,NULL,NULL,Orientation_item_fill_cb,&notification_list[5]);
	if(g!=NULL)
		elm_list_item_append(list,notification_list[6].name,NULL,NULL,Gyroscope_item_fill_cb,&notification_list[6]);
	if(h!=NULL)
		elm_list_item_append(list,notification_list[7].name,NULL,NULL,Light_item_fill_cb,&notification_list[7]);
	if(i!=NULL)
		elm_list_item_append(list,notification_list[8].name,NULL,NULL,Proximity_item_fill_cb,&notification_list[8]);
	if(j!=NULL)
		elm_list_item_append(list,notification_list[9].name,NULL,NULL,Pressure_item_fill_cb,&notification_list[9]);
	if(k!=NULL)
		elm_list_item_append(list,notification_list[10].name,NULL,NULL,UltraViolet_item_fill_cb,&notification_list[10]);
	if(l!=NULL)
		elm_list_item_append(list,notification_list[11].name,NULL,NULL,Temperature_item_fill_cb,&notification_list[11]);
	if(m!=NULL)
		elm_list_item_append(list,notification_list[12].name,NULL,NULL,Humidity_item_fill_cb,&notification_list[12]);


	DestroyAccelerometer(a);
	DestroyGravity(b);
	DestroyLinearAccelation(c);
	DestroyMagnetometer(d);
	DestroyRotationVector(e);
	DestroyOrientation(f);
	DestroyGyroscope(g);
	DestroyLight(h);
	DestroyProximity(i);
	DestroyPressure(j);
	DestroyUltraViolet(k);
	DestroyTemperature(l);
	DestroyHumidity(m);

	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);

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
	image->extractInfo(image,"/opt/usr/media/Downloads/1.jpg");
	snprintf(data->result_text,1024,"image <br>/opt/usr/media/Downloads/1.jpg<br>metadata extract complete");
}


void  getimageBurstId (notification_data* data){
	Image image= image_get_instance();
	if(((ImageExtends*)image)->imageMetaHandle){
			String str =image->getBurstId(image);
		snprintf(data->result_text,1024,"MeiaID: %s",str?str:"(none)");

		}
		else{
			snprintf(data->result_text,1024,"press extractInfo button first");
		}
}
void  getimageMediaId (notification_data* data){
	Image image= image_get_instance();
	if(((ImageExtends*)image)->imageMetaHandle){
		String str =image->getMediaId(image);
	snprintf(data->result_text,1024,"MeiaID: %s",str?str:"(none)");

	}
	else{
		snprintf(data->result_text,1024,"press extractInfo button first");
	}


}
void  getimageDateTaken (notification_data* data){
	Image image= image_get_instance();
	if(((ImageExtends*)image)->imageMetaHandle){
		String str = image->getDateTaken(image);
	snprintf(data->result_text,1024,"MeiaID: %s",str?str:"(none)");

	}
	else{
		snprintf(data->result_text,1024,"press extractInfo button first");
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
		snprintf(data->result_text,1024,"press extractInfo button first");

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
		snprintf(data->result_text,1024,"press extractInfo button first");

	}

}

void deletefile(notification_data* data){
	File file = NewFile();
	if(access("/opt/usr/media/Downloads/3.mp3",F_OK)!=-1){

	file->Delete("/opt/usr/media/Downloads/3.mp3");
	sprintf(data->result_text,"/opt/usr/media/Downloads/3.mp3<br>deleted");
	}
	else
	{
		sprintf(data->result_text,"delete target File:<br>/opt/usr/media/Downloads/3.mp3<br>doesn't exist");
	}
	DestroyFile(file);
}
void copyfile(notification_data* data){
		File file = NewFile();
		if(access("/opt/usr/media/Downloads/2.mp3",F_OK)!=-1){

		file->Copy("/opt/usr/media/Downloads/2.mp3","/opt/usr/media/Downloads/3.mp3");
		sprintf(data->result_text,"/opt/usr/media/Downloads/2.mp3"
				"<br><br>copied to<br><br>"
				"/opt/usr/media/Downloads/3.mp3");

		}else{
			sprintf(data->result_text,"copy source file:<br>/opt/usr/media/Downloads/2.mp3 doesn't exist");
		}
		DestroyFile(file);

}
void movefile(notification_data* data){
	File file = NewFile();
	if(access("/opt/usr/media/Downloads/3.mp3",F_OK)!=-1){
	file->Move("/opt/usr/media/Downloads/3.mp3","/opt/usr/media/Downloads/4.mp3");
	sprintf(data->result_text,"/opt/usr/media/Downloads/3.mp3<br><br>moved to<br><br>/opt/usr/media/Downloads/4.mp3");
	}
	else
	{
		sprintf(data->result_text,"/opt/usr/media/Downloads/3.mp3 doesn't exist");

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
	evas_object_show(img);							// Make the given Evas object visible
	Video v= video_get_instance();

	if(((VideoExtends*)v)->uri&&((VideoExtends*)v)->EvasObject)
	{
	v->Play(v);
	sprintf(data->result_text,"video play");

	}
	else{
		sprintf(data->result_text,"press<br>setEvasObject button<br>setURI(Video)<br>first");
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
			sprintf(data->result_text,"press<br>setEvasObject button<br>setURI(Video)<br>first");
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
			sprintf(data->result_text,"press<br>setEvasObject button<br>setURI(Video)<br>first");
		}
}
void recordvideo(notification_data* data){

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
	v->setURI(v,"/opt/usr/media/Videos/test.mp4");
}

void setevasObject(notification_data* data){

	Video v= video_get_instance();
	v->setObject(v,img);
}

void playaudio(notification_data* data){
	Audio a=audio_get_instance();
	if(	((AudioExtends*) a)->uri)
		a->Play(a);
}
void pauseaudio(notification_data* data){
	Audio a=audio_get_instance();

	if(	((AudioExtends*) a)->uri)
		a->Pause(a);
	else
	{

	}
}
void stopaudio(notification_data* data){
	Audio a=audio_get_instance();

	if(	((AudioExtends*) a)->uri)
		a->Stop(a);

}
void recordaudio(notification_data* data){

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
	a->setURI(a,"/opt/usr/media/Music/Over the Horizon.mp3");
	sprintf(data->result_text,"audiofile path <br>/opt/usr/media/Music/Over the Horizon.mp3<br> set");
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

