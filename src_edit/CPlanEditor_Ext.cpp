#include "CPlanEditor.h"

namespace pvmEditor {
  const short stroke_sz = 2;  // px thickness of common borders (e.g., for buttons)
  const SDL_Point* btn_col = &palette::cyan;        // default button color
  const SDL_Point* hov_col = &palette::light_cyan;  // default hover-over-button color
  const SDL_Point* nul_col = &palette::gray;        // default inactive button color
  const SDL_Point* on_col  = &palette::green;       // default button-on color
  const SDL_Point* off_col = &palette::red;         // default button-off color
  const SDL_Color* btn_fcol = &rgb::black;          // default button text color
  const short outline_sz = 2;
  const SDL_Point* outline_col      = &palette::light_cyan; // color of outline for placing tiles
  const SDL_Point* big_outline_col  = &palette::dark_cyan;  // color of outline if too large for patterns
  const SDL_Point* domain_col       = &palette::yellow; // outline for created domain
  const SDL_Point* conf_domain_col  = &palette::red;    // hover-over-domain color
  namespace adjArea {
    const short w = 160;
    const short h = 80;
    const short x = (WWIDTH - w) / 2;
    const short y = (WHEIGHT - h) / 2;
    const SDL_Rect window = CAsset::getRect(x,y,w,h);
    const short info_w  = 130;
    const short info_x  = x + ((w - info_w) / 2);
    const short info_h  = 40;
    const SDL_Rect info_rec = CAsset::getRect(info_x, y, info_w, info_h);
    const short btn_w   = 40;
    const short btn_h   = 16;
    const short btn_y   = y + info_h;
    const short spac_w  = 20;
    const short yes_x   = x + ((w - (spac_w + (btn_w * 2))) / 2);
    const short no_x    = yes_x + btn_w + spac_w;
    const SDL_Rect yes_btn = CAsset::getRect(yes_x, btn_y, btn_w, btn_h);
    const SDL_Rect no_btn  = CAsset::getRect(no_x, btn_y, btn_w, btn_h);
    const char* const info = "Are you sure you want to remove these maps?";
    const SDL_Point* window_col = &palette::black;
    const SDL_Point* border_col = &palette::white;
    const SDL_Color* title_fcol = &rgb::white;  // title/info text color
  }
  namespace tileOpts {
    const short w = 80;
    const short tset_h = 32;  // height of change-tileset button
    const short tile_h = 16;  // height of change-tile button
    const short spac = 4; // spacing between buttons
    // const short x = 180;
    const short x = WWIDTH + (EWIDTH - WWIDTH - w) / 2;
    // const short tset_y = WHEIGHT + ((EHEIGHT - WHEIGHT) - (tset_h + tile_h + spac)) / 2;
    // const short tile_y = tset_y + tset_h + spac;
    const short tset_y = 20;
    const short tile_y = tset_y + tset_h + spac;
    const SDL_Rect ts_button = CAsset::getRect(x, tset_y, w, tset_h);
    const SDL_Rect tile_button = CAsset::getRect(x, tile_y, w, tile_h);
    const SDL_Color* title_fcol = &rgb::black;
    const char* const ts_title = "Change Tileset";
    const char* const tile_title = "Select Tile";
  }
  namespace patternOpts {
    const short w = 80;
    const short h = 24;
    const short x = WWIDTH + (EWIDTH - WWIDTH - w) / 2;
    const short y = 76;
    const SDL_Rect button = CAsset::getRect(x, y, w, h);
    const SDL_Color* title_fcol = &rgb::black;
    const char* const off_title = "Use Pattern";
    const char* const on_title  = "Free Pattern";
  }
  namespace layerOpts {
    const short w = 80;
    const short x = WWIDTH + (EWIDTH - WWIDTH - w) / 2;
    const short h = 32;
    const short spac = 4;
    const short add_y = 108;
    const short del_y = add_y + h + spac;
    const SDL_Rect add_button = CAsset::getRect(x, add_y, w, h);
    const SDL_Rect del_button = CAsset::getRect(x, del_y, w, h);
    // const SDL_Rect sel_button;
    // const SDL_Rect edt_button;
    const char* const add_str = "Create\nlayer";
    const char* const del_str = "Delete\nLayer";
    namespace addOpts {
      const short w = 320;
      const short h = 240;
      const short x = (WWIDTH - w) / 2;
      const short y = (WHEIGHT - h) / 2;
      const SDL_Rect window = CAsset::getRect(x, y, w, h);
      const short list_w = 112;
      const short list_header_h  = 32;
      const SDL_Rect list_header = CAsset::getRect(x, y, list_w, list_header_h);
      const short k_w       = 24; // width of k-index column
      const short z_w       = 24; // width of depth (z) column
      const short list_x    = x + (list_w - k_w - z_w) / 2;
      const short list_y    = y + list_header_h;
      const short list_item_w   = k_w + z_w;
      const short list_item_h   = 9;
      const SDL_Rect k_title_r  = CAsset::getRect(list_x, list_y, k_w, list_item_h);
      const SDL_Rect z_title_r  = CAsset::getRect(list_x + k_w, list_y, z_w, list_item_h);

