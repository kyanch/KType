#pragma once
#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>

#include <fstream>
#include <sstream>

#include "typetextctrl.h"

class InputFrame : public wxFrame {
 public:
  InputFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
      : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    inputor = new TypeTextCtrl(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(inputor, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(sizer);
    this->Layout();
    load_file();
  }

 private:
  void load_file() {
    std::ifstream in(__FILE__);
    if (in) {
      std::stringstream ss;
      ss << in.rdbuf();
      inputor->load_content(ss.str());
    }
  }
  void init_input();
  void ignore_keydown(wxKeyEvent& e) {}
  void ignore_mouse(wxMouseEvent& e) {}

 private:
  TypeTextCtrl* inputor;
};