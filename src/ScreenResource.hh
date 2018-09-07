// TODO - Documentation

#ifndef   __ScreenResource_hh
#define   __ScreenResource_hh

#include <Bitmap.hh>
#include <Color.hh>
#include <Font.hh>
#include <Texture.hh>
#include <Util.hh>

#include <vector>

class BScreen;

struct ToolbarOptions {
  bool enabled;
  int placement;
  bool always_on_top, auto_hide;
  int width_percent;
  std::string strftime_format;
};

struct SlitOptions {
  int direction;
  int placement;
  bool always_on_top, auto_hide;
};

struct WindowStyle {
  struct {
    bt::Color text, foreground, frame_border;
    bt::Texture title, label, button, handle, grip;
  } focus, unfocus;
  bt::Alignment alignment;
  bt::Bitmap iconify, maximize, restore, close;
  bt::Font font;
  bt::Texture pressed;
  unsigned int title_margin, label_margin, button_margin,
    frame_border_width, handle_height;

  // calculated
  unsigned int title_height, label_height, button_width, grip_width;
};

struct ToolbarStyle {
  bt::Bitmap left, right;
  bt::Color slabel_text, wlabel_text, clock_text, foreground;
  bt::Texture toolbar, slabel, wlabel, clock, button, pressed;
  bt::Font font;
  bt::Alignment alignment;
  unsigned int frame_margin, label_margin, button_margin;

  // calculated extents
  unsigned int toolbar_height, label_height, button_width, hidden_height;
};

struct SlitStyle {
  bt::Texture slit;
  unsigned int margin;
};


class ScreenResource : public bt::NoCopy {
public:
  void loadStyle(BScreen* screen, const std::string& style);
  void load(bt::Resource& res, unsigned int screen);
  void save(bt::Resource& res, BScreen* screen);

  inline const ToolbarOptions &toolbarOptions(void) const
  { return _toolbarOptions; }
  inline const SlitOptions &slitOptions(void) const
  { return _slitOptions; }

  inline const WindowStyle &windowStyle(void) const
  { return _windowStyle; }
  inline const ToolbarStyle &toolbarStyle(void) const
  { return _toolbarStyle; }
  inline const SlitStyle &slitStyle(void) const
  { return _slitStyle; }

  inline unsigned int workspaceCount(void) const
  { return workspace_count; }
  inline void setWorkspaceCount(unsigned int w)
  { workspace_count = w; }

  const bt::ustring workspaceName(unsigned int i) const;
  void setWorkspaceName(unsigned int w, const bt::ustring &name);

  inline const std::string& rootCommand(void) const
  { return root_command; }

private:
  ToolbarOptions _toolbarOptions;
  SlitOptions _slitOptions;

  WindowStyle _windowStyle;
  ToolbarStyle _toolbarStyle;
  SlitStyle _slitStyle;

  unsigned int workspace_count;
  std::vector<bt::ustring> workspace_names;
  std::string root_command;
};

#endif // __ScreenResource_hh
