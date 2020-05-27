// ���[���h�r���[�ˉe�ϊ��s��錾
struct VS_OUT
{
	float4 Position :POSITION;
	float4 Color			  :COLORO;
};

//�O���[�o���ϐ�
float4x4 WVP;				//���[���h����ˉe�܂ł̕ϊ��s��

float4x4 WIT;				//���[���h�s��̋t�s��̓]�u�s��

float4   LightDir;			//r���C�g�̕����x�N�g��

float4   LightIntensity;	//���ˌ��̋��x

float4   Diffuse;			//�g�U���˗�

float4x4 matWorldViewProj;




// ���_�V�F�[�_
OU_VS BasicTransform( float4 Position : POSITION, float3 Normal :NORMAL) : POSITION
{
   // ���[�J�����W�ɂ��钸�_�����[���h�r���[�ˉe�ϊ���
   // ��C�ɃX�N���[�����W�ɂ��Ă��܂�
	VS_OUT Out = (VS_OUT)0;

	Out.Position = mul(Position, WVP);

	float3 WNormal = normalize(mul(Normal(float3x3)WIT));

	//���̎��̓����o�[�g�̗]���藝���������A�ʏ�A�����o�[�g�Ɩ����f���Ƃ����Ί��̒����܂߂邱�Ƃ������悤�ł�
	Out.Color = LightIntensity * Diffuse * dot(WNormal, LightDir);

   return mul( LocalPos, matWorldViewProj);
}

// �s�N�Z���V�F�[�_
float4 NoWorkingPixelShader(VS_OUT In) : COLOR
{
   // ���͂��ꂽ�X�N���[���s�N�Z���̐F�����̂܂܃X���[
   return Diffuse;//RGBA(���b�h�A�O���[���A�u���[�A�����x)
}


//�R���p�C��
technique BasicTec
{
   pass P0
   {
      VertexShader = compile vs_2_0 BasicTransform();
      PixelShader = compile ps_2_0 NoWorkingPixelShader();
   }
}