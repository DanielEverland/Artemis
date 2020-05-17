#include <string>
#include <map>
#include <d3dcompiler.h>

#include "ShaderLoader.h"

#include "Source/DirectX/DirectXHelper.h"

#include "Include/Utility/Directory.h"
#include "Include/Utility/Path.h"

using std::map;
using std::string;
using std::wstring;
using ArtemisEngine::Directory;
using namespace ArtemisEngine::IO;

const string ShaderLoader::PixelShaderExtension = ".cpso";
const string ShaderLoader::VertexShaderExtension = ".cvso";

// One MB
const int ShaderLoader::BlobSize = 1024 * 1024;

map<string, ComPtr<ID3D11PixelShader>> ShaderLoader::LoadPixelShaders(const string& shaderDir, ComPtr<ID3D11Device>& device, map<string, ComPtr<ID3D11PixelShader>>& container)
{
	list<string> shaderFiles = Directory::GetAllFilesWithExtension(shaderDir, PixelShaderExtension);
	map<string, ComPtr<ID3D11PixelShader>> shaders;

	for (string& path : shaderFiles)
	{
		ComPtr<ID3D11PixelShader> shader;
		CreatePixelShader(path, device, shader);

		if (shader.Get() != nullptr)
			shaders.emplace(GetShaderName(path), shader);
	}

	return shaders;
}

map<string, ComPtr<ID3D11VertexShader>> ShaderLoader::LoadVertexShaders(const string& shaderDir, ComPtr<ID3D11Device>& device, map<string, ComPtr<ID3D11VertexShader>>& container)
{
	list<string> shaderFiles = Directory::GetAllFilesWithExtension(shaderDir, VertexShaderExtension);
	map<string, ComPtr<ID3D11VertexShader>> shaders;

	for (string& path : shaderFiles)
	{
		ComPtr<ID3D11VertexShader> shader;
		CreateVertexShader(path, device, shader);

		if (shader.Get() != nullptr)
			shaders.emplace(GetShaderName(path), shader);
	}

	return shaders;
}

void ShaderLoader::CreatePixelShader(const string& path, ComPtr<ID3D11Device>& device, ComPtr<ID3D11PixelShader>& shader)
{
	ComPtr<ID3DBlob> blob;
	LoadToBlob(path, blob);

	ThrowIfFailed(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf()));
}

void ShaderLoader::CreateVertexShader(const string& path, ComPtr<ID3D11Device>& device, ComPtr<ID3D11VertexShader>& shader)
{
	ComPtr<ID3DBlob> blob;
	LoadToBlob(path, blob);

	ThrowIfFailed(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf()));
}

void ShaderLoader::LoadToBlob(const string& path, ComPtr<ID3DBlob>& blob)
{
	wstring widePath(path.length(), L' ');
	std::copy(path.begin(), path.end(), widePath.begin());

	ThrowIfFailed(D3DCreateBlob(BlobSize, blob.GetAddressOf()));
	ThrowIfFailed(D3DReadFileToBlob(widePath.c_str(), blob.GetAddressOf()));
}

string ShaderLoader::GetShaderName(const string& shaderPath)
{
	return Path::GetFilenameWithoutExtension(shaderPath);
}
