#include "pch.h"

#include <immintrin.h>


// Start is called before the first frame update
void ParticleSystem::EngineStart()
{
	_vbSize = 20;
	_vbBatchSize = 10;
	Init(_fileName);
	for(int i = 0; i < _vbSize; i++)
	{
		AddParticle();
	}
}

// Update is called once per frame
void ParticleSystem::EngineUpdate()
{
	AnimateParticle();
	Render();
}

ParticleSystem::~ParticleSystem()
{
	if (_vb != nullptr)
		_vb->Release();
	if (_tex != nullptr)
		_tex->Release();

	for(auto att : _particles)
	{
		delete att;
		_particles.remove(att);
	}
}

void ParticleSystem::Init(string texFileName)
{
	//D3DXCreateTextureFromFile(d3ddev, L"Particle\\corona.png", &_tex);

	string pathTexture = "Particle\\" + texFileName;
	// Create the texture
	if (FAILED(D3DXCreateTextureFromFileA(d3ddev,
		pathTexture.c_str(),
		&_tex)))
	{
		MessageBox(0, L"Failed to load texture from disk", 0, 0);
	}

	_mat.Ambient.r = _mat.Ambient.g = _mat.Ambient.b = 0.0f;
	_mat.Ambient.a = 1.0f;
	_mat.Diffuse.r = _mat.Diffuse.g = _mat.Diffuse.b = 1.0f;
	_mat.Diffuse.a = 1.0f;

	d3ddev->CreateVertexBuffer(
		_vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		0);
}

void ParticleSystem::Reset()
{
	for (auto attribute : _particles)
	{
		ResetParticle(attribute);
	}
}

//resetParticule initialise a particle
void ParticleSystem::ResetParticle(Attribute* attribute)
{
	//is meant to do a snow effect but is modified to have rock falling

	attribute->_isAlive = true;
	// get random x, z coordinate for the position of the snowflake.

	D3DXVECTOR3 minM = D3DXVECTOR3(-50,-50,-50);
	D3DXVECTOR3 maxM = D3DXVECTOR3(50, 50, 50);

	Utils::GetRandomVector(
		&attribute->_position,
		&minM,
		&maxM);
	// no randomness for height (y-coordinate). Snowflake
	// always starts at the top of bounding box.
	attribute->_position.y = maxM.y;
	// snowflakes fall downward and slightly to the left
	attribute->_velocity.x = Utils::GetRandomFloat(0.0f, 1.0f) * -1.0f;
	attribute->_velocity.y = Utils::GetRandomFloat(3.0f, 10.0f) * -10.0f;
	attribute->_velocity.z = 0.0f;

	attribute->_age = 0.0f;
	attribute->_lifeTime = 20.0f;

	// white snowflake
	attribute->_color = D3DCOLOR_XRGB(120, 120, 120);

}

void ParticleSystem::AddParticle()
{
	Attribute* attribute = new Attribute();

	ResetParticle(attribute);

	_particles.push_back(attribute);
}

void ParticleSystem::PreRender()
{
	d3ddev->SetRenderState(D3DRS_LIGHTING, false);
	d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	d3ddev->SetRenderState(D3DRS_POINTSIZE, Utils::FToDword(_size));
	d3ddev->SetRenderState(D3DRS_POINTSIZE_MAX, Utils::FToDword(_sizeMax));
	// control the size of the particle relative to distance
	d3ddev->SetRenderState(D3DRS_POINTSCALE_A, Utils::FToDword(0.0f));
	d3ddev->SetRenderState(D3DRS_POINTSCALE_B, Utils::FToDword(0.0f));
	d3ddev->SetRenderState(D3DRS_POINTSCALE_C, Utils::FToDword(1.0f));
	//// use alpha from texture
	////d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void ParticleSystem::Render()
{
	if (!_particles.empty())
	{
		// set render states
		PreRender();
		d3ddev->SetMaterial(&_mat);

		d3ddev->SetTexture(0, _tex);
		d3ddev->SetFVF(FVF);
		d3ddev->SetStreamSource(0, _vb, 0, sizeof(Particle));


		// start at beginning if we're at the end of the vb
		if (_vbOffset >= _vbSize)
			_vbOffset = 0;
		Particle* v = 0;
		_vb->Lock(
			_vbOffset * sizeof(Particle),
			_vbBatchSize * sizeof(Particle),
			(void**)&v,
			_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
		DWORD numParticlesInBatch = 0;
		//
		// Until all particles have been rendered.
		//
		list<Attribute*>::iterator i;
		for (auto attribute : _particles)
		{
			if (attribute->_isAlive)
			{
				//
				// Copy a batch of the living particles to the
				// next vertex buffer segment
				//
				v->_position = attribute->_position;
				v->_color = (D3DCOLOR)attribute->_color;
				v++; // next element;
				numParticlesInBatch++; //increase batch counter
				// is this batch full?
				if (numParticlesInBatch == _vbBatchSize)
				{
					//
					// Draw the last batch of particles that was
					// copied to the vertex buffer.
					//
					_vb->Unlock();

					if (attribute->_matrixInitialized == false && _attachMatrix == false)
					{
						attribute->_transformM = transform->GetMatrix();
						attribute->_matrixInitialized = true;
					}
					else if (_attachMatrix == true)
					{
						attribute->_transformM = transform->GetMatrix();
					}

					d3ddev->SetTransform(D3DTS_WORLD, &attribute->_transformM);

					d3ddev->DrawPrimitive(
						D3DPT_POINTLIST,
						_vbOffset,
						_vbBatchSize);
					//
					// While that batch is drawing, start filling the
					// next batch with particles.
					//
					// move the offset to the start of the next batch
					_vbOffset += _vbBatchSize;
					// don't offset into memory thats outside the vb's
					// range. If we're at the end, start at the beginning.
					if (_vbOffset >= _vbSize)
						_vbOffset = 0;
					_vb->Lock(
						_vbOffset * sizeof(Particle),
						_vbBatchSize * sizeof(Particle),
						(void**)&v,
						_vbOffset ? D3DLOCK_NOOVERWRITE :
						D3DLOCK_DISCARD);
					numParticlesInBatch = 0; // reset for new batch
				}//end if
			}//end if
		}//end for
		_vb->Unlock();
		// it’s possible that the LAST batch being filled never
		// got rendered because the condition
		// (numParticlesInBatch == _vbBatchSize) would not have
		// been satisfied. We draw the last partially filled batch now.
		if (numParticlesInBatch)
		{
			d3ddev->DrawPrimitive(
				D3DPT_POINTLIST,
				_vbOffset,
				numParticlesInBatch);
		}
		// next block
		_vbOffset += _vbBatchSize;
		PostRender();
	}//end if
}

void ParticleSystem::PostRender()
{
	d3ddev->SetRenderState(D3DRS_LIGHTING, true);
	d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void ParticleSystem::AnimateParticle()
{
	for (auto attribute : _particles)
	{
		attribute->_position += attribute->_velocity * Time::deltaTime;

		// nope so kill it, but we want to recycle dead
		// particles, so respawn it instead.
		attribute->_age += Time::deltaTime;

		if (attribute->_position.y <= -150)
		{
			ResetParticle(attribute);
		}
	}
}


void ParticleSystem::removeDeadParticles()
{
	bool noMoreAlive = true;

	for (auto attribute : _particles)
	{
		if (attribute->_isAlive == true)
			noMoreAlive = false;
	}

	if (noMoreAlive == true)
	{
		Destroy(gameObject);
	}
}
