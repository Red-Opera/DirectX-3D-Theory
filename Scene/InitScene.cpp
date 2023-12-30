#include "stdafx.h"
#include <xnamath.h>

class InitScene : public DX3DApp
{
public:
	InitScene(HINSTANCE hInstance);
	~InitScene();

	bool Init();
	void OnResize();
	
	// DX3DApp��(��) ���� ��ӵ�
	void UpdateScene(float dt) override;
	void DrawScene() override;
};

// ���α׷� �� ���� ���� ����Ǵ� �Լ�
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// ����� ������ ��� ������� �޸� ���� ����� �ߴ�.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	InitScene initScene(hInstance);

	if (!initScene.Init())
		return 0;

	return initScene.Run();
}

InitScene::InitScene(HINSTANCE hInstance) : DX3DApp(hInstance)
{
}

InitScene::~InitScene()
{
}

bool InitScene::Init()
{
	if (!DX3DApp::Init())
		return false;

	return true;
}

void InitScene::OnResize()
{
	DX3DApp::OnResize();
}

void InitScene::UpdateScene(float dt)
{
}

void InitScene::DrawScene()
{
	assert(deviceContext);
	assert(swapChain);

	// �ĸ� ���۸� �ʱ�ȭ��
	deviceContext->ClearRenderTargetView(renderTargetView, reinterpret_cast<const float*>(&Colors::Blue));

	// ���� ���۸� 1.0f, ���ٽ� ���۸� 0���� �����.
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// �ĸ� ���۸� ȭ�鿡 ǥ���Ѵ�.
	HR(swapChain->Present(0, 0));
}
