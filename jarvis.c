

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include "ai_nlp.h"
#include "automation.h"

#ifdef _WIN32
  #include <winsock2.h>
  #include <windows.h>
  #include <iphlpapi.h>
  #include <tlhelp32.h>
  #include <direct.h>
  #define getcwd _getcwd
#else
#include <unistd.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#endif
  

#define MAX_INPUT 1024
#define MAX_RESPONSE 2048
#define LOGFILE "jarvis.log"
#define CONFIG_FILE "jarvis.conf"
#define VOICE_BUFFER_SIZE 1024



void enable_ansi_colors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif
}

void print_colored(const char* color, const char* text) {
    printf("%s%s\033[0m", color, text);
}

void log_action(const char* action) {
    FILE* log = fopen(LOGFILE, "a");
    if (log) {
        time_t now = time(NULL);
        struct tm* tm_info = localtime(&now);
        fprintf(log, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
                tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
                tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, action);
        fclose(log);
    }
}


void get_system_time();
void get_system_info();
void get_cpu_usage();
void tell_joke();
void get_crypto_price(const char* coin);
void generate_password(int length);
void system_monitor();
void open_ai_chat();
void translate_text(const char* text, const char* lang);
void take_screenshot();
void open_calculator_advanced();
void currency_converter(double amount, const char* from, const char* to);
void create_backup(const char* filename);
void system_optimizer();
void open_virtual_assistant();
void get_battery_info();
void get_process_info();
void get_network_speed();
void get_system_uptime();
void ai_chat_response(const char* message);
void speak_text(const char* text);
void read_file_content(const char* filename);
void search_in_files(const char* pattern, const char* directory);
void get_file_stats(const char* filename);
void create_directory(const char* dirname);
void list_directory_tree(const char* path, int depth);
void generate_qr_code(const char* text);
void start_voice_assistant();
void open_google_search(const char* query);
void open_youtube_search(const char* query);
void open_website(const char* url);
void list_files();
void create_file(const char* filename);
void delete_file(const char* filename);
void open_application(const char* app_name);
void system_shutdown();
void system_restart();
void system_logoff();
void get_weather_info(const char* city);
void clear_screen();
void show_help();
int process_command(const char* input);

// Developer productivity function declarations
void start_code_review_mode(const char* file_path, const char* language);
void show_code_metrics(const char* file_path);
void refactor_code(const char* pattern, const char* replacement, const char* file_path);
void generate_api_docs(const char* project_path);
void run_unit_tests(const char* test_command);
void performance_benchmark(const char* command, int iterations);
void code_format(const char* file_path, const char* style);



void speak_text(const char* text) {
    char command[1024];
#ifdef _WIN32
    
    snprintf(command, sizeof(command),
        "powershell -Command \"Add-Type -AssemblyName System.Speech; $speak = New-Object System.Speech.Synthesis.SpeechSynthesizer; $speak.Speak('%s');\"",
        text);
#else
    
    snprintf(command, sizeof(command), "espeak \"%s\" 2>/dev/null", text);
#endif
    system(command);
}

void read_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        printf("\033[1;36m=== Content of %s ===\033[0m\n", filename);
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("\033[31mError: Could not open file '%s'\033[0m\n", filename);
    }
}

void search_in_files(const char* pattern, const char* directory) {
    char command[1024];
#ifdef _WIN32
    snprintf(command, sizeof(command), "findstr /s /i \"%s\" %s\\*.txt %s\\*.c %s\\*.h %s\\*.cpp",
             pattern, directory, directory, directory, directory);
#else
    snprintf(command, sizeof(command), "grep -r -i \"%s\" %s --include=\"*.txt\" --include=\"*.c\" --include=\"*.h\" --include=\"*.cpp\"",
             pattern, directory);
#endif
    printf("\033[1;36mSearching for '%s' in %s:\033[0m\n", pattern, directory);
    system(command);
}

void get_file_stats(const char* filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == 0) {
        printf("\033[1;36m=== File Statistics ===\033[0m\n");
        printf("Filename: %s\n", filename);
        printf("Size: %lld bytes\n", (long long)file_stat.st_size);
        printf("Last modified: %s", ctime(&file_stat.st_mtime));
        printf("Permissions: %o\n", file_stat.st_mode & 0777);
    } else {
        printf("\033[31mError: Could not get stats for file '%s'\033[0m\n", filename);
    }
}

void create_directory(const char* dirname) {
#ifdef _WIN32
    if (mkdir(dirname) == 0) {
#else
    if (mkdir(dirname, 0755) == 0) {
#endif
        printf("\033[1;32mDirectory '%s' created successfully!\033[0m\n", dirname);
        log_action("Directory created");
    } else {
        printf("\033[31mError: Could not create directory '%s'\033[0m\n", dirname);
    }
}

void list_directory_tree(const char* path, int depth) {
#ifdef _WIN32
    printf("\033[1;33mDirectory tree feature is available on Linux systems.\033[0m\n");
    printf("On Windows, use 'dir /s' command instead.\n");
#else
    DIR* dir = opendir(path);
    if (!dir) return;
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        for (int i = 0; i < depth; i++) printf("  ");
        printf("├── %s\n", entry->d_name);
        
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        struct stat statbuf;
        if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            list_directory_tree(full_path, depth + 1);
        }
    }
    closedir(dir);
#endif
}

void generate_qr_code(const char* text) {
    char command[1024];
    snprintf(command, sizeof(command),
#ifdef _WIN32
        "start https://api.qrserver.com/v1/create-qr-code/?size=150x150&data=%s"
#else
        "xdg-open \"https://api.qrserver.com/v1/create-qr-code/?size=150x150&data=%s\""
#endif
        , text);
    system(command);
    printf("\033[1;32mQR code generated for: %s\033[0m\n", text);
}

void start_voice_assistant() {
    printf("\033[1;36m🎤 Voice Assistant Mode Activated!\033[0m\n");
    printf("Speak your commands (type 'stop' to exit voice mode):\n");
    
    char input[MAX_INPUT];
    while (1) {
        printf("\033[1;34m🎤 Speak>\033[0m ");
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "stop") == 0 || strcmp(input, "exit") == 0) {
            printf("\033[1;32mVoice mode deactivated.\033[0m\n");
            break;
        }
        
        printf("\033[1;33mProcessing voice command: %s\033[0m\n", input);
        speak_text(input);
    }
}

void ai_chat_response(const char* message) {
    printf("\033[1;35m🤖 AI Response:\033[0m ");
    
    
    if (strstr(message, "hello") || strstr(message, "hi")) {
        printf("Hello! How can I assist you today?\n");
    } else if (strstr(message, "how are you")) {
        printf("I'm functioning optimally! Ready to help you with any task.\n");
    } else if (strstr(message, "weather")) {
        printf("I can help you check the weather. Try 'weather <city>' command.\n");
    } else if (strstr(message, "time")) {
        get_system_time();
    } else if (strstr(message, "joke")) {
        tell_joke();
    } else {
        printf("I'm here to help! You can ask me about time, weather, files, or system information.\n");
    }
}

