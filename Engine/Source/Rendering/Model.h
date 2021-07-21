#pragma once

#include "Core.h"
#include "DirectXCore.h"

namespace ArtemisEngine
{
	class Model
	{
	public:
		Model();
		Model(const Model&);
		~Model();

		bool Initialize(ID3D11Device*);
		void Shutdown();
		void Render(ID3D11DeviceContext*);

		int GetIndexCount();
	
	private:
		struct VertexType
		{
			XMFLOAT3 position;
			XMFLOAT4 color;
		};

		ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
		int m_vertexCount, m_indexCount;

		bool InitializeBuffers(ID3D11Device*);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);
	};
}
