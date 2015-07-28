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

#ifndef NOTIFICATION_CONTROL_H_
#define NOTIFICATION_CONTROL_H_

#include <stdbool.h>
#include <Evas.h>
#define TEXT_SHORT_LEN 256
#define TEXT_MAX_LEN 1024

typedef struct _notification_data notification_data;
typedef void (* notification_cb)(notification_data *);

struct _notification_data
{
     char name[TEXT_SHORT_LEN];
     void* status;
     int press_count;
     double progress_value;
     notification_cb callback;
     char result_text[TEXT_MAX_LEN];
};






/**
 * @brief Delete all ongoing notifications
 */
void delete_all_ongoing_notifications();

/**
 * @brief increase badge count by one. If the badge doesn't exist, then it is created.
 * @param[out]   count  badge count
 * @return true if success, false if failure
 */
bool increase_badge(unsigned int *count);

/**
 * @brief decrease badge count by one.
 * @param[out]   count  badge count
 * @return true if success, false if failure
 */
bool decrease_badge(unsigned int *count);


void none(notification_data* data);
#endif /* NOTIFICATION_CONTROL_H_ */
