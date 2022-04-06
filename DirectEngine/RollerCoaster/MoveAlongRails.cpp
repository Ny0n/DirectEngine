#include "MoveAlongRails.h"

#include "Options.h"

MoveAlongRails::~MoveAlongRails()
{
	if (_pTransformWhithoutCursor != nullptr)
		_pTransformWhithoutCursor->Delete();
}

void MoveAlongRails::Update()
{
	_cubes = _pRailMaker->GetCube();

	if (!_toDelete.empty() && _toDelete.size() == 25)
	{
		MeshRenderer* cube = _toDelete.front();
		_toDelete.pop_front();
		list<GameObject*> targets = _pRailMaker->GetTarget();

		if (!targets.empty())
		{
			GameObject* toBeDeleted = targets.front();

			if (Utils::DistanceWithOutSquareRoot(toBeDeleted->transform->GetPosition(), cube->transform->GetPosition()) < _distanceMaxTarget)
			{
				targets.pop_front();
				Destroy(toBeDeleted);
				_pRailMaker->SetTarget(targets);
			}

			Destroy(cube->gameObject);
		}
	}

	Move();

	if(_nbStep > 0)
	{
		D3DXQUATERNION currentQuat = _pTransformWhithoutCursor->GetQuaternion();
		currentQuat = Utils::SLERP(&currentQuat, &_cubeQuat, 10*Time::deltaTime);
		_pTransformWhithoutCursor->SetQuaternion(currentQuat);

		_nbStep--;
	}
}

void MoveAlongRails::Start()
{
	_pRailMaker = gameObject->GetComponent<RailMaker>();
	_pTransformWhithoutCursor = new Transform();
	_pTransformWhithoutCursor->SetPosition(transform->GetPosition());
}

void MoveAlongRails::Move()
{
	if(_cubes.empty())
		return;

	D3DXVECTOR3 target = _cubes.front()->transform->GetPosition() 
						+ _cubes.front()->transform->GetUp() * 4;

	D3DXVECTOR3 pos = transform->GetPosition();
	D3DXVECTOR3 vecteurDir = (target - pos);
	D3DXVec3Normalize(&vecteurDir, &vecteurDir);
	
	pos += vecteurDir * Options::playerSpeed * Time::deltaTime;
	
	if (std::abs(pos.x - target.x) <= _almostOnSpot 
		&& std::abs(pos.z - target.z) <= _almostOnSpot 
		&& std::abs(pos.y - target.y) <= _almostOnSpot)
	{
		MeshRenderer* cube = _pRailMaker->PopFrontCube();
		_toDelete.push_back(cube);
		_cubes = _pRailMaker->GetCube();

		_cubeQuat = _cubes.front()->transform->GetQuaternion();
		auto currentquat = _pTransformWhithoutCursor->GetQuaternion();

		if(_cubeQuat.x != currentquat.x || _cubeQuat.y != currentquat.y 
			|| _cubeQuat.z != currentquat.z || _cubeQuat.w != currentquat.w)
			_nbStep = 20; //Smooth rotation
	}

	_pTransformWhithoutCursor->SetPosition(pos);
}




