#ifndef __TextToType_H_
#define __TextToType_H_


class TextToType
{
private:
    String* text = "";

protected:
public:
    TextToType();
    String* getText();
    void setText(String* text);
};

#endif //__TextToType_H_
