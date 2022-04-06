#include "PauseScript.h"

PauseScript::PauseScript()
{
}

PauseScript::~PauseScript()
{
}

void PauseScript::OnEnable()
{
	Time::timeScale = 0;
	isPaused = true;
}

void PauseScript::OnDisable()
{
	Time::timeScale = 1;
	isPaused = false;
}

// **************************** //

// Start is called before the first frame update
void PauseScript::Start()
{
	
}

// Update is called once per frame
void PauseScript::Update()
{
}
