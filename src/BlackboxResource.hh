// TODO - Documentation.

#ifndef   __BlackboxResource_hh
#define   __BlackboxResource_hh

#include "ScreenResource.hh"

#include <Timer.hh>
#include <Util.hh>
#include <strings.h>

class Blackbox;

enum FocusModel {
  SloppyFocusModel,
  ClickToFocusModel
};

enum WindowPlacementPolicy {
  RowSmartPlacement = 400,
  ColSmartPlacement,
  CenterPlacement,
  CascadePlacement,
  LeftRight,
  RightLeft,
  TopBottom,
  BottomTop
};

struct Cursors {
  Cursor pointer;
  Cursor move;
  Cursor resize_top_left;
  Cursor resize_bottom_left;
  Cursor resize_top_right;
  Cursor resize_bottom_right;
};

class BlackboxResource: public bt::NoCopy {
private:
  ScreenResource *screen_resources;

  Cursors _cursors;

  std::string menu_file, style_file, rc_file;
  Time double_click_interval;
  bt::timeval auto_raise_delay;

  FocusModel focus_model;
  int window_placement_policy;
  int row_direction, col_direction;
  bool ignore_shaded;
  bool auto_raise;
  bool click_raise;
  bool opaque_move;
  bool opaque_resize;
  bool full_max;
  bool focus_new_windows;
  bool focus_last_window_on_workspace;
  bool allow_scroll_lock;
  bool change_workspace_with_mouse_wheel;
  bool shade_window_with_mouse_wheel;
  bool toolbar_actions_with_mouse_wheel;
  unsigned int edge_snap_threshold;
  unsigned int window_snap_threshold;

public:
  BlackboxResource(const std::string& rc);
  ~BlackboxResource(void);

  void load(Blackbox& blackbox);
  void save(Blackbox& blackbox);

  inline ScreenResource &screenResource(unsigned int screen)
  { return screen_resources[screen]; }

  inline const Cursors &cursors(void) const
  { return _cursors; }

  inline const char* rcFilename(void) const
  { return rc_file.c_str(); }
  inline const char* menuFilename(void) const
  { return menu_file.c_str(); }
  inline const char* styleFilename(void) const
  { return style_file.c_str(); }

  inline void saveStyleFilename(const std::string& name)
  { style_file = name; }

  inline Time doubleClickInterval(void) const
  { return double_click_interval; }
  inline const bt::timeval& autoRaiseDelay(void) const
  { return auto_raise_delay; }

  // window focus model
  inline FocusModel focusModel(void) const
  { return focus_model; }
  inline void setFocusModel(FocusModel fm)
  { focus_model = fm; }

  inline bool autoRaise(void) const
  { return auto_raise; }
  inline void setAutoRaise(bool b = true)
  { auto_raise = b; }

  inline bool clickRaise(void) const
  { return click_raise; }
  inline void setClickRaise(bool b = true)
  { click_raise = b; }

  // window placement
  inline int windowPlacementPolicy(void) const
  { return window_placement_policy; }
  inline void setWindowPlacementPolicy(int p)
  { window_placement_policy = p;    }

  inline int rowPlacementDirection(void) const
  { return row_direction; }
  inline void setRowPlacementDirection(int d)
  { row_direction = d; }

  inline int colPlacementDirection(void) const
  { return col_direction; }
  inline void setColPlacementDirection(int d)
  { col_direction = d;       }

  inline bool placementIgnoresShaded(void) const
  { return ignore_shaded; }
  inline void setPlacementIgnoresShaded(bool f)
  { ignore_shaded = f; }

  // other window options
  inline bool opaqueMove(void) const
  { return opaque_move; }
  inline void setOpaqueMove(bool b = true)
  { opaque_move = b; }

  inline bool opaqueResize(void) const
  { return opaque_resize; }
  inline void setOpaqueResize(bool b = true)
  { opaque_resize = b; }

  inline bool fullMaximization(void) const
  { return full_max; }
  inline void setFullMaximization(bool b = true)
  { full_max = b; }

  inline bool focusNewWindows(void) const
  { return focus_new_windows; }
  inline void setFocusNewWindows(bool b = true)
  { focus_new_windows = b; }

  inline bool focusLastWindowOnWorkspace(void) const
  { return focus_last_window_on_workspace; }
  inline void setFocusLastWindowOnWorkspace(bool b = true)
  { focus_last_window_on_workspace = b; }

  inline bool changeWorkspaceWithMouseWheel(void) const
  { return change_workspace_with_mouse_wheel; }
  inline void setChangeWorkspaceWithMouseWheel(bool b = true)
  { change_workspace_with_mouse_wheel = b; }

  inline bool shadeWindowWithMouseWheel(void) const
  { return shade_window_with_mouse_wheel; }
  inline void setShadeWindowWithMouseWheel(bool b = true)
  { shade_window_with_mouse_wheel = b; }

  inline bool toolbarActionsWithMouseWheel(void) const
  { return toolbar_actions_with_mouse_wheel; }
  inline void setToolbarActionsWithMouseWheel(bool b = true)
  { toolbar_actions_with_mouse_wheel = b; }

  inline bool allowScrollLock(void) const
  { return allow_scroll_lock; }
  inline void setAllowScrollLock(bool a)
  { allow_scroll_lock = a; }

  inline unsigned int edgeSnapThreshold(void) const
  { return edge_snap_threshold; }
  inline void setEdgeSnapThreshold(unsigned int t)
  { edge_snap_threshold = t; }

  inline unsigned int windowSnapThreshold(void) const
  { return window_snap_threshold; }
  inline void setWindowSnapThreshold(unsigned int t)
  { window_snap_threshold = t; }
};

#endif
