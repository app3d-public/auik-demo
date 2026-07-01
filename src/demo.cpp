#include <auik/auik.hpp>
#include <auik/demo.hpp>
#include <auik/demo_style_tags.hpp>
#include <auik/widgets/checkbox.hpp>
#include <auik/widgets/color_picker.hpp>
#include <auik/widgets/column.hpp>
#include <auik/widgets/combobox.hpp>
#include <auik/widgets/containers.hpp>
#include <auik/widgets/drag.hpp>
#include <auik/widgets/image.hpp>
#include <auik/widgets/image_button.hpp>
#include <auik/widgets/menu.hpp>
#include <auik/widgets/progress_bar.hpp>
#include <auik/widgets/radio_button.hpp>
#include <auik/widgets/slider.hpp>
#include <auik/widgets/switch_button.hpp>
#include <auik/widgets/tabbar.hpp>
#include <auik/widgets/table.hpp>
#include <auik/widgets/text.hpp>
#include <auik/widgets/text_button.hpp>
#include <auik/widgets/textbox.hpp>
#include <auik/widgets/tree.hpp>
#include <auik/widgets/window.hpp>

#define AUIK_DEMO_MAIN_MENU_BAR_ID     0x09A8D50Du
#define AUIK_DEMO_WINDOW_ID            0x09A8D50E
#define AUIK_DEMO_BASIC_HEADER_ID      0x09A8D510u
#define AUIK_DEMO_BASIC_COLUMNS_ID     0x09A8D511u
#define AUIK_DEMO_SECTION_COLUMNS_ID   0x09A8D512u
#define AUIK_DEMO_SELECTION_HEADER_ID  0x09A8D513u
#define AUIK_DEMO_SELECTION_COLUMNS_ID 0x09A8D514u
#define AUIK_DEMO_COLOR_HEADER_ID      0x09A8D515u
#define AUIK_DEMO_COLOR_COLUMNS_ID     0x09A8D516u
#define AUIK_DEMO_SLIDERS_HEADER_ID    0x09A8D517u
#define AUIK_DEMO_SLIDERS_COLUMNS_ID   0x09A8D518u
#define AUIK_DEMO_LAYOUT_HEADER_ID     0x09A8D519u
#define AUIK_DEMO_LAYOUT_COLUMNS_ID    0x09A8D51Au
#define AUIK_DEMO_LABEL_WIDTH          145.0f
#define AUIK_DEMO_ROW_INLINE_SPACING   8.0f

namespace auik
{
    namespace
    {
        Text *make_demo_label(u32 id, StringView text)
        {
            auto *label = make_text(id, text, {AUIK_DEMO_LABEL_WIDTH, AUIK_SIZE_Y_FIT});
            label->set_style_tag(AUIK_STYLE_TAG_DEMO_LABEL);
            return label;
        }

        Text *make_demo_vertical_label(u32 id, StringView text)
        {
            auto *label = make_text(id, text, AUIK_SIZE_FIT);
            label->set_style_tag(AUIK_STYLE_TAG_DEMO_LABEL);
            return label;
        }

        Text *make_demo_plain_vertical_label(u32 id, StringView text) { return make_text(id, text, AUIK_SIZE_FIT); }

        Block *make_demo_value_text(u32 id, StringView text, HAlign align)
        {
            auto *row = make_block(id);
            row->set_size({270.0f, AUIK_SIZE_Y_FIT});
            row->add_child(make_text(id ^ AUIK_TAG_TEXT, text),
                           make_layout_flags(ChildLayout::block, align, VAlign::center));
            return row;
        }

        void add_labeled_row(Block *slot, u32 label_id, StringView label, Widget *control)
        {
            const auto inline_center = make_layout_flags(ChildLayout::inline_, HAlign::left, VAlign::center);
            const auto center = make_layout_flags(ChildLayout::block, HAlign::left, VAlign::center);
            slot->add_child(make_demo_label(label_id, label), inline_center);
            slot->add_child(control, center);
        }

        void add_vertical_labeled_control(Block *slot, u32 label_id, StringView label, Widget *control,
                                          HAlign label_align = HAlign::left)
        {
            const auto label_layout = make_layout_flags(ChildLayout::block, label_align, VAlign::center);
            const auto control_layout = make_layout_flags(ChildLayout::block, label_align, VAlign::center);
            slot->add_child(make_demo_vertical_label(label_id, label), label_layout);
            slot->add_child(control, control_layout);
        }

