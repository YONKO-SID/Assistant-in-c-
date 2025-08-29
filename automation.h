#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tlhelp32.h>
#else
#include <sqlite3.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

#define MAX_TASK_LENGTH 256
#define MAX_EXPRESSION_LENGTH 100
#define TASK_DB "tasks.db"

typedef struct {
    int id;
    char expression[MAX_EXPRESSION_LENGTH];
    char message[MAX_TASK_LENGTH];
    time_t next_execution;
    int interval_seconds;
    int repeat_count;
    int is_active;
} ScheduledTask;


void init_task_scheduler();
void add_scheduled_task(const char* expression, const char* message, int interval_seconds, int repeat_count);
void list_scheduled_tasks();
void remove_scheduled_task(int task_id);
void check_and_execute_tasks();


void clipboard_history();
void save_to_clipboard(const char* text);
void clear_clipboard_history();
char* get_clipboard_text();


void list_windows();
void tile_windows();
void move_window(const char* direction);
void focus_window(const char* window_title);


void send_notification(const char* title, const char* message, int delay_seconds);
void list_pending_notifications();
void clear_notifications();


void organize_files(const char* directory, const char* rules_file);
void create_organization_rules(const char* rules_file);


void encrypt_file(const char* filepath, const char* password);
void decrypt_file(const char* filepath, const char* password);


void docker_ps();
void docker_start(const char* container_name);
void wsl_list();


void wifi_control(const char* action);
void bluetooth_pair(const char* device_name);


void list_services();
void start_service(const char* service_name);
void stop_service(const char* service_name);


void create_project(const char* type, const char* name);
void run_project(const char* project_path);


void git_status(const char* repo_path);
void git_smart_commit(const char* repo_path, const char* message);
void git_sync(const char* repo_path);


void http_request(const char* method, const char* url, const char* data);
void pretty_print_json(const char* json_string);


void list_ports();
void kill_port(int port);
void kill_process_by_name(const char* process_name);
void list_processes_by_port(int port);


void tail_log(const char* filepath, const char* filter);
void start_log_monitor(const char* filepath);


void add_snippet(const char* name, const char* command);
void run_snippet(const char* name);
void list_snippets();


void media_control(const char* action);
void media_volume(int level);


void get_currency_rate(const char* from, const char* to, double amount);
void get_crypto_price_real(const char* coin);


void confirm_dangerous_action(const char* action_name);
int check_permission(const char* permission_type);
void set_permission(const char* permission_type, int allowed);


void set_config(const char* key, const char* value);
void switch_profile(const char* profile_name);
void list_profiles();


void load_plugin(const char* plugin_path);
void list_plugins();
void unload_plugin(const char* plugin_name);


void show_dashboard();
void update_dashboard();

void start_code_review_mode(const char* file_path, const char* language);
void show_code_metrics(const char* file_path);
void refactor_code(const char* pattern, const char* replacement, const char* file_path);
void generate_api_docs(const char* project_path);
void run_unit_tests(const char* test_command);
void code_coverage_report(const char* project_path);
void dependency_check(const char* project_path);
void security_scan(const char* project_path);
void performance_benchmark(const char* command, int iterations);
void memory_leak_check(const char* executable_path);
void code_format(const char* file_path, const char* style);
void lint_code(const char* file_path, const char* linter_command);
void debug_mode(const char* executable_path, const char* arguments);
void generate_uml_diagram(const char* source_dir, const char* output_file);
void profile_code(const char* executable_path);
void database_migration(const char* migration_command);
void deploy_to_server(const char* deployment_script);
void create_microservice(const char* service_name, const char* framework);
void containerize_app(const char* app_path);
void cloud_deploy(const char* cloud_provider, const char* config_file);
#endif