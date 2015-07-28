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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "utils/config.h"

/* Content paths */

static const char *const result_1_text = "Hello there.";
static const char *const result_2_text = "WhoIsIt";

#define LAYOUT "layout"
#define MESSAGE_POST "message_post"
#define RECEIVED_DATA "Received_data"
#define TEXT_SHORT_LEN 256
#define MESSAGE_PROGRESS -1

/* Result message text constants */
static const char *const result_message = "ResultMessage =";
static const char *const result_message_success_text = "SUCCESS";
static const char *const result_message_failure_text = "FAILURE";
static const char *const notify_message_text = "The notify message is";
static const char *const launch_argument_text = "launchArgument is";
static const char *const badge_is_text = "Badge is";
static const char *const app_message_text = "AppMessage";
static const char *const ongoing_activity_progress_text = "Ongoing Activity Progress is";
static const char *const ongoing_by_app_control_text = "OngoingByAppControl";
static const char *const title_text = "TitleText ";
static const char *const percentage_content_text = "Progress(%). Press count #";
static const char *const byte_content_text = "Progress(Byte). Press count #";
static const char *const text_content_text = "Text. Press count #";
static const char *const remove_ongoing_notification_text = "All Notifications have been removed.";
static const char *const remove_ongoing_notification_by_app_control_text = "OngoingNotificationByAppControl has been removed.";
static const char *const remove_ongoing_notification_by_app_id_text = "OngoingNotificationByAppId has been removed.";
static const double percentage_max = 1.0;
static const double percentage_increment = 0.1;
static const double percentage_multiplier = 100;
static const double byte_max = 7000000;
static const double byte_increment = 78461;
static const int invalid_argument = -1;
static const char *const alert_text = "AlertText";
static const char *const notification_app = "NotificationApp";
static const char *const number_alert_text = "17 AlertText";
static const char *const first_line = "First line";
static const char *const other_columns = "Other columns";
static const char *const second_length = "Second long length sting";
static const char *const line_text = "line";
static const char *const app_control = "AppControl to me";
static const char *const notify_with_request = "New Notification arrived with NotificationRequest by AppId.";
static const char *const operation_id_is_text = "operationId is";
static const char *const uri_is_text = "uri is";
static const char *const target_app_id_text = "The target AppId is";
static const char *const app_id_is_text = "AppId is";
static const char *const icon_path_is_text = "Icon path is";
static const char *const remove_text = "Individual notification has been removed.";
static const char *const operation_id_text = "http://tizen.org/appcontrol/operation/notification_temporary";
static const char *const extra_data_tizen_org = "http://tizen.org/appcontrol/data/notification";
static const char *const uri_text = "mailto:test@tizen.org";
static const char *const mime_text = "audio/mp4";
static const char *const app_control_request = "AppControlRequestReceived";
static const char *const req_id = "reqId:";
static const char *const operation_id = "operationId:";
static const char *const uri_data_text = "pUriData:";
static const char *const mime_type = "pMimeType:";
static const char *const extra_data = "ExtraData:";
static const char *const key_value = "(Key/Value):";

#endif /* CONSTANTS_H_ */
