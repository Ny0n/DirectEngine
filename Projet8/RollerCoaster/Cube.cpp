#include "Cube.h"

Cube::Cube(GameObject* g, float size)
{
	_Transform = g->transform;
	_Size = size;

    type = ComponentType::movable_cube;
    

}

void Cube::Start()
{

}

void Cube::Update(float runTime, float deltaTime)
{
    cubeRender();
    
    cubePlacement();
}

void Cube::cubeRender()
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
    d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &_VBuffer,
        NULL);

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

    // create a index buffer interface called i_buffer
    d3ddev->CreateIndexBuffer(36 * sizeof(short),
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &_IBuffer,
        NULL);

    // lock i_buffer and load the indices into it
    _IBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    _IBuffer->Unlock();
}
void Cube::cubePlacement()
{
    D3DXMATRIX matTranslate;    // a matrix to store the translation information

    // build a matrix to move the model 12 units along the x-axis and 4 units along the y-axis
    // store it to matTranslate
    D3DXMATRIX matRotate;
    D3DXMATRIX matRotateX;
    D3DXMATRIX matRotateY;
    D3DXMATRIX matRotateZ;
    D3DXMATRIX matScale;
    D3DXMATRIX finalMat;
    //D3DXMATRIX matTranslate;
    D3DXMatrixIdentity(&matRotateX);
    //D3DXMatrixIdentity(&matRotateY);
    D3DXMatrixIdentity(&matRotateZ);
    D3DXMatrixIdentity(&matScale);
    D3DXMatrixIdentity(&matTranslate);

    D3DXMatrixRotationX(&matRotateX, _Transform->quaternion.x);
    D3DXMatrixRotationY(&matRotateY, _Transform->quaternion.y);    // the front side
    D3DXMatrixRotationZ(&matRotateZ, _Transform->quaternion.z);

    D3DXMatrixScaling(&matScale, _Transform->scale.x, _Transform->scale.y, _Transform->scale.z);

    D3DXMatrixTranslation(&matTranslate, _Transform->position.x, _Transform->position.y, _Transform->position.z);

    matRotate = matRotateX;
    matRotate *= matRotateY;
    matRotate *= matRotateZ;

    finalMat = matRotate;

    finalMat *= matTranslate;



    finalMat *= matScale;


    // select the vertex buffer to display
    d3ddev->SetStreamSource(0, _VBuffer, 0, sizeof(CUSTOMVERTEX));
    d3ddev->SetIndices(_IBuffer);

    //d3ddev->SetTransform(D3DTS_WORLD, &finalMat);
    //d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    //d3ddev->SetTransform(D3DTS_WORLD, &finalMatB);
    //d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    // draw the Hypercraft
    d3ddev->SetTransform(D3DTS_WORLD, &finalMat);
    d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);


    // copy the vertex buffer to the back buffer
    //d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}