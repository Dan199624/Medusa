#include "pch.h"
#include "log.h"
#include "patterns.h"
#include "hooks.h"
#include "menu.h"
#include "functions.h"

DWORD WINAPI cleanup(LPVOID lpvParameter) {
    medusa::g_functions.cleanup();
    medusa::g_menu.cleanup();
    medusa::g_hooks.cleanup();
    medusa::g_logger.log("Cleanup", "Medusa Unloaded Sucessfully");
    medusa::g_logger.cleanup();

    g_running = false;
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpvParameter), EXIT_SUCCESS);
}

DWORD WINAPI init(LPVOID lpvParameter) {  
    medusa::g_logger.init();   
    medusa::g_patterns.scan();
    medusa::g_hooks.init();
    medusa::g_menu.init();
    medusa::g_functions.init();

    g_running = true;
    medusa::g_logger.log("Init", "Medusa Loaded Sucessfully");

    while (g_running) {
        if (GetAsyncKeyState(VK_END)) {
            g_running = false;
        }
        std::this_thread::sleep_for(1ms);
    }   
    cleanup(lpvParameter);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        if (HANDLE hThread = CreateThread(nullptr, NULL, init, hModule, NULL, nullptr)) {
            CloseHandle(hThread);
        }
    }
    return TRUE;
}

