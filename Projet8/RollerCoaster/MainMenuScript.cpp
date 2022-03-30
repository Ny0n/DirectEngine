#include "MainMenuScript.h"

#include "Options.h"


MainMenuScript::MainMenuScript(GameObject* menuGO, GameObject* optionsGO, GameObject* creditsGO,Button* listBtn[4], InputField* listInputField[3], CheckBox* listCheckBox[5]) : _menuGO(menuGO), _optionsGO(optionsGO), _creditsGO(creditsGO)
{
	for (int i = 0; i < 4; i++)
	{
		_listBtn[i] = listBtn[i];
	}

	for (int i = 0; i < 3; i++)
	{
		_listInputField[i] = listInputField[i];
	}

	for (int i = 0; i < 5; i++)
	{
		_listCheckBox[i] = listCheckBox[i];
	}
}

MainMenuScript::~MainMenuScript()
{
}

void MainMenuScript::MyFunc()
{
	/*auto randX = rand() % 400;
	auto randY = rand() % 350;
	_button->rectTopLeft = D3DXVECTOR2(randX, randY);
	_button->rectBottomRight = D3DXVECTOR2(randX + 300, randY +50);*/
	
}

void MainMenuScript::OnPlay()
{
	SceneManager::LoadScene("DefaultScene");
	Cursor::SetVisible(false);
}

void MainMenuScript::OnOptions()
{
	_menuGO->SetEnabled(false);
	_optionsGO->SetEnabled(true);

	auto btn = _optionsGO->GetComponent<Button>();
	btn->onClick = RUNNER(BackToMenu);
}

void MainMenuScript::OnCredits()
{
	_menuGO->SetEnabled(false);
	_creditsGO->SetEnabled(true);

	auto btn = _creditsGO->GetComponent<Button>();
	btn->onClick = RUNNER(BackToMenu);
}

void MainMenuScript::OnQuit()
{
	Application::Quit();
}

void MainMenuScript::BackToMenu()
{
	_menuGO->SetEnabled(true);
	_optionsGO->SetEnabled(false);
	_creditsGO->SetEnabled(false);
}

void MainMenuScript::ToggleAudio()
{
	AudioManager::SetActive(_listCheckBox[2]->IsChecked());
}

// **************************** //

void MainMenuScript::Start()
{
	//_button->onClick = RUNNER(MyFunc);
	_listBtn[0]->onClick = RUNNER(OnPlay);
	_listBtn[1]->onClick = RUNNER(OnOptions);
	_listBtn[2]->onClick = RUNNER(OnCredits);
	_listBtn[3]->onClick = RUNNER(OnQuit);

	_listCheckBox[2]->onClick = RUNNER(ToggleAudio);

	_menuGO->SetEnabled(true);

	//if the gameobject is never set to true it wont be destroyed
	_optionsGO->SetEnabled(true);
	_optionsGO->SetEnabled(false);

	//if the gameobject is never set to true it wont be destroyed
	_creditsGO->SetEnabled(true);
	_creditsGO->SetEnabled(false);

	_listInputField[0]->SetText(Options::pseudo);
	_listInputField[1]->SetText(to_wstring(static_cast<int>(Options::playerSpeed)));
	_listInputField[2]->SetText(to_wstring(static_cast<int>(Options::timerValue)));

	_listCheckBox[0]->SetCheck(Options::showTimer);
	_listCheckBox[1]->SetCheck(Options::showFps);
	_listCheckBox[2]->SetCheck(Options::toggleAudio);
	_listCheckBox[3]->SetCheck(Options::rotatingCrosshair);
	_listCheckBox[4]->SetCheck(Options::pulsingCrosshair);
}

void MainMenuScript::Update()
{
	Options::pseudo = _listInputField[0]->GetText();
	Options::playerSpeed = static_cast<float>(_wtof(_listInputField[1]->GetText().c_str()));
	Options::timerValue = static_cast<float>(_wtof(_listInputField[2]->GetText().c_str()));

	Options::showTimer = _listCheckBox[0]->IsChecked();
	Options::showFps = _listCheckBox[1]->IsChecked();
	Options::toggleAudio = _listCheckBox[2]->IsChecked();
	Options::rotatingCrosshair = _listCheckBox[3]->IsChecked();
	Options::pulsingCrosshair = _listCheckBox[4]->IsChecked();
}