      const short work_x = x + list_w;
      const short work_w = w - list_w;
      const short work_header_h = 64;
      const short work_y = y + work_header_h;
      const short work_h = h - work_header_h;
      const SDL_Rect work_header = CAsset::getRect(work_x, y, work_w, work_header_h);

      const short option_h    = work_h / 3; // 3 options: k, z, and confirm/cancel
      const SDL_Rect k_header = CAsset::getRect(work_x, work_y, work_w, option_h / 2);
      const SDL_Rect z_header = CAsset::getRect(work_x, work_y + option_h, work_w, option_h / 2);
      const short field_w     = 24;
      const short field_x     = work_x + ((work_w - field_w) / 2);
      const SDL_Rect k_field  = CAsset::getRect(field_x, k_header.y + k_header.h, field_w, option_h / 4);
      const SDL_Rect z_field  = CAsset::getRect(field_x, z_header.y + z_header.h, field_w, option_h / 4);
      const short incr_size   = option_h / 4;

      const short decide_w  = 64;
      const short decide_h  = 16;
      const short decide_y  = work_y + (option_h * 2) + ((option_h - decide_h) / 2);
      const short conf_x    = work_x + (((work_w / 2) - decide_w) / 2);
      const short canc_x    = conf_x + (work_w / 2);
      const SDL_Rect conf_btn = CAsset::getRect(conf_x, decide_y, decide_w, decide_h);
      const SDL_Rect canc_btn = CAsset::getRect(canc_x, decide_y, decide_w, decide_h);

      const char* const info = "Pick the new layer's height Z \nand rendering index K.\n\
                                Higher Z $R$R Higher elevation\n\
                                Higher K $R$R Later rendering";
      const char* const list_title = "Preview";
      const char* const new_k_title = "New Layer K";
      const char* const new_z_title = "New Layer Z";
      const char* const conf_title = "Create";
      const char* const canc_title = "Cancel";
      const SDL_Point* window_col = &palette::black;
      const SDL_Point* border_col = &palette::white;
      const SDL_Point* field_col  = &palette::white;
      const SDL_Point* item_col_A = &palette::light_gray;
      const SDL_Point* item_col_B = &palette::silver;
      const SDL_Point* active_col = &palette::green;
      const SDL_Point* new_col    = &palette::yellow;
      const SDL_Color* title_fcol = &rgb::white;  // title/info text color
    }
    namespace delOpts {
      const short w = 180;
      const short h = 240;
      const short x = (WWIDTH - w) / 2;
      const short y = (WHEIGHT - h) / 2;
      const SDL_Rect window = CAsset::getRect(x, y, w, h);
      const short list_header_h  = 32;
      const SDL_Rect list_header = CAsset::getRect(x, y, w, list_header_h);
      const short k_w       = 24; // width of k-index column
      const short z_w       = 24; // width of depth (z) column
      const short list_x    = x + (w - k_w - z_w) / 2;
      const short list_y    = y + list_header_h;
      const short list_item_w   = k_w + z_w;
      const short list_item_h   = 9;
      const SDL_Rect k_title_r  = CAsset::getRect(list_x, list_y, k_w, list_item_h);
      const SDL_Rect z_title_r  = CAsset::getRect(list_x + k_w, list_y, z_w, list_item_h);

      const short decide_w  = 64;
      const short decide_h  = 16;
      const short decide_y  = y + h - 32;
      const short conf_x    = x + ((w / 2) - decide_w) / 2;
      const short canc_x    = conf_x + (w / 2);
      const SDL_Rect conf_btn = CAsset::getRect(conf_x, decide_y, decide_w, decide_h);
      const SDL_Rect canc_btn = CAsset::getRect(canc_x, decide_y, decide_w, decide_h);

