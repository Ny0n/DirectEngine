#pragma once

#include "EngineLib.h"

class Score : public MonoBehaviour
{
	string GetType() override { return NAMEOF(Score); }

	void Start() override;
	void Update() override;

public:
	Score(Textbox* scoreBox);
	~Score() override;

	static void AddScore(int n);

private:
	Textbox* _scoreBox;
	static int _score;
};
