#include "CECINESTPASUNSCRIPT.h"

CECINESTPASUNSCRIPT::CECINESTPASUNSCRIPT(Image* img) : _img(img)
{

}

CECINESTPASUNSCRIPT::~CECINESTPASUNSCRIPT()
{
}

// **************************** //

// Start is called before the first frame update
void CECINESTPASUNSCRIPT::Start()
{
}

// Update is called once per frame
void CECINESTPASUNSCRIPT::Update()
{
	_img->rotation += .01f;
	_img->scale = D3DXVECTOR2(cos(Time::time), cos(Time::time));
}
