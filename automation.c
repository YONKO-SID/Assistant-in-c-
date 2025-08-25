#include "automation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <sqlext.h>
#include <tlhelp32.h>
#include <shellapi.h>
#pragma comment(lib, "odbc32.lib")
#else
#include <sqlite3.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <curl/curl.h>
#endif

ScheduledTask tasks[100];
int task_count = 0;

// Utility function declarations
long get_memory_usage();
time_t get_start_time();

#ifdef _WIN32
// Windows implementation

void init_task_scheduler() {
    printf("🔄 Task scheduler initialized (Windows version)\n");
}

void add_scheduled_task(const char* expression, const char* message, int interval_seconds, int repeat_count) {
    if (task_count >= 100) {
        printf("❌ Maximum tasks reached (100)\n");
        return;
    }
    
    tasks[task_count].id = task_count + 1;
    strncpy(tasks[task_count].expression, expression, MAX_EXPRESSION_LENGTH - 1);
    strncpy(tasks[task_count].message, message, MAX_TASK_LENGTH - 1);
    tasks[task_count].next_execution = time(NULL) + interval_seconds;
    tasks[task_count].interval_seconds = interval_seconds;
    tasks[task_count].repeat_count = repeat_count;
    tasks[task_count].is_active = 1;
    
    printf("✅ Task %d scheduled: %s (every %d seconds, %d repeats)\n", 
           tasks[task_count].id, message, interval_seconds, repeat_count);
    task_count++;
}

void list_scheduled_tasks() {
    printf("\n📅 Scheduled Tasks:\n");
    printf("ID  | Expression        | Message          | Next Execution    | Status\n");
    printf("----|-------------------|------------------|-------------------|--------\n");
    
    for (int i = 0; i < task_count; i++) {
        char time_str[20];
        struct tm* tm_info = localtime(&tasks[i].next_execution);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
        
        printf("%-3d | %-16s | %-16s | %-17s | %s\n",
               tasks[i].id, tasks[i].expression, tasks[i].message,
               time_str, tasks[i].is_active ? "Active" : "Inactive");
    }
}

void remove_scheduled_task(int task_id) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == task_id) {
            printf("🗑️ Removed task %d: %s\n", task_id, tasks[i].message);
            tasks[i].is_active = 0;
            return;
        }
    }
    printf("❌ Task %d not found\n", task_id);
}

void check_and_execute_tasks() {
    time_t current_time = time(NULL);
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].is_active && tasks[i].next_execution <= current_time) {
            printf("⏰ Executing scheduled task: %s\n", tasks[i].message);
            
            // Execute the task based on expression
            if (strcmp(tasks[i].expression, "notify") == 0) {
                send_notification("Scheduled Task", tasks[i].message, 0);
            }
            // Add more task types here
            
            // Update next execution time
            if (tasks[i].repeat_count > 0) {
                tasks[i].repeat_count--;
                tasks[i].next_execution = current_time + tasks[i].interval_seconds;
            } else {
                tasks[i].is_active = 0;
            }
        }
    }
}

void list_windows() {
    printf("🔍 Listing Windows:\n");
#ifdef _WIN32
    HWND hwnd = GetTopWindow(NULL);
    while (hwnd) {
        char title[256];
        GetWindowText(hwnd, title, sizeof(title));
        if (strlen(title) > 0) {
            RECT rect;
            GetWindowRect(hwnd, &rect);
            printf("📱 %s (%dx%d at %d,%d)\n", title, 
                   rect.right - rect.left, rect.bottom - rect.top,
                   rect.left, rect.top);
        }
        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
    }
#else
    printf("⚠️ Window listing only available on Windows\n");
#endif
}

void send_notification(const char* title, const char* message, int delay_seconds) {
#ifdef _WIN32
    NOTIFYICONDATA nid = {0};
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = FindWindow("ConsoleWindowClass", NULL);
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;
    nid.uTimeout = delay_seconds * 1000;
    strncpy(nid.szInfoTitle, title, sizeof(nid.szInfoTitle));
    strncpy(nid.szInfo, message, sizeof(nid.szInfo));
    
    if (Shell_NotifyIcon(NIM_ADD, &nid)) {
        printf("📢 Notification sent: %s\n", message);
    }
#else
    printf("🔔 Notification: %s - %s (delay: %ds)\n", title, message, delay_seconds);
#endif
}

#else
// Linux implementation - more complex due to system differences

void init_task_scheduler() {
    printf("🔄 Task scheduler initialized (Linux version)\n");
}

// Similar function implementations for Linux with appropriate system calls
// Would use dbus for notifications, xdotool for window management, etc.

#endif

// Platform-independent functions

void clipboard_history() {
    char *clipboard_text = get_clipboard_text();
    if (clipboard_text) {
        printf("📋 Clipboard: %s\n", clipboard_text);
        free(clipboard_text);
    } else {
        printf("📋 Clipboard is empty or not accessible\n");
    }
}

void docker_ps() {
    printf("🐳 Docker containers:\n");
#ifdef _WIN32
    system("docker ps");
#else
    system("docker ps");
#endif
}

