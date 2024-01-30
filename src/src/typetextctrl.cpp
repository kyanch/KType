#include "typetextctrl.h"

void TypeTextCtrl::load_content(const wxString& str) {
  cursor_pos = 0;
  error_pos.clear();
  content = str;
  this->Clear();
  this->BeginStyle(background_attr);
  this->WriteText(content);
  this->EndStyle();
  this->SetInsertionPoint(0);
}
void TypeTextCtrl::handle_unprintable_input(const wxUniChar input,
                                            const wxUniChar content) {
  char c = 0;
  // ignore unprintable unicode, only handle ascii
  if (!input.GetAsChar(&c)) return;
  switch (c) {
    // backspace
    case '\b':
      retro_last();
      break;
    case '\r':
    case '\n':
      // return allowed only when no error
      if (!this->error_pos.empty()) {
        return;
      }
      if (content == '\r') {
        // '\r'=> pos+1  '\r\n' => pos+2
        int index = this->content[cursor_pos + 1] == '\n' ? 2 : 1;
        cursor_pos += index;
      } else if (content == '\n') {
        cursor_pos += 1;
      }
      break;
  }
  update_pos();
}
void TypeTextCtrl::OnChar(wxKeyEvent& event) {
  wxUniChar input = event.GetUnicodeKey();
  wxUniChar content = peek_next();

  if (!std::iswprint(input)) {
    return handle_unprintable_input(input, content);
  }
  // process content line end
  if (content == '\r' || content == '\n') {
    // a printable input never matchs a line end;
    return;
  }
  consum_next();
  // for normal condition
  if (content == input) {
    // input a right char
    this->SetStyle(cursor_pos - 1, cursor_pos, right_attr);
  } else {
    // input an error char
    this->Replace(cursor_pos - 1, cursor_pos, input);
    error_pos.push_back(cursor_pos - 1);
    this->SetStyle(cursor_pos - 1, cursor_pos, err_attr);
  }
  update_pos();
  return;
}