#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <list>
#include <map>

using Microsoft::WRL::ComPtr;
using std::string;
using std::map;

class ShaderLoader
{
public:
	static map<string, ComPtr<ID3D11PixelShader>> LoadPixelShaders(
		const string& shaderDir, ComPtr<ID3D11Device>& device, map<string, ComPtr<ID3D11PixelShader>>& container);
	static map<string, ComPtr<ID3D11VertexShader>> LoadVertexShaders(const string& shaderDir, ComPtr<ID3D11Device>& device, map<string, ComPtr<ID3D11VertexShader>>& container);
	
private:
	static const int BlobSize;
	static const string PixelShaderExtension;
	static const string VertexShaderExtension;

	static void CreatePixelShader(const string& path, ComPtr<ID3D11Device>& device, ComPtr<ID3D11PixelShader>& shader);	
	static void CreateVertexShader(const string& path, ComPtr<ID3D11Device>& device, ComPtr<ID3D11VertexShader>& shader);
	
	static void LoadToBlob(const string& path, ComPtr<ID3DBlob>& blob);
	static string GetShaderName(const string& shaderPath);
};
