#include "pch.h"

Image::~Image()
{
	ppTexture->Release();
	ppSprite->Release();
}

Image::Image(): EngineComponent()
{
}


void Image::EngineStart()
{
	position.x = 0;
	position.y = 0;

	scale.x = 1;
	scale.y = 1;

	rotation = 0;

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(filePath, &info);

	if (originalSize)
	{
		height = info.Height;
		width = info.Width;
	}
	
	//D3DXCreateTextureFromFile(d3ddev, filePath, &ppTexture);
	D3DXCreateTextureFromFileEx(d3ddev,
		filePath,
		width,
		height,
		info.MipLevels,
		0,
		info.Format,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFFFFFFFF,
		&info,
		NULL,
		&ppTexture);

	
	D3DXCreateSprite(d3ddev, &ppSprite);	
}

void Image::EngineUpdate()
{
	Render();
}

void Image::Render()
{
	D3DXMATRIX Mat;
	D3DXMatrixTransformation2D(&Mat, NULL, NULL, &scale, &rotationCenter, rotation, &position);
	//Render mon image
	ppSprite->Begin(0);
	ppSprite->SetTransform(&Mat);
	ppSprite->Draw(ppTexture, NULL, NULL, NULL, 0xFFFFFFFF);

	ppSprite->End();
}