        void add_option_row(Block *slot, Widget *control, u32 text_id, StringView text)
        {
            const auto inline_center = make_layout_flags(ChildLayout::inline_, HAlign::left, VAlign::center);
            const auto center = make_layout_flags(ChildLayout::block, HAlign::left, VAlign::center);
            auto *label = make_text(text_id, text, AUIK_SIZE_FIT, default_text_layout_flags(), TextAnchorY::middle);
            label->set_tight_content_height(true);
            slot->add_child(control, inline_center);
            slot->add_child(label, center);
        }

        void make_basic_controls_column(Block *slot)
        {
            auto *button = make_text_button(0x09A8D520u, "Button", {230.0f, AUIK_SIZE_Y_FIT});
            add_labeled_row(slot, 0x09A8D521u, "Button", button);

            const auto inline_center = make_layout_flags(ChildLayout::inline_, HAlign::left, VAlign::center);
            const auto center = make_layout_flags(ChildLayout::block, HAlign::left, VAlign::center);
            slot->add_child(make_demo_label(0x09A8D525u, "ImageButton"), inline_center);
            slot->add_child(
                make_image_button(0x09A8D523u, get_cached_image(AUIK_DEMO_ICON_STAR), {0.0f, 0.0f}, {42.0f, 42.0f}),
                inline_center);
            slot->add_child(
                make_image_button(0x09A8D524u, get_cached_image(AUIK_DEMO_ICON_HEART), {0.0f, 0.0f}, {42.0f, 42.0f}),
                center);

            add_labeled_row(slot, 0x09A8D526u, "Input Text",
                            make_textbox(0x09A8D527u, "Hello, world!", 230.0f, TextFlagBits::none));
            add_labeled_row(
                slot, 0x09A8D528u, "Combo Box",
                make_combobox(0x09A8D529u, {"Option 1", "Option 2", "Option 3"}, 1u, {230.0f, AUIK_SIZE_Y_FIT}));
        }

        void make_basic_status_column(Block *slot)
        {
            const auto inline_center = make_layout_flags(ChildLayout::inline_, HAlign::left, VAlign::center);
            const auto center = make_layout_flags(ChildLayout::block, HAlign::left, VAlign::center);
            slot->add_child(make_demo_label(0x09A8D533u, "Progress Bar"), inline_center);
            slot->add_child(make_progress_bar(0x09A8D531u, 0.67f, 0.0f, 1.0f, 270.0f), inline_center);
            auto *progress_percent = make_text(0x09A8D532u, "67%", {48.0f, AUIK_SIZE_Y_FIT});
            progress_percent->set_style_tag(AUIK_STYLE_TAG_PROGRESS_PERCENT);
            slot->add_child(progress_percent, center);

            add_labeled_row(slot, 0x09A8D534u, "Text (Left)",
                            make_demo_value_text(0x09A8D535u, "This is left-aligned text.", HAlign::left));
            add_labeled_row(slot, 0x09A8D536u, "Text (Center)",
                            make_demo_value_text(0x09A8D537u, "This is centered text.", HAlign::center));
            add_labeled_row(slot, 0x09A8D538u, "Text (Right)",
                            make_demo_value_text(0x09A8D539u, "This is right-aligned text.", HAlign::right));
        }

        void make_basic_disabled_column(Block *slot)
        {
            auto *disabled_text = make_text(0x09A8D540u, "This is disabled text.", {260.0f, AUIK_SIZE_Y_FIT});
            disabled_text->set_disabled();
            add_labeled_row(slot, 0x09A8D541u, "Disabled Text", disabled_text);

            auto *disabled_textbox = make_textbox(0x09A8D542u, "Disabled input", acul::string{}, TextFlagBits::none,
                                                  {260.0f, AUIK_SIZE_Y_MIN_FIT});
            disabled_textbox->set_disabled();
            add_labeled_row(slot, 0x09A8D543u, "Disabled Input", disabled_textbox);
            add_labeled_row(slot, 0x09A8D544u, "Password Input",
                            make_textbox(0x09A8D545u, "password", 260.0f, TextFlagBits::password));
        }

