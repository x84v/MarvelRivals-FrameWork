
uintptr_t ProcessAddress;
uintptr_t BaseAddress;
struct _Communication
{
	BOOLEAN RequestBase;
	BOOLEAN ReadMemory;
	uintptr_t BaseAddress;
	ULONG ProcessID;
	UINT_PTR Address;
	void* Output;
	ULONGLONG Size;
};


typedef __int64(__fastcall* SysCallWin32)(void*);
SysCallWin32 NtRIMObserve = nullptr;
bool IsConnected()
{
	if (!NtRIMObserve)
	{
		const HMODULE win32u = GetModuleHandleA("win32u.dll");
		if (!win32u)
			return false;

		NtRIMObserve = reinterpret_cast<SysCallWin32>(GetProcAddress(win32u, "NtRIMObserveNextInput"));
	}
	return NtRIMObserve;
}

ULONG64 GetBaseAddress()
{
	_Communication W = { 0 };
	W.RequestBase = TRUE;
	W.ProcessID = ProcessAddress;
	NtRIMObserve(&W);
	return W.BaseAddress;
}

void ReadPhysical(PVOID address, PVOID buffer, DWORD size) {
	_Communication W = { 0 };
	W.ReadMemory = TRUE;
	W.ProcessID = ProcessAddress;
	W.Size = size;
	W.Address = (UINT_PTR)address;
	W.Output = buffer;
	NtRIMObserve(&W);
}

template <typename T>
T Read(uint64_t address) {
	T buffer{ };
	ReadPhysical((PVOID)address, &buffer, sizeof(T));
	return buffer;
}


INT32 FindProcess(const std::wstring& process_name) {
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) {
		do {
			if (!lstrcmpiW(pt.szExeFile, process_name.c_str())) {
				CloseHandle(hsnap);
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap);
	return 0;
}