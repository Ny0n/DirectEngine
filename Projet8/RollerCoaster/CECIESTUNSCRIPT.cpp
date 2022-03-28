#include "CECIESTUNSCRIPT.h"

CECIESTUNSCRIPT::CECIESTUNSCRIPT()
{
}

CECIESTUNSCRIPT::CECIESTUNSCRIPT(Button* button) : _button(button)
{
}

CECIESTUNSCRIPT::~CECIESTUNSCRIPT()
{
	//delete _image;
}

void CECIESTUNSCRIPT::MyFunc()
{
	Utils::Println("test");
	auto pd = rand() % 400;
	auto fdp = rand() % 350;
	_button->rectTopLeft = D3DXVECTOR2(pd, fdp);
	_button->rectBottomRight = D3DXVECTOR2(pd + 300, fdp +50);
}

// **************************** //

void CECIESTUNSCRIPT::Start()
{
	_button->onClick = RUNNER(MyFunc);

	
}

void CECIESTUNSCRIPT::Update()
{
	
}

