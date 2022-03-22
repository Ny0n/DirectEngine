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

	d3ddev->CreateOffscreenPlainSurface(width,
										height,
										info.Format,
										D3DPOOL_DEFAULT,
										&surface,
										NULL);

	D3DXLoadSurfaceFromFile(surface,
		NULL,
		NULL,
		filePath,
		NULL,
		D3DX_DEFAULT,
		0xFF000000,
		NULL);
}

void Image::Render()
{
	Canvas::Render();

	//Render mon image
	LPDIRECT3DSURFACE9 backBuffer = nullptr;
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	if (surface == nullptr)
	{
		Utils::Println("null");
	}
	else
		Utils::Println("pas null");

	d3ddev->UpdateSurface(surface, NULL, backBuffer, NULL);

	if (backBuffer != nullptr)
		backBuffer->Release();
}