      const char* const info = "Click the layer you would like to remove.\n\
                                Click Delete to confirm.";
      const char* const conf_title = "Delete";
      const char* const canc_title = "Cancel";
      const SDL_Point* window_col = &palette::black;
      const SDL_Point* border_col = &palette::white;
      const SDL_Point* item_col_A = &palette::light_gray;
      const SDL_Point* item_col_B = &palette::silver;
      const SDL_Point* active_col = &palette::light_red;
      const SDL_Color* title_fcol = &rgb::white;  // title/info text color
    }
  }
  namespace visOpts {
    const short nOpts = 4;    // number of visible-module options
    const short opts[] = {
      pvm_visflags::MAP,
      pvm_visflags::SOLID,
      pvm_visflags::TYPE,
      pvm_visflags::FILL
    };
    const short w = 64;      // visible-module width
    const short h = 80;
    const short opt_h = h / (nOpts + 1);
    // const short x = 20;
    // const short y = WHEIGHT + ((EHEIGHT - WHEIGHT) - h) / 2;
    const short x = WWIDTH + (EWIDTH - WWIDTH - w) / 2;
    const short y = 180;
    const SDL_Rect title_r = CAsset::getRect(x, y, w, opt_h);
    const SDL_Rect buttons[] = {
      CAsset::getRect(x, y + opt_h, w, opt_h),
      CAsset::getRect(x, y + opt_h * 2, w, opt_h),
      CAsset::getRect(x, y + opt_h * 3, w, opt_h),
      CAsset::getRect(x, y + opt_h * 4, w, opt_h)
    };
    const SDL_Color* title_fcol = &rgb::black;
    const char* const title = "Visibility";
    const char* const labels[] = {
      "Tile", "Solid", "Type", "Fill"
    };
  }
  namespace placeOpts {
    const short nOpts = 3;    // number of placement-module options
    const short opts[] = {
      ENABLE_BG,
      ENABLE_COLL,
      ENABLE_TYPE
    };
    const short w = 64;
    const short h = 64;
    const short opt_h = h / (nOpts + 1);
    // const short x = 100;
    // const short y = WHEIGHT + ((EHEIGHT - WHEIGHT) - h) / 2;
    const short x = WWIDTH + (EWIDTH - WWIDTH - w) / 2;
    const short y = 270;
    const SDL_Rect title_r = CAsset::getRect(x, y, w, opt_h);
    const SDL_Rect buttons[] = {
      CAsset::getRect(x, y + opt_h, w, opt_h),
      CAsset::getRect(x, y + opt_h * 2, w, opt_h),
      CAsset::getRect(x, y + opt_h * 3, w, opt_h)
    };
    const SDL_Color* title_fcol = &rgb::black;
    const char* const title = "Placement";
    const char* const labels[] = {
      "Tile", "Solid", "Type"
    };
  }
  namespace solidOpts {
    const short w = 64;
    const short h = 16;
    const short x = WWIDTH + ((EWIDTH - WWIDTH - w) / 2);
    const short y = WHEIGHT - 20 - h;
    const SDL_Rect button = CAsset::getRect(x, y, w, h);
    const char* const labels[] = {
      "Solid Off", "Solid On"
    };
  }
  namespace typeOpts {
    const short type_sz = 16; // w/h of type icon
    const short cols = 4;     // N of icons in a row (N of columns)
    const short spac = 2;     // spacing between icons
    const short x = WWIDTH + ((EWIDTH - WWIDTH - (type_sz * cols) - (spac * (cols - 1))) / 2);
    const short y = WHEIGHT - 100;
    const SDL_Point pos = CAsset::getPos(x, y);
    const SDL_Point* hl_col = &palette::red;
  }
  namespace opacOpts {
    const short nMeters = 3;
    const short meter_x = 20;
    const short meter_w = ((MAX_RGBA + 1) / 2) + (stroke_sz * 2);
    const short meter_h = 10;
    const short title_h = 10;
    const short opt_h   = meter_h + title_h;
    const short title_y = WHEIGHT + 10;
    const short meter_y = title_y + title_h;
    const SDL_Rect r_titles[] = {
      CAsset::getRect(meter_x, title_y, meter_w, meter_h),
      CAsset::getRect(meter_x, title_y + opt_h, meter_w, meter_h),
      CAsset::getRect(meter_x, title_y + (opt_h * 2), meter_w, meter_h)
    };
    const SDL_Rect meters[] = {
      CAsset::getRect(meter_x, meter_y, meter_w, meter_h),
      CAsset::getRect(meter_x, meter_y + opt_h, meter_w, meter_h),
      CAsset::getRect(meter_x, meter_y + (opt_h * 2), meter_w, meter_h)
    };
    const char* const titles[] = {
      "Active Opacity",
      "Overlay Opacity",
      "Underlay Opacity"
    };
    const short button_h = 16;
    const short button_y = title_y + (opt_h * 3) + ((opt_h - button_h) / 2);
    const SDL_Rect more_button = CAsset::getRect(meter_x, button_y, meter_w, button_h);
    const char* const more_title = "Specify ...";
    namespace adjOpts {
      const short w = 320;
      const short h = 280;
      const short x = (WWIDTH - w) / 2;
      const short y = (WHEIGHT - h) / 2;
      const SDL_Rect window = CAsset::getRect(x, y, w, h);
      const short header_w = 280;
      const short header_h = 32;
      const SDL_Rect header = CAsset::getRect(x + ((w - header_w) / 2), y, header_w, header_h);

