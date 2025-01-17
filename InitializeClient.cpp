#include <iostream>
#include <windows.h>

typedef int(__cdecl* InitializeClientFunc)();
typedef int(__cdecl* ConnectToServerFunc)(const char*, int);
typedef int(__cdecl* SendDataFunc)(const char*);
typedef int(__cdecl* DisconnectFromServerFunc)();
typedef void(__cdecl* CleanupClientFunc)();

int main() {
    HMODULE hModule = LoadLibrary(L"Mods/HogReborns/HogReborns.dll");
    if (!hModule) {
        std::cerr << "Échec du chargement de la DLL" << std::endl;
        return 1;
    }

    InitializeClientFunc InitializeClient = (InitializeClientFunc)GetProcAddress(hModule, "InitializeClient");
    if (!InitializeClient) {
        std::cerr << "Échec de l'obtention de l'adresse de InitializeClient" << std::endl;
        return 1;
    }

    int result = InitializeClient();
    std::cout << "Résultat de InitializeClient: " << result << std::endl;

    FreeLibrary(hModule);
    return 0;
}
