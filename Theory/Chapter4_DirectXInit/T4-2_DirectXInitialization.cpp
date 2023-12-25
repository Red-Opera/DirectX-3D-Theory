#include "stdafx.h"

// ========================================================
//	DirectX 3D�� �ʱ�ȭ
// ========================================================

/*
	1. D3D11CreateDevice �Լ��� �̿��Ͽ� ID3D11Device �������̽��� ID3D11DeviceContext �������̽��� �����Ѵ�.
	2. ID3D11Device::CheckMultisampleQualityLevels�� �̿��Ͽ� 4X MASS ǰ�� ���� ���θ� Ȯ���Ѵ�.
	3. DXGI_SWAP_CHAIN_DESE ����ü�� �ۼ��Ͽ� ��ȯ �罽�� Ư���� �����Ѵ�.
	4. IDXGIFactory �������̽��� �̿��Ͽ� IDXGISwapChain �ν��Ͻ��� �����Ѵ�.
	5. ��ȯ �罽�� �ִ� �ĸ� ������ ���� ��� �並 �����Ѵ�.
	6. ���̨����ٽ� ���ۿ� ���ۿ� ����Ǵ� ���̨����ٽ� �並 �����Ѵ�.
	7. ���� ��� ��� ���̨����ٽ� �並 DirectX 3D�� ����� �� �ֵ��� ������ ������������ ��� ���ձ� �ܰ迡 ���´�.
	8. ����Ʈ�� �����Ѵ�.
*/

// ========================================================
//	��ġ�� ��ġ ���� ����
// ========================================================

/*
	- DirectX 3D�� �����ϱ� ���ؼ� ID3D11Device�� ID3D11DeviceContext�� �����ؾ� �Ѵ�.

	ID3D11Device�� ID3D11DeviceContext
		1. ID3D11Device : DirectX 3D 11 ��ġ
			- �ϵ���� ��� ���� Ȯ�� (Feature Level Check)
			- �ڿ��� �Ҵ��ϴµ� ���

			- 
		2. ID3D11DeviceContext : DirectX 3D 11 ��ġ�� ����
			- ������ ����� ��µǴ� ����� ����
			- GPU�� ������ ������ ����� ����

		- �׷��� ��ġ �ϵ��� �����ϱ� ���� �������̽�
		- �ϵ����� GPU �޸� �ڿ� �Ҵ�, �ĸ� ���� �����, ���� ���������� �ܰ� ����, ���ϱ��� �׸��� ���� ����

	D3D11CreateDevice �Ű����� ����
		- DriverType�� ������ �� �ִ� ��
			1. D3D_DRIVER_TYPE_REFERENCE : Reference device�� �����Ͽ� ��Ȯ���� ��ǥ�� �ϴ� Ÿ������ ������̳� Ư���� ��Ȳ�� �� ��� (�ϵ��� �������� �ʴ� ��� ����, ������ ���� ����)
			2. D3D_DRIVER_TYPE_SOFTWARE : GPU�� ������� �ʰ� ����Ʈ���� ������(WARP(GPU�� ������� �ʰ� CPU ���) ������)�� �䳻���� Ÿ������ GPU ������ ����� ��Ȳ�� �� ���
			3. D3D_DRIVER_TYPE_WARP : D3D_DRIVER_TYPE_SOFTWARE���� �������ս��� �����ִ� WARP �����⸦ ����ϱ� ���� Ÿ��

		- Flags�� ������ �� �ִ� �÷��� ��
			1. D3D11_CREATE_DEVICE_SINGLETHREADED : ��Ƽ �����带 ������� �ʴ� ������ ���� �� ����ϸ� ���� ���� ��� (ID3D11Device:CreateDeferredContext�� ȣ���ϸ� ����)
			2. D3D11_CREATE_DEVICE_DEBUG : ��Ÿ�� ����� �� ����̽� ���� �� ���� ������ Ȯ���ϴµ� ������ �� (VC++ ��� â�� ����� �޽����� ǥ��)

*/

