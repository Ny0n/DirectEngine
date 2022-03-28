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
	//Utils::Println("----------------------------");
	//Utils::Println(_cubes.front()->transform->GetUp().x);
	//Utils::Println(_cubes.front()->transform->GetUp().y);
	//Utils::Println(_cubes.front()->transform->GetUp().z);
	//Utils::Println(transform->GetUp().x);
	//Utils::Println(transform->GetUp().y);
	//Utils::Println(transform->GetUp().z);
	D3DXVECTOR3 pos = transform->GetPosition();
	D3DXVECTOR3 vecteurDir = (target - pos);
	D3DXVec3Normalize(&vecteurDir, &vecteurDir);
	
	pos += vecteurDir * _speed * Time::deltaTime;
	
	if (std::abs(pos.x - target.x) <= _almostOnSpot && std::abs(pos.z - target.z) <= _almostOnSpot && std::abs(pos.y - target.y) <= _almostOnSpot)
	{
		_previousDir = _cubes.front()->transform->GetForward();
		Cube* cube = _rm->PopFrontCube();

		cube->gameObject->Destroy();
		_cubes = _rm->GetCube();

		cubeQuat = _cubes.front()->transform->GetQuaternion();
		transformWhithoutCursor->SetQuaternion(cubeQuat);
		NbreStep = 20;
	}
	transformWhithoutCursor->SetPosition(pos);
}