void wifi_control(const char* action) {
    if (strcmp(action, "on") == 0) {
        printf("📡 Turning Wi-Fi on...\n");
#ifdef _WIN32
        system("netsh interface set interface \"Wi-Fi\" admin=enable");
#else
        system("nmcli radio wifi on");
#endif
    } else if (strcmp(action, "off") == 0) {
        printf("📡 Turning Wi-Fi off...\n");
#ifdef _WIN32
        system("netsh interface set interface \"Wi-Fi\" admin=disable");
#else
        system("nmcli radio wifi off");
#endif
    } else if (strcmp(action, "scan") == 0) {
        printf("📡 Scanning for networks...\n");
#ifdef _WIN32
        system("netsh wlan show networks");
#else
        system("nmcli dev wifi list");
#endif
    }
}

void list_services() {
    printf("🔄 System services:\n");
#ifdef _WIN32
    system("sc query state= all | findstr SERVICE_NAME");
#else
    system("systemctl list-units --type=service --all");
#endif
}

void git_status(const char* repo_path) {
    printf("📊 Git status for: %s\n", repo_path);
    char command[512];
    snprintf(command, sizeof(command), "cd \"%s\" && git status", repo_path);
    system(command);
}

void list_ports() {
    printf("🌐 Listening ports:\n");
#ifdef _WIN32
    system("netstat -an | findstr LISTENING");
#else
    system("netstat -tulpn | grep LISTEN");
#endif
}

void kill_port(int port) {
    printf("💥 Killing processes on port %d...\n", port);
#ifdef _WIN32
    char command[100];
    snprintf(command, sizeof(command), "netstat -ano | findstr :%d", port);
    system(command);
    printf("⚠️ Manually kill using: taskkill /PID <pid> /F\n");
#else
    char command[100];
    snprintf(command, sizeof(command), "fuser -k %d/tcp", port);
    system(command);
#endif
}

void media_control(const char* action) {
    if (strcmp(action, "play") == 0) {
        printf("▶️ Media play\n");
#ifdef _WIN32
        // Send media play key
#else
        system("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Play");
#endif
    } else if (strcmp(action, "pause") == 0) {
        printf("⏸️ Media pause\n");
#ifdef _WIN32
        // Send media pause key
#else
        system("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Pause");
#endif
    } else if (strcmp(action, "next") == 0) {
        printf("⏭️ Next track\n");
#ifdef _WIN32
        // Send media next key
#else
        system("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next");
#endif
    }
}

void get_crypto_price_real(const char* coin) {
    printf("💰 Getting crypto price for %s...\n", coin);
    char command[256];
#if defined(_WIN32)
    snprintf(command, sizeof(command), "curl -s \"https://api.coingecko.com/api/v3/simple/price?ids=%s&vs_currencies=usd\"", coin);
#else
    snprintf(command, sizeof(command), "curl -s \"https://api.coingecko.com/api/v3/simple/price?ids=%s&vs_currencies=usd\"", coin);
#endif
    system(command);
}

void show_dashboard() {
    printf("\n📊 Jarvis Dashboard\n");
    printf("═══════════════════════════════════════\n");
    printf("🔄 Tasks scheduled: %d\n", task_count);
    printf("💻 Memory usage: ~%.2f MB\n", (double)get_memory_usage() / 1024 / 1024);
    printf("⌚ Uptime: %ld seconds\n", (long)time(NULL) - get_start_time());
    printf("📅 Next task in: ");
    
    time_t next_task = -1;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].is_active) {
            if (next_task == -1 || tasks[i].next_execution < next_task) {
                next_task = tasks[i].next_execution;
            }
        }
    }
    
    if (next_task != -1) {
        time_t remaining = next_task - time(NULL);
        printf("%ld seconds\n", remaining);
    } else {
        printf("No scheduled tasks\n");
    }
    printf("═══════════════════════════════════════\n");
}

// Utility functions implementation
long get_memory_usage() {
    // Placeholder - would use platform-specific memory APIs
    return 1024 * 1024; // 1MB placeholder
}

time_t get_start_time() {
    static time_t start_time = 0;
    if (start_time == 0) {
        start_time = time(NULL);
    }
    return start_time;
}

#if defined(_WIN32)
char* get_clipboard_text() {
    if (!OpenClipboard(NULL)) return NULL;
    
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (!hData) {
        CloseClipboard();
        return NULL;
    }
    
    char* text = (char*)GlobalLock(hData);
    if (!text) {
        CloseClipboard();
        return NULL;
    }
    
    char* result = strdup(text);
    GlobalUnlock(hData);
    CloseClipboard();
    return result;
}

void save_to_clipboard(const char* text) {
    if (!OpenClipboard(NULL)) return;
    
    EmptyClipboard();
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
    if (!hGlobal) {
        CloseClipboard();
        return;
    }
    
    char* pGlobal = (char*)GlobalLock(hGlobal);
    strcpy(pGlobal, text);
    GlobalUnlock(hGlobal);
    
    SetClipboardData(CF_TEXT, hGlobal);
    CloseClipboard();
    printf("📋 Saved to clipboard: %s\n", text);
}
#else
// Linux clipboard functions would use xclip/xsel
char* get_clipboard_text() {
    FILE* fp = popen("xclip -o -selection clipboard", "r");
    if (!fp) return NULL;
    
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), fp)) {
        pclose(fp);
        return strdup(buffer);
    }
    pclose(fp);
    return NULL;
}

void save_to_clipboard(const char* text) {
    char command[1024];
    snprintf(command, sizeof(command), "echo '%s' | xclip -selection clipboard", text);
    system(command);
    printf("📋 Saved to clipboard: %s\n", text);
}
#endif