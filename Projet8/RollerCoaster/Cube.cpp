#include "Cube.h"

void Cube::Start()
{
}

void Cube::Update()
{
    CubeRender();
    CubePlacement();
}

void Cube::CubeRender()
{
    float baseSize;
    baseSize = 1;

    CUSTOMVERTEX vertices[] =
    {
        { -baseSize, -baseSize, +baseSize, 0.0f, 0.0f, 1.0f, },    // side 1
        { +baseSize, -baseSize, +baseSize, 0.0f, 0.0f, 1.0f, },
        { -baseSize, +baseSize, +baseSize, 0.0f, 0.0f, 1.0f, },
        { +baseSize, +baseSize, +baseSize, 0.0f, 0.0f, 1.0f, },

        { -baseSize, -baseSize, -baseSize, 0.0f, 0.0f, -1.0f, },    // side 2
        { -baseSize, +baseSize, -baseSize, 0.0f, 0.0f, -1.0f, },
        { +baseSize, -baseSize, -baseSize, 0.0f, 0.0f, -1.0f, },
        { +baseSize, +baseSize, -baseSize, 0.0f, 0.0f, -1.0f, },

        { -baseSize, +baseSize, -baseSize, 0.0f, 1.0f, 0.0f, },    // side 3
        { -baseSize, +baseSize, +baseSize, 0.0f, 1.0f, 0.0f, },
        { +baseSize, +baseSize, -baseSize, 0.0f, 1.0f, 0.0f, },
        { +baseSize, +baseSize, +baseSize, 0.0f, 1.0f, 0.0f, },

        { -baseSize, -baseSize, -baseSize, 0.0f, -1.0f, 0.0f, },    // side 4
        { +baseSize, -baseSize, -baseSize, 0.0f, -1.0f, 0.0f, },
        { -baseSize, -baseSize, +baseSize, 0.0f, -1.0f, 0.0f, },
        { +baseSize, -baseSize, +baseSize, 0.0f, -1.0f, 0.0f, },

        { +baseSize, -baseSize, -baseSize, 1.0f, 0.0f, 0.0f, },    // side 5
        { +baseSize, +baseSize, -baseSize, 1.0f, 0.0f, 0.0f, },
        { +baseSize, -baseSize, +baseSize, 1.0f, 0.0f, 0.0f, },
        { +baseSize, +baseSize, +baseSize, 1.0f, 0.0f, 0.0f, },

        { -baseSize, -baseSize, -baseSize, -1.0f, 0.0f, 0.0f, },    // side 6 
        { -baseSize, -baseSize, +baseSize, -1.0f, 0.0f, 0.0f, },
        { -baseSize, +baseSize, -baseSize, -1.0f, 0.0f, 0.0f, },
        { -baseSize, +baseSize, +baseSize, -1.0f, 0.0f, 0.0f, },

    };

    VOID* pVoid;    // a void pointer

    // lock _VBuffer and load the vertices into it
    _VBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    _VBuffer->Unlock();

    // create the indices using an int array
    short indices[] =
    {
        0, 1, 2,    // side 1
        2, 1, 3,
        4, 5, 6,    // side 2
        6, 5, 7,
        8, 9, 10,    // side 3
        10, 9, 11,
        12, 13, 14,    // side 4
        14, 13, 15,
        16, 17, 18,    // side 5
        18, 17, 19,
        20, 21, 22,    // side 6
        22, 21, 23,
    };

    // lock i_buffer and load the indices into it
    _IBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    _IBuffer->Unlock();
}

void Cube::CubePlacement()
{
    D3DXMATRIX finalMat = transform->GetMatrix();
    d3ddev->SetTransform(D3DTS_WORLD, &(finalMat));
    d3ddev->SetStreamSource(0, _VBuffer, 0, sizeof(CUSTOMVERTEX));
    d3ddev->SetIndices(_IBuffer);

    // draw the cube
    d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

    // copy the vertex buffer to the back buffer
    //d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
