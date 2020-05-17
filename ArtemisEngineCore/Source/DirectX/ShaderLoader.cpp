﻿#include <string>
#include <map>
#include <d3dcompiler.h>

#include "ShaderLoader.h"

#include "Source/DirectX/DirectXHelper.h"

#include "Include/Exceptions/InvalidOperationException.h"
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

		if(shader.Get() == nullptr)
			throw InvalidOperationException("Could not create shader at " + path);
		
		if (shader.Get() != nullptr)
			shaders.emplace(GetShaderName(path), shader);
	}

	return shaders;
}

map<string, VertexShaderObject> ShaderLoader::LoadVertexShaders(const string& shaderDir, ComPtr<ID3D11Device>& device, map<string, VertexShaderObject>& container)
{
	list<string> shaderFiles = Directory::GetAllFilesWithExtension(shaderDir, VertexShaderExtension);
	map<string, VertexShaderObject> shaders;

	for (string& path : shaderFiles)
	{
		ComPtr<ID3DBlob> blob;
		LoadToBlob(path, blob);
		
		ComPtr<ID3D11VertexShader> shader;
		ThrowIfFailed(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf()));

		if (shader.Get() == nullptr)
			throw InvalidOperationException("Could not create shader at " + path);
		
		shaders.emplace(GetShaderName(path), VertexShaderObject(blob.Get(), shader, device));
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
