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
	D3DXIMAGE_INFO info;
	HR(D3DXGetImageInfoFromFile(filePath, &info))

	if (originalSize)
	{
		height = info.Height;
		width = info.Width;
	}
	
	//D3DXCreateTextureFromFile(d3ddev, filePath, &ppTexture);
	HR(D3DXCreateTextureFromFileEx(d3ddev,
		filePath,
		width,
		height,
		info.MipLevels,
		0,
		info.Format,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
		&info,
		NULL,
		&ppTexture))

	
	HR(D3DXCreateSprite(d3ddev, &ppSprite))
}

void Image::EngineUpdate()
{
	Render();
}

void Image::Render()
{
	if (ppTexture == NULL)
		return;

	D3DXMATRIX Mat;
	D3DXMatrixTransformation2D(&Mat, NULL, NULL, &scale, &rotationCenter, rotation, &position);
	//Render mon image
	HR(ppSprite->Begin(0))
	HR(ppSprite->SetTransform(&Mat))
	HR(ppSprite->Draw(ppTexture, NULL, NULL, NULL, 0xFFFFFFFF))

	HR(ppSprite->End())
}
