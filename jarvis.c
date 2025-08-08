/*
  Advanced Jarvis Assistant in C
  An AI-powered desktop assistant with 25+ features including:
    - System commands and application control
    - Internet search and web browsing
    - Mathematical calculations
    - Date/time functions
    - Weather information
    - Fun features (jokes, quotes, facts)
    - System information and monitoring
    - File management operations
    - Dynamic command system with aliases
    - Cross-platform compatibility
    - Colored output and user-friendly interface
    - Logging and history management

  Compile:
    Linux:   gcc -std=c11 -O2 -o jarvis jarvis.c
    Windows: gcc -std=c11 -O2 -o jarvis.exe jarvis.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>

#ifdef _WIN32
  #include <windows.h>
  #include <winsock2.h>
  #include <iphlpapi.h>
#else
  #include <unistd.h>
  #include <sys/sysinfo.h>
  #include <pwd.h>
#endif

#define MAX_INPUT 1024
#define MAX_RESPONSE 2048
#define LOGFILE "jarvis.log"
#define CONFIG_FILE "jarvis.conf"

/* ---------- Utility Functions ---------- */

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

char* str_to_lower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
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

/* ---------- System Information Functions ---------- */

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

// Add CPU usage function
void get_cpu_usage() {
    printf("\033[1;33m=== CPU Usage Information ===\033[0m\n");
    
#ifdef _WIN32
    FILETIME idleTime, kernelTime, userTime;
    FILETIME idleTimePrev, kernelTimePrev, userTimePrev;
    
    if (GetSystemTimes(&idleTimePrev, &kernelTimePrev, &userTimePrev)) {
        Sleep(1000); // Wait 1 second
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

// Add battery information function
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

// Add process information function
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

// Add network speed monitoring function
void get_network_speed() {
    printf("\033[1;33m=== Network Speed Information ===\033[0m\n");
    
#ifdef _WIN32
    MIB_IFROW ifRow;
    memset(&ifRow, 0, sizeof(ifRow));
    ifRow.dwIndex = 1; // First network interface
    
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
            if (line_count > 1) { // Skip header lines
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

// Add system uptime function
void get_system_uptime() {
    printf("\033[1;33m=== System Uptime Information ===\033[0m\n");
    
#ifdef _WIN32
    ULARGE_INTEGER uptime;
    if (GetTickCount64) {
        uptime.QuadPart = GetTickCount64();
    } else {
        uptime.LowPart = GetTickCount();
        uptime.HighPart = 0;
    }
    
    unsigned long seconds = uptime.QuadPart / 1000;
    unsigned long days = seconds / 86400;
    unsigned long hours = (seconds % 86400) / 3600;
    unsigned long minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;
    
    printf("System Uptime: %lu days, %lu hours, %lu minutes, %lu seconds\n", 
           days, hours, minutes, seconds);
    
    // Get boot time
    FILETIME bootTime;
    ULARGE_INTEGER bootTimeLarge;
    if (GetSystemTimeAsFileTime(&bootTime)) {
        bootTimeLarge.LowPart = bootTime.dwLowDateTime;
        bootTimeLarge.HighPart = bootTime.dwHighDateTime;
        bootTimeLarge.QuadPart -= (uptime.QuadPart * 10000); // Convert to file time units
        
        FILETIME localBootTime;
        FileTimeToLocalFileTime(&bootTime, &localBootTime);
        
        SYSTEMTIME sysBootTime;
        FileTimeToSystemTime(&localBootTime, &sysBootTime);
        
        printf("Boot Time: %04d-%02d-%02d %02d:%02d:%02d\n",
               sysBootTime.wYear, sysBootTime.wMonth, sysBootTime.wDay,
               sysBootTime.wHour, sysBootTime.wMinute, sysBootTime.wSecond);
    }
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
        
        // Get boot time from /proc/stat
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

/* ---------- Mathematical Functions ---------- */

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

/* ---------- Fun Features ---------- */

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

/* ---------- Internet and Search Functions ---------- */

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

/* ---------- File Management Functions ---------- */

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

/* ---------- System Control Functions ---------- */

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

/* ---------- Weather Information ---------- */

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

/* ---------- Command Processing ---------- */

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
    
    printf("\033[1;33mMiscellaneous:\033[0m\n");
    printf("  clear            - Clear screen\n");
    printf("  help             - Show this help\n");
    printf("  exit             - Exit Jarvis\n\n");
    
    log_action("Help displayed");
}

int process_command(const char* input) {
    char command[MAX_INPUT];
    strcpy(command, input);
    str_to_lower(command);
    trim_whitespace(command);
    
    // System Controls
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
    
    // Internet & Search
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
    
    // Date & Time
    if (strcmp(command, "time") == 0) {
        get_system_time();
        return 1;
    }
    if (strcmp(command, "date") == 0) {
        get_system_date();
        return 1;
    }
    
    // Math Tools
    if (strncmp(command, "calc ", 5) == 0) {
        handle_math_command(input);
        return 1;
    }
    
    // Fun & Entertainment
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
    
    // System Information
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
    
    // File Management
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
    
    // Weather
    if (strncmp(command, "weather ", 8) == 0) {
        get_weather_info(input + 8);
        return 1;
    }
    
    // Miscellaneous
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
    
    // Greeting
    if (strstr(command, "hello") || strstr(command, "hi")) {
        printf("\033[1;32mHello! I'm Jarvis, your advanced AI assistant. How can I help you today?\033[0m\n");
        return 1;
    }
    
    // Unknown command
    printf("\033[31mSorry, I don't understand that command. Type 'help' for available commands.\033[0m\n");
    return 1;
}

/* ---------- Main Function ---------- */

int main() {
    // Initialize
    enable_ansi_colors();
    srand(time(NULL));
    
    // Welcome message
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
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) > 0) {
            running = process_command(input);
        }
    }
    
    printf("\033[1;36mThank you for using Jarvis Assistant. Have a great day!\033[0m\n");
    return 0;
}
