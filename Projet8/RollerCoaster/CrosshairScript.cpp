#include "CrosshairScript.h"

CrosshairScript::CrosshairScript(Image* img) : _img(img)
{

}

CrosshairScript::~CrosshairScript()
{
}

// **************************** //

// Start is called before the first frame update
void CrosshairScript::Start()
{
}

// Update is called once per frame
void CrosshairScript::Update()
{
	_img->rotation += .01f;
	_img->scale = D3DXVECTOR2(cos(Time::time), cos(Time::time));
}
