#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <thread>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <minwindef.h>
#include <vadefs.h>
#include <bitset>
#include <shlobj.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <stack>

using namespace std::chrono_literals;

inline bool g_running;

#endif 
