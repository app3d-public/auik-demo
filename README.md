# Auik Demo

`auik-demo` is a small reproducible demo module for Auik. It builds a showcase window with the standard demo sections:

- main menu bar
- basic widgets
- selection controls
- color pickers
- sliders and drags
- layout and data widgets

## Screenshots

[<img src="./screenshots/demo.png" alt="screenshot" width="350"/>](./screenshots/demo.png)

## Integration

Add Auik and the demo module as sibling directories before compiling the host's ASD theme:

```cmake
add_subdirectory(modules/auik)
add_subdirectory(modules/auik-demo)

compile_auik_asd_theme("${AUIK_BASE_THEME}"
    APP_IDS_CSV "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/style_tags_id.csv"
    INPUT_FOLDERS
        "${AUIK_DEMO_STYLE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ui"
)

target_sources(my_app PRIVATE ${AUIK_ASD_SRC})
target_include_directories(my_app PRIVATE ${AUIK_ASD_INCLUDE_DIR})
target_link_libraries(my_app PRIVATE auik auik-demo)
add_dependencies(my_app ${AUIK_ASD_TARGET})
```

`AUIK_DEMO_STYLE_DIR` contains the demo's `theme.asd` and `style_tags_id.csv`. The module registers its own style IDs when you call `add_subdirectory`. If the host has no styles of its own, omit `APP_IDS_CSV` and keep only `AUIK_DEMO_STYLE_DIR` in `INPUT_FOLDERS`.

## Runtime Setup

Load the generated host theme before creating the demo widgets. Include the public header:

```cpp
#include <auik/demo.hpp>
```

Before creating the demo window, configure demo icon images:

```cpp
Font *ui_font = /* host-provided loaded UI font */;
if (!auik::configure_demo_icons(ui_font, dpi))
{
    // The supplied font did not contain any supported star/heart fallback glyphs.
}
```

`auik-demo` does not ship fonts. The host must provide a loaded `Font*`. The demo tries common fallback glyphs for the star and heart image buttons and stores them in the Auik image cache as:

- `AUIK_DEMO_ICON_STAR`
- `AUIK_DEMO_ICON_HEART`

Then create the demo UI:

```cpp
auto *menu = auik::make_demo_main_menu_bar();
auto *window = auik::make_demo_window();
```

Attach those widgets to the same root/window tree used by the host application. `make_demo_main_menu_bar()` returns a full-width menu bar. `make_demo_window()` returns a decorated demo window containing all demo sections.


## Notes

- The demo window is built from existing Auik widgets only.

## License
This project is licensed under the  [MIT License](LICENSE).

## Contacts
For any questions or feedback, you can reach out via [email](mailto:wusikijeronii@gmail.com) or open a new issue.
