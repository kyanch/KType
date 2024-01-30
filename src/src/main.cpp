#include "main.h"

#include "inputframe.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  InputFrame *frame =
      new InputFrame("Inputtor", wxDefaultPosition, wxDefaultSize);
  frame->Show(true);
  return true;
}