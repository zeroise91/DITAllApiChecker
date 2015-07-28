/*
 * components.h
 *
 *  Created on: Jul 16, 2015
 *      Author: parkbeomchan
 */
#include "model/notification-control.h"
#include "dit.h"
#ifndef COMPONENTS_H_
#define COMPONENTS_H_

//item_list session
 notification_data *communication_list_get(int *size);
 notification_data *bouetooth_component_list_get(int *size);
 notification_data *gps_component_list_get(int *size);
 notification_data *http_component_list_get(int *size);
 notification_data *nfc_component_list_get(int *size);
 notification_data *socket_component_list_get(int *size);

 notification_data *device_list_get(int *size);
 notification_data *devicestatus_list_get(int *size);
 notification_data *file_component_list_get(int *size);
 notification_data *preference_component_list_get(int *size);
 notification_data *sensor_component_list_get(int *size);
 notification_data *vibrator_component_list_get(int *size);

 notification_data *interface_list_get(int *size);
 notification_data *log_component_list_get(int *size);
 notification_data *notification_component_list_get(int *size);
 notification_data *ongoingnotification_component_list_get(int *size);

 //cb session
  void log_fill_item_cb(void *data, Evas_Object *obj, void *event_info);
  void notification_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void ongoingnotification_item_fill_cb(void *data, Evas_Object *obj, void *event_info);

  void devicestatus_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void file_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void preference_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void sensor_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void vibrator_item_fill_cb(void *data, Evas_Object *obj, void *event_info);

  void bouetooth_fill_item_cb(void *data, Evas_Object *obj, void *event_info);
  void gps_fill_item_cb(void *data, Evas_Object *obj, void *event_info);
  void http_fill_item_cb(void *data, Evas_Object *obj, void *event_info);
  void nfc_fill_item_cb(void *data, Evas_Object *obj, void *event_info);
  void socket_fill_item_cb(void *data, Evas_Object *obj, void *event_info);

  void Accelerometer_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void MagnetoMeter_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Gravity_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void LinearAccelation_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void MagnetoMeter_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void RotationVector_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Orientation_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Gyroscope_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Light_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Proximity_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Pressure_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void UltraViolet_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Temperature_item_fill_cb(void *data, Evas_Object *obj, void *event_info);
  void Humidity_item_fill_cb(void *data, Evas_Object *obj, void *event_info);

  void accaddCallback(notification_data* data);
  void accdatachCallback(notification_data* data);
  void accoff(notification_data* data);
  void accon(notification_data* data);
  void accisSupported(notification_data* data);
  void accgetValue(notification_data* data);

  void GravityaddCallback(notification_data* data);
  void GravitydatachCallback(notification_data* data);
  void Gravityoff(notification_data* data);
  void Gravityon(notification_data* data);
  void GravityisSupported(notification_data* data);
  void GravitygetValue(notification_data* data);

  void LinearAccelationaddCallback(notification_data* data);
  void LinearAccelationdatachCallback(notification_data* data);
  void LinearAccelationoff(notification_data* data);
  void LinearAccelationon(notification_data* data);
  void LinearAccelationisSupported(notification_data* data);
  void LinearAccelationgetValue(notification_data* data);

  void MagnetoMeteraddCallback(notification_data* data);
  void MagnetoMeterdatachCallback(notification_data* data);
  void MagnetoMeteroff(notification_data* data);
  void MagnetoMeteron(notification_data* data);
  void MagnetoMeterisSupported(notification_data* data);
  void MagnetoMetergetValue(notification_data* data);

  void RotationVectoraddCallback(notification_data* data);
  void RotationVectordatachCallback(notification_data* data);
  void RotationVectoroff(notification_data* data);
  void RotationVectoron(notification_data* data);
  void RotationVectorisSupported(notification_data* data);
  void RotationVectorgetValue(notification_data* data);

  void OrientationaddCallback(notification_data* data);
  void OrientationdatachCallback(notification_data* data);
  void Orientationoff(notification_data* data);
  void Orientationon(notification_data* data);
  void OrientationisSupported(notification_data* data);
  void OrientationgetValue(notification_data* data);

  void GyroscopeaddCallback(notification_data* data);
  void GyroscopedatachCallback(notification_data* data);
  void Gyroscopeoff(notification_data* data);
  void Gyroscopeon(notification_data* data);
  void GyroscopeisSupported(notification_data* data);
  void GyroscopegetValue(notification_data* data);

  void LightaddCallback(notification_data* data);
  void LightdatachCallback(notification_data* data);
  void Lightoff(notification_data* data);
  void Lighton(notification_data* data);
  void LightisSupported(notification_data* data);
  void LightgetValue(notification_data* data);

  void ProximityaddCallback(notification_data* data);
  void ProximitydatachCallback(notification_data* data);
  void Proximityoff(notification_data* data);
  void Proximityon(notification_data* data);
  void ProximityisSupported(notification_data* data);
  void ProximitygetValue(notification_data* data);

  void PressureaddCallback(notification_data* data);
  void PressuredatachCallback(notification_data* data);
  void Pressureoff(notification_data* data);
  void Pressureon(notification_data* data);
  void PressureisSupported(notification_data* data);
  void PressuregetValue(notification_data* data);

  void UltraVioletaddCallback(notification_data* data);
  void UltraVioletdatachCallback(notification_data* data);
  void UltraVioletoff(notification_data* data);
  void UltraVioleton(notification_data* data);
  void UltraVioletisSupported(notification_data* data);
  void UltraVioletgetValue(notification_data* data);

  void TemperatureaddCallback(notification_data* data);
  void TemperaturedatachCallback(notification_data* data);
  void Temperatureoff(notification_data* data);
  void Temperatureon(notification_data* data);
  void TemperatureisSupported(notification_data* data);
  void TemperaturegetValue(notification_data* data);

  void HumidityaddCallback(notification_data* data);
  void HumiditydatachCallback(notification_data* data);
  void Humidityoff(notification_data* data);
  void Humidityon(notification_data* data);
  void HumidityisSupported(notification_data* data);
  void HumiditygetValue(notification_data* data);


  void Lock(notification_data* data);
  void unLock(notification_data* data);
  void Dim(notification_data* data);
  void getBright(notification_data* data);
  void setBright(notification_data* data);

  void getLevel(notification_data* data);
  void isCharging(notification_data* data);

  void onflash(notification_data* data);
  void offflash(notification_data* data);

  void preference_int_get(notification_data* data);
  void preference_string_get(notification_data* data);
  void preference_boolean_get(notification_data* data);
  void preference_double_get(notification_data* data);
  void preference_int_set(notification_data* data);
  void preference_string_set(notification_data* data);
  void preference_boolean_set(notification_data* data);
  void preference_double_set(notification_data* data);
  void preference__remove(notification_data* data);
  void preference__clear(notification_data* data);


  void deletefile(notification_data* data);
  void copyfile(notification_data* data);
  void movefile(notification_data* data);
  void searchfile(notification_data* data);

  void playvideo(notification_data* data);
  void pausevideo(notification_data* data);
  void stopvideo(notification_data* data);
  void recordvideo(notification_data* data);
  void getvideoinfo(notification_data* data);
  void setURI_video(notification_data* data);
  void setevasObject(notification_data* data);

  void playaudio(notification_data* data);
  void pauseaudio(notification_data* data);
  void stopaudio(notification_data* data);
  void recordaudio(notification_data* data);
  void getaudioInfo(notification_data* data);
  void setURI_audio(notification_data* data);

  void  extractinfo(notification_data* data);
  void  getimageBurstId (notification_data* data);
  void  getimageMediaId (notification_data* data);
  void  getimageDateTaken (notification_data* data);
  void	getimageWidth(notification_data* data);
  void	getimageHeight(notification_data* data);

  //sensor empty


  void Custom(notification_data* data);
  void Short(notification_data* data);
  void Middle(notification_data* data);
  void Long(notification_data* data);

  //interface
  void logerror(notification_data* data);
  void loginfo(notification_data* data);
  void logdebug(notification_data* data);
  void logwarning(notification_data* data);


  void setNIcon(notification_data* data);
  void setNTitle(notification_data* data);
  void setNText(notification_data* data);
  void setNSound(notification_data* data);
  void NShow(notification_data* data);
  void NHide(notification_data* data);


  void setONIcon(notification_data* data);
  void setONTitle(notification_data* data);
  void setONText(notification_data* data);
  void setONSound(notification_data* data);
  void setONProgress(notification_data* data);
  void ONShow(notification_data* data);
  void ONHide(notification_data* data);
  void Onupdate(notification_data* data);
  //
  void isBTaccessible(notification_data* data);
  void onBTconnect(notification_data* data);
  void onBTdisconnect(notification_data* data);
  void BTrecv(notification_data* data);
  void BTsend(notification_data* data);
  void isBTconnected(notification_data* data);

  void isGPSaccessible(notification_data* data);
  void onGPSconnect(notification_data* data);
  void onGPSdisconnect(notification_data* data);
  void GPSrecv(notification_data* data);

  void isHTTPaccessible(notification_data* data);
  void onHTTPconnect(notification_data* data);
  void onHTTPdisconnect(notification_data* data);
  void HTTPdownload(notification_data* data);
  void HTTPPost(notification_data* data);
  void HTTPGet(notification_data* data);

  void isNFCaccessible(notification_data* data);
  void onNFCconnect(notification_data* data);
  void onNFCdisconnect(notification_data* data);
  void NFCsend(notification_data* data);
  void NFCrecv(notification_data* data);

  void issockAccessible(notification_data* data);
  void onsockConnect(notification_data* data);
  void onsockDisconnect(notification_data* data);
  void socksend(notification_data* data);
  void sockrecv(notification_data* data);



#endif /* COMPONENTS_H_ */
