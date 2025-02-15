#include "main.h"

void Render() {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		ImGuiMenu::ShowMenu = !ImGuiMenu::ShowMenu;
	}
	
	//Rendering here!
	//SetWindowLongW(Overlay.Hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
	//SetWindowLongW(Overlay.Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

	ImGui::EndFrame();
	DirectX9.pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (DirectX9.pDevice->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		DirectX9.pDevice->EndScene();
	}

	HRESULT result = DirectX9.pDevice->Present(NULL, NULL, NULL, NULL);
	if (result == D3DERR_DEVICELOST && DirectX9.pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		DirectX9.pDevice->Reset(&DirectX9.pParameters);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

void MainLoop() {
	static RECT OldRect;
	ZeroMemory(&DirectX9.Message, sizeof(MSG));

	ImGuiIO& io = ImGui::GetIO();
	while (DirectX9.Message.message != WM_QUIT) {
		if (PeekMessage(&DirectX9.Message, Overlay.Hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&DirectX9.Message);
			DispatchMessage(&DirectX9.Message);
		}

		HWND TempHwnd = GetWindow(Process.Hwnd, GW_HWNDPREV);
		SetWindowPos(Overlay.Hwnd, TempHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		RECT TempRect;
		POINT TempPoint;
		ZeroMemory(&TempRect, sizeof(RECT));
		ZeroMemory(&TempPoint, sizeof(POINT));

		GetClientRect(Process.Hwnd, &TempRect);
		ClientToScreen(Process.Hwnd, &TempPoint);
		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		ImGuiIO& io = ImGui::GetIO();
		if (TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom) {
			OldRect = TempRect;
			Settings::Width = TempRect.right;
			Settings::Height = TempRect.bottom;
			DirectX9.pParameters.BackBufferWidth = Settings::Width;
			DirectX9.pParameters.BackBufferHeight = Settings::Height;
			SetWindowPos(Overlay.Hwnd, (HWND)0, TempPoint.x, TempPoint.y, Settings::Width, Settings::Height, SWP_NOREDRAW);
			DirectX9.pDevice->Reset(&DirectX9.pParameters);
		}

		Render();
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (DirectX9.pDevice != NULL) {
		DirectX9.pDevice->EndScene();
		DirectX9.pDevice->Release();
	}
	if (DirectX9.IDirect3D9 != NULL) {
		DirectX9.IDirect3D9->Release();
	}

	DestroyWindow(Overlay.Hwnd);
	UnregisterClass(Overlay.WindowClass.lpszClassName, Overlay.WindowClass.hInstance);
}


int main()
{
	Overlay.Name = RandomString(10).c_str();
	if (Overlay.Name == NULL) {
		MessageBoxA(0, "Failed to create Overlay.", "Error", MB_ICONERROR);
		Sleep(3000);
		exit(2);
	}

	if (!FindHandle()) {
	   MessageBoxA(0, "Failed to get Driver Handle", "Error", MB_ICONERROR);
	   Sleep(3000);
	   exit(2);
        }

       ProcessAddress = FindProcess(L"Marvel-Win64-Shipping.exe");
       if (!ProcessAddress) {
	   MessageBoxA(0, "Failed to get ProcessAddress", "Error", MB_ICONERROR);
	   Sleep(3000);
	   exit(2);
       }

       BaseAddress = FindBaseImage();
       if (!BaseAddress) {
	   MessageBoxA(0, "Failed to get BaseAddress", "Error", MB_ICONERROR);
	   Sleep(3000);
	   exit(2);
       }

	SetupOverlay();
	DirectXInit();
	while (TRUE) {
		MainLoop();
	}
}
