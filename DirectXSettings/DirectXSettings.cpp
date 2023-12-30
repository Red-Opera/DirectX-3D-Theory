#include "stdafx.h"
#include "DirectXSettings.h"

HRESULT CreateDevice(UINT* createDeviceFlags, D3D_FEATURE_LEVEL* featureLevel, D3D_DRIVER_TYPE driverType, ID3D11Device** device, ID3D11DeviceContext** deviceContext)
{
#if defined (DEBUG) || defined(_DEBUG)
    *createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // Device�� ������
    HRESULT hr = D3D11CreateDevice(
        0,
        driverType,         // GPU �ϵ���� �������� ������ (D3D_DRIVER_TYPE_HARDWARE)
        0,
        *createDeviceFlags,
        0, 0,               // �⺻ ��� ���� �迭 (D3D_FEATURE_LEVEL_11_0�θ� ���)
        D3D11_SDK_VERSION,
        device,
        featureLevel,
        deviceContext
    );

    // Device�� �����Ǿ����� Ȯ����
    if (FAILED(hr))
    {
        MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
        return S_FALSE;
    }

    // �׷��� �ϵ��� D3D_FEATRUE_LEVEL_11_0�� �����ϴ��� Ȯ��
    if (*featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        MessageBox(0, L"DirectX 3D Feature Level 11 UnSupported.", 0, 0);
        return S_FALSE;
    }

    return S_OK;
}

void CheckMSAAQuality(ID3D11Device* device, UINT* msaaQuality)
{
    HR(device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, msaaQuality));  // MSAA�� �����Ǵ��� Ȯ��
    assert(*msaaQuality > 0);                                                                // ������ ��� 0���� ū ���� ��ȯ�Ǿ� ������
}

void SwapChainSettings(DX3DApp* dx3dApp, DXGI_MODE_DESC* backBufferModeDESC, DXGI_SAMPLE_DESC* massDESC, DXGI_SWAP_CHAIN_DESC* swapChainDESC)
{
    // �ĸ� ���� ����
    backBufferModeDESC->Width = dx3dApp->GetClientWidth();                          // �ĸ� ���� �ʺ�
    backBufferModeDESC->Height = dx3dApp->GetClientHeight();                        // �ĸ� ���� ����

    backBufferModeDESC->RefreshRate.Denominator = 1;                                 // â �ֻ��� �и�
    backBufferModeDESC->RefreshRate.Numerator = 60;                                  // â �ֻ��� ����

    backBufferModeDESC->Format = DXGI_FORMAT_R8G8B8A8_UNORM;                         // �ĸ� ���� �ȼ� ���� (���� 8��Ʈ�� �ϴ°� �����ϰ� �� ������ �ǹ̰� ����)
    backBufferModeDESC->ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;     // ȭ�� ��� ����
    backBufferModeDESC->Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                     // ȭ�� ��� ũ�� ���� ����

    // MSAA�� ����� ���
    if (dx3dApp->GetUsageMSAA())
    {
        massDESC->Count = 4;                               // 4��� Ȯ�� ��
        massDESC->Quality = dx3dApp->GetMSAAQuality() - 1; // CheckMultisampleQualityLevels�� ���ؼ� ���� ��� ��
    }

    // MSAA�� ������� ���� ���
    else
    {
        massDESC->Count = 1;
        massDESC->Quality = 0;
    }

    // ���� ü�� ����
    swapChainDESC->SampleDesc = *massDESC;
    swapChainDESC->BufferDesc = *backBufferModeDESC;
    swapChainDESC->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // �ĸ� ���ۿ� �����ϱ� ���� ���� ����
    swapChainDESC->BufferCount = 1;                                  // ���� ���۸��� �ϱ� ���� 1��
    swapChainDESC->OutputWindow = dx3dApp->MainWnd();                // ����� â ����
    swapChainDESC->Windowed = true;                                  // â ��� ���� O
    swapChainDESC->SwapEffect = DXGI_SWAP_EFFECT_DISCARD;            // ���ο� �����ӿ� �׸�
    swapChainDESC->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // ȭ���� �ٲ� �� ������ �ػ󵵷� ����
}

void CreateSwapChain(ID3D11Device* device, DXGI_SWAP_CHAIN_DESC swapChainDESC, IDXGISwapChain** swapChain)
{
    IDXGIDevice* dxgiDevice = nullptr;
    HR(device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

    IDXGIAdapter* dxgiAdapter = nullptr;
    HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

    // CreateSwapChain�� ����ϱ� ���� ���� ����
    IDXGIFactory* dxgiFactory = nullptr;
    HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

    // swapChain ����
    HR(dxgiFactory->CreateSwapChain(device, &swapChainDESC, swapChain));

    ReleaseCOM(dxgiDevice);
    ReleaseCOM(dxgiAdapter);
    ReleaseCOM(dxgiFactory);
}

void CreateRenderTargetView(IDXGISwapChain* swapChain, ID3D11Device* device, ID3D11RenderTargetView** renderTargetView)
{
    ID3D11Texture2D* backBuffer;
    
    // ��ȯ �罽�� ���۸� ������ (0��° �ĸ� ���۸� ID3D11Texture2D �������� 3��° �μ��� ��ȯ)
    HR(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));

    // �ĸ� ���۷� RenderTargetView�� ������
    device->CreateRenderTargetView(backBuffer, 0, renderTargetView);
    
    ReleaseCOM(backBuffer);
}

void CreateDepthStencilView(DX3DApp* dx3dApp, ID3D11Texture2D** depthStencilBuffer, ID3D11DepthStencilView** depthStencilView)
{
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = dx3dApp->GetClientWidth();
    depthStencilDesc.Height = dx3dApp->GetClientHeight();
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;                             // ���� �� ���ٽ� ���۴� �Ѱ��� 2���� �迭�� ���
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    if (dx3dApp->GetUsageMSAA())
    {
        depthStencilDesc.SampleDesc.Count = 4;
        depthStencilDesc.SampleDesc.Quality = dx3dApp->GetMSAAQuality() - 1;
    }

    else
    {
        depthStencilDesc.SampleDesc.Count = 1;
        depthStencilDesc.SampleDesc.Quality = 0;
    }

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    HR(dx3dApp->GetDevice()->CreateTexture2D(&depthStencilDesc, 0, depthStencilBuffer));          // 2��° �Ű����� : 2D �ؽ�ó�� �⺻������ �Էµ� �� (DepthStenil�� �⺻������ DirectX�� ä�� ��)
    HR(dx3dApp->GetDevice()->CreateDepthStencilView(*depthStencilBuffer, 0, depthStencilView));   // 2��° �Ű����� : View DESC ��
}

void CreateViewPort(DX3DApp* dx3dApp, ID3D11DeviceContext* deviceContext, D3D11_VIEWPORT* viewPort)
{
    viewPort->TopLeftX = 0.0f;
    viewPort->TopLeftY = 0.0f;
    viewPort->Width = static_cast<float> (dx3dApp->GetClientWidth());
    viewPort->Height = static_cast<float> (dx3dApp->GetClientHeight());
    viewPort->MinDepth = 0.0f;
    viewPort->MaxDepth = 1.0f;

    // ������ ������������ RS �ܰ迡 ViewPort ���� (1��° �Ű����� : �� ��Ʈ�� ����(�� ��Ʈ 2�� �̻��� ��� ȭ���� ���� �� ����))
    deviceContext->RSSetViewports(1, viewPort);
}
