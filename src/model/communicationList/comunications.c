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
#include <stdio.h>
#include <Eina.h>
#include "Interface/Log.h"
#include <Elementary.h>
#include "components.h"
#include "view/tab-view.h"
#include "Commnucation/Http.h"
#include "Commnucation/Socket.h"
#include "Commnucation/Bluetooth.h"
#include "Commnucation/GPS.h"
#include "Commnucation/NFC.h"

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


notification_data *communication_list_get(int *size)
{
	static notification_data communications[] =
	{
			{ "BLUETOOTH", NULL,  0, 0, none, },
			{ "GPS", NULL,  0, 0, none, },
			{ "HTTP", NULL,  0, 0, none, },
			{ "NFC", NULL,  0, 0, none, },
			{ "SOCKET", NULL,  0, 0, none, }
	};
	*size = sizeof(communications) / sizeof(communications[0]);
	return communications;
}

notification_data *bouetooth_component_list_get(int *size)
{
	static notification_data communications[] =
	{
			{ "isAccessible", NULL,  0, 0, isBTaccessible, },
			{ "onConnect", NULL,  0, 0, onBTconnect, },
			{ "onDisconnect", NULL,  0, 0, onBTdisconnect, },
			{ "Recv", NULL,  0, 0, BTrecv, },
			{ "Send", NULL,  0, 0, BTsend, },
			{ "isConnected", NULL,  0, 0, isBTconnected, }

	};
	*size = sizeof(communications) / sizeof(communications[0]);
	return communications;
}

notification_data *gps_component_list_get(int *size)
{
	static notification_data communications[] =
	{
			{ "isAccessible", NULL,  0, 0, isGPSaccessible, },
			{ "onConnect", NULL,  0, 0, onGPSconnect, },
			{ "onDisconnect", NULL,  0, 0, onGPSdisconnect, },
			{ "Recv", NULL,  0, 0, GPSrecv, }
	};
	*size = sizeof(communications) / sizeof(communications[0]);
	return communications;
}

notification_data *http_component_list_get(int *size)
{
	static notification_data communications[] =
	{
			{ "isAccessible", NULL,  0, 0, isHTTPaccessible, },
			{ "onConnect", NULL,  0, 0, onHTTPconnect, },
			{ "onDisconnect", NULL,  0, 0, onHTTPdisconnect, },
			{ "Download", NULL,  0, 0, HTTPdownload, },
			{ "Post", NULL,  0, 0, HTTPPost, },
			{ "Get", NULL,  0, 0, HTTPGet, }

	};
	*size = sizeof(communications) / sizeof(communications[0]);
	return communications;
}

notification_data *nfc_component_list_get(int *size)
{
	static notification_data communications[] =
	{
			{ "isAccessible", NULL,  0, 0, isNFCaccessible, },
			{ "onConnect", NULL,  0, 0, onNFCconnect, },
			{ "onDisconnect", NULL,  0, 0, onNFCdisconnect, },
			{ "Send", NULL,  0, 0, NFCsend, },
			{ "Recv", NULL,  0, 0, NFCrecv, }

	};
	*size = sizeof(communications) / sizeof(communications[0]);
	return communications;
}

notification_data *socket_component_list_get(int *size)
{
	static notification_data communications[] =
	{
			{ "isAccessible", NULL,  0, 0, issockAccessible, },
			{ "onConnect", NULL,  0, 0, onsockConnect, },
			{ "onDisconnect", NULL,  0, 0, onsockDisconnect, },
			{ "send", NULL,  0, 0, socksend, },
			{ "recv", NULL,  0, 0, sockrecv, }

	};
	*size = sizeof(communications) / sizeof(communications[0]);
	return communications;
}



void bouetooth_fill_item_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=bouetooth_component_list_get(&size);

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


void gps_fill_item_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=gps_component_list_get(&size);

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

void http_fill_item_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=http_component_list_get(&size);

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

void nfc_fill_item_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=nfc_component_list_get(&size);

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

void socket_fill_item_cb(void *data, Evas_Object *obj, void *event_info)
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
	notification_list=socket_component_list_get(&size);

	for(int i=0;i<size;i++){

		notification_list[i].status=lists;
		elm_list_item_append(list,notification_list[i].name,NULL,NULL,_tab_view_layout_fill_cb2depth,&notification_list[i]);
	}


	evas_object_hide(elm_object_part_content_unset(datas->layout, "elm.swallow.content"));
	elm_object_part_content_set(datas->layout, "elm.swallow.content", list);
	evas_object_show(list);


	datas->navi_item = elm_naviframe_item_push(datas->navi, datas->name, NULL, NULL,datas->layout , NULL);
}

Http Http_get_instance(){

	static Http pHttp= NULL;

	if(pHttp==NULL)
		pHttp= NewHttp();
	return pHttp;
}

