#include "TextToType.h"

TextToType::TextToType() {
}

std::string TextToType::getText() const {
  return text;
}

void TextToType::setText(std::string text) {
  this->text = text;
}
