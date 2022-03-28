#include "RailMaker.h"

void RailMaker::Start()
{
	//MoveForward();

	srand(time(0));
	Turn(-90);
	for (int i = 0; i < 60; i++)
		MoveForward();
	Turn(-90);
}

void RailMaker::Update()
{
	/* generate secret number between 1 and 10: */

	float farestCubedist = 0;
	if (!_cubes.empty())
		farestCubedist = Utils::DistanceWithOutSquareRoot(transform->GetPosition(), _cubes.back()->transform->GetPosition());
	if (farestCubedist < (_maxDistance - _spaceBetween) * (_maxDistance - _spaceBetween))
	{
		float random = rand() % 100;
		if (random <= 2.5f)
		{
			Turn(-90);
		}
		else if (random <= 5)
		{
			Turn(90);
		}
		else
		{
			MoveForward();
		}
		random = rand() % 100;
		if (random <= 2.5f && _currentStep == 0)
		{
			_angleUp = 90;
			_currentStep = _step;
		}
		else if (random <= 5 && _currentStep == 0)
		{
			_angleUp = -90;
			_currentStep = _step;
		}
	}
}

void RailMaker::Turn(float rotate)
{
	D3DXVECTOR3 position = transform->GetPosition();
	Cube* farestCube = nullptr;
	GameObject* box = nullptr;
	for(int i = 0 ; i < _step; i++)
	{
		box = new GameObject();
		box->AddComponent(new Cube());
		box->GetComponent<Cube>();
		D3DXVECTOR3  vector;
		if (!_cubes.empty())
		{
			vector = _cubes.back()->transform->GetPosition() + _cubes.back()->transform->GetForward() * _spaceBetween;
			box->transform->SetQuaternion(_cubes.back()->transform->GetQuaternion());
		}
			
		else
			vector = transform->GetPosition() + transform->GetForward() * _spaceBetween;
		
		//vector.y += _spaceBetween * i;
		box->transform->SetPosition(vector);
		box->transform->RotateYaw((rotate / _step),Space::Self);
		if(_currentStep>0)
		{
			box->transform->RotatePitch((_angleUp / _step), Space::Self);
			_currentStep--;
		}
		
		Instantiate(box);
		_cubes.push_back(box->GetComponent<Cube>());
	}

	
}

void RailMaker::MoveForward()
{
	float farestCubedist = 0;
	D3DXVECTOR3 position = transform->GetPosition();
	Cube* farestCube = nullptr;
	GameObject* box = nullptr;
	Cube* MovingRail = nullptr;
	if (!_cubes.empty())
		farestCubedist = Utils::DistanceWithOutSquareRoot(position, _cubes.back()->transform->GetPosition());
	else
	{
		farestCubedist = 0;
	}
	if (farestCubedist < (_maxDistance - _spaceBetween) * (_maxDistance - _spaceBetween))
	{
		box = new GameObject();
		box->AddComponent<Cube>();

		D3DXVECTOR3  vector;
		if (!_cubes.empty())
		{
			vector = _cubes.back()->transform->GetPosition() + _cubes.back()->transform->GetForward() * _spaceBetween;
			box->transform->SetQuaternion(_cubes.back()->transform->GetQuaternion());
		}
		else
		{
			vector = transform->GetPosition() + transform->GetForward() * _spaceBetween;
		}
		if (_currentStep > 0)
		{
			box->transform->RotatePitch((_angleUp / _step), Space::Self);
			_currentStep--;
		}
		box->transform->SetPosition(vector);
		Instantiate(box);
		_cubes.push_back(box->GetComponent<Cube>());

	}

	
}

Cube* RailMaker::PopFrontCube()
{
	Cube* cube = _cubes.front();
	_cubes.pop_front();
	return cube;
}
