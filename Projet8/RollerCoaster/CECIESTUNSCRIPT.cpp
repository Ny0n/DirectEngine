#include "CECIESTUNSCRIPT.h"

CECIESTUNSCRIPT::CECIESTUNSCRIPT()
{
}

CECIESTUNSCRIPT::CECIESTUNSCRIPT(Image* image) : _image(image)
{
	_image->rotationCenter = D3DXVECTOR2(100, 100);
}

CECIESTUNSCRIPT::~CECIESTUNSCRIPT()
{
	//delete _image;
}

// **************************** //

void CECIESTUNSCRIPT::Start()
{
}

void CECIESTUNSCRIPT::Update()
{
	_image->rotation += Time::deltaTime * speed;
}
