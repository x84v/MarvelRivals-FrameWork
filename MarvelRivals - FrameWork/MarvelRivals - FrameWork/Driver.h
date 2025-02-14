

uintptr_t BaseAddress;
uintptr_t ProcessAddress;
HANDLE DriverHandle;

#define Write_Code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x20, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define Read_Code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x21, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define Base_Code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x22, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
struct Request {
	uintptr_t base_id;
	uintptr_t process_id;
	UINT_PTR address;
	void* output;
	void* input;
	ULONGLONG size;
};

bool FindHandle() {
	DriverHandle = CreateFileW(L"\\\\.\\Interptr", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (!DriverHandle || (DriverHandle == INVALID_HANDLE_VALUE))
		return false;

	return true;
}

uintptr_t FindBaseImage() {
	Request arguments = { 0 };
	arguments.process_id = ProcessAddress;
	if (!DeviceIoControl(DriverHandle, Base_Code, &arguments, sizeof(arguments),
		&arguments, sizeof(arguments), NULL, NULL)) {
		return 0;
	}
	return arguments.base_id;
}

void ReadPhysical(PVOID address, PVOID buffer, DWORD size) {
	Request arguments = { 0 };
	arguments.address = (ULONGLONG)address;
	arguments.output = buffer;
	arguments.size = size;
	arguments.process_id = ProcessAddress;
	DeviceIoControl(DriverHandle, Read_Code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
}

void WritePhysical(PVOID address, PVOID buffer, DWORD size) {
	Request arguments = { 0 };
	arguments.address = (ULONGLONG)address;
	arguments.input = buffer;
	arguments.size = size;
	arguments.process_id = ProcessAddress;
	DeviceIoControl(DriverHandle, Write_Code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
}

template <typename T>
T Read(uint64_t address) {
	T buffer{ };
	ReadPhysical((PVOID)address, &buffer, sizeof(T));
	return buffer;
}

template <typename T>
T Write(uint64_t address, T buffer) {

	WritePhysical((PVOID)address, &buffer, sizeof(T));
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
