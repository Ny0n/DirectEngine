#pragma once

struct Particle
{
	D3DXVECTOR3 position;
	//float red, green, blue;
	//float velocity;
	//bool active;
};

struct VertexData
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
	D3DXVECTOR4 color;
};

class ParticleSystem : public EngineComponent
{
	string GetType() override { return NAMEOF(ParticleSystem); }
	void EngineStart() override;
	void EngineUpdate() override;


	~ParticleSystem() override;

};
