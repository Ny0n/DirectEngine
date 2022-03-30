#include "MoveAlongRails.h"

MoveAlongRails::~MoveAlongRails()
{
	if (transformWhithoutCursor != nullptr)
		transformWhithoutCursor->Delete();
	
}

void MoveAlongRails::Update()
{

	_cubes = _rm->GetCube();
	if (!_toDelete.empty() && _toDelete.size() == 25)
	{
		MeshRenderer* cube = _toDelete.front();
		_toDelete.pop_front();
		list<GameObject*> targets = _rm->GetTarget();
		if (!targets.empty())
		{


			GameObject* toBeDeleted = targets.front();
			if (Utils::DistanceWithOutSquareRoot(toBeDeleted->transform->GetPosition(), cube->transform->GetPosition()) < 1000)
			{
				targets.pop_front();
				Destroy(toBeDeleted);
				_rm->SetTarget(targets);
			}
			Destroy(cube->gameObject);
		}
	}
	Move();
	if(NbreStep > 0)
	{
		D3DXQUATERNION currentQuat = transformWhithoutCursor->GetQuaternion();
		currentQuat = Utils::SLERP(&currentQuat, &cubeQuat, 10*Time::deltaTime);
		transformWhithoutCursor->SetQuaternion(currentQuat);
		NbreStep--;
	}
}

void MoveAlongRails::Start()
{
	_rm = gameObject->GetComponent<RailMaker>();
	transformWhithoutCursor = new Transform();
	transformWhithoutCursor->SetPosition(transform->GetPosition());
}

void MoveAlongRails::Move()
{
	if(_cubes.empty())
		return;

	/*D3DXVECTOR3 target =_cubes.front()->transform->GetPosition();*/
	D3DXVECTOR3 target = _cubes.front()->transform->GetPosition()+ _cubes.front()->transform->GetUp()*4;

	D3DXVECTOR3 pos = transform->GetPosition();
	D3DXVECTOR3 vecteurDir = (target - pos);
	D3DXVec3Normalize(&vecteurDir, &vecteurDir);
	
	pos += vecteurDir * _speed * Time::deltaTime;
	
	if (std::abs(pos.x - target.x) <= _almostOnSpot && std::abs(pos.z - target.z) <= _almostOnSpot && std::abs(pos.y - target.y) <= _almostOnSpot)
	{
		_previousDir = _cubes.front()->transform->GetForward();
		MeshRenderer* cube = _rm->PopFrontCube();
		_toDelete.push_back(cube);
		_cubes = _rm->GetCube();

		cubeQuat = _cubes.front()->transform->GetQuaternion();
		auto currentquat = transformWhithoutCursor->GetQuaternion();
		if(cubeQuat.x != currentquat.x || cubeQuat.y != currentquat.y || cubeQuat.z != currentquat.z || cubeQuat.w != currentquat.w)
			NbreStep = 20;
	}
	transformWhithoutCursor->SetPosition(pos);
}




