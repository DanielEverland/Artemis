#include <string>
#include <d3dcompiler.h>

#include "Source/DirectX/DirectXHelper.h"
#include "Include/Utility/Directory.h"

#include "ShaderLoader.h"

using std::string;
using std::wstring;
using ArtemisEngine::Directory;

// One MB
const int ShaderLoader::BlobSize = 1024 * 1024;

void ShaderLoader::LoadShaders(ComPtr<ID3D11Device>& device)
{
	string shaderDir = Directory::GetShaderDirectory();
	list<string> shaderFiles = Directory::GetAllFilesWithExtension(shaderDir, ".cso");

	for(string& path : shaderFiles)
	{
		wstring widePath(path.length(), L' ');
		std::copy(path.begin(), path.end(), widePath.begin());
		
		ID3DBlob* blob;
		ThrowIfFailed(D3DCreateBlob(BlobSize, &blob));
		
	 	ThrowIfFailed(D3DReadFileToBlob(widePath.c_str(), &blob));
		
		ID3D11PixelShader* shader;
		ThrowIfFailed(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader));
	}
}