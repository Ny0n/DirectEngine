#include "MoveAlongRails.h"
#include "MoveAlongRails.h"
void MoveAlongRails::Update()
{
	_cubes = _rm->GetCube();
	Move();
}

void MoveAlongRails::Start()
{
	_rm = static_cast<RailMaker*>(gameObject->GetComponent(NAMEOF(RailMaker)));
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
		Cube* cube = _rm->PopFrontCube();
		cube->gameObject->Destroy();
	}
	/*if(vecteurDir.x != _previousDir.x && vecteurDir.z!= _previousDir.z)
	 transform->RotateYaw(asin(D3DXVec3Dot(&vecteurDir, &_previousDir)));*/
	_previousDir = vecteurDir;
	transform->SetPosition(pos);
}