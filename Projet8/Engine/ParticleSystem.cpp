#include "pch.h"

#include <immintrin.h>


// Start is called before the first frame update
void ParticleSystem::EngineStart()
{
	init(L"");
	for(int i = 0; i < _vbSize; i++)
	{
		addParticle();
	}
}

// Update is called once per frame
void ParticleSystem::EngineUpdate()
{
	for (auto attribute : _particles)
	{
		attribute->_position += attribute->_velocity * Time::deltaTime;
		
		// is the point outside bounds?
		if (attribute->_position.y <= -30)
		{
			// nope so kill it, but we want to recycle dead
			// particles, so respawn it instead.
			resetParticle(attribute);
		}
	}

	render();
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

void ParticleSystem::init(LPCWSTR texFileName)
{
	//D3DXCreateTextureFromFile(d3ddev, L"Particle\\corona.png", &_tex);

	string pathTexture = "Particle\\pierre.png";
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

void ParticleSystem::reset()
{
	for (auto attribute : _particles)
	{
		resetParticle(attribute);
	}
}

void ParticleSystem::resetParticle(Attribute* attribute)
{
	attribute->_isAlive = true;
	// get random x, z coordinate for the position of the snowflake.

	D3DXVECTOR3 min = D3DXVECTOR3(-50, 20, -50);
	D3DXVECTOR3 max = D3DXVECTOR3(50, 20, 50);

	Utils::GetRandomVector(
		&attribute->_position,
		&min,
		&max);

	// no randomness for height (y-coordinate). Snowflake
	// always starts at the top of bounding box.
	//attribute->_position.y = 20;
	// snowflakes fall downward and slightly to the left
	attribute->_velocity.x = 0;
	attribute->_velocity.y = Utils::GetRandomFloat(0.0f, 1.0f) * -20.0f;
	attribute->_velocity.z = 0.0f;
	// white snowflake
	attribute->_color = D3DCOLOR_ARGB(0,255,255, 255);
}

void ParticleSystem::addParticle()
{
	Attribute* attribute = new Attribute();

	resetParticle(attribute);

	_particles.push_back(attribute);
}

void ParticleSystem::preRender()
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

void ParticleSystem::render()
{
	if (!_particles.empty())
	{
		// set render states
		preRender();
		d3ddev->SetMaterial(&_mat);

		d3ddev->SetTexture(0, _tex);
		d3ddev->SetFVF(FVF);
		d3ddev->SetStreamSource(0, _vb, 0, sizeof(Particle));

		D3DXMATRIX matrix = transform->GetMatrix();
		d3ddev->SetTransform(D3DTS_WORLD, &matrix);


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
		postRender();
	}//end if
}

void ParticleSystem::postRender()
{
	d3ddev->SetRenderState(D3DRS_LIGHTING, true);
	d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

bool ParticleSystem::isEmpty()
{
	return false;
}

bool ParticleSystem::isDead()
{
	return false;
}

void ParticleSystem::removeDeadParticles()
{
	list<Attribute*>::iterator i;

	for (auto attribute : _particles)
	{
		if ( attribute->_isAlive == false)
		{
			// erase returns the next iterator, so no need
			// to incrememnt to the next one ourselves.
			i = _particles.erase(i);
		}
		else
		{
			i++; // next in list
		}
	}
}
