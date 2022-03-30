#include "CrosshairScript.h"

#include "Options.h"

CrosshairScript::CrosshairScript(Image* img) : _img(img)
{

}

CrosshairScript::~CrosshairScript()
{
}

void CrosshairScript::OnEnable()
{
	Cursor::SetVisible(false);
}

void CrosshairScript::OnDisable()
{
	Cursor::SetVisible(true);
}

// **************************** //

// Start is called before the first frame update
void CrosshairScript::Start()
{
}

// Update is called once per frame
void CrosshairScript::Update()
{
	if (Options::rotatingCrosshair)
		_img->rotation += 1 * Time::deltaTime;

	if (Options::pulsingCrosshair)
		_img->scale = D3DXVECTOR2(cos(Time::time), cos(Time::time));
}
