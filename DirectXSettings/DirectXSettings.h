#pragma once
#include "stdafx.h"

// Device ���� (��ȯ �� : createDeviceFlags, featureLevel, device, deviceImmediateContext)
HRESULT CreateDevice(UINT* createDeviceFlags, D3D_FEATURE_LEVEL* featureLevel, ID3D11Device** device, ID3D11DeviceContext** deviceContext);

// 4X MSAA ǰ�� ���� ���� ���� (��ȯ �� : massQuality)
void GetMSAAQuality(ID3D11Device* device, UINT* msaaQuality);

// ��ȯ �罽�� ���� (��ȯ �� : backBufferModeDESC, massDESC, swapChainDESC)
void SwapChainSettings(HWND hWnd, UINT msaaQuality, DXGI_MODE_DESC* backBufferModeDESC, DXGI_SAMPLE_DESC* massDESC, DXGI_SWAP_CHAIN_DESC* swapChainDESC);

// ��ȯ �罽�� ���� (��ȯ �� : swapChain)
void CreateSwapChain(ID3D11Device* device, DXGI_SWAP_CHAIN_DESC swapChainDESC, IDXGISwapChain** swapChain);

// ���� Ÿ�� �� ���� (��ȯ �� : renderTargetView)
void CreateRenderTargetView(IDXGISwapChain* swapChain, ID3D11Device* device, ID3D11RenderTargetView** renderTargetView);

// ���� �� ���ٽ� ���ۿ� �� ���� (��ȯ �� : depthStencilBuffer, depthStencilView)
void CreateDepthStencilView(ID3D11Device* device, UINT msaaQuality, ID3D11Texture2D** depthStencilBuffer, ID3D11DepthStencilView** depthStencilView);

// ����Ʈ ���� (��ȯ �� : viewPort)
void CreateViewPort(ID3D11DeviceContext* deviceContext, D3D11_VIEWPORT* viewPort);