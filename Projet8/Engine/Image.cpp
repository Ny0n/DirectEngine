#include "pch.h"
#include "Image.h"

Image::~Image()
{
	//delete surface;
}

void Image::EngineStart()
{
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(filePath, &info);

	if (originalSize)
	{
		height = info.Height;
		width = info.Width;
	}
	
	D3DXCreateTextureFromFile(d3ddev, filePath, &ppTexture);
	
	D3DXCreateSprite(d3ddev, &ppSprite);
}

void Image::Render()
{
	Canvas::Render();

	//Render mon image
	ppSprite->Draw(ppTexture, NULL, NULL, NULL, 0xFFFFFF);
}
