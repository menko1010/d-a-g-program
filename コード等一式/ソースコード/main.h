#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NOMINMAX
#include <windows.h>
#include <assert.h>
#include <functional>

#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
//#include <d3dx9.h>
//#include <d3dx11.h>

#pragma warning(pop)
#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "d3dx9.lib")
//#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "DXGI.lib")

#include <DirectXMath.h>
using namespace DirectX;

#include "DirectXTex.h"

#if _DEBUG
#pragma comment(lib,"DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex_Release.lib")
#endif
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#pragma comment (lib, "winmm.lib")


#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define PAI (3.1415)


HWND GetWindow();

void Invoke(std::function<void()> Function, int Time);