        CollapseHeader *make_basic_widgets_header()
        {
            auto *header = make_collapse_header(AUIK_DEMO_BASIC_HEADER_ID, "Basic Widgets", true);
            auto *columns = make_column(AUIK_DEMO_BASIC_COLUMNS_ID, 3u, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT});
            make_basic_controls_column((*columns)[0u]);
            make_basic_status_column((*columns)[1u]);
            make_basic_disabled_column((*columns)[2u]);
            header->add_child(columns);
            return header;
        }

        void make_selection_checkbox_column(Block *slot)
        {
            slot->add_child(make_demo_vertical_label(0x09A8D560u, "Checkboxes"));
            add_option_row(slot, make_checkbox(0x09A8D561u, false), 0x09A8D562u, "Unchecked");
            add_option_row(slot, make_checkbox(0x09A8D563u, true), 0x09A8D564u, "Checked");
        }

        void make_selection_radio_column(Block *slot)
        {
            slot->add_child(make_demo_vertical_label(0x09A8D565u, "Radio Buttons"));
            add_option_row(slot, make_radio_button(0x09A8D566u, false), 0x09A8D567u, "Option A");
            add_option_row(slot, make_radio_button(0x09A8D568u, true), 0x09A8D569u, "Option B");
        }

        void make_selection_switch_column(Block *slot)
        {
            slot->add_child(make_demo_vertical_label(0x09A8D56Au, "Switches / Toggles"));
            add_option_row(slot, make_switch_button(0x09A8D56Bu, true), 0x09A8D56Cu, "Switch On");
            add_option_row(slot, make_switch_button(0x09A8D56Du, false), 0x09A8D56Eu, "Switch Off");
        }

        CollapseHeader *make_selection_controls_header()
        {
            auto *header = make_collapse_header(AUIK_DEMO_SELECTION_HEADER_ID, "Selection Controls", true);
            auto *columns = make_column(AUIK_DEMO_SELECTION_COLUMNS_ID, 3u, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT});
            make_selection_checkbox_column((*columns)[0u]);
            make_selection_radio_column((*columns)[1u]);
            make_selection_switch_column((*columns)[2u]);
            header->add_child(columns);

