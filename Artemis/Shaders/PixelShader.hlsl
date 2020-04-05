cbuffer PerObject
{
	float4x4 WorldViewProj;
};

struct PixelIn
{
	float3 Position : POSITION;
	float4 Color : COLOR;
};

float4 main(PixelIn pixelIn) : SV_TARGET
{
	return pixelIn.Color;
}