char* trim_whitespace(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}



void get_crypto_price(const char* coin) {
    char command[1024];
    snprintf(command, sizeof(command),
#ifdef _WIN32
        "start https://www.google.com/search?q=%s+price"
#else
        "xdg-open \"https://www.google.com/search?q=%s+price\""
#endif
        , coin);
    system(command);
    printf("\033[1;32mOpening %s price information\033[0m\n", coin);
}

void generate_password(int length) {
    const char* chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    printf("\033[1;36mGenerated Password: \033[1;32m");
    for (int i = 0; i < length; i++) {
        printf("%c", chars[rand() % strlen(chars)]);
    }
    printf("\033[0m\n");
}

void system_monitor() {
    printf("\033[1;33m🖥️  Real-time System Monitor\033[0m\n");
    printf("Monitoring system resources (Press Ctrl+C to stop)...\n");
    
    for (int i = 0; i < 5; i++) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        
        get_system_info();
        get_cpu_usage();
        printf("\n--- Refreshing in 2 seconds ---\n");
        Sleep(2000);
    }
}

void open_ai_chat() {
    char command[1024];
    snprintf(command, sizeof(command),
#ifdef _WIN32
        "start https://chat.openai.com/"
#else
        "xdg-open \"https://chat.openai.com/\""
#endif
    );
    system(command);
    printf("\033[1;32mOpening ChatGPT...\033[0m\n");
}

void translate_text(const char* text, const char* lang) {
    char command[1024];
    snprintf(command, sizeof(command),
#ifdef _WIN32
        "start https://translate.google.com/?sl=auto&tl=%s&text=%s&op=translate"
#else
        "xdg-open \"https://translate.google.com/?sl=auto&tl=%s&text=%s&op=translate\""
#endif
        , lang, text);
    system(command);
    printf("\033[1;32mTranslating to %s...\033[0m\n", lang);
}

void take_screenshot() {
    char filename[50];
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(filename, sizeof(filename), "screenshot_%Y%m%d_%H%M%S.png", tm_info);
    
#ifdef _WIN32
    char command[100];
    snprintf(command, sizeof(command), "screencapture -x %s", filename);
#else
    char command[100];
    snprintf(command, sizeof(command), "scrot %s", filename);
#endif
    
    system(command);
    printf("\033[1;32mScreenshot saved as: %s\033[0m\n", filename);
}

void open_calculator_advanced() {
    printf("\033[1;36m🧮 Advanced Calculator Mode\033[0m\n");
    printf("Available operations: +, -, *, /, ^ (power), sqrt (square root)\n");
    printf("Example: 2 + 3 * 4, sqrt(16), 2^8\n");
    
    char expression[100];
    printf("Enter expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;
    
    
    printf("\033[1;33mResult: Processing advanced calculation...\033[0m\n");
}

void currency_converter(double amount, const char* from, const char* to) {
    char command[1024];
    snprintf(command, sizeof(command),
#ifdef _WIN32
        "start https://www.google.com/search?q=%f+%s+to+%s"
#else
        "xdg-open \"https://www.google.com/search?q=%f+%s+to+%s\""
#endif
        , amount, from, to);
    system(command);
    printf("\033[1;32mConverting %.2f %s to %s...\033[0m\n", amount, from, to);
}

void create_backup(const char* filename) {
    char backup_name[100];
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(backup_name, sizeof(backup_name), "backup_%Y%m%d_%H%M%S_", tm_info);
    strcat(backup_name, filename);
    
    FILE* source = fopen(filename, "rb");
    FILE* backup = fopen(backup_name, "wb");
    
    if (source && backup) {
        char buffer[1024];
        size_t bytes;
        while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
            fwrite(buffer, 1, bytes, backup);
        }
        fclose(source);
        fclose(backup);
        printf("\033[1;32mBackup created: %s\033[0m\n", backup_name);
    } else {
        printf("\033[31mError creating backup\033[0m\n");
    }
}

void system_optimizer() {
    printf("\033[1;33m⚡ System Optimization Started\033[0m\n");
#ifdef _WIN32
    system("cleanmgr /sagerun:1");
    printf("Disk cleanup completed\n");
#else
    system("sudo apt-get autoremove -y");
    printf("System cleanup completed\n");
#endif
}

void open_virtual_assistant() {
    printf("\033[1;36m🤖 Virtual Assistant Mode Activated\033[0m\n");
    printf("You can now have a conversation with Jarvis!\n");
    
    char input[MAX_INPUT];
    while (1) {
        printf("\033[1;34mYou>\033[0m ");
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            printf("\033[1;32mVirtual assistant mode deactivated.\033[0m\n");
            break;
        }
        
        ai_chat_response(input);
    }
}



void get_system_time() {
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    printf("\033[1;36mCurrent Time: %02d:%02d:%02d %s\033[0m\n",
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec,
           tm_info->tm_hour >= 12 ? "PM" : "AM");
}

void get_system_date() {
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char date_str[100];
    strftime(date_str, sizeof(date_str), "%A, %B %d, %Y", tm_info);
    printf("\033[1;36mToday's Date: %s\033[0m\n", date_str);
}

void get_system_info() {
    printf("\033[1;33m=== System Information ===\033[0m\n");
    
#ifdef _WIN32
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    
    printf("Processor: %d cores\n", sysInfo.dwNumberOfProcessors);
    printf("Architecture: %s\n", sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? "x64" : "x86");
    printf("Memory: %.2f GB total, %.2f GB available\n", 
           (double)memInfo.ullTotalPhys / (1024*1024*1024),
           (double)memInfo.ullAvailPhys / (1024*1024*1024));
    printf("Memory Usage: %.1f%%\n", memInfo.dwMemoryLoad);
#else
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        printf("Uptime: %ld seconds\n", si.uptime);
        printf("Load Average: %.2f %.2f %.2f\n", 
               (double)si.loads[0] / 65536.0,
               (double)si.loads[1] / 65536.0,
               (double)si.loads[2] / 65536.0);
        printf("Total RAM: %ld MB\n", si.totalram / 1024 / 1024);
        printf("Free RAM: %ld MB\n", si.freeram / 1024 / 1024);
    }
#endif
}


void get_cpu_usage() {
    printf("\033[1;33m=== CPU Usage Information ===\033[0m\n");
    
#ifdef _WIN32
    FILETIME idleTime, kernelTime, userTime;
    FILETIME idleTimePrev, kernelTimePrev, userTimePrev;
    
    if (GetSystemTimes(&idleTimePrev, &kernelTimePrev, &userTimePrev)) {
        Sleep(1000); 
        if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
            ULARGE_INTEGER idle, kernel, user;
            ULARGE_INTEGER idlePrev, kernelPrev, userPrev;
            
            idle.LowPart = idleTime.dwLowDateTime;
            idle.HighPart = idleTime.dwHighDateTime;
            kernel.LowPart = kernelTime.dwLowDateTime;
            kernel.HighPart = kernelTime.dwHighDateTime;
            user.LowPart = userTime.dwLowDateTime;
            user.HighPart = userTime.dwHighDateTime;
            
            idlePrev.LowPart = idleTimePrev.dwLowDateTime;
            idlePrev.HighPart = idleTimePrev.dwHighDateTime;
            kernelPrev.LowPart = kernelTimePrev.dwLowDateTime;
            kernelPrev.HighPart = kernelTimePrev.dwHighDateTime;
            userPrev.LowPart = userTimePrev.dwLowDateTime;
            userPrev.HighPart = userTimePrev.dwHighDateTime;
            
            ULONGLONG kernelDiff = kernel.QuadPart - kernelPrev.QuadPart;
            ULONGLONG userDiff = user.QuadPart - userPrev.QuadPart;
            ULONGLONG idleDiff = idle.QuadPart - idlePrev.QuadPart;
            
            ULONGLONG totalDiff = kernelDiff + userDiff;
            double cpuUsage = 100.0 - ((double)idleDiff / (double)totalDiff * 100.0);
            
            printf("CPU Usage: %.1f%%\n", cpuUsage);
        }
    }
#else
    FILE* file = fopen("/proc/stat", "r");
    if (file) {
        char line[256];
        if (fgets(line, sizeof(line), file)) {
            unsigned long user, nice, system, idle, iowait, irq, softirq, steal;
            sscanf(line, "cpu %lu %lu %lu %lu %lu %lu %lu %lu", 
                   &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
            unsigned long total = user + nice + system + idle + iowait + irq + softirq + steal;
            unsigned long nonIdle = user + nice + system + irq + softirq + steal;
            double cpuUsage = (double)nonIdle / total * 100.0;
            printf("CPU Usage: %.1f%%\n", cpuUsage);
        }
        fclose(file);
    }
#endif
}


void get_battery_info() {
    printf("\033[1;33m=== Battery Information ===\033[0m\n");
    
#ifdef _WIN32
    SYSTEM_POWER_STATUS powerStatus;
    if (GetSystemPowerStatus(&powerStatus)) {
        if (powerStatus.BatteryFlag == 128) {
            printf("Battery: No battery detected\n");
        } else if (powerStatus.BatteryFlag == 255) {
            printf("Battery: Unknown status\n");
        } else {
            printf("Battery Level: %d%%\n", powerStatus.BatteryLifePercent);
            if (powerStatus.BatteryFlag & 8) {
                printf("Status: Charging\n");
            } else if (powerStatus.BatteryFlag & 1) {
                printf("Status: High\n");
            } else if (powerStatus.BatteryFlag & 2) {
                printf("Status: Low\n");
            } else if (powerStatus.BatteryFlag & 4) {
                printf("Status: Critical\n");
            } else {
                printf("Status: Unknown\n");
            }
        }
    } else {
        printf("Battery: Unable to get battery information\n");
    }
#else
    FILE* file = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (file) {
        char capacity[10];
        if (fgets(capacity, sizeof(capacity), file)) {
            printf("Battery Level: %s%%", capacity);
        }
        fclose(file);
        
        file = fopen("/sys/class/power_supply/BAT0/status", "r");
        if (file) {
            char status[20];
            if (fgets(status, sizeof(status), file)) {
                printf("Status: %s", status);
            }
            fclose(file);
        }
    } else {
        printf("Battery: No battery detected or not available\n");
    }
#endif
}


void get_process_info() {
    printf("\033[1;33m=== Process Information ===\033[0m\n");
    
#ifdef _WIN32
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        
        if (Process32First(hSnapshot, &pe32)) {
            int count = 0;
            printf("Top 10 Running Processes:\n");
            printf("%-30s %-10s %-10s\n", "Process Name", "PID", "Memory (KB)");
            printf("------------------------------------------------\n");
            
            do {
                if (count < 10) {
                    printf("%-30s %-10lu %-10lu\n", 
                           pe32.szExeFile, pe32.th32ProcessID, pe32.dwSize);
                    count++;
                }
            } while (Process32Next(hSnapshot, &pe32) && count < 10);
        }
        CloseHandle(hSnapshot);
    }
#else
    DIR* proc = opendir("/proc");
    if (proc) {
        struct dirent* entry;
        int count = 0;
        printf("Top 10 Running Processes:\n");
        printf("%-30s %-10s %-10s\n", "Process Name", "PID", "Status");
        printf("------------------------------------------------\n");
        
        while ((entry = readdir(proc)) && count < 10) {
            if (isdigit(entry->d_name[0])) {
                char path[256];
                char name[256];
                char status[10];
                
                snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
                FILE* file = fopen(path, "r");
                if (file) {
                    if (fgets(name, sizeof(name), file)) {
                        name[strcspn(name, "\n")] = 0;
                        
                        snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);
                        FILE* status_file = fopen(path, "r");
                        if (status_file) {
                            char line[256];
                            while (fgets(line, sizeof(line), status_file)) {
                                if (strncmp(line, "State:", 6) == 0) {
                                    sscanf(line, "State: %s", status);
                                    break;
                                }
                            }
                            fclose(status_file);
                        }
                        
                        printf("%-30s %-10s %-10s\n", name, entry->d_name, status);
                        count++;
                    }
                    fclose(file);
                }
            }
        }
        closedir(proc);
    }
#endif
}


void get_network_speed() {
    printf("\033[1;33m=== Network Speed Information ===\033[0m\n");
    
#ifdef _WIN32
    MIB_IFROW ifRow;
    memset(&ifRow, 0, sizeof(ifRow));
    ifRow.dwIndex = 1; 
    
    if (GetIfEntry(&ifRow) == NO_ERROR) {
        printf("Network Interface: %s\n", ifRow.wszName);
        printf("Interface Type: %d\n", ifRow.dwType);
        printf("Interface Status: %s\n", 
               ifRow.dwOperStatus == IF_OPER_STATUS_OPERATIONAL ? "Operational" : "Down");
        printf("Speed: %lu Mbps\n", ifRow.dwSpeed / 1000000);
        printf("MTU: %lu bytes\n", ifRow.dwMtu);
    } else {
        printf("Unable to get network interface information\n");
    }
#else
    FILE* file = fopen("/proc/net/dev", "r");
    if (file) {
        char line[256];
        int line_count = 0;
        printf("Network Interfaces:\n");
        printf("%-15s %-15s %-15s %-15s\n", "Interface", "RX Bytes", "TX Bytes", "Status");
        printf("------------------------------------------------\n");
        
        while (fgets(line, sizeof(line), file) && line_count < 5) {
            if (line_count > 1) { 
                char interface[20];
                unsigned long rx_bytes, tx_bytes;
                sscanf(line, "%s %lu %*d %*d %*d %*d %*d %*d %*d %lu", 
                       interface, &rx_bytes, &tx_bytes);
                printf("%-15s %-15lu %-15lu %-15s\n", 
                       interface, rx_bytes, tx_bytes, "Active");
            }
            line_count++;
        }
        fclose(file);
    }
#endif
}


