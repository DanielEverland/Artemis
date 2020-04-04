cbuffer cbPerObject
{
	float4x4 worldViewProj;
};

struct VertexIn
{
	float3 PosL : POSITION;
	float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float4 Color : COLOR;
};

VertexOut VS(VertexIn vertexIn)
{
	VertexOut vertexOut;

	// Transform to homogenous clip space.
	vertexOut.PosH = mul(float4(iPosL, 1.0f), worldViewProj);

	// Just pass vertex color into pixel shader
	vertexOut.Color = vertexIn.Color;

	return vertexOut;
}

float4 PS(VertexOut pixelIn) : SV_Target
{
	return pixelIn.Color;
}