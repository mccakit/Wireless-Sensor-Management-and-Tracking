#pragma once
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
inline constexpr int g_bytes_to_read {8};
struct SerialPort
{
    HANDLE handle_to_COM;
    COMSTAT status;

    SerialPort(const std::string& port_name,const uint64_t baudrate)
    {
        handle_to_COM = CreateFileA(static_cast<LPCSTR>(port_name.c_str()), GENERIC_READ | GENERIC_WRITE, 0, nullptr,
                                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        DCB dcb_serial_parameters = {0};
        dcb_serial_parameters.DCBlength = sizeof(dcb_serial_parameters);
        GetCommState(handle_to_COM, &dcb_serial_parameters);
        dcb_serial_parameters.BaudRate = baudrate;
        dcb_serial_parameters.ByteSize = 8;
        dcb_serial_parameters.StopBits = ONESTOPBIT;
        dcb_serial_parameters.Parity = NOPARITY;
        dcb_serial_parameters.fDtrControl = DTR_CONTROL_ENABLE;
        SetCommState(handle_to_COM, &dcb_serial_parameters);
        PurgeComm(handle_to_COM, PURGE_RXCLEAR | PURGE_TXCLEAR);
        Sleep(1000);
    }

    ~SerialPort()
    {
        CloseHandle(handle_to_COM);
    }

    void read_serial_port(std::string& buffer)
    {
        DWORD errors;
        ClearCommError(handle_to_COM, &errors, &status);

        DWORD bytes_read;
        uint64_t to_read = 0;
        if(status.cbInQue > 0)
        {
            to_read = (status.cbInQue > g_bytes_to_read) ? g_bytes_to_read : status.cbInQue;
        }
        buffer.resize(to_read);
        ReadFile(handle_to_COM, &buffer[0], to_read, &bytes_read, nullptr);
    }
};