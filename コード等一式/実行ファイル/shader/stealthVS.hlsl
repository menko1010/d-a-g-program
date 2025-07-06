#include"common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.Position = mul(In.Position, wvp);

    float2 tex = Out.Position.xy;
    tex.x /= Out.Position.w;
    tex.y /= Out.Position.w;
    
    tex.x = (tex.x * 0.002f) + 0.5f + 0.05f;//0.002‚Í“K“–‚È‹üÜ—¦‚±‚ê‚ª–³‚¢‚ÆŠ®‘S‚É‚«‚¦‚ÄŒ©‚¦‚È‚­‚È‚éB
    tex.y = (tex.y * (-0.5f)) + 0.5f + 0.05f;
    tex = saturate(tex);
    
    Out.TexCoord = tex;
}