namespace Sample
{
	// D3D11CreateDevice ����
	HRESULT D3D11CreateDevice(
		IDXGIAdapter* pAdapter,						// ���÷��� �����(�׷��� ī�� ����, ȭ�� ��� ��ȯ ����)�� ������ (0 �Ǵ� NULL�� ������ ��� �⺻ ����͸� ���)
		D3D_DRIVER_TYPE DriverType,					// � Ÿ���� �׷��� ����̹��� ����Ұ����� ����
		HMODULE Software,							// ����Ʈ���� �����⸦ ����� �� �����ϴ� �Ű�����
		UINT Flags,									// Ư�� ������ �߰��� �� ����ϴ� �Ű�����
		CONST D3D_FEATURE_LEVEL* pFeatureLevels,	// D3D_FEATURE_LEVEL ���� ���ҵ��� �迭�� ���� (���� ������� �����ϴ� ����, NULL ������ �ְ� ��� �������� ����)
		UINT FeatureLevels,							// D3D_FEATURE_LEVEL ���� ���ҵ��� �迭�� ����
		UINT SDKVersion,							// D3D11_SDK_VERSION ����
		ID3D11Device** ppDevice,					// D3D11CreateDevice�� ������ Device�� ��ȯ��
		D3D_FEATURE_LEVEL* pFeatureLevel,			// pFeatureLevels �迭���� �� ó���� �����Ǵ� ����
		ID3D11DeviceContext** pImmdiateContext		// D3D11CreateDevice�� ������ DeviceContext�� ��ȯ��
	);
}

// ========================================================
//	4X MSAA ǰ�� ���� ���� ����
// ========================================================

/*
	- ��ġ�� ������ �� �̷������ ����
	- ID3D11Device�� ���� ��ü�� �ִ� CheckMultisampleQualityLevels�� �̿��Ѵ�.
	- CheckMultisampleQualityLevels�� ���������� �Էµ� UINT ���� ��ȯ�� �Ǹ� 0���� ū�� Ȯ���Ѵ�.
	- ��ȯ�� UINT ���� 0���� Ŭ��� 4X MSAA�� ������ �Ѵٴ� ���̴�.
*/

// ========================================================
//	��ȯ �罽�� ����
// ========================================================

/*
	- ǰ�� ���� ���� ���� �� �ۼ���
	- DXGI_SWAP_CHAIN_DESC ����ü�� �ۼ��ؾ� ��

	DXGI_SWAP_CHAIN_DESC�� �ɹ� ����
		- SwapEffect�� ������ �� �ִ� ��
			1. DXGI_SWAP_EFFECT_DISCARD : ���� �������� ������ �����ϰ� ���ο� �������� �׸� (���� ȿ������ ���, ����)
			2. DXGI_SWAP_EFFECT_SEQUENTIAL : ���� �������� ������ ������ ä�� ���ο� ���������� ��ü

		- Flags�� ������ �� �ִ� ��
			1. DXGI_SWAP_CHAIN_FLAG_NONPREROTATED : ���� ������ ������ ȭ������ ���� �� �̹��� ȸ���� ��
			2. DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH : ��üȭ�鿡�� â��� �� ����� â�� ���� �����

	DXGI_MODE_DESC�� �ɹ� ����
		- ScanlineOrdering : ȭ���� �׷����� ����
			1. DXGI_MODE_SCALING_UNSPECIFIED : ȭ���� �׷����� ������ �������� ���� (�ϵ��� �ڵ����� ������ ����)
			2. DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE : ȭ���� ������ �Ʒ��� ���������� �����
			3. DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST : ���ͷ��̽� ��ĵ (Ȧ����° �� ���� �����, ¦����° �� ���)
			4. DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST : ���ͷ��̽� ��ĵ (¦����° �� ���� �����, Ȧ����° �� ���)

		- Scaling : ȭ�鿡 ����� �� ����� �̹��� ũ��
			1. DXGI_MODE_SCALING_UNSPECIFIED : ũ�⸦ �����ϰų� ��ġ�� �ٲ��� ���� (�ϵ��� �ڵ����� ������ ����)
			2. DXGI_MODE_SCALING_CENTERED : ũ�⸦ �������� �ʰ� ȭ�� �߾ӿ� ��ġ�ϵ��� ����
			3. DXGI_MODE_SCALING_STRETCHED : ȭ���� ���÷����� ȭ�鿡 ������
			4. DXGI_MODE_SCALING_ASPECT_RATIO_STRETCHED : ��� ������� �̹����� ������ ���� ���÷��� ũ�⸸ŭ �ִ�� �ø�
*/

namespace Sample
{
	// DXGI_SWAP_CHAIN_DESC ����ü
	typedef struct DXGI_SWAP_CHAIN_DESC
	{
		DXGI_MODE_DESC BufferDesc;					// ������ ��ü���� �Ӽ��� ������ ����ü
		DXGI_SAMPLE_DESC SampleDesc;				// ����ǥ��ȭ�� ���� ǥ���� ������ ǰ�� ����
		DXGI_USAGE BufferUsage;						// ������ ��� �뵵
		UINT BufferCount;							// �ĸ� ������ ����
		HWND OutputWindow;							// ������ ����� ����� â�� �ڵ�
		BOOL Windowed;								// â ��� ����
		DXGI_SWAP_EFFECT SwapEffect;				// �ĸ� ���� ��ȯ�� ȿ��
		UINT Flags;									// �߰����� �÷���
	} DXGI_SWAP_CHAIN_DESC;

	// DXGI_MODE_DESC
	typedef struct DXGI_MODE_DESC
	{
		UINT Width;									// ���ϴ� �ĸ� ���� �ʺ�
		UINT Height;								// ���ϴ� �ĸ� ���� ����
		DXGI_RATIONAL RefreshRate;					// ���÷��� ��� ������
		DXGI_FORMAT Format;							// �ĸ� ���� �ȼ� ����
		DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;	// ���÷��� ��ĵ���� ���
		DXGI_MODE_SCALING Scaling;					// ���÷��� ��ʸ��
	} DXGI_MODE_DESC;
}

// ========================================================
//	��ȯ �罽�� ����
// ========================================================

/*
	- ��ȯ �罽�� ���������� ������ �Ѵ�.
	- IDXGIFactory�� IDXGIFactory::CreateSwapChain�� �̿��Ͽ� ��ȯ �罽(IDXGISwapChain)�� �����.

	CreateSwapChain �̿��
		1. CreateSwapChain�� ����ϱ� ���� IDXGIFactory�� CreateDXGIFactory�� �̿��Ͽ� �ν��Ͻ��� �����.
		2. �׳� ����ϸ� ������ �߻��ϱ� ������ Device ������ ���� IDXGIFactory�� ����ؾ� �Ѵ�.
		3. �׷��� ������ COM ���� ������ ���ľ� �Ѵ�.
*/

namespace Sample
{
	class IDXGIFactory
	{
		HRESULT CreateSwapChain(
			IUnknown* pDevice,				// ID3D11Device�� ����Ű�� ������
			DXGI_SWAP_CHAIN_DESC* pDesc,	// ��ȯ �罽 ����
			IDXGISwapChain** ppSwapChain	// ������ ���� ���� ��ȯ�� ����
		);
	};
}

// ========================================================
//	���� ��� ���� ����
// ========================================================

/*
	- �ĸ� ���۸� ���������ο� �����ϱ� ���ؼ��� �ĸ� ���۸� ���� �������� ���ϱ� ������ ���� Ÿ�� �並 �����Ѵ�.
	- ���� Ÿ�� ��� ��� ���ձ�(Output Merger) �ܰ迡 ����� �ĸ� ���ۿ� �׸� �� �ִ�.
*/

// ========================================================
//	���� �� ���ٽ� ���ۿ� �� ����
// ========================================================

