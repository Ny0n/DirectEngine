#include "CECIESTUNSCRIPT.h"

void CECIESTUNSCRIPT::Update()
{
	_image->rotation += Time::deltaTime * speed;
	speed -= speed / 2.0f;
	
}

CECIESTUNSCRIPT::CECIESTUNSCRIPT(Image* image) : _image(image)
{
	_image->rotationCenter = D3DXVECTOR2(100, 100);
}

CECIESTUNSCRIPT::~CECIESTUNSCRIPT()
{
	//delete _image;
}
