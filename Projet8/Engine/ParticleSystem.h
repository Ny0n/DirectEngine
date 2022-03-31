#pragma once

struct Particle
{
	D3DXVECTOR3 _position;
	D3DCOLOR _color;
	static const DWORD FVF;
};

struct Attribute
{
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _acceleration;
	float      _lifeTime;
	float      _age;
	D3DXCOLOR   _color;
	D3DXCOLOR   _colorFade;
	bool       _isAlive;

	D3DXMATRIX _transformM;
	bool _matrixInitialized;
};

class ParticleSystem : public EngineComponent
{
	string GetType() override { return NAMEOF(ParticleSystem); }
	void EngineUpdate() final;


	virtual void Init(string texFileName);
	virtual void Reset();
	virtual void ResetParticle(Attribute* attribute);
	virtual void AddParticle();
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual void AnimateParticle();

	string _fileName = "pierre.png";

protected:
	void EngineStart() override;
	~ParticleSystem() override;
	virtual void removeDeadParticles();

	const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	D3DXVECTOR3 _origin;
	float _emitRate;
	float _size = 0.8f;
	float _sizeMax = 25.0f;
	bool _attachMatrix = true;

	IDirect3DTexture9* _tex;
	D3DMATERIAL9 _mat;
	LPDIRECT3DVERTEXBUFFER9 _vb;

	list<Attribute*> _particles;
	DWORD _vbSize = 2048;
	DWORD _vbOffset;
	DWORD _vbBatchSize = 512;

};
