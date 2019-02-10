struct VInput
{
    float4 Position : POSITION;
    float2 UV : TEXCOORD0;
};

struct VOutput
{
    float4 Position : POSITION;
    float2 UV : TEXCOORD0;
};

struct PInput
{
    float2 UV : TEXCOORD0;
};

float4x4 OrthoMatrix;
float4x4 WorldMatrix;
texture SamplingTexture;
sampler2D MainSampler = sampler_state
{
    Texture = SamplingTexture;
};
VOutput mainVertex(VInput Input)
{
    VOutput Output;
    Output.Position = mul(Input.Position, WorldMatrix);
    Output.Position = mul(Output.Position, OrthoMatrix);

    Output.UV = Input.UV;
    return Output;
}
float4 mainPixel(PInput Input) : COLOR
{
//    return float4(1, 1, 0, 1);
    return tex2D(MainSampler, Input.UV);
}

technique Main
{
    pass PASS_0
    {
        VertexShader = compile vs_2_0 mainVertex();
        PixelShader = compile ps_2_0 mainPixel();
    }
}