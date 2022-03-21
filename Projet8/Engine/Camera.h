#pragma once

class Camera final : public EngineComponent
{

public:
	const char* GetType() override { return NAMEOF(Camera); }
    
    void EngineStart() override;
    void EngineUpdate() override;

};
