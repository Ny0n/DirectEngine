#include "MoveAlongRails.h"
MoveAlongRails::~MoveAlongRails()
{
	if (transformWhithoutCursor != nullptr)
		transformWhithoutCursor->Destroy();
}

void MoveAlongRails::Update()
{
	_cubes = _rm->GetCube();
	Move();
	if(NbreStep > 0)
	{
		D3DXQUATERNION currentQuat = transformWhithoutCursor->GetQuaternion();
		currentQuat = Utils::SLERP(&currentQuat, &cubeQuat, 5*Time::deltaTime);
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

	D3DXVECTOR3 target =_cubes.front()->transform->GetPosition();
	target.y = 0;
	D3DXVECTOR3 pos = transform->GetPosition();
	D3DXVECTOR3 vecteurDir = (target - pos);
	D3DXVec3Normalize(&vecteurDir, &vecteurDir);
	
	pos += vecteurDir * _speed * Time::deltaTime;
	
	if (std::abs(pos.x - target.x) <= _almostOnSpot && std::abs(pos.z - target.z) <= _almostOnSpot)
	{
		_previousDir = _cubes.front()->transform->GetForward();
		Cube* cube = _rm->PopFrontCube();

		cube->gameObject->Destroy();
		_cubes = _rm->GetCube();
		
		cubeQuat = _cubes.front()->transform->GetQuaternion();
		NbreStep = 100;
	}
	
	transformWhithoutCursor->SetPosition(pos);
}


