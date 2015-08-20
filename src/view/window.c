
#include "view/window.h"

#include <Elementary.h>

#define APP_NAME "ditapichecker"

window_obj *win_create()
{
    window_obj *obj = calloc(1, sizeof(window_obj));
    if(!obj)
    {
        return NULL;
    }

    obj->win = elm_win_add(NULL, APP_NAME, ELM_WIN_BASIC);
    elm_win_conformant_set(obj->win, EINA_TRUE);
    evas_object_show(obj->win);

    elm_win_indicator_mode_set(obj->win, ELM_WIN_INDICATOR_SHOW);
    obj->conform = elm_conformant_add(obj->win);
    evas_object_size_hint_weight_set(obj->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(obj->win, obj->conform);
    evas_object_show(obj->conform);

    obj->bg = elm_bg_add(obj->conform);
    evas_object_size_hint_weight_set(obj->bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(obj->bg);

    elm_object_part_content_set(obj->conform, "elm.swallow.bg", obj->bg);

    return obj;
}

void win_destroy(window_obj *win)
{
    if(win)
    {
        evas_object_del(win->win);
        free(win);
    }
}

void win_lower(window_obj *win)
{
    if(win)
    {
        elm_win_lower(win->win);
    }
}

void win_raise(window_obj *win)
{
    if(win)
    {
        elm_win_raise(win->win);
    }
}

void win_set_layout(window_obj *obj, Evas_Object *layout)
{
    if(!obj || !layout)
    {
        return;
    }
    elm_object_part_content_set(obj->conform, "elm.swallow.content", layout);
    obj->layout = layout;
}

Evas_Object *win_get_host_layout(const window_obj *win)
{
    if(!win)
    {
        return NULL;
    }
    return win->conform;
}
