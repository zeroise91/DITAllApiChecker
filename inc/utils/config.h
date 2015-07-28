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

#ifndef CONFIG_H_
#define CONFIG_H_

#include <app.h>
#include <app_common.h>
#include <stdio.h>
#include "logger.h"
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>

static inline const char *get_package_name();
static inline const char *get_resource_path(const char *file_path);
static inline const char *get_shared_res_path();
static inline const char *get_shared_resource_path(const char *file_path);
#define PACKAGE get_package_name()

#include <app_control.h>
#define SERVICE_DATA_TEXT APP_CONTROL_DATA_TEXT
#define SERVICE_DATA_TO APP_CONTROL_DATA_TO
#define SERVICE_ERROR_NONE APP_CONTROL_ERROR_NONE
#define MAIN_MENU_PATH get_shared_resource_path("images/mainmenu.png")
#define THUMBNAIL_PATH get_shared_resource_path("images/thumbnail1.jpg")
#define ICON1_PATH get_shared_resource_path("images/icon1.png")
#define ICON2_PATH get_shared_resource_path("images/icon2.png")
#define SOUND_PATH get_shared_resource_path("sounds/sound.mp3")
#define SETTING_PKGNAME "com.samsung.setting-lite"

/**
 * @brief Get package name
 * @return Package name
 */
static inline const char *get_package_name()
{
    static char package_name[PATH_MAX] = { '\0' };
    if(package_name[0] == '\0')
    {
        char *package_name_buf = NULL;
        app_get_id(&package_name_buf);
        strncpy(package_name, package_name_buf, strlen(package_name_buf));
        free(package_name_buf);
    }
    return package_name;
}

/**
 * @brief Get resources folder absolute path
 * @return Absolute path to resources folder
 */
static inline const char *get_res_path()
{
    static char res_folder_path[PATH_MAX] = { '\0' };
    if(res_folder_path[0] == '\0')
    {
        char *resource_path_buf = app_get_resource_path();
        strncpy(res_folder_path, resource_path_buf, PATH_MAX-1);
        free(resource_path_buf);
    }
    return res_folder_path;
}

/**
 * @brief Get resource absolute path
 * @param[in]   file_path   Resource path relative to resources directory
 * @return Resource absolute path
 */
static inline const char *get_resource_path(const char *file_path)
{
    static char res_path[PATH_MAX] = { '\0' };
    snprintf(res_path, PATH_MAX, "%s%s", get_res_path(), file_path);
    return res_path;
}

/**
 * @brief Get shared resources folder absolute path
 * @return Absolute path to shared resources folder
 */
static inline const char *get_shared_res_path()
{
    static char shared_res_folder_path[PATH_MAX] = { '\0' };
    if(shared_res_folder_path[0] == '\0')
    {
        char *resource_path_buf = app_get_shared_resource_path();
        strncpy(shared_res_folder_path, resource_path_buf, PATH_MAX-1);
        free(resource_path_buf);
    }
    return shared_res_folder_path;
}

/**
 * @brief Get shared resource absolute path
 * @param[in]   file_path   Resource path relative to shared resources directory
 * @return Resource absolute path
 */
static inline const char *get_shared_resource_path(const char *file_path)
{
    static char shared_res_path[PATH_MAX] = { '\0' };
    snprintf(shared_res_path, PATH_MAX, "%s%s", get_shared_res_path(), file_path);
    return shared_res_path;
}

#endif /* CONFIG_H_ */
