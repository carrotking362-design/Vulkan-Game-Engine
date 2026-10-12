#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <future>

#include "../engine/debug.hpp"
#include "pipe_data_processing.hpp"

#define PIPE_NAME L"\\\\.\\pipe\\EasyEditor0"

class pipe{
private:
    static bool readExact(HANDLE hPipe, void* buffer, DWORD bytesToRead){
        DWORD totalRead = 0;
        while(totalRead < bytesToRead){
            DWORD read = 0;
            if(!ReadFile(hPipe, static_cast<char*>(buffer) + totalRead, bytesToRead - totalRead, &read, nullptr) || read == 0){
                return false;
            }
            totalRead += read;
        }
        return true;
    }

    static bool writeExact(HANDLE hPipe, const void* buffer, DWORD bytesToWrite){
        DWORD totalWritten = 0;
        while (totalWritten < bytesToWrite) {
            DWORD written = 0;
            if (!WriteFile(hPipe, static_cast<const char*>(buffer) + totalWritten, bytesToWrite - totalWritten, &written, nullptr)) {
                return false;
            }
            totalWritten += written;
        }
        return true;
    }


    static inline std::future<void> asyncMethod;
public:
    static void asyncStart(){
        asyncMethod = std::async(std::launch::async, &pipe::start);
    }

    static void start(){
        HANDLE hPipe = INVALID_HANDLE_VALUE;
        
        debug::log("connecting to pipe..");
    
        while (true) {
            hPipe = CreateFileW(PIPE_NAME, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
            if (hPipe != INVALID_HANDLE_VALUE) break;

            DWORD err = GetLastError();
            if (err == ERROR_PIPE_BUSY) {
                WaitNamedPipeW(PIPE_NAME, 2000);   // pipe exists but its one instance is taken
                debug::warn("pipe exists. but instance is already taken?.");
            } else if (err == ERROR_FILE_NOT_FOUND) {
                Sleep(250);                        // server not up yet
                debug::warn("server not found..");
            } else {
                debug::error("failed to connect: " + std::to_string(err));
                return;
            }
        }

        debug::log("connected to pipe!");

        while(true){
            uint8_t header = 0;
            uint8_t command = 0;
            uint32_t args_length = 0;

            if (!readExact(hPipe, &header, 1)) break;
            if (!readExact(hPipe, &command, 1)) break;
            if (!readExact(hPipe, &args_length, sizeof(args_length))) break;

            std::vector<uint8_t> vec_args(args_length);
            if (args_length > 0) {
                if (!readExact(hPipe, vec_args.data(), args_length)) break;
            }

            std::vector<uint8_t> vec_out = to_ui::processCommand(header, command, vec_args);

            int32_t respLength = static_cast<int32_t>(vec_out.size());
            std::vector<uint8_t> packet(sizeof(respLength) + vec_out.size());
            memcpy(packet.data(), &respLength, sizeof(respLength));
            if (!vec_out.empty()) {
                memcpy(packet.data() + sizeof(respLength), vec_out.data(), vec_out.size());
            }

            if (!writeExact(hPipe, packet.data(), static_cast<DWORD>(packet.size()))) break;
        }

    }

};