void get_system_uptime() {
    printf("\033[1;33m=== System Uptime Information ===\033[0m\n");
    
#ifdef _WIN32
    ULARGE_INTEGER uptime;
    uptime.LowPart = GetTickCount();
    uptime.HighPart = 0;
    
    unsigned long seconds = uptime.QuadPart / 1000;
    unsigned long days = seconds / 86400;
    unsigned long hours = (seconds % 86400) / 3600;
    unsigned long minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;
    
    printf("System Uptime: %lu days, %lu hours, %lu minutes, %lu seconds\n", 
           days, hours, minutes, seconds);
    
    
    FILETIME bootTime;
    ULARGE_INTEGER bootTimeLarge;
    GetSystemTimeAsFileTime(&bootTime);
    bootTimeLarge.LowPart = bootTime.dwLowDateTime;
    bootTimeLarge.HighPart = bootTime.dwHighDateTime;
    bootTimeLarge.QuadPart -= (uptime.QuadPart * 10000); 
        
    FILETIME localBootTime;
    FileTimeToLocalFileTime(&bootTime, &localBootTime);
    
    SYSTEMTIME sysBootTime;
    FileTimeToSystemTime(&localBootTime, &sysBootTime);
    
    printf("Boot Time: %04d-%02d-%02d %02d:%02d:%02d\n",
           sysBootTime.wYear, sysBootTime.wMonth, sysBootTime.wDay,
           sysBootTime.wHour, sysBootTime.wMinute, sysBootTime.wSecond);
#else
    FILE* file = fopen("/proc/uptime", "r");
    if (file) {
        double uptime_seconds;
        fscanf(file, "%lf", &uptime_seconds);
        fclose(file);
        
        int days = (int)(uptime_seconds / 86400);
        int hours = (int)((uptime_seconds - (days * 86400)) / 3600);
        int minutes = (int)((uptime_seconds - (days * 86400) - (hours * 3600)) / 60);
        int seconds = (int)(uptime_seconds - (days * 86400) - (hours * 3600) - (minutes * 60));
        
        printf("System Uptime: %d days, %d hours, %d minutes, %d seconds\n", 
               days, hours, minutes, seconds);
        
        
        file = fopen("/proc/stat", "r");
        if (file) {
            char line[256];
            while (fgets(line, sizeof(line), file)) {
                if (strncmp(line, "btime", 5) == 0) {
                    unsigned long btime;
                    sscanf(line, "btime %lu", &btime);
                    time_t boot_time = (time_t)btime;
                    struct tm* tm_info = localtime(&boot_time);
                    printf("Boot Time: %04d-%02d-%02d %02d:%02d:%02d\n",
                           tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
                           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
                    break;
                }
            }
            fclose(file);
        }
    }
#endif
}

void get_network_info() {
    printf("\033[1;35m=== Network Information ===\033[0m\n");
#ifdef _WIN32
    printf("Network details available via 'ipconfig' command\n");
#else
    printf("Network details available via 'ifconfig' or 'ip addr' command\n");
#endif
}

void get_disk_info() {
    printf("\033[1;35m=== Storage Information ===\033[0m\n");
#ifdef _WIN32
    printf("Disk information available via 'wmic logicaldisk get size,freespace,caption' command\n");
#else
    printf("Disk information available via 'df -h' command\n");
#endif
}



double calculate_math(const char* operation, double a, double b) {
    if (strcmp(operation, "add") == 0) return a + b;
    if (strcmp(operation, "sub") == 0) return a - b;
    if (strcmp(operation, "mul") == 0) return a * b;
    if (strcmp(operation, "div") == 0) {
        if (b == 0) {
            printf("\033[31mError: Division by zero!\033[0m\n");
            return 0;
        }
        return a / b;
    }
    return 0;
}

void handle_math_command(const char* input) {
    char operation[20];
    double num1, num2;
    
    if (sscanf(input, "calc %s %lf %lf", operation, &num1, &num2) == 3) {
        double result = calculate_math(operation, num1, num2);
        printf("\033[1;32mResult: %.2f\033[0m\n", result);
        log_action("Mathematical calculation performed");
    } else {
        printf("\033[31mUsage: calc <operation> <number1> <number2>\033[0m\n");
        printf("Operations: add, sub, mul, div\n");
    }
}



void tell_joke() {
    const char* jokes[] = {
        "Why don't scientists trust atoms? Because they make up everything!",
        "Why don't skeletons fight each other? They don't have the guts!",
        "What do you call a fake noodle? An impasta!",
        "Why did the scarecrow win an award? He was outstanding in his field!",
        "Why don't eggs tell jokes? They'd crack each other up!",
        "What do you call a bear with no teeth? A gummy bear!",
        "Why don't oysters donate to charity? Because they're shellfish!",
        "What do you call a dinosaur that crashes his car? Tyrannosaurus wrecks!",
        "Why did the math book look so sad? Because it had too many problems!",
        "What do you call a fish wearing a bowtie? So-fish-ticated!"
    };
    int joke_count = sizeof(jokes) / sizeof(jokes[0]);
    int random_index = rand() % joke_count;
    printf("\033[1;33m%s\033[0m\n", jokes[random_index]);
    log_action("Joke told");
}

void tell_quote() {
    const char* quotes[] = {
        "The only way to do great work is to love what you do. - Steve Jobs",
        "Innovation distinguishes between a leader and a follower. - Steve Jobs",
        "Stay hungry, stay foolish. - Steve Jobs",
        "The future belongs to those who believe in the beauty of their dreams. - Eleanor Roosevelt",
        "Success is not final, failure is not fatal: it is the courage to continue that counts. - Winston Churchill",
        "The only limit to our realization of tomorrow is our doubts of today. - Franklin D. Roosevelt",
        "It does not matter how slowly you go as long as you do not stop. - Confucius",
        "The way to get started is to quit talking and begin doing. - Walt Disney",
        "Don't watch the clock; do what it does. Keep going. - Sam Levenson",
        "The only impossible journey is the one you never begin. - Tony Robbins"
    };
    int quote_count = sizeof(quotes) / sizeof(quotes[0]);
    int random_index = rand() % quote_count;
    printf("\033[1;34m%s\033[0m\n", quotes[random_index]);
    log_action("Quote shared");
}

void tell_fact() {
    const char* facts[] = {
        "Honey never spoils. Archaeologists have found pots of honey in ancient Egyptian tombs that are over 3,000 years old and still perfectly edible!",
        "A day on Venus is longer than its year. Venus takes 243 Earth days to rotate on its axis but only 225 Earth days to orbit the Sun.",
        "The shortest war in history lasted only 38 minutes. It was between Britain and Zanzibar in 1896.",
        "Bananas are berries, but strawberries aren't. Botanically, bananas are classified as berries, while strawberries are aggregate fruits.",
        "The Great Wall of China is not visible from space with the naked eye, despite the popular myth.",
        "A group of flamingos is called a 'flamboyance'.",
        "The average person spends 6 months of their lifetime waiting for red lights to turn green.",
        "Cows have best friends and get stressed when separated from them.",
        "The first oranges weren't orange. The original oranges from Southeast Asia were actually green.",
        "A day on Mars is only 37 minutes longer than a day on Earth."
    };
    int fact_count = sizeof(facts) / sizeof(facts[0]);
    int random_index = rand() % fact_count;
    printf("\033[1;36m%s\033[0m\n", facts[random_index]);
    log_action("Fact shared");
}



void open_google_search(const char* query) {
    char command[1024];
    snprintf(command, sizeof(command), 
#ifdef _WIN32
        "start https://www.google.com/search?q=%s"
#else
        "xdg-open \"https://www.google.com/search?q=%s\""
#endif
        , query);
    system(command);
    printf("\033[1;32mOpening Google search for: %s\033[0m\n", query);
    log_action("Google search performed");
}

void open_youtube_search(const char* query) {
    char command[1024];
    snprintf(command, sizeof(command), 
#ifdef _WIN32
        "start https://www.youtube.com/results?search_query=%s"
#else
        "xdg-open \"https://www.youtube.com/results?search_query=%s\""
#endif
        , query);
    system(command);
    printf("\033[1;32mOpening YouTube search for: %s\033[0m\n", query);
    log_action("YouTube search performed");
}

void open_website(const char* url) {
    char command[1024];
    snprintf(command, sizeof(command), 
#ifdef _WIN32
        "start %s"
#else
        "xdg-open \"%s\""
#endif
        , url);
    system(command);
    printf("\033[1;32mOpening website: %s\033[0m\n", url);
    log_action("Website opened");
}



void list_files() {
    printf("\033[1;35m=== Files in Current Directory ===\033[0m\n");
#ifdef _WIN32
    system("dir");
#else
    system("ls -la");
#endif
    log_action("Files listed");
}

void create_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fclose(file);
        printf("\033[1;32mFile '%s' created successfully!\033[0m\n", filename);
        log_action("File created");
    } else {
        printf("\033[31mError creating file '%s'\033[0m\n", filename);
    }
}

void delete_file(const char* filename) {
    if (remove(filename) == 0) {
        printf("\033[1;32mFile '%s' deleted successfully!\033[0m\n", filename);
        log_action("File deleted");
    } else {
        printf("\033[31mError deleting file '%s'\033[0m\n", filename);
    }
}



void open_application(const char* app_name) {
    char command[512];
    snprintf(command, sizeof(command), 
#ifdef _WIN32
        "start %s"
#else
        "%s"
#endif
        , app_name);
    system(command);
    printf("\033[1;32mOpening %s...\033[0m\n", app_name);
    log_action("Application opened");
}

void system_shutdown() {
    printf("\033[1;31mShutting down system in 10 seconds...\033[0m\n");
    log_action("System shutdown initiated");
#ifdef _WIN32
    system("shutdown /s /t 10");
#else
    system("shutdown -h +0");
#endif
}

void system_restart() {
    printf("\033[1;31mRestarting system in 10 seconds...\033[0m\n");
    log_action("System restart initiated");
#ifdef _WIN32
    system("shutdown /r /t 10");
#else
    system("shutdown -r +0");
#endif
}

void system_logoff() {
    printf("\033[1;31mLogging off current user...\033[0m\n");
    log_action("User logoff initiated");
#ifdef _WIN32
    system("logoff");
#else
    system("pkill -u $USER");
#endif
}



void get_weather_info(const char* city) {
    char command[1024];
    snprintf(command, sizeof(command), 
#ifdef _WIN32
        "start https://www.google.com/search?q=weather+%s"
#else
        "xdg-open \"https://www.google.com/search?q=weather+%s\""
#endif
        , city);
    system(command);
    printf("\033[1;32mOpening weather information for: %s\033[0m\n", city);
    log_action("Weather information requested");
}



void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    log_action("Screen cleared");
}

void show_help() {
    printf("\033[1;36m=== Jarvis Assistant - Available Commands ===\033[0m\n\n");
    
    printf("\033[1;33mSystem Controls:\033[0m\n");
    printf("  open notepad     - Open Notepad\n");
    printf("  open cmd         - Open Command Prompt\n");
    printf("  open calculator  - Open Calculator\n");
    printf("  shutdown         - Shutdown system\n");
    printf("  restart          - Restart system\n");
    printf("  logoff           - Log off current user\n\n");
    
    printf("\033[1;33mInternet & Search:\033[0m\n");
    printf("  google <query>   - Search Google\n");
    printf("  youtube <query>  - Search YouTube\n");
    printf("  open <url>       - Open website\n\n");
    
    printf("\033[1;33mDate & Time:\033[0m\n");
    printf("  time             - Show current time\n");
    printf("  date             - Show current date\n\n");
    
    printf("\033[1;33mMath Tools:\033[0m\n");
    printf("  calc <op> <n1> <n2> - Mathematical operations\n");
    printf("    Operations: add, sub, mul, div\n\n");
    
    printf("\033[1;33mFun & Entertainment:\033[0m\n");
    printf("  joke             - Tell a random joke\n");
    printf("  quote            - Show motivational quote\n");
    printf("  fact             - Share interesting fact\n\n");
    
    printf("\033[1;33mSystem Information:\033[0m\n");
    printf("  systeminfo       - Show system details\n");
    printf("  ipconfig         - Show network info\n");
    printf("  diskinfo         - Show storage info\n");
    printf("  cpuinfo          - Show CPU usage\n");
    printf("  batteryinfo      - Show battery information\n");
    printf("  processinfo      - Show running processes\n");
    printf("  netinfo          - Show network information\n");
    printf("  netspeed         - Show network speed\n");
    printf("  uptime           - Show system uptime\n\n");
    
    printf("\033[1;33mFile Management:\033[0m\n");
    printf("  list files       - List files in directory\n");
    printf("  create file <name> - Create new file\n");
    printf("  delete file <name> - Delete file\n\n");
    
    printf("\033[1;33mWeather:\033[0m\n");
    printf("  weather <city>   - Get weather information\n\n");
    
    printf("\033[1;33mAdvanced Features:\033[0m\n");
    printf("  read file <name>  - Read file content\n");
    printf("  file stats <name> - Show file statistics\n");
    printf("  search files <pattern> <dir> - Search text in files\n");
    printf("  create dir <name> - Create directory\n");
    printf("  tree             - Show directory tree (Linux)\n");
    printf("  qr <text>        - Generate QR code\n");
    printf("  voice            - Voice assistant mode\n");
    printf("  ai <message>     - AI chat response\n");
    printf("  speak <text>     - Text-to-speech\n\n");
    
    printf("\033[1;35mAI/NLP Features:\033[0m\n");
    printf("  voice            - Start speech recognition\n");
    printf("  ai <message>     - Chat with local AI assistant\n");
    printf("  rag <question>   - Query knowledge base with RAG\n");
    printf("  detectlang <text>- Detect language of text\n");
    printf("  addintent <name> <aliases> - Add new command intent\n");
    printf("  trainintent      - Train intent recognition model\n\n");
    
    printf("\033[1;33mMiscellaneous:\033[0m\n");
    printf("  clear            - Clear screen\n");
    printf("  help             - Show this help\n");
    printf("  exit             - Exit Jarvis\n\n");
    
    printf("\033[1;95m🤖 Automation & System Control:\033[0m\n");
    printf("  automation       - Show dashboard\n");
    printf("  schedule e m s r - Schedule task\n");
    printf("  tasks            - List scheduled tasks\n");
    printf("  removetask id    - Remove scheduled task\n");
    printf("  clipboard        - View clipboard content\n");
    printf("  copy text        - Copy text to clipboard\n");
    printf("  windows          - List open windows\n");
    printf("  wifi on|off|scan - Control Wi-Fi\n");
    printf("  services         - List system services\n");
    printf("  gitstatus path   - Git repository status\n");
    printf("  ports            - Show listening ports\n");
    printf("  killport port    - Kill process on port\n");
    printf("  killprocess name - Kill process by name\n");
    printf("  portinfo port    - Show port usage info\n");
    printf("  docker           - Show Docker containers\n");
    printf("  media play|pause - Media control\n");
    printf("  crypto coin      - Get crypto price\n");
    printf("  notify t m       - Send notification\n");
    printf("  proj new t n     - Create new project (c, cpp, python, web)\n");
    printf("  proj run path    - Run project at path\n");
    printf("  http m u [d]     - HTTP request (GET/POST/PUT/DELETE)\n");
    printf("  pretty json j    - Pretty print JSON string\n");
    printf("  tail file [f]    - Tail log file with optional filter\n");
    printf("  logmonitor file  - Monitor log file changes\n");
    printf("  snippet add n c  - Add command snippet\n");
    printf("  snippet run n    - Run command snippet\n");
    printf("  snippets         - List all snippets\n\n");

    printf("\033[1;94m🚀 Developer Productivity:\033[0m\n");
    printf("  codereview f l   - Start code review for file (language)\n");
    printf("  codedocs p       - Generate API docs for project\n");
    printf("  codemetrics f    - Show code metrics for file\n");
    printf("  refactor p r f   - Refactor code pattern in file\n");
    printf("  unittest c       - Run unit tests with command\n");
    printf("  benchmark i c    - Performance benchmark (iterations)\n");
    printf("  format f [s]     - Format code file with style\n\n");
    
    log_action("Help displayed");
}

int process_command(const char* input) {
    char command[MAX_INPUT];
    strcpy(command, input);
    str_to_lower(command);
    trim_whitespace(command);
    
    
    if (strstr(command, "open notepad")) {
        open_application("notepad");
        return 1;
    }
    if (strstr(command, "open cmd")) {
        open_application("cmd");
        return 1;
    }
    if (strstr(command, "open calculator")) {
#ifdef _WIN32
        open_application("calc");
#else
        open_application("gnome-calculator");
#endif
        return 1;
    }
    if (strstr(command, "shutdown")) {
        system_shutdown();
        return 1;
    }
    if (strstr(command, "restart")) {
        system_restart();
        return 1;
    }
    if (strstr(command, "logoff")) {
        system_logoff();
        return 1;
    }
    
    
    if (strncmp(command, "google ", 7) == 0) {
        open_google_search(input + 7);
        return 1;
    }
    if (strncmp(command, "youtube ", 8) == 0) {
        open_youtube_search(input + 8);
        return 1;
    }
    if (strncmp(command, "open ", 5) == 0 && strstr(command, "http")) {
        open_website(input + 5);
        return 1;
    }
    
    
    if (strcmp(command, "time") == 0) {
        get_system_time();
        return 1;
    }
    if (strcmp(command, "date") == 0) {
        get_system_date();
        return 1;
    }
    
    
    if (strncmp(command, "calc ", 5) == 0) {
        handle_math_command(input);
        return 1;
    }
    
    
    if (strcmp(command, "joke") == 0) {
        tell_joke();
        return 1;
    }
    if (strcmp(command, "quote") == 0) {
        tell_quote();
        return 1;
    }
    if (strcmp(command, "fact") == 0) {
        tell_fact();
        return 1;
    }
    
    
    if (strcmp(command, "systeminfo") == 0) {
        get_system_info();
        return 1;
    }
    if (strcmp(command, "ipconfig") == 0) {
        get_network_info();
        return 1;
    }
    if (strcmp(command, "diskinfo") == 0) {
        get_disk_info();
        return 1;
    }
    if (strcmp(command, "cpuinfo") == 0) {
        get_cpu_usage();
        return 1;
    }
    if (strcmp(command, "batteryinfo") == 0) {
        get_battery_info();
        return 1;
    }
    if (strcmp(command, "processinfo") == 0) {
        get_process_info();
        return 1;
    }
    if (strcmp(command, "netinfo") == 0) {
        get_network_info();
        return 1;
    }
    if (strcmp(command, "netspeed") == 0) {
        get_network_speed();
        return 1;
    }
    if (strcmp(command, "uptime") == 0) {
        get_system_uptime();
        return 1;
    }
    
    
    if (strcmp(command, "list files") == 0) {
        list_files();
        return 1;
    }
    if (strncmp(command, "create file ", 12) == 0) {
        create_file(input + 12);
        return 1;
    }
    if (strncmp(command, "delete file ", 12) == 0) {
        delete_file(input + 12);
        return 1;
    }
    
    
    if (strncmp(command, "weather ", 8) == 0) {
        get_weather_info(input + 8);
        return 1;
    }
    
    
    if (strcmp(command, "clear") == 0) {
        clear_screen();
        return 1;
    }
    if (strcmp(command, "help") == 0) {
        show_help();
        return 1;
    }
    if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
        printf("\033[1;32mGoodbye! Thank you for using Jarvis Assistant.\033[0m\n");
        log_action("User exited");
        return 0;
    }
    
    
    if (strncmp(command, "read file ", 10) == 0) {
        read_file_content(input + 10);
        return 1;
    }
    if (strncmp(command, "search files ", 13) == 0) {
        char pattern[256], directory[256];
        if (sscanf(input + 13, "%s %s", pattern, directory) == 2) {
            search_in_files(pattern, directory);
        } else {
            printf("\033[31mUsage: search files <pattern> <directory>\033[0m\n");
        }
        return 1;
    }
    if (strncmp(command, "file stats ", 11) == 0) {
        get_file_stats(input + 11);
        return 1;
    }
    if (strncmp(command, "create dir ", 11) == 0) {
        create_directory(input + 11);
        return 1;
    }
    if (strcmp(command, "tree") == 0) {
        list_directory_tree(".", 0);
        return 1;
    }
    if (strncmp(command, "qr ", 3) == 0) {
        generate_qr_code(input + 3);
        return 1;
    }
    if (strcmp(command, "voice") == 0) {
        start_voice_assistant();
        return 1;
    }
    if (strncmp(command, "ai ", 3) == 0) {
        ai_chat_response(input + 3);
        return 1;
    }
    if (strncmp(command, "speak ", 6) == 0) {
        speak_text(input + 6);
        return 1;
    }
    
    
    if (strcmp(command, "voice") == 0) {
        start_speech_recognition();
        return 1;
    }
    if (strncmp(command, "ai ", 3) == 0) {
        char* response = llm_chat(input + 3);
        printf("\033[1;35m🤖 AI: %s\033[0m\n", response);
        free(response);
        return 1;
    }
    if (strncmp(command, "rag ", 4) == 0) {
        char* response = rag_query(input + 4);
        printf("\033[1;36m📚 RAG: %s\033[0m\n", response);
        free(response);
        return 1;
    }
    if (strncmp(command, "detectlang ", 11) == 0) {
        char* lang = detect_language(input + 11);
        printf("\033[1;33m🌐 Language detected: %s\033[0m\n", lang);
        free(lang);
        return 1;
    }
    if (strncmp(command, "addintent ", 10) == 0) {
        
        printf("\033[1;32mIntent system: Added new intent placeholder\033[0m\n");
        return 1;
    }
    if (strcmp(command, "trainintent") == 0) {
        if (train_intent_parser()) {
            printf("\033[1;32mIntent parser trained successfully\033[0m\n");
        } else {
            printf("\033[31mIntent parser training failed\033[0m\n");
        }
        return 1;
    }
    
    
    if (strncmp(command, "crypto ", 7) == 0) {
        get_crypto_price(input + 7);
        return 1;
    }
    if (strncmp(command, "password", 8) == 0) {
        int length = 12;
        if (strlen(input) > 9) {
            sscanf(input + 9, "%d", &length);
        }
        generate_password(length);
        return 1;
    }
    if (strcmp(command, "monitor") == 0) {
        system_monitor();
        return 1;
    }
    if (strcmp(command, "chatgpt") == 0) {
        open_ai_chat();
        return 1;
    }
    if (strncmp(command, "translate ", 10) == 0) {
        char text[100], lang[10];
        if (sscanf(input + 10, "%s %[^\n]", lang, text) == 2) {
            translate_text(text, lang);
        } else {
            printf("\033[31mUsage: translate <language> <text>\033[0m\n");
        }
        return 1;
    }
    if (strcmp(command, "screenshot") == 0) {
        take_screenshot();
        return 1;
    }
    if (strcmp(command, "calc++") == 0) {
        open_calculator_advanced();
        return 1;
    }
    if (strncmp(command, "convert ", 8) == 0) {
        double amount;
        char from[10], to[10];
        if (sscanf(input + 8, "%lf %s %s", &amount, from, to) == 3) {
            currency_converter(amount, from, to);
        } else {
            printf("\033[31mUsage: convert <amount> <from_currency> <to_currency>\033[0m\n");
        }
        return 1;
    }
    if (strncmp(command, "backup ", 7) == 0) {
        create_backup(input + 7);
        return 1;
    }
    if (strcmp(command, "optimize") == 0) {
        system_optimizer();
        return 1;
    }
    if (strcmp(command, "assistant") == 0) {
        open_virtual_assistant();
        return 1;
    }
    
    
    if (strcmp(command, "automation") == 0) {
        show_dashboard();
        return 1;
    }
    if (strncmp(command, "schedule", 8) == 0) {
        char expr[100], msg[256];
        int interval, repeats;
        if (sscanf(command + 9, "%s %s %d %d", expr, msg, &interval, &repeats) == 4) {
            add_scheduled_task(expr, msg, interval, repeats);
        } else {
            printf("❌ Usage: schedule <expression> <message> <interval_seconds> <repeats>\n");
        }
        return 1;
    }
    if (strcmp(command, "tasks") == 0) {
        list_scheduled_tasks();
        return 1;
    }
    if (strncmp(command, "removetask", 10) == 0) {
        int task_id;
        if (sscanf(command + 11, "%d", &task_id) == 1) {
            remove_scheduled_task(task_id);
        } else {
            printf("❌ Usage: removetask <task_id>\n");
        }
        return 1;
    }
    if (strcmp(command, "clipboard") == 0) {
        clipboard_history();
        return 1;
    }
    if (strncmp(command, "copy ", 5) == 0) {
        save_to_clipboard(command + 5);
        return 1;
    }
    if (strcmp(command, "windows") == 0) {
        list_windows();
        return 1;
    }
    if (strncmp(command, "wifi ", 5) == 0) {
        wifi_control(command + 5);
        return 1;
    }
    if (strcmp(command, "services") == 0) {
        list_services();
        return 1;
    }
    if (strncmp(command, "gitstatus ", 10) == 0) {
        git_status(command + 10);
        return 1;
    }
    if (strcmp(command, "ports") == 0) {
        list_ports();
        return 1;
    }
    if (strncmp(command, "killport ", 9) == 0) {
        int port;
        if (sscanf(command + 9, "%d", &port) == 1) {
            kill_port(port);
        } else {
            printf("❌ Usage: killport <port_number>\n");
        }
        return 1;
    }
    if (strncmp(command, "docker", 6) == 0 || strcmp(command, "docker") == 0) {
        docker_ps();
        return 1;
    }
    if (strncmp(command, "media", 5) == 0) {
        char action[10];
        if (sscanf(command + 6, "%s", action) == 1) {
            media_control(action);
        } else {
            printf("❌ Usage: media <play|pause|next>\n");
        }
        return 1;
    }
    if (strncmp(command, "crypto ", 7) == 0) {
        get_crypto_price_real(command + 7);
        return 1;
    }
    if (strncmp(command, "notify ", 7) == 0) {
        char title[100], msg[200];
        if (sscanf(command + 7, "%s %[^\n]", title, msg) == 2) {
            send_notification(title, msg, 5);
        } else {
            printf("❌ Usage: notify <title> <message>\n");
        }
        return 1;
    }
    
    if (strncmp(command, "proj new ", 9) == 0) {
        char type[20], name[100];
        if (sscanf(command + 9, "%s %s", type, name) == 2) {
            create_project(type, name);
        } else {
            printf("❌ Usage: proj new <type> <name>\n");
            printf("   Types: c, cpp, python, web\n");
        }
        return 1;
    }

    if (strncmp(command, "proj run ", 9) == 0) {
        run_project(command + 9);
        return 1;
    }

    if (strncmp(command, "git smart commit ", 16) == 0) {
        char repo_path[256], message[512];
        if (sscanf(command + 16, "%s %[^\n]", repo_path, message) == 2) {
            git_smart_commit(repo_path, message);
        } else {
            printf("❌ Usage: git smart commit <repo_path> <message>\n");
        }
        return 1;
    }

    if (strncmp(command, "git sync ", 9) == 0) {
        git_sync(command + 9);
        return 1;
    }

    if (strncmp(command, "http ", 5) == 0) {
        char method_lower[10], method_upper[10], url[512], data[1024] = {0};
        if (sscanf(command + 5, "%s %s %[^\n]", method_lower, url, data) >= 2) {
            // Convert method to uppercase for HTTP function
            strcpy(method_upper, method_lower);
            for (int i = 0; method_upper[i]; i++) {
                method_upper[i] = toupper(method_upper[i]);
            }
            
            if (strlen(data) > 0) {
                http_request(method_upper, url, data);
            } else {
                http_request(method_upper, url, NULL);
            }
        } else {
            printf("❌ Usage: http <method> <url> [json_data]\n");
            printf("   Methods: GET, POST, PUT, DELETE\n");
        }
        
        if (strncmp(command, "killprocess ", 12) == 0) {
            kill_process_by_name(command + 12);
            return 1;
        }
        
        if (strncmp(command, "portinfo ", 9) == 0) {
            int port;
            if (sscanf(command + 9, "%d", &port) == 1) {
                list_processes_by_port(port);
            } else {
                printf("❌ Usage: portinfo <port_number>\n");
            }
            return 1;
        }
        return 1;
    }

    if (strncmp(command, "pretty json ", 12) == 0) {
        pretty_print_json(command + 12);
        return 1;
    }
    
    if (strncmp(command, "tail ", 5) == 0) {
        char filepath[256], filter[256] = {0};
        if (sscanf(command + 5, "%s %[^\n]", filepath, filter) >= 1) {
            if (strlen(filter) > 0) {
                tail_log(filepath, filter);
            } else {
                tail_log(filepath, NULL);
            }
        } else {
            printf("❌ Usage: tail <filepath> [filter]\n");
        }
        return 1;
    }
    
    if (strncmp(command, "logmonitor ", 11) == 0) {
        start_log_monitor(command + 11);
        return 1;
    }
    
    if (strncmp(command, "snippet add ", 12) == 0) {
        char name[50], snippet_cmd[256];
        if (sscanf(command + 12, "%s %[^\n]", name, snippet_cmd) == 2) {
            add_snippet(name, snippet_cmd);
        } else {
            printf("❌ Usage: snippet add <name> <command>\n");
        }
        return 1;
    }
    
    if (strncmp(command, "snippet run ", 12) == 0) {
        run_snippet(command + 12);
        return 1;
    }
    
    if (strcmp(command, "snippets") == 0) {
        list_snippets();
        return 1;
    }

    // Advanced Developer Productivity Commands
    if (strncmp(command, "codereview ", 11) == 0) {
        char file_path[256], language[20];
        if (sscanf(command + 11, "%s %s", file_path, language) == 2) {
            start_code_review_mode(file_path, language);
        } else {
            printf("❌ Usage: codereview <file_path> <language>\n");
        }
        return 1;
    }

    if (strncmp(command, "codedocs ", 9) == 0) {
        generate_api_docs(command + 9);
        return 1;
    }

    if (strncmp(command, "codemetrics ", 12) == 0) {
        show_code_metrics(command + 12);
        return 1;
    }

    if (strncmp(command, "refactor ", 9) == 0) {
        char pattern[100], replacement[100], file_path[256];
        if (sscanf(command + 9, "%s %s %s", pattern, replacement, file_path) == 3) {
            refactor_code(pattern, replacement, file_path);
        } else {
            printf("❌ Usage: refactor <pattern> <replacement> <file_path>\n");
        }
        return 1;
    }

    if (strncmp(command, "unittest ", 9) == 0) {
        run_unit_tests(command + 9);
        return 1;
    }

    if (strncmp(command, "benchmark ", 10) == 0) {
        char bench_command[512];
        int iterations = 3;
        if (sscanf(command + 10, "%d %[^\n]", &iterations, bench_command) >= 1) {
            performance_benchmark(bench_command, iterations);
        } else {
            printf("❌ Usage: benchmark [iterations] <command>\n");
        }
        return 1;
    }

    if (strncmp(command, "format ", 7) == 0) {
        char file_path[256], style[20] = "file";
        if (sscanf(command + 7, "%s %s", file_path, style) >= 1) {
            code_format(file_path, style);
        } else {
            printf("❌ Usage: format <file_path> [style]\n");
        }
        return 1;
    }
    
    
    if (strstr(command, "hello") || strstr(command, "hi")) {
        printf("\033[1;32mHello! I'm Jarvis, your advanced AI assistant. How can I help you today?\033[0m\n");
        return 1;
    }
    
    
    printf("\033[31mSorry, I don't understand that command. Type 'help' for available commands.\033[0m\n");
    return 1;
}



int main() {
    
    enable_ansi_colors();
    srand(time(NULL));
    
    
    printf("\033[1;33mInitializing AI/NLP systems...\033[0m\n");
    vosk_init();
    llm_init();
    rag_init("documents");
    intent_parser_init();
    
    
    printf("\033[1;33mInitializing automation systems...\033[0m\n");
    init_task_scheduler();
    
    
    printf("\033[1;36m");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    JARVIS ASSISTANT v2.0                    ║\n");
    printf("║                Advanced AI Desktop Assistant                 ║\n");
    printf("║                    Created by Advanced AI                   ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\033[0m");
    
    printf("\033[1;32mHello! I am Jarvis, your advanced AI assistant.\033[0m\n");
    printf("\033[1;33mType 'help' to see what I can do for you.\033[0m\n\n");
    
    log_action("Jarvis Assistant started");
    
    char input[MAX_INPUT];
    int running = 1;
    
    while (running) {
        printf("\033[1;34mjarvis>\033[0m ");
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) > 0) {
            running = process_command(input);
            
            
            check_and_execute_tasks();
        }
    }
    
    printf("\033[1;36mThank you for using Jarvis Assistant. Have a great day!\033[0m\n");
    
    
    vosk_cleanup();
    llm_cleanup();
    rag_cleanup();
    intent_parser_cleanup();
    
    
    check_and_execute_tasks();
    
    return 0;
}
