#include "MainMenuScript.h"

#include "BackgroundMusic.h"
#include "Options.h"


MainMenuScript::MainMenuScript(GameObject* menuGO, GameObject* optionsGO, GameObject* creditsGO,Button* listBtn[4], InputField* listInputField[3], CheckBox* listCheckBox[5], Textbox* timerIPText, Textbox* scoreIPText, GameObject* easterEggGO)
: _menuGO(menuGO), _optionsGO(optionsGO), _creditsGO(creditsGO), _timerIPText(timerIPText), _scoreIPText(scoreIPText), _easterEggGO(easterEggGO)
{
	for (int i = 0; i < 4; i++)
	{
		_listBtn[i] = listBtn[i];
	}

	for (int i = 0; i < 4; i++)
	{
		_listInputField[i] = listInputField[i];
	}

	for (int i = 0; i < 6; i++)
	{
		_listCheckBox[i] = listCheckBox[i];
	}
}

MainMenuScript::~MainMenuScript()
{
}

void MainMenuScript::OnPlay()
{
	SceneManager::LoadScene("GameScene");
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
	StopEasterEgg();
}

void MainMenuScript::ToggleEasterEgg()
{
	_easterEggGO->GetComponent<Image>()->SetEnabled(true);
	StartEasterEgg();
}

void MainMenuScript::StartEasterEgg()
{
	BackgroundMusic::Instance->source->Pause();
	_easterEggSource->Restart();
}

void MainMenuScript::StopEasterEgg()
{
	_easterEggSource->Stop();
	BackgroundMusic::Instance->source->Resume();
}

void MainMenuScript::ToggleAudio()
{
	AudioManager::SetActive(_listCheckBox[2]->IsChecked());
}

void MainMenuScript::DisableTimer()
{
	//for lisibilty
	auto timerInputField = _listInputField[2];

	if (timerInputField->IsEnabled())
	{
		timerInputField->SetEnabled(false);
		_timerIPText->SetEnabled(false);
	}
	else
	{
		timerInputField->SetEnabled(true);
		_timerIPText->SetEnabled(true);
	}
}

void MainMenuScript::DisableScore()
{
	//for lisibilty
	auto scoreInputField = _listInputField[3];

	if (scoreInputField->IsEnabled())
	{
		scoreInputField->SetEnabled(false);
		_scoreIPText->SetEnabled(false);
	}
	else
	{
		scoreInputField->SetEnabled(true);
		_scoreIPText->SetEnabled(true);
	}
}

void MainMenuScript::OnEnable()
{
}

// **************************** //

void MainMenuScript::Start()
{
	//_button->onClick = RUNNER(MyFunc);
	_listBtn[0]->onClick = RUNNER(OnPlay);
	_listBtn[1]->onClick = RUNNER(OnOptions);
	_listBtn[2]->onClick = RUNNER(OnCredits);
	_listBtn[3]->onClick = RUNNER(OnQuit);

	// Toggle Audio Checkbox
	_listCheckBox[2]->onClick = RUNNER(ToggleAudio);

	//Show Timer Checkbox
	_listCheckBox[0]->onClick = RUNNER(DisableTimer);

	//Show Score Checkbox
	_listCheckBox[5]->onClick = RUNNER(DisableScore);

	_menuGO->SetEnabled(true);
	
	//if the gameobject is never set to true it wont be destroyed
	_optionsGO->SetEnabled(true);
	_optionsGO->SetEnabled(false);

	_creditsGO->SetEnabled(true);
	_creditsGO->SetEnabled(false);

	_easterEggGO->SetEnabled(true);
	_easterEggGO->GetComponent<Image>()->SetEnabled(true);
	_easterEggGO->SetEnabled(false);
	_easterEggGO->GetComponent<Image>()->SetEnabled(false);

	_easterEggGO->GetComponent<Button>()->onClick = RUNNER(ToggleEasterEgg);

	_listInputField[0]->SetText(Options::pseudo);
	_listInputField[1]->SetText(to_wstring(static_cast<int>(Options::playerSpeed)));
	_listInputField[2]->SetText(to_wstring(static_cast<int>(Options::timerValue)));
	_listInputField[3]->SetText(to_wstring(Options::scoreMin));

	_listCheckBox[0]->SetCheck(Options::showTimer);
	_listCheckBox[1]->SetCheck(Options::showFps);
	_listCheckBox[2]->SetCheck(Options::toggleAudio);
	_listCheckBox[3]->SetCheck(Options::rotatingCrosshair);
	_listCheckBox[4]->SetCheck(Options::pulsingCrosshair);
	_listCheckBox[5]->SetCheck(Options::showScore);

	_easterEggSource = gameObject->GetComponent<AudioSource>();
}

void MainMenuScript::Update()
{
	Options::pseudo = _listInputField[0]->GetText().c_str();
	Options::playerSpeed = static_cast<float>(_wtof(_listInputField[1]->GetText().c_str()));
	Options::timerValue = static_cast<float>(_wtof(_listInputField[2]->GetText().c_str()));
	Options::scoreMin = _wtoi(_listInputField[3]->GetText().c_str());

	Options::showTimer = _listCheckBox[0]->IsChecked();
	Options::showFps = _listCheckBox[1]->IsChecked();
	Options::toggleAudio = _listCheckBox[2]->IsChecked();
	Options::rotatingCrosshair = _listCheckBox[3]->IsChecked();
	Options::pulsingCrosshair = _listCheckBox[4]->IsChecked();
	Options::showScore = _listCheckBox[5]->IsChecked();

	if (_creditsGO->IsEnabled())
	{
		_easterEggGO->SetEnabled(true);
	}
	else
	{
		_easterEggGO->SetEnabled(false);
		_easterEggGO->GetComponent<Image>()->SetEnabled(false);
	}
}