Bluetooth bluetooth_get_instance(){

	static Bluetooth pBT= NULL;

	if(pBT==NULL){
		pBT= NewBluetooth();
	}return pBT;
}

NFC nfc_get_instance(){

	static NFC pNFC =NULL;
	if(pNFC==NULL){
		pNFC=NewNFC();
	}
	return pNFC;
}

GPS gps_get_instance(){

	static GPS pGPS =NULL;
	if(pGPS==NULL){
		pGPS=NewGps();
	}
	return pGPS;
}

Socket Socket_get_instance(){
	static Socket sock =NULL;
	if(sock==NULL){
		sock=NewSocket();
	}
	return sock;
}
void isBTaccessible(notification_data* data)
{
	Bluetooth bt = bluetooth_get_instance();
	bt->isAccessible(bt);
	sprintf(data->result_text,"%s",bt?"is accessible":"not accessible");
}
void onBTconnect(notification_data* data)
{
	Bluetooth bt = bluetooth_get_instance();

	bool b = bt->onConnect(bt);
	if(b==true){

		sprintf(data->result_text,"connect success<br>mac_address:<br>%s",((BluetoothExtends*)bt)->remoteMACAddr);
	}
	else
	{
	sprintf(data->result_text,"%s","connect fail");
	}

}
void onBTdisconnect(notification_data* data)
{
	Bluetooth bt = bluetooth_get_instance();
	bool b =bt->onDisconnect(bt);

	sprintf(data->result_text,"%s",b?"disconnect success":"disconnect fail");
}

void BTrecv(notification_data* data)
{
	Bluetooth bt = bluetooth_get_instance();
	String recv=NULL;
	bt->FileRecv(bt,&recv);
	sprintf(data->result_text,"%s","File Receiving on");



}
void BTsend(notification_data* data)
{
	Bluetooth bt = bluetooth_get_instance();
	if(bt-> isConnected(bt)){
	String sendfilepath= getSharedResourceFile("music/Over the Horizon.mp3");
	bt->FileSend(bt,sendfilepath);
	sprintf(data->result_text,"%s<br>sending to<br>%s",sendfilepath,((BluetoothExtends*)bt)->remoteMACAddr);
	free(sendfilepath);
	}
	else
	{
		sprintf(data->result_text,"not connected");
	}
}
void isBTconnected(notification_data* data)
{
	Bluetooth bt = bluetooth_get_instance();
	bool x= bt->isConnected(bt);
	sprintf(data->result_text,"%s",x?"is connected":"not connected");
}

void isGPSaccessible(notification_data* data)
{
	GPS pGPS = gps_get_instance();
	bool b = pGPS->isAccessible(pGPS);
	sprintf(data->result_text,"%s",b?"accessible":"not accessible");

}
void onGPSconnect(notification_data* data)
{
	GPS pGPS = gps_get_instance();
	bool b= pGPS->onConnect(pGPS);
	sprintf(data->result_text,"%s",b?"connected":"not connected");


}
void onGPSdisconnect(notification_data* data)
{
	GPS pGPS = gps_get_instance();
	bool b=pGPS->onDisconnect(pGPS);
	sprintf(data->result_text,"%s",b?"disconnected":"not disconnected");

}
void GPSrecv(notification_data* data)
{
	GPS pGPS = gps_get_instance();
	Location l = pGPS->Recv(pGPS);
	if(l.validation == true)
		sprintf(data->result_text,"latitude : %lf<br>longitude : %lf",l.latitude, l.longitude);
	else
		sprintf(data->result_text,"Recv Fail try Again");
}

