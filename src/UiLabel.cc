#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

class UiLabel : public UiControl {
 public:
  UiLabel();
  UiLabel(const char* text);
  DEFINE_CONTROL_METHODS()
  void setText(std::string text);
  std::string getText();
};

UiLabel::UiLabel(const char* text) : UiControl((uiControl*)uiNewLabel(text)) {}
UiLabel::UiLabel() : UiControl((uiControl*)uiNewLabel("")) {}

INHERITS_CONTROL_METHODS(UiLabel)

void UiLabel::setText(std::string text) {
  const char* char_ptr = text.c_str();
  uiLabelSetText((uiLabel*)getHandle(), char_ptr);
}

std::string UiLabel::getText() {
  char* char_ptr = uiLabelText((uiLabel*)getHandle());
  std::string s(char_ptr);
  uiFreeText(char_ptr);
  return s;
}

NBIND_CLASS(UiLabel) {
  construct<const char*>();
  construct<>();
  DECLARE_CHILD_CONTROL_METHODS()
  getset(getText, setText);
  method(getText);
  method(setText);
}
