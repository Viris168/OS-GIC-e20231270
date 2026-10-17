
/* file_creator_win.c */
#include <windows.h>
#include <string.h>

int main() {
    HANDLE hFile = CreateFile(
        "output.txt",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        const char *err = "Error opening file!\n";
        DWORD errWritten;
        WriteFile(GetStdHandle(STD_ERROR_HANDLE), err, strlen(err), &errWritten, NULL);
        return 1;
    }

    const char *text = "Hello from Operating Systems class!\n";
    DWORD bytesWritten;
    WriteFile(hFile, text, strlen(text), &bytesWritten, NULL);

    CloseHandle(hFile);

    const char *msg = "File created successfully!\n";
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), msg, strlen(msg), &bytesWritten, NULL);

    return 0;
}
