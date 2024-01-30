#pragma once
#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>

#include <vector>

class TypeTextCtrl : public wxRichTextCtrl {
 public:
  TypeTextCtrl(wxWindow* parent, wxWindowID id,
               const wxString& value = wxEmptyString,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize, long style = wxRE_MULTILINE)
      : wxRichTextCtrl(parent, id, value, pos, size, style),
        cursor_pos(0),
        background_attr(*wxBLACK),
        right_attr(*wxGREEN),
        err_attr(*wxRED) {
    block_default_behaviors();
    Bind(wxEVT_CHAR, &TypeTextCtrl::OnChar, this);
  }
  void load_content(const wxString& str);

  // text movement
  wxUniChar peek_next() { return content[cursor_pos]; }
  wxUniChar consum_next() { return content[cursor_pos++]; }
  void retro_last() {
    if (cursor_pos == 0) return;
    this->BeginStyle(background_attr);
    this->Replace(cursor_pos - 1, cursor_pos,
                  this->content.GetChar(cursor_pos - 1));
    this->EndStyle();
    if (!error_pos.empty() && error_pos.back() == cursor_pos - 1) {
      error_pos.pop_back();
    }
    cursor_pos--;
  }

 protected:
  void block_default_behaviors() {
    // Prohibit any cursor movement caused by user.
    Bind(wxEVT_LEFT_DOWN, &TypeTextCtrl::ignore_mouse, this);
    Bind(wxEVT_RIGHT_DOWN, &TypeTextCtrl::ignore_mouse, this);
    Bind(wxEVT_MIDDLE_DOWN, &TypeTextCtrl::ignore_mouse, this);
    Bind(wxEVT_MOTION, &TypeTextCtrl::ignore_mouse, this);
    // Prohibit clipboard
    Bind(wxEVT_COMMAND_TEXT_CUT, &TypeTextCtrl::ignore_clipboard, this);
    Bind(wxEVT_COMMAND_TEXT_PASTE, &TypeTextCtrl::ignore_clipboard, this);
  }

  void ignore_mouse(wxMouseEvent&) {}
  void ignore_clipboard(wxClipboardTextEvent&) {}
  // change keyboard event
  void OnChar(wxKeyEvent& event);

 private:
  void update_pos() { this->SetInsertionPoint(cursor_pos); }

  void handle_unprintable_input(const wxUniChar in, const wxUniChar content);

 private:
  long cursor_pos;  // cache for GetInsertionPostion()
  wxString content;
  std::vector<long> error_pos;
  wxTextAttr background_attr, right_attr, err_attr;
};