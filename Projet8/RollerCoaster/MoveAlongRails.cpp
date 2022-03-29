#include "MoveAlongRails.h"


MoveAlongRails::~MoveAlongRails()
{
	if (transformWhithoutCursor != nullptr)
		transformWhithoutCursor->Delete();

	
	
}

void MoveAlongRails::Update()
{

	_tiles = _rm->GetTiles();
	if (!_toDelete.empty() && _toDelete.size() == 25)
	{
		Tile* tile = _toDelete.front();
		_toDelete.pop_front();
		auto tmp =_tiles.front();
		if(tile->_cube != nullptr)
			Destroy(tile->_cube->gameObject);
		if(tile->_target != nullptr)
			Destroy(tile->_target);
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
	if(_tiles.empty())
		return;

	/*D3DXVECTOR3 target =_cubes.front()->transform->GetPosition();*/
	D3DXVECTOR3 target = _tiles.front()->_cube->transform->GetPosition()+ _tiles.front()->_cube->transform->GetUp()*4;

	D3DXVECTOR3 pos = transform->GetPosition();
	D3DXVECTOR3 vecteurDir = (target - pos);
	D3DXVec3Normalize(&vecteurDir, &vecteurDir);
	
	pos += vecteurDir * _speed * Time::deltaTime;
	
	if (std::abs(pos.x - target.x) <= _almostOnSpot && std::abs(pos.z - target.z) <= _almostOnSpot && std::abs(pos.y - target.y) <= _almostOnSpot)
	{
		_previousDir = _tiles.front()->_cube->transform->GetForward();
		auto tile = _rm->PopFrontCube();
		_toDelete.push_back(tile);
		_tiles = _rm->GetTiles();

		cubeQuat = _tiles.front()->_cube->transform->GetQuaternion();
		auto currentquat = transformWhithoutCursor->GetQuaternion();
		if(cubeQuat.x != currentquat.x || cubeQuat.y != currentquat.y || cubeQuat.z != currentquat.z || cubeQuat.w != currentquat.w)
			NbreStep = 20;
	}
	transformWhithoutCursor->SetPosition(pos);
}




