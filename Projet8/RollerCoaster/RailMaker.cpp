#include "RailMaker.h"


void RailMaker::Update()
{
	float farestCubedist = 0;
	D3DXVECTOR3 position = transform->GetPosition();
	Cube* farestCube =nullptr;
	GameObject* box = nullptr;
	Cube* MovingRail = nullptr;
	if(!cubes.empty())
		farestCubedist = Utils::DistanceWithOutSquareRoot(position, cubes.back()->transform->GetPosition());
	if(farestCubedist < (_maxDistance - _spaceBetween)*(_maxDistance - _spaceBetween))
	{
		if(box == nullptr)
		{
			box = scene->CreateEmpty();
			box->AddComponent(new Cube());
			(Cube*)box->GetComponent(NAMEOF(Cube));
		}
		
		D3DXVECTOR3  vector;
		if (!cubes.empty())
			vector = cubes.back()->transform->GetPosition() + transform->GetForward() * _spaceBetween ;
		else
			vector = transform->GetPosition() + transform->GetForward() * _spaceBetween;
		vector.y = -4;
		if (!cubes.empty())
			box->transform->SetQuaternion(cubes.front()->transform->GetQuaternion());
		box->transform->SetPosition(vector);
		scene->Instantiate(box);
		cubes.push_back((Cube*)box->GetComponent(NAMEOF(Cube)));
		
	}

	Cube* firstCreated = cubes.front();
	if(cubes.front()->transform->GetPosition().z < transform->GetPosition().z )
	{
		
		cubes.pop_front();
	}

}

void RailMaker::Start()
{
	Turn();
}

void RailMaker::Turn()
{
	D3DXVECTOR3 position = transform->GetPosition();
	Cube* farestCube = nullptr;
	GameObject* box = nullptr;
	for(int i = 0 ; i < _step; i++)
	{
		box = scene->CreateEmpty();
		box->AddComponent(new Cube());
		(Cube*)box->GetComponent(NAMEOF(Cube));
		if (!cubes.empty())
			box->transform->SetQuaternion(cubes.front()->transform->GetQuaternion());
		if(i>=0)
			box->transform->RotateYaw(i*(_rotate / _step));
		D3DXVECTOR3  vector;
		if (!cubes.empty())
			vector = cubes.back()->transform->GetPosition() + cubes.back()->transform->GetForward() * _spaceBetween ;
		else
			vector = transform->GetPosition() + transform->GetForward() * _spaceBetween;
		vector.y = -4;
		box->transform->SetPosition(vector);
		scene->Instantiate(box);
		cubes.push_back((Cube*)box->GetComponent(NAMEOF(Cube)));
	}

	
}
