#pragma once
#include <d3dx9.h>
#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/*directX�f�o�C�X����}�N��*/
#define SAFE_RELEASE(p) do { if(p){ (p)->Release(); (p) = NULL;} } while(0)
