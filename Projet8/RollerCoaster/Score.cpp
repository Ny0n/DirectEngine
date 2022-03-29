#include "Score.h"

int Score::_score = 0;

Score::Score(Textbox* scoreBox) : _scoreBox(scoreBox)
{
}

Score::~Score()
{
}

void Score::AddScore(int n)
{
	_score += n;
}

// **************************** //

// Start is called before the first frame update
void Score::Start()
{
	
}

// Update is called once per frame
void Score::Update()
{
	_scoreBox->text = L"Score: " + to_wstring(_score);
}
