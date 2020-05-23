cbuffer PerObject
{
	float4x4 WorldViewProj;
};

struct VertexIn
{
	float3 PosLocal : POSITION;
	float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosHomogenous : SV_POSITION;
	float4 Color : COLOR;
};

VertexOut main(VertexIn vertexIn)
{
	VertexOut vertexOut;

	// Transform to homogeneous clip space.
	//vertexOut.PosHomogenous = mul(float4(vertexIn.PosLocal, 1.0f), WorldViewProj);
	vertexOut.PosHomogenous = float4(vertexIn.PosLocal, 1.0f);

	// Just pass vertex color into the pixel shader.
	vertexOut.Color = vertexIn.Color;

	return vertexOut;
}