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


#ifndef TAB_VIEW_H_
#define TAB_VIEW_H_

#include <Evas.h>

/**
 * @brief add new tab to application main window
 * @param[in]   parent   parent widget
 */
void tab_view_add(Evas_Object *parent);
void _layout_view_destroy2(void *data, Evas *e, Evas_Object *obj, void *event_info);

void _tab_view_layout_fill_cb2depth(void *data, Evas_Object *obj, void *event_info);
void _sensorcallback_layout_fill_cb2depth(void *data, Evas_Object *obj, void *event_info);

#endif /* TAB_VIEW_H_ */