            add_vertical_labeled_control(
                header, 0x09A8D56Fu, "Tabbar",
                make_tabbar(0x09A8D570u, {"General", "Settings", "Advanced", "About"}, TabbarFlagBits::none, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT}));
            return header;
        }

        void add_color_picker_column(Block *slot, u32 label_id, StringView label, Widget *picker)
        { add_vertical_labeled_control(slot, label_id, label, picker, HAlign::center); }

        CollapseHeader *make_color_pickers_header()
        {
            auto *header = make_collapse_header(AUIK_DEMO_COLOR_HEADER_ID, "Color Pickers", true);
            auto *columns = make_column(AUIK_DEMO_COLOR_COLUMNS_ID, 3u, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT});
            add_color_picker_column((*columns)[0u], 0x09A8D580u, "Circle Color Picker",
                                    make_circle_color_picker(0x09A8D581u, 140.0f, {1.0f, 0.25f, 0.5f, 1.0f}));
            add_color_picker_column((*columns)[1u], 0x09A8D582u, "Square Color Picker",
                                    make_square_color_picker(0x09A8D583u, 140.0f, {0.25f, 0.78f, 1.0f, 1.0f}));
            add_color_picker_column(
                (*columns)[2u], 0x09A8D584u, "Gradient Picker",
                make_gradient_color_picker(0x09A8D585u, {0.78f, 0.25f, 1.0f, 1.0f}, {150.0f, 140.0f}));
            header->add_child(columns);
            return header;
        }

        Column *make_selection_and_color_section()
        {
            auto *columns = make_column(AUIK_DEMO_SECTION_COLUMNS_ID, 2u, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT});
            (*columns)[0u]->add_child(make_selection_controls_header());
            (*columns)[1u]->add_child(make_color_pickers_header());
            return columns;
        }

        acul::vector<amal::vec4> make_demo_gradient_colors()
        {
            return {
                {0.20f, 0.45f, 1.00f, 1.0f}, // blue
                {0.00f, 0.85f, 0.75f, 1.0f}, // cyan
                {1.00f, 0.82f, 0.18f, 1.0f}, // yellow
                {1.00f, 0.28f, 0.55f, 1.0f}, // pink
            };
        }

        void make_sliders_column(Block *slot)
        {
            add_labeled_row(slot, 0x09A8D590u, "Slider", make_slider(0x09A8D591u, 0.56f, 0.0f, 1.0f, 270.0f));
            add_labeled_row(slot, 0x09A8D592u, "Range Slider",
                            make_range_slider(0x09A8D593u, 0.2f, 0.8f, 0.0f, 1.0f, 270.0f));
            add_labeled_row(slot, 0x09A8D594u, "Gradient Slider",
                            make_gradient_slider(0x09A8D595u, 0.62f, 0.0f, 1.0f, make_demo_gradient_colors(), 270.0f));
            add_labeled_row(
                slot, 0x09A8D596u, "Opacity Slider",
                make_transparency_slider(0x09A8D597u, 0.65f, {0.75f, 0.2f, 1.0f, 1.0f}, 0.0f, 1.0f, 270.0f));
        }

        void make_hsl_sliders_column(Block *slot)
        {
            acul::vector<amal::vec4> saturation_colors{
                {0.5f, 0.5f, 0.5f, 1.0f},
                {0.18f, 0.42f, 1.0f, 1.0f},
            };
            acul::vector<amal::vec4> lightness_colors{
                {0.0f, 0.0f, 0.0f, 1.0f},
                {0.18f, 0.42f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f, 1.0f},
            };

            add_labeled_row(slot, 0x09A8D598u, "Hue", make_hsl_slider(0x09A8D599u, 210.0f, 270.0f));
            add_labeled_row(slot, 0x09A8D59Au, "Saturation",
                            make_gradient_slider(0x09A8D59Bu, 0.65f, 0.0f, 1.0f, saturation_colors, 270.0f));
            add_labeled_row(slot, 0x09A8D59Cu, "Lightness",
                            make_gradient_slider(0x09A8D59Du, 0.45f, 0.0f, 1.0f, lightness_colors, 270.0f));
        }

        void make_drags_column(Block *slot)
        {
            add_labeled_row(slot, 0x09A8D59Eu, "Drag Int",
                            make_drag_int(0x09A8D59Fu, 42, 0, 100, 1.0f, {160.0f, AUIK_SIZE_Y_FIT}));
            add_labeled_row(
                slot, 0x09A8D5A0u, "Drag Float",
                make_drag_float(0x09A8D5A1u, 1.234f, 0.0f, 10.0f, 0.01f, {160.0f, AUIK_SIZE_Y_FIT}));
        }

        CollapseHeader *make_sliders_and_drags_header()
        {
            auto *header = make_collapse_header(AUIK_DEMO_SLIDERS_HEADER_ID, "Sliders and Drags", true);
            auto *columns = make_column(AUIK_DEMO_SLIDERS_COLUMNS_ID, 3u, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT});
            make_sliders_column((*columns)[0u]);
            make_hsl_sliders_column((*columns)[1u]);
            make_drags_column((*columns)[2u]);
            header->add_child(columns);
            return header;
        }

        Text *make_demo_cell_text(u32 id, StringView text)
        { return make_text(id, text, AUIK_SIZE_FIT, default_text_layout_flags(), TextAnchorY::middle); }

        Table::Cell make_demo_table_cell(u32 id, StringView text)
        {
            return make_table_cell(make_demo_cell_text(id, text));
        }

        Table *make_demo_table()
        {
            Table::Rows rows{
                {make_demo_table_cell(0x09A8D5B0u, "Alpha"), make_demo_table_cell(0x09A8D5B1u, "Core"),
                 make_demo_table_cell(0x09A8D5B2u, "123.45")},
                {make_demo_table_cell(0x09A8D5B3u, "Bravo"), make_demo_table_cell(0x09A8D5B4u, "UI"),
                 make_demo_table_cell(0x09A8D5B5u, "67.89")},
                {make_demo_table_cell(0x09A8D5B6u, "Charlie"), make_demo_table_cell(0x09A8D5B7u, "Tools"),
                 make_demo_table_cell(0x09A8D5B8u, "9.81")},
                {make_demo_table_cell(0x09A8D5B9u, "Delta"), make_demo_table_cell(0x09A8D5BAu, "Render"),
                 make_demo_table_cell(0x09A8D5BBu, "3.14")},
                {make_demo_table_cell(0x09A8D5D0u, "Echo"), make_demo_table_cell(0x09A8D5D1u, "Audio"),
                 make_demo_table_cell(0x09A8D5D7u, "0.25")},
                {make_demo_table_cell(0x09A8D5D8u, "Foxtrot"), make_demo_table_cell(0x09A8D5DBu, "Physics"),
                 make_demo_table_cell(0x09A8D5DCu, "12.00")},
            };
            auto *table = make_table(0x09A8D5BCu, std::move(rows), {400.0f, AUIK_SIZE_Y_FIT});
            table->set_header({make_demo_table_cell(0x09A8D5BDu, "Name"),
                               make_demo_table_cell(0x09A8D5BEu, "Category"),
                               make_demo_table_cell(0x09A8D5BFu, "Value")});
            table->set_alternating_rows(true);
            table->set_column_settings({{TableColumnSizing::stretch, 1.3f, 80.0f},
                                        {TableColumnSizing::stretch, 1.0f, 70.0f},
                                        {TableColumnSizing::stretch, 0.8f, 60.0f}});
            return table;
        }

        TableTree *make_demo_tree_table()
        {
            auto *tree = make_table_tree(0x09A8D5C0u, {400.0f, AUIK_SIZE_Y_FIT});
            tree->set_alternating_rows(true);
            tree->set_column_settings(
                {{TableColumnSizing::stretch, 1.45f, 130.0f}, {TableColumnSizing::stretch, 0.75f, 80.0f}});

            const size_t scene =
                tree->add_node(make_demo_cell_text(0x09A8D5C1u, "Scene"), {make_demo_cell_text(0x09A8D5E0u, "Folder")});
            const size_t camera = tree->add_node(make_demo_cell_text(0x09A8D5C2u, "Camera"),
                                                 {make_demo_cell_text(0x09A8D5E1u, "Folder")}, scene);
            tree->add_node(make_demo_cell_text(0x09A8D5C3u, "Transform"),
                           {make_demo_cell_text(0x09A8D5E2u, "Component")}, camera);
            tree->add_node(make_demo_cell_text(0x09A8D5C4u, "Lens"), {make_demo_cell_text(0x09A8D5E3u, "Component")},
                           camera);
            const size_t light = tree->add_node(make_demo_cell_text(0x09A8D5C5u, "Light"),
                                                {make_demo_cell_text(0x09A8D5E4u, "Folder")}, scene);
            tree->add_node(make_demo_cell_text(0x09A8D5C6u, "Sun"), {make_demo_cell_text(0x09A8D5E5u, "Light")}, light);
            tree->add_node(make_demo_cell_text(0x09A8D5C7u, "Fill"), {make_demo_cell_text(0x09A8D5E6u, "Light")},
                           light);
            tree->add_node(make_demo_cell_text(0x09A8D5E7u, "Cube"), {make_demo_cell_text(0x09A8D5E8u, "Mesh")}, scene);
            return tree;
        }

        Column *make_demo_column_widget()
        {
            auto *columns = make_column(0x09A8D5C8u, 2u, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT});
            (*columns)[0u]->add_child(make_demo_plain_vertical_label(0x09A8D5C9u, "Column 1"));
            (*columns)[0u]->add_child(make_text_button(0x09A8D5CAu, "Item A1", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[0u]->add_child(make_text_button(0x09A8D5CBu, "Item A2", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[0u]->add_child(make_text_button(0x09A8D5D5u, "Item A3", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[0u]->add_child(make_text_button(0x09A8D5DDu, "Item A4", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[0u]->add_child(make_text_button(0x09A8D5DEu, "Item A5", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[1u]->add_child(make_demo_plain_vertical_label(0x09A8D5CCu, "Column 2"));
            (*columns)[1u]->add_child(make_text_button(0x09A8D5CDu, "Item B1", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[1u]->add_child(make_text_button(0x09A8D5CEu, "Item B2", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[1u]->add_child(make_text_button(0x09A8D5D6u, "Item B3", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[1u]->add_child(make_text_button(0x09A8D5F0u, "Item B4", {150.0f, AUIK_SIZE_Y_FIT}));
            (*columns)[1u]->add_child(make_text_button(0x09A8D5F1u, "Item B5", {150.0f, AUIK_SIZE_Y_FIT}));
            return columns;
        }

        MultilineTextbox *make_demo_scroll_block()
        {
            const char *editor_text =
                "CollapseHeader *make_layout_and_data_header()\n"
                "{\n"
                "    auto *header = make_collapse_header(AUIK_DEMO_LAYOUT_HEADER_ID, \"Layout and Data\", true);\n"
                "    auto *columns = make_column(AUIK_DEMO_LAYOUT_COLUMNS_ID, 4u, {AUIK_SIZE_X_FILL, "
                "AUIK_SIZE_Y_FIT});\n"
                "    (*columns)[0u]->add_child(make_demo_vertical_label(0x09A8D5D2u, \"Table\"));\n"
                "    (*columns)[0u]->add_child(make_demo_table());\n"
                "    (*columns)[1u]->add_child(make_demo_vertical_label(0x09A8D5D3u, \"Tree Table\"));\n"
                "    (*columns)[1u]->add_child(make_demo_tree_table());\n"
                "    (*columns)[2u]->add_child(make_demo_vertical_label(0x09A8D5D4u, \"Column\"));\n"
                "    (*columns)[2u]->add_child(make_demo_column_widget());\n"
                "    (*columns)[3u]->add_child(make_demo_vertical_label(0x09A8D5DAu, \"Scroll Block\"));\n"
                "    (*columns)[3u]->add_child(make_demo_scroll_block());\n"
                "    header->add_child(columns);\n"
                "    return header;\n"
                "}";
            return make_multiline_textbox(0x09A8D5D9u, editor_text, {AUIK_SIZE_X_FILL, 240.0f}, false);
        }

        CollapseHeader *make_layout_and_data_header()
        {
            auto *header = make_collapse_header(AUIK_DEMO_LAYOUT_HEADER_ID, "Layout and Data", true);
            auto *columns = make_column(AUIK_DEMO_LAYOUT_COLUMNS_ID, 4u, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT});
            (*columns)[0u]->add_child(make_demo_vertical_label(0x09A8D5D2u, "Table"));
            (*columns)[0u]->add_child(make_demo_table());
            (*columns)[1u]->add_child(make_demo_vertical_label(0x09A8D5D3u, "Tree Table"));
            (*columns)[1u]->add_child(make_demo_tree_table());
            (*columns)[2u]->add_child(make_demo_vertical_label(0x09A8D5D4u, "Column"));
            (*columns)[2u]->add_child(make_demo_column_widget());
            (*columns)[3u]->add_child(make_demo_vertical_label(0x09A8D5DAu, "Scroll Block"));
            (*columns)[3u]->add_child(make_demo_scroll_block());
            header->add_child(columns);
            return header;
        }
    } // namespace

    AUIK_DEMO_EXPORT bool configure_demo_icons(Font *font, f32 dpi)
    {
        if (!font) return false;

        auto load_icon = [font, dpi](u32 id, std::initializer_list<u32> candidates) {
            for (const u32 codepoint : candidates)
            {
                const FontIconGlyphLoader icon{.size = round_font_px(40.0f * dpi),
                                               .codepoints = {codepoint},
                                               .ids = {id},
                                               .load_flags = font->load_flags(),
                                               .render_mode = font->render_mode(),
                                               .display_size = {20.0f, 20.0f}};
                if (load_font_icons(font, &icon)) return true;
            }
            return false;
        };

        return load_icon(AUIK_DEMO_ICON_STAR, {0x2605u, 0x2217u, 0x002Au}) &&
               load_icon(AUIK_DEMO_ICON_HEART, {0x2665u, 0x2661u, 0x002Bu});
    }

    AUIK_DEMO_EXPORT MenuBar *make_demo_main_menu_bar()
    {
        return auik::make_main_menu_bar(AUIK_DEMO_MAIN_MENU_BAR_ID,
                                        {"File", "Edit", "View", "Tools", "Window", "Help"});
    }

    AUIK_DEMO_EXPORT Window *make_demo_window()
    {
        auto *demo_window = auik::make_decorated_window(AUIK_DEMO_WINDOW_ID, "Demo Window",
                                                        {{14.0f, 84.0f}, {AUIK_SIZE_X_FILL, AUIK_SIZE_Y_FIT}});
        demo_window->add_child(make_basic_widgets_header());
        demo_window->add_child(make_selection_and_color_section());
        demo_window->add_child(make_sliders_and_drags_header());
        demo_window->add_child(make_layout_and_data_header());
        return demo_window;
    }
} // namespace auik
