// ワールドビュー射影変換行列宣言
struct VS_OUT
{
	float4 Position :POSITION;
	float4 Color			  :COLORO;
};

//グローバル変数
float4x4 WVP;				//ワールドから射影までの変換行列

float4x4 WIT;				//ワールド行列の逆行列の転置行列

float4   LightDir;			//rライトの方向ベクトル

float4   LightIntensity;	//入射光の強度

float4   Diffuse;			//拡散反射率

float4x4 matWorldViewProj;




// 頂点シェーダ
OU_VS BasicTransform( float4 Position : POSITION, float3 Normal :NORMAL) : POSITION
{
   // ローカル座標にある頂点をワールドビュー射影変換で
   // 一気にスクリーン座標にしてしまう
	VS_OUT Out = (VS_OUT)0;

	Out.Position = mul(Position, WVP);

	float3 WNormal = normalize(mul(Normal(float3x3)WIT));

	//この式はランバートの余弦定理だけだが、通常、ランバート照明モデルといえば環境の頂を含めることが多いようです
	Out.Color = LightIntensity * Diffuse * dot(WNormal, LightDir);

   return mul( LocalPos, matWorldViewProj);
}

// ピクセルシェーダ
float4 NoWorkingPixelShader(VS_OUT In) : COLOR
{
   // 入力されたスクリーンピクセルの色をそのままスルー
   return Diffuse;//RGBA(レッド、グリーン、ブルー、透明度)
}


//コンパイル
technique BasicTec
{
   pass P0
   {
      VertexShader = compile vs_2_0 BasicTransform();
      PixelShader = compile ps_2_0 NoWorkingPixelShader();
   }
}