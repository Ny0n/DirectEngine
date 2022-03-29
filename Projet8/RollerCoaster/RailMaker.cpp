#include "RailMaker.h"

void RailMaker::Start()
{
	//MoveForward();

	srand(time(0));

}

void RailMaker::Update()
{
	/* generate secret number between 1 and 10: */

	float farestCubedist = 0;
	
	if (_tiles.size() < _maxDistance)
	{
		float random = rand() % 100;
		if (random <= 1.5f && _currentStepRight == 0)
		{
			_angleRight = 45;
			_currentStepRight = _step;
		}
		else if (random <= 3.0f && _currentStepRight == 0)
		{
			_angleRight = 45;
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
		MoveForward();
	}
}

RailMaker::~RailMaker()
{

	_tiles.clear();
}

void RailMaker::MoveForward()
{
	D3DXVECTOR3 position = transform->GetPosition();
	GameObject* box = nullptr;
	box = new GameObject();

	LPCWSTR path = L"Mesh\\rail.x";

	box->AddComponent<MeshRenderer>(path);

	D3DXVECTOR3  vector;
	if (!_tiles.empty())
	{
		vector = _tiles.back()->cube->transform->GetPosition() + _tiles.back()->cube->transform->GetForward() * _spaceBetween;
		box->transform->SetQuaternion(_tiles.back()->cube->transform->GetQuaternion());
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
	float random = rand() % 100;
	GameObject* targetGo = nullptr;
	if(random<=5)
	{
		targetGo = new GameObject();
		float randomX = rand() %20 - 5;
		float randomY = rand() %10 + 5;
		GameObject* targetGo = new GameObject();
		D3DXVECTOR3 targetPos = box->transform->GetPosition();
		targetPos += box->transform->GetRight() * randomX;
		targetPos += box->transform->GetUp() * randomY;
		targetGo->transform->SetPosition(targetPos);
		targetGo->AddComponent<MeshRenderer>(L"Mesh\\sphere.x");
		targetGo->AddComponent<Collider>();
		Instantiate(targetGo);
	}
	Tile* t = new Tile();
	t->cube = box->GetComponent<MeshRenderer>();
	t->target = targetGo;
	_tiles.push_back(t);

	
}

Tile* RailMaker::PopFrontCube()
{
	if (_tiles.empty())
		return nullptr;
	Tile* tile = _tiles.front();
	_tiles.pop_front();
	return tile;
}
