#include "CECIESTUNSCRIPT.h"

void CECIESTUNSCRIPT::Update()
{
	
	_image->position = D3DXVECTOR2(600, 400);
	_textbox->boxColor = D3DCOLOR_ARGB(255, x++, y++, z++);

	_textbox->text = std::to_wstring(x);
}

CECIESTUNSCRIPT::CECIESTUNSCRIPT(Image* image, Textbox* textbox) : _image(image), _textbox(textbox)
{
	_image->rotationCenter = D3DXVECTOR2(100, 100);
}

CECIESTUNSCRIPT::~CECIESTUNSCRIPT()
{
	
	//delete _image;
}