void isHTTPaccessible(notification_data* data)
{

	Http pHttp= Http_get_instance();
	bool b=pHttp->isAccessible(pHttp);
	sprintf(data->result_text,"%s",b?"accessible":"not accessible");

}
void onHTTPconnect(notification_data* data)
{
	Http pHttp= Http_get_instance();
	if(pHttp->isAccessible(pHttp))
	{
		bool b=pHttp->onConnect(pHttp,"210.118.74.89/test",3000);
		sprintf(data->result_text,"%s",b?"connect ok":"connect fail");
	}
	else
	{
		sprintf(data->result_text,"not accessible");
	}
}
void onHTTPdisconnect(notification_data* data)
{
	Http pHttp= Http_get_instance();
	if(pHttp->isAccessible(pHttp))
	{
			bool b=pHttp->onDisconnect(pHttp);
			sprintf(data->result_text,"%s",b?"disconnect ok":"disconnect fail");
	}
	else
		{
			sprintf(data->result_text,"not accessible");
		}
}
void HTTPdownload(notification_data* data)
{
	Http http= Http_get_instance();
	if(http->isAccessible(http)){

		http->onConnect(http,"210.118.74.89/img",3000);

		http->Download(http,"test.jpg");
		sprintf(data->result_text,"%s","file downloading ");


	}
	else
		{
			sprintf(data->result_text,"not accessible");
		}
}
void HTTPPost(notification_data* data)
{
	Http http= Http_get_instance();
	if(http->isAccessible(http)){
		http->onConnect(http,"210.118.74.89/test",3000);
		String x=NULL;
		http->Post(http,"id=dittestmessage ",&x);
		sprintf(data->result_text,"%s",(x!=NULL)?x:"got nothing");
		free(x);
	}
	else
		{
			sprintf(data->result_text,"not accessible");
		}

}
void HTTPGet(notification_data* data)
{
	Http http= Http_get_instance();
	if(http->isAccessible(http)){
		http->onConnect(http,"210.118.74.89/test",3000);
		String x=NULL;
		http->Get(http,"dittestmessage",&x);
		sprintf(data->result_text,"%s",(x!=NULL)?x:"got nothing");
		free(x);
	}
	else
		{
			sprintf(data->result_text,"not accessible");
		}

}

void isNFCaccessible(notification_data* data)
{
	NFC pnfc= nfc_get_instance();
	bool b = pnfc->isAccessible(pnfc);
	snprintf(data->result_text,1024,"%s",b?"is accessible":"not accessible");
}
void onNFCconnect(notification_data* data)
{
	NFC pnfc= nfc_get_instance();
	if(pnfc->isAccessible(pnfc))
	{
		if(pnfc->onConnect(pnfc))
		{
			sprintf(data->result_text,"NFC connect successfully");

		}else
		{
			sprintf(data->result_text,"NFC connect failed");
		}
	}
	else
	{
		sprintf(data->result_text,"this devices do not supports NFC");
	}

}
void onNFCdisconnect(notification_data* data)
{
	NFC pnfc= nfc_get_instance();
	if(pnfc->isAccessible(pnfc))
	{
		if(pnfc->onDisconnect(pnfc))
		{
			sprintf(data->result_text,"NFC disconnected successfully");

		}else
		{
			sprintf(data->result_text,"NFC disconnect failed");
		}
	}
	else
	{
		sprintf(data->result_text,"this devices do not supports NFC");
	}
}
void NFCsend(notification_data* data)
{
	NFC pnfc= nfc_get_instance();
	if(pnfc->isAccessible(pnfc))
	{
		NDEF msg=CreateNDEF("text","test");
		pnfc->Send(pnfc,msg);

	}
	else
	{
		sprintf(data->result_text,"this devices do not supports NFC");
	}

}
void NFCrecv(notification_data* data)
{
	NFC pnfc= nfc_get_instance();
	if(pnfc->isAccessible(pnfc))
	{
		NDEF msg= pnfc->Recv(pnfc);

		if(msg.tag==NULL){
			sprintf(data->result_text,"msg is<br> not received");
		}
		else
		{
			sprintf(data->result_text,"msg is %s",msg.msg);

		}

	}
	else
	{
		sprintf(data->result_text,"this devices do not supports NFC");
	}

}

void issockAccessible(notification_data* data)
{
	Socket sock =Socket_get_instance();
	bool b=sock->isAccessible(sock);

	sprintf(data->result_text,"%s",b?"accessible":"not accessible");

}
void onsockConnect(notification_data* data)
{
	Socket sock =Socket_get_instance();
	if(sock->isAccessible(sock)){

		bool b=sock->onConnect(sock,"210.118.74.89",3300);
		sprintf(data->result_text,"%s",b?"connect ok":"connect fail");

	}
	else{
		sprintf(data->result_text,"this device does't support socket");
	}


}
void onsockDisconnect(notification_data* data)
{
	Socket sock =Socket_get_instance();
	if(sock->isAccessible(sock)){
		bool b=sock->onDisconnect(sock);
		sprintf(data->result_text,"%s",b?"disconnect ok":"disconnect fail");

	}
	else{
		sprintf(data->result_text,"this device does't support socket");
	}

}
void socksend(notification_data* data)
{
	Socket sock =Socket_get_instance();
	if(sock->isAccessible(sock)){
		bool b= sock->Send(sock,"hello");
		sprintf(data->result_text,"%s",b?"send ok":"send fail");
	}
	else{
		sprintf(data->result_text,"this device does't support socket");
	}

}
void sockrecv(notification_data* data)
{
	Socket sock =Socket_get_instance();
	if(sock->isAccessible(sock)){
	String x=NULL;
	 bool b =sock->Recv(sock,&x);
	sprintf(data->result_text,"%s",b?x:"recv fail");
	}
	else
	{
		sprintf(data->result_text,"this device does't support socket");

	}
}

