/*
 * sensor_elements.c
 *
 *  Created on: Jul 23, 2015
 *      Author: parkbeomchan
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


#include "Device/Sensor.h"

typedef struct
{
	Evas_Object *navi;
	Elm_Object_Item *navi_item;
	Evas_Object *layout;
	const char *name;
} layout_view_data2;






notification_data *Accelerometer_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, accaddCallback, },
			{ "datachCallback", NULL,  0, 0, accdatachCallback, },
			{ "On", NULL,  0, 0, accon, },
			{ "Off", NULL,  0, 0, accoff, },
			{ "isSupported", NULL,  0, 0, accisSupported, },
			{ "getValue", NULL,  0, 0, accgetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *Gravity_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, GravityaddCallback, },
			{ "datachCallback", NULL,  0, 0, GravitydatachCallback, },
			{ "On", NULL,  0, 0, Gravityon, },
			{ "Off", NULL,  0, 0, Gravityoff, },
			{ "isSupported", NULL,  0, 0, GravityisSupported, },
			{ "getValue", NULL,  0, 0, GravitygetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}
notification_data *LinearAccelation_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, LinearAccelationaddCallback, },
			{ "datachCallback", NULL,  0, 0, LinearAccelationdatachCallback, },
			{ "On", NULL,  0, 0, LinearAccelationoff, },
			{ "Off", NULL,  0, 0, LinearAccelationon, },
			{ "isSupported", NULL,  0, 0, LinearAccelationisSupported, },
			{ "getValue", NULL,  0, 0, LinearAccelationgetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *MagnetoMeter_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, MagnetoMeteraddCallback, },
			{ "datachCallback", NULL,  0, 0, MagnetoMeterdatachCallback, },
			{ "On", NULL,  0, 0, MagnetoMeteron, },
			{ "Off", NULL,  0, 0, MagnetoMeteroff, },
			{ "isSupported", NULL,  0, 0, MagnetoMeterisSupported, },
			{ "getValue", NULL,  0, 0, MagnetoMetergetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *Rotationvector_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, RotationVectoraddCallback, },
			{ "datachCallback", NULL,  0, 0, RotationVectordatachCallback, },
			{ "On", NULL,  0, 0, RotationVectoron, },
			{ "Off", NULL,  0, 0, RotationVectoroff, },
			{ "isSupported", NULL,  0, 0, RotationVectorisSupported, },
			{ "getValue", NULL,  0, 0, RotationVectorgetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *Orientation_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, OrientationaddCallback, },
			{ "datachCallback", NULL,  0, 0, OrientationdatachCallback, },
			{ "On", NULL,  0, 0, Orientationon, },
			{ "Off", NULL,  0, 0, Orientationoff, },
			{ "isSupported", NULL,  0, 0, OrientationisSupported, },
			{ "getValue", NULL,  0, 0, OrientationgetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}


notification_data *Gyroscope_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, GyroscopeaddCallback, },
			{ "datachCallback", NULL,  0, 0, GyroscopedatachCallback, },
			{ "On", NULL,  0, 0, Gyroscopeon, },
			{ "Off", NULL,  0, 0, Gyroscopeoff, },
			{ "isSupported", NULL,  0, 0, GyroscopeisSupported, },
			{ "getValue", NULL,  0, 0, GyroscopegetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}


notification_data *Light_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, LightaddCallback, },
			{ "datachCallback", NULL,  0, 0, LightdatachCallback, },
			{ "On", NULL,  0, 0, Lighton, },
			{ "Off", NULL,  0, 0, Lightoff, },
			{ "isSupported", NULL,  0, 0, LightisSupported, },
			{ "getValue", NULL,  0, 0, LightgetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *Proximity_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, ProximityaddCallback, },
			{ "datachCallback", NULL,  0, 0, ProximitydatachCallback, },
			{ "On", NULL,  0, 0, Proximityon, },
			{ "Off", NULL,  0, 0, Proximityoff, },
			{ "isSupported", NULL,  0, 0, ProximityisSupported, },
			{ "getValue", NULL,  0, 0, ProximitygetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *Pressure_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, PressureaddCallback, },
			{ "datachCallback", NULL,  0, 0, PressuredatachCallback, },
			{ "On", NULL,  0, 0, Pressureon, },
			{ "Off", NULL,  0, 0, Pressureoff, },
			{ "isSupported", NULL,  0, 0, PressureisSupported, },
			{ "getValue", NULL,  0, 0, PressuregetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *UltraViolet_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, UltraVioletaddCallback, },
			{ "datachCallback", NULL,  0, 0, UltraVioletdatachCallback, },
			{ "On", NULL,  0, 0, UltraVioleton, },
			{ "Off", NULL,  0, 0, UltraVioletoff, },
			{ "isSupported", NULL,  0, 0, none, },
			{ "getValue", NULL,  0, 0, UltraVioletgetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *Temperature_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, TemperatureaddCallback, },
			{ "datachCallback", NULL,  0, 0, TemperaturedatachCallback, },
			{ "On", NULL,  0, 0, Humidityon, },
			{ "Off", NULL,  0, 0, TemperaturedatachCallback, },
			{ "isSupported", NULL,  0, 0, TemperatureisSupported, },
			{ "getValue", NULL,  0, 0, TemperaturegetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}

notification_data *Humidity_component_list_get(int *size){
	static notification_data components[] =
	{
			{ "addCallback", NULL,  0, 0, HumidityaddCallback, },
			{ "datachCallback", NULL,  0, 0, HumiditydatachCallback, },
			{ "On", NULL,  0, 0, Humidityon, },
			{ "Off", NULL,  0, 0, Humidityoff, },
			{ "isSupported", NULL,  0, 0, HumidityisSupported, },
			{ "getValue", NULL,  0, 0, HumiditygetValue, }

	};
	*size = sizeof(components) / sizeof(components[0]);
	return components;
}


void Accelerometer_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Accelerometer_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void MagnetoMeter_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=MagnetoMeter_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void Gravity_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Gravity_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void LinearAccelation_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=LinearAccelation_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void RotationVector_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Rotationvector_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void Orientation_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Orientation_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void Gyroscope_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Gyroscope_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void Light_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Light_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void Proximity_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Proximity_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}


void Pressure_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Pressure_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}
void UltraViolet_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=UltraViolet_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void Temperature_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Temperature_component_list_get(&size);

	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}

void Humidity_item_fill_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=Humidity_component_list_get(&size);
	notification_list[0].status=lists;

	elm_list_item_append(list,notification_list[0].name,NULL,NULL,_sensorcallback_layout_fill_cb2depth,&notification_list[0]);

	for(int i=1;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);

	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
	//	_tab_view_layout_fill_cb2depth(data,obj,event_info);
}


Accelerometer Accelerometer_get_Instance(){
	static Accelerometer pAccelerometer=NULL;
	(pAccelerometer==NULL)? pAccelerometer=NewAccelerometer():pAccelerometer ;
	return pAccelerometer;
}

Gravity Gravity_get_Instance(){
	static Gravity Gravity=NULL;
	(Gravity==NULL)? Gravity=NewGravity():Gravity ;
	return Gravity;
}

LinearAccelation LinearAccelation_get_Instance(){
	static LinearAccelation LinearAccelation=NULL;
	(LinearAccelation==NULL)? LinearAccelation=NewLinearAccelation():LinearAccelation ;
	return LinearAccelation;
}

Magnetometer MagnetoMeter_get_Instance(){
	static Magnetometer MagnetoMeter=NULL;
	(MagnetoMeter==NULL)? MagnetoMeter=NewMagnetometer():MagnetoMeter ;
	return MagnetoMeter;
}


RotationVector RotationVector_get_Instance(){
	static RotationVector RotationVector=NULL;
	(RotationVector==NULL)? RotationVector=NewRotationVector():RotationVector ;
	return RotationVector;
}

Orientation Orientation_get_Instance(){
	static Orientation Orientation=NULL;
	(Orientation==NULL)? Orientation=NewOrientation():Orientation ;
	return Orientation;
}

Gyroscope Gyroscope_get_Instance(){
	static Gyroscope Gyroscope=NULL;
	(Gyroscope==NULL)? Gyroscope=NewGyroscope():Gyroscope ;
	return Gyroscope;
}

Light Light_get_Instance(){
	static Light Light=NULL;
	(Light==NULL)? Light=NewLight():Light ;
	return Light;
}

Pressure Pressure_get_Instance(){
	static Pressure Pressure=NULL;
	(Pressure==NULL)? Pressure=NewPressure():Pressure ;
	return Pressure;
}

Proximity Proximity_get_Instance(){
	static Proximity Proximity=NULL;
	(Proximity==NULL)? Proximity=NewProximity():Proximity ;
	return Proximity;
}
UltraViolet UltraViolet_get_Instance(){
	static UltraViolet UltraViolet=NULL;
	(UltraViolet==NULL)? UltraViolet=NewUltraViolet():UltraViolet ;
	return UltraViolet;
}

Temperature Temperature_get_Instance(){
	static Temperature Temperature=NULL;
	(Temperature==NULL)? Temperature=NewTemperature():Temperature ;
	return Temperature;
}

Humidity Humidity_get_Instance(){
	static Humidity Humidity=NULL;
	(Humidity==NULL)? Humidity=NewHumidity():Humidity ;
	return Humidity;
}

void accCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"accurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void accaddCallback(notification_data *data){
	Accelerometer pA= Accelerometer_get_Instance();
	pA->addCallback(pA,accCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void accdatachCallback(notification_data *data){
	Accelerometer pA= Accelerometer_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void accon(notification_data *data){
	Accelerometer pA= Accelerometer_get_Instance();
	pA->On(pA);
}
void accoff(notification_data *data){
	Accelerometer pA= Accelerometer_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void accisSupported(notification_data* data){
	Accelerometer pA= Accelerometer_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void accgetValue(notification_data* data){
	Accelerometer pA= Accelerometer_get_Instance();
	Accelerometer_data vs= pA->getValue(pA);

	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"accurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.x,vs.y,vs.z);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.x);
	LOGI("%.2f",vs.y);
	LOGI("%.2f",vs.z);
}

void GravityCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Gravityurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void GravityaddCallback(notification_data *data){
	Gravity pA= Gravity_get_Instance();
	pA->addCallback(pA,GravityCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void GravitydatachCallback(notification_data *data){
	Gravity pA= Gravity_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Gravityon(notification_data *data){
	Gravity pA= Gravity_get_Instance();
	pA->On(pA);
}
void Gravityoff(notification_data *data){
	Gravity pA= Gravity_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void GravityisSupported(notification_data* data){
	Gravity pA= Gravity_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void GravitygetValue(notification_data* data){
	Gravity pA= Gravity_get_Instance();
	Gravity_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Gravityurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.x,vs.y,vs.z);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}

	LOGI("%.2f",vs.x);
	LOGI("%.2f",vs.y);
	LOGI("%.2f",vs.z);
}

void LinearAccelationCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"LinearAccelationurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void LinearAccelationaddCallback(notification_data *data){
	LinearAccelation pA= LinearAccelation_get_Instance();
	pA->addCallback(pA,LinearAccelationCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void LinearAccelationdatachCallback(notification_data *data){
	LinearAccelation pA= LinearAccelation_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void LinearAccelationon(notification_data *data){
	LinearAccelation pA= LinearAccelation_get_Instance();
	pA->On(pA);
}
void LinearAccelationoff(notification_data *data){
	LinearAccelation pA= LinearAccelation_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void LinearAccelationisSupported(notification_data* data){
	LinearAccelation pA= LinearAccelation_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void LinearAccelationgetValue(notification_data* data){
	LinearAccelation pA= LinearAccelation_get_Instance();
	LinearAcceleration_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"LinearAccelationurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.x,vs.y,vs.z);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.x);
	LOGI("%.2f",vs.y);
	LOGI("%.2f",vs.z);
}

void MagnetoMeterCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"MagnetoMeterurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void MagnetoMeteraddCallback(notification_data *data){
	Magnetometer pA= MagnetoMeter_get_Instance();
	pA->addCallback(pA,MagnetoMeterCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void MagnetoMeterdatachCallback(notification_data *data){
	Magnetometer pA= MagnetoMeter_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void MagnetoMeteron(notification_data *data){
	Magnetometer pA= MagnetoMeter_get_Instance();
	pA->On(pA);
}
void MagnetoMeteroff(notification_data *data){
	Magnetometer pA= MagnetoMeter_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void MagnetoMeterisSupported(notification_data* data){
	Magnetometer pA= MagnetoMeter_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void MagnetoMetergetValue(notification_data* data){
	Magnetometer pA= MagnetoMeter_get_Instance();
	Magnetometer_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"MagnetoMeterurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.x,vs.y,vs.z);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.x);
	LOGI("%.2f",vs.y);
	LOGI("%.2f",vs.z);
}

void RotationVectorCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"RotationVectorurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void RotationVectoraddCallback(notification_data *data){
	RotationVector pA= RotationVector_get_Instance();
	pA->addCallback(pA,RotationVectorCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void RotationVectordatachCallback(notification_data *data){
	RotationVector pA= RotationVector_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void RotationVectoron(notification_data *data){
	RotationVector pA= RotationVector_get_Instance();
	pA->On(pA);
}
void RotationVectoroff(notification_data *data){
	RotationVector pA= RotationVector_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void RotationVectorisSupported(notification_data* data){
	RotationVector pA= RotationVector_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void RotationVectorgetValue(notification_data* data){
	RotationVector pA= RotationVector_get_Instance();
	RotationVector_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"RotationVectorurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.x,vs.y,vs.z);}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}

	LOGI("%.2f",vs.x);
	LOGI("%.2f",vs.y);
	LOGI("%.2f",vs.z);
}


void OrientationCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Orientationurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void OrientationaddCallback(notification_data *data){
	Orientation pA= Orientation_get_Instance();
	pA->addCallback(pA,OrientationCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void OrientationdatachCallback(notification_data *data){
	Orientation pA= Orientation_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Orientationon(notification_data *data){
	Orientation pA= Orientation_get_Instance();
	pA->On(pA);
}
void Orientationoff(notification_data *data){
	Orientation pA= Orientation_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void OrientationisSupported(notification_data* data){
	Orientation pA= Orientation_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void OrientationgetValue(notification_data* data){
	Orientation pA= Orientation_get_Instance();
	Orientation_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Orientationurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.x,vs.y,vs.z);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.x);
	LOGI("%.2f",vs.y);
	LOGI("%.2f",vs.z);
}

void GyroscopeCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Gyroscopeurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void GyroscopeaddCallback(notification_data *data){
	Gyroscope pA= Gyroscope_get_Instance();
	pA->addCallback(pA,GyroscopeCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void GyroscopedatachCallback(notification_data *data){
	Gyroscope pA= Gyroscope_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Gyroscopeon(notification_data *data){
	Gyroscope pA= Gyroscope_get_Instance();
	pA->On(pA);
}
void Gyroscopeoff(notification_data *data){
	Gyroscope pA= Gyroscope_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void GyroscopeisSupported(notification_data* data){
	Gyroscope pA= Gyroscope_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void GyroscopegetValue(notification_data* data){
	Gyroscope pA= Gyroscope_get_Instance();
	Gyroscope_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Gyroscopeurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.x,vs.y,vs.z);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.x);
	LOGI("%.2f",vs.y);
	LOGI("%.2f",vs.z);
}
void LightCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Lighturancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void LightaddCallback(notification_data *data){
	Light pA= Light_get_Instance();
	pA->addCallback(pA,LightCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void LightdatachCallback(notification_data *data){
	Light pA= Light_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Lighton(notification_data *data){
	Light pA= Light_get_Instance();
	pA->On(pA);
}
void Lightoff(notification_data *data){
	Light pA= Light_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void LightisSupported(notification_data* data){
	Light pA= Light_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void LightgetValue(notification_data* data){
	Light pA= Light_get_Instance();
	Light_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Lighturancy: %d<br>"
				"level: %f"

				,vs.timestamp,vs.value_count,vs.accuracy,vs.level);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.level);
}

void ProximityCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Proximityurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void ProximityaddCallback(notification_data *data){
	Proximity pA= Proximity_get_Instance();
	pA->addCallback(pA,ProximityCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void ProximitydatachCallback(notification_data *data){
	Proximity pA= Proximity_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Proximityon(notification_data *data){
	Proximity pA= Proximity_get_Instance();
	pA->On(pA);
}
void Proximityoff(notification_data *data){
	Proximity pA= Proximity_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void ProximityisSupported(notification_data* data){
	Proximity pA= Proximity_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void ProximitygetValue(notification_data* data){
	Proximity pA= Proximity_get_Instance();
	Proximity_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Proximityurancy: %d<br>"
				"proximity: %f<br>"
				,vs.timestamp,vs.value_count,vs.accuracy,vs.proximity);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}

	LOGI("%.2f",vs.proximity);
}


void PressureCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Pressureurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void PressureaddCallback(notification_data *data){
	Pressure pA= Pressure_get_Instance();
	pA->addCallback(pA,PressureCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void PressuredatachCallback(notification_data *data){
	Pressure pA= Pressure_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Pressureon(notification_data *data){
	Pressure pA= Pressure_get_Instance();
	pA->On(pA);
}
void Pressureoff(notification_data *data){
	Pressure pA= Pressure_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void PressureisSupported(notification_data* data){
	Pressure pA= Pressure_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void PressuregetValue(notification_data* data){
	Pressure pA= Pressure_get_Instance();
	Pressure_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Pressureurancy: %d<br>"
				"x: %f<br>"
				"y: %f<br>"
				"z: %f<br>",
				vs.timestamp,vs.value_count,vs.accuracy,vs.hPa);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.hPa);

}

void UltraVioletCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"UltraVioleturancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void UltraVioletaddCallback(notification_data *data){
	UltraViolet pA= UltraViolet_get_Instance();
	pA->addCallback(pA,UltraVioletCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void UltraVioletdatachCallback(notification_data *data){
	UltraViolet pA= UltraViolet_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void UltraVioleton(notification_data *data){
	UltraViolet pA= UltraViolet_get_Instance();
	pA->On(pA);
}
void UltraVioletoff(notification_data *data){
	UltraViolet pA= UltraViolet_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void UltraVioletisSupported(notification_data* data){
	UltraViolet pA= UltraViolet_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void UltraVioletgetValue(notification_data* data){
	UltraViolet pA= UltraViolet_get_Instance();
	UltraViolet_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"UltraVioleturancy: %d<br>"
				"uvIndex: %f<br>"
				,
				vs.timestamp,vs.value_count,vs.accuracy,vs.uvindex);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.uvindex);
}

void TemperatureCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Temperatureurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void TemperatureaddCallback(notification_data *data){
	Temperature pA= Temperature_get_Instance();
	pA->addCallback(pA,TemperatureCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void TemperaturedatachCallback(notification_data *data){
	Temperature pA= Temperature_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Temperatureon(notification_data *data){
	Temperature pA= Temperature_get_Instance();
	pA->On(pA);
}
void Temperatureoff(){
	Temperature pA= Temperature_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void TemperatureisSupported(notification_data* data){
	Temperature pA= Temperature_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void TemperaturegetValue(notification_data* data){
	Temperature pA= Temperature_get_Instance();
	Temperature_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Temperatureurancy: %d<br>"
				"celcius: %f<br>"
				,
				vs.timestamp,vs.value_count,vs.accuracy,vs.celsius);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.celsius);

}

void HumidityCALLBACK(sensor_h sensor, sensor_event_s *event, void *user_data){

	notification_data*data=	(notification_data*)user_data;
	snprintf(data->result_text,1024,
			"timestamp: %llu<br>"
			"value_count: %d<br>"
			"Humidityurancy: %d<br>"
			"x: %f<br>"
			"y: %f<br>"
			"z: %f<br>",
			event->timestamp,event->value_count,event->accuracy,
			event->values[0],event->values[1],event->values[2]);

	elm_object_text_set(_get_title(), data->result_text);


}


void HumidityaddCallback(notification_data *data){
	Humidity pA= Humidity_get_Instance();
	pA->addCallback(pA,HumidityCALLBACK,100,data);
	snprintf(data->result_text,1024,"add callback completed");
}
void HumiditydatachCallback(notification_data *data){
	Humidity pA= Humidity_get_Instance();
	pA->detachCallback(pA);
	snprintf(data->result_text,1024,"detach callback completed");
}

void Humidityon(notification_data *data){
	Humidity pA= Humidity_get_Instance();
	pA->On(pA);
}
void Humidityoff(notification_data *data){
	Humidity pA= Humidity_get_Instance();
	pA->Off(pA);
	LOGI("OFF called");
}


void HumidityisSupported(notification_data* data){
	Humidity pA= Humidity_get_Instance();
	bool x=pA->isSupported(pA);
	snprintf(data->result_text,1024,"%s",x?"supports":"do not supports");
}

void HumiditygetValue(notification_data* data){
	Humidity pA= Humidity_get_Instance();
	Humidity_data vs= pA->getValue(pA);
	if(vs.accuracy!=0)
	{
		snprintf(data->result_text,1024,
				"timestamp: %llu<br>"
				"value_count: %d<br>"
				"Humidityurancy: %d<br>"
				"humilitypercent: %f<br>"
				,
				vs.timestamp,vs.value_count,vs.accuracy,vs.percent);
	}
	else
	{
		snprintf(data->result_text,1024,"Sensor is off");
	}
	LOGI("%.2f",vs.percent);
}









