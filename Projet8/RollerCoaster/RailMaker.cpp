#include "RailMaker.h"
#include "Target.h"

void RailMaker::Start()
{
	srand(time(0));
}

void RailMaker::Update()
{	
	if (_cubes.size() < _maxDistance)
	{
		//next rail will have 3% (1.5% for a left turn, 1.5% for a right turn)
		//to start a 45° turn of 10 rails  
		float random = rand() % 100;

		if (random <= 1.5f && _currentStepRight == 0)
		{
			_angleRight = 45;
			_currentStepRight = _step;
		}
		else if (random <= 3.0f && _currentStepRight == 0)
		{
			_angleRight = -45;
			_currentStepRight = _step;
		}
		
		random = rand() % 100;

		if (random <= 1.5f && _currentStepUp == 0)
		{
			_angleUp = 45;
			_currentStepUp = _step;
		}
		else if (random <= 3.0f && _currentStepUp == 0)
		{
			_angleUp = -45;
			_currentStepUp = _step;
		}

		CreateLevelStep();
	}
}

RailMaker::~RailMaker()
{
	_targets.clear();
}

void RailMaker::CreateLevelStep()
{
	D3DXVECTOR3 position = transform->GetPosition();

	GameObject* box = new GameObject();
	LPCWSTR path = L"Mesh\\rail.x";
	box->AddComponent<MeshRenderer>(path);

	D3DXVECTOR3  vector;
	if (_cubes.empty() == false)
	{
		vector = _cubes.back()->transform->GetPosition() + _cubes.back()->transform->GetForward() * _spaceBetween;
		box->transform->SetQuaternion(_cubes.back()->transform->GetQuaternion());
	}
	else
	{
		vector = transform->GetPosition() + transform->GetForward() * _spaceBetween;
	}

	if (_currentStepUp > 0)
	{
		box->transform->RotatePitch((_angleUp / _step), Space::Self);
		_currentStepUp--;
	}

	if (_currentStepRight > 0)
	{
		box->transform->RotateYaw((_angleRight / _step), Space::Self);
		_currentStepRight--;
	}

	box->transform->SetPosition(vector);
	Instantiate(box);

	_cubes.push_back(box->GetComponent<MeshRenderer>());

	box->transform->SetPosition(vector);
	Instantiate(box);

	//5% chance to add a target with the new rail
	float random = rand() % 100;
	if (random <= 5)
	{
		GameObject* targetGo =  new GameObject();
		float randomX = rand() % 20 - 5;
		float randomY = rand() % 10 + 5;

		D3DXVECTOR3 targetPos = box->transform->GetPosition();
		targetPos += box->transform->GetRight() * randomX;
		targetPos += box->transform->GetUp() * randomY;

		targetGo->transform->SetPosition(targetPos);

		targetGo->AddComponent<MeshRenderer>(L"Mesh\\target.x");
		targetGo->AddComponent<Collider>();

		const auto script = new Target(&_targets);
		script->SetLookAt(transform);
		targetGo->AddComponent(script);

		Instantiate(targetGo);
		_targets.push_back(targetGo);
	}
}

MeshRenderer* RailMaker::PopFrontCube()
{
	if (_cubes.empty())
		return nullptr;
	MeshRenderer* cube = _cubes.front();
	_cubes.pop_front();
	return cube;
}