/*
	- ���� ���۴� �ȼ����� ���� ������ ��� 2���� �ؽ�ó
	- D3D11_TEXTURE_DESC�� ��� ������ ä�� �� ID3D11Device�� CreateTexutre2D �޼ҵ带 ȣ���Ͽ� �����Ѵ�.

	D3D11_TEXTURE2D_DESC ��� ���� ����
		- Usage�� ���� ������ ��
			1. D3D11_USAGE_DEFAULT : �ڿ��� GPU�� �а� �� �� ���� (CPU�� �а� �� ���� ����)
			2. D3D11_USAGE_IMMUTABLE : �ڿ��� GPU�� �б⸸ ������ (CPU�� �а� �� ���� ����, GPU�� �� �� ����)
			3. D3D11_USAGE_DYNAMIC : �ڿ��� GPU�� �а� CPU�� �� �� ��� (�ڿ��� ����ϰ� ������ �� ���, ���ɿ� ���� ����)
			4. D3D11_USAGE_STAGING : CPU �Ǵ� GPU���� �б� ���� ��� ���� (CPU �ڿ��� GPU�� ������ �� ���, ���� �������� ���ɿ� ���� ����)

		- BindFlags�� ������ �� �ִ� ��
			1. D3D11_BIND_RENDER_TARGET : �ؽ�ó�� ���� ������� ������ ���ο� ���
			2. D3D11_BIND_SHADER_RESOURCE : �ؽ�ó�� ���̴� �ڿ����� ������ ���ο� ���
			3. D3D11_BIND_DEPTH_STENCIL : �ؽ�ó�� ���� �� ���ٽ� ���� �ڿ����� ������ ���ο� ���

		- CPUAccessFlags : CPU�� �ڿ��� �����ϴ� ���
			1. D3D11_CPU_ACCESS_WRITE : CPU�� �ڿ��� �ڷḦ ���
			2. D3D11_CPU_ACCESS_READ : CPU�� �ڿ��� �б� ������ ����
*/

namespace Sample
{
	typedef struct D3D11_TEXTURE2D_DESC
	{
		UINT Width;						// ���� �� ���ٽ� ������ �ʺ�
		UINT Height;					// ���� �� ���ٽ� ������ ����
		UINT MipLevels;					// �Ӹ� ������ ����
		UINT ArraySize;					// �ؽ�ó �迭�� ���� (���� �� ���ٽ� ���۴� �Ѱ��� �ؽ�ó�� ����)
		DXGI_FORMAT Format;				// �ؼ��� �������� DXGI_FORMAT �������� ���
		DXGI_SAMPLE_DESC SampleDesc;	// ���� ǥ�� ������ ǰ�� ������ ������
		D3D11_USAGE Usage;				// �ؽ�ó�� �뵵 (�ؽ�ó�� � �뵵�� ������ ������ ���ο� ����� ������ ����)
		UINT CPUAccessFlags;			// CPU�� �ڿ��� �����ϴ� ���
		UINT MiscFlags;					// ��Ÿ �÷���
	} D3D11_TEXTURE2D_DESC;
}

// ========================================================
//	����� ��� ���ձ� �ܰ迡 ����
// ========================================================

/*
	- �ĸ� ���ۿ� ���� �� ���ٽ� ���۸� ������ ������������ ��� ���ձ� �ܰ迡 ����� �Ѵ�.
	- DeviceContext�� �ִ� OMSetRenderTargets �޼ҵ带 �̿��Ͽ� ���´�.
*/

// ========================================================
//	����Ʈ ����
// ========================================================

/*
	- ���ϴ� 3���� ����� �ĸ� ������ �Ϻθ� ���簢�� �������� ����
	- D3D11_VIEWPORT ����ü�� �ۼ��ؾ� �Ѵ�.
	- VIEWPORT�� ���� ���۴� Ư�� ȿ���� ������� ���� �� �ּҴ� 0, �ִ�� 1�� �����Ѵ�.

	- D3D11_VIEWPORT�� �ϼ� �� I3D11DeviceContext�� RSSetViewports�� �̿��Ͽ� ����Ʈ�� �����Ѵ�.
*/

namespace Sample
{
	typedef struct D3D11_VIEWPORT
	{
		FLOAT TopLeftX;		// �� ��Ʈ ���� �� X ��ǥ
		FLOAT TopLeftY;		// �� ��Ʈ ���� �� Y ��ǥ
		FLOAT Width;		// ���� ũ��
		FLOAT Height;		// ���� ũ��
		FLOAT MinDepth;		// �ּ� ���� ����
		FLOAT MaxDepth;		// �ִ� ���� ����
	} D3D11_VIEWPORT;
}