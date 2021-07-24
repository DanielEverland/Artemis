#pragma once

#include <map>

#include "Core.h"
#include "GraphicsDevice.h"

namespace ArtemisEngine
{
	class ShaderLoader
	{
	public:
		static void LoadAllShaders(shared_ptr<GraphicsDevice> device);
		static ComPtr<ID3D11VertexShader> GetVertexShader(const string& shaderName);
		static ComPtr<ID3D11PixelShader> GetPixelShader(const string& shaderName);
		static ComPtr<ID3DBlob> GetVertexShaderBLOB(const string& shaderName);

	private:
		static string ExpectedExtension;

		static map<string, ComPtr<ID3D11VertexShader>> VertexShaders;
		static map<string, ComPtr<ID3D11PixelShader>> PixelShaders;
		static map<string, ComPtr<ID3DBlob>> VertexShaderBlobs;

		[[nodiscard]] static string GetDirectory(const string& shaderTypeName);
		[[nodiscard]] static string GetGlobalShaderDirectory();
		
		static void LoadShaderType(const string& shaderTypeName, function<void(const string& filePath, const string& relativeNameWithoutExt, ComPtr<ID3DBlob> blob)> loadFunc);
	};
}
