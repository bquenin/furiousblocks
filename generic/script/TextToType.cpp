#include "TextToType.h"

TextToType::TextToType()
{
}

String* TextToType::getText()
{
    return text;
}

void TextToType::setText(String* text)
{
    this->text = text;
}