      // for each layer, we need K, Z, opacity meter, and force switch.
      const short layer_h = 9;
      const short k_w = 24;
      const short z_w = 24;
      const short meter_w = ((MAX_RGBA + 1) / 2) + (stroke_sz * 2);
      const short force_w = 32;
      const short spac_w = 2;
      const short total_w = k_w + z_w + meter_w + force_w + (spac_w * 3);

      const short spac_h = 4;

      const short k_x = x + (w - total_w) / 2;
      const short z_x = k_x + k_w + spac_w;
      const short meter_x = z_x + z_w + spac_w;
      const short force_x = meter_x + meter_w + spac_w;

      const SDL_Rect k_r = CAsset::getRect(k_x, y + header_h, k_w, layer_h);
      const SDL_Rect z_r = CAsset::getRect(z_x, y + header_h, z_w, layer_h);
      const SDL_Rect meter_r = CAsset::getRect(meter_x, y + header_h, meter_w, layer_h);
      const SDL_Rect force_r = CAsset::getRect(force_x, y + header_h, force_w, layer_h);

      const short footer_w  = 200;
      const short footer_h  = 48;
      const short footer_x  = x + ((w - footer_w) / 2);
      const short footer_y  = (y + h - footer_h);
      const short decide_w  = 64;
      const short decide_h  = 16;
      const short decide_y  = footer_y + ((footer_h - decide_h) / 2);
      const short conf_x    = footer_x + (((footer_w / 2) - decide_w) / 2);
      const short canc_x    = conf_x + (footer_w / 2);
      const SDL_Rect conf_btn = CAsset::getRect(conf_x, decide_y, decide_w, decide_h);
      const SDL_Rect canc_btn = CAsset::getRect(canc_x, decide_y, decide_w, decide_h);

      const char* const info = "Adjust specific layer opacities,\n\
                                and enable using force.\n\
                                With force off, default opacities are used.";
      const char* const k_title = "K";
      const char* const z_title = "Z";
      const char* const meter_title = "Opacity Meter";
      const char* const force_title = "Force";
      const char* const conf_title  = "Confirm";
      const char* const canc_title  = "Cancel";
      const SDL_Point* window_col = &palette::black;
      const SDL_Point* border_col = &palette::white;
      const SDL_Point* item_col_A = &palette::light_gray;
      const SDL_Point* item_col_B = &palette::silver;
      const SDL_Color* title_fcol = &rgb::white;  // title/info text color
    }
  }
  namespace basicLayer {
    const short module_x = 200;
    const short module_y = WHEIGHT + 10;
    const short module_w = 200;
    const short module_h = 80;
    const SDL_Rect module_r = CAsset::getRect(module_x, module_y, module_w, module_h);
    const short k_w = 24;
    const short z_w = 24;
    const short item_w = k_w + z_w;
    const short item_h = 9;
    const short max_num_lists = 3;
    const short items_per_list = 7;
    const short spac_w = (module_w - (item_w * max_num_lists)) / (max_num_lists + 1);
    const SDL_Rect k_r = CAsset::getRect(module_x + spac_w, module_y, k_w, item_h);
    const SDL_Rect z_r = CAsset::getRect(k_r.x + k_w, module_y, k_w, item_h);
    const SDL_Point* item_col_A = &palette::white;
    const SDL_Point* item_col_B = &palette::silver;
    const SDL_Point* active_col = &palette::green;
    const SDL_Point* hover_col  = &palette::yellow;
  }
} // planview map editor namespaces //
