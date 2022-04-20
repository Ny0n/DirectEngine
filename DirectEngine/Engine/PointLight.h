#pragma once

class PointLight final : public EngineComponent
{
	string GetType() override { return NAMEOF(PointLight); }

	void EngineStart() override;
	void EngineUpdate() override;

public:
	PointLight(D3DXCOLOR color, float range = 50.0f, float attenuation = 0.1f);
	~PointLight() override;

	Supplier(D3DXVECTOR3) offset = SUPPLIER(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:
	static int _nbLights;

	D3DXCOLOR _color;
	float _range;
	float _attenuation;
	int _lightID;

	D3DLIGHT9 _light;
	bool _started = false;

};
