
//Basic VS includes
#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <math.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <Uxtheme.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "d3d9.lib")

//ImGui Interface (Includes)
#include "ImGui\imgui_impl_dx9.h"
#include "ImGui\imgui_impl_win32.h"
#include "ImGui\imgui_internal.h"

//Include our Structure
#include "Struct.h"

namespace Settings {
	float Width = GetSystemMetrics(SM_CXSCREEN);
	float Height = GetSystemMetrics(SM_CYSCREEN);
}

//Generate Randomized strings
std::string RandomString(int length) {
	const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	std::string randomString;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i < length; ++i) {
		int randomIndex = std::rand() % characters.length();
		randomString += characters[randomIndex];
	}
	return randomString;
}

//ImGui Interface (Main Setup)
#include "ImGui Setup.h"