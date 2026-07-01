#pragma once

#include <auik-demo/symbol_export.h>
#include <auik/auik.hpp>
#include <auik/widgets/menu.hpp>
#include <auik/widgets/window.hpp>

#define AUIK_DEMO_ICON_STAR  0x62C9D04Du
#define AUIK_DEMO_ICON_HEART 0xB4B57F0Du

namespace auik
{
    AUIK_DEMO_EXPORT bool configure_demo_icons(Font *font, f32 dpi = 1.0f);
    AUIK_DEMO_EXPORT MenuBar *make_demo_main_menu_bar();
    AUIK_DEMO_EXPORT Window *make_demo_window();
}
