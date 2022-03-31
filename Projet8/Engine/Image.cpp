#include "pch.h"

Image::~Image()
{
	_texture->Release();
	_sprite->Release();
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
		&_texture))

	
	HR(D3DXCreateSprite(d3ddev, &_sprite))
}

void Image::EngineUpdate()
{
	Render();
}

void Image::Render()
{
	if (_texture == NULL)
		return;

	D3DXMATRIX Mat;
	D3DXMatrixTransformation2D(&Mat, NULL, NULL, &scale, &rotationCenter, rotation, &position);
	//Render mon image

	D3DXVECTOR3 center = D3DXVECTOR3(0,0, 0);

	if (drawFromCenter)
		center = D3DXVECTOR3(width * .5f, height * .5f, 0);

	HR(_sprite->Begin(D3DXSPRITE_ALPHABLEND))
	HR(_sprite->SetTransform(&Mat))
	HR(_sprite->Draw(_texture, NULL, &center, NULL, imageColor))

	HR(_sprite->End())
}
