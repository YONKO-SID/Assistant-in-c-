# Jarvis Assistant - Complete Commands Guide

## Overview
Jarvis Assistant is an advanced AI-powered desktop assistant with over 50+ commands across multiple categories including system control, internet, AI/NLP, automation, file management, and more.

## System Control Commands

### Application Control
- `open notepad` - Open Notepad application
- `open cmd` - Open Command Prompt
- `open calculator` - Open Calculator app
- `shutdown` - Shutdown system (with 10s delay)
- `restart` - Restart system (with 10s delay)  
- `logoff` - Log off current user

### System Information
- `systeminfo` - Show detailed system specifications
- `ipconfig` - Show network configuration
- `diskinfo` - Show storage information
- `cpuinfo` - Show CPU usage statistics
- `batteryinfo` - Show battery status and level
- `processinfo` - Show top 10 running processes
- `netinfo` - Show network interface information
- `netspeed` - Show network speed metrics
- `uptime` - Show system uptime and boot time

## Internet & Search Commands

### Web Browsing
- `google <query>` - Open Google search in browser
- `youtube <query>` - Search YouTube videos
- `open <url>` - Open any website URL
- `weather <city>` - Get weather information for a city

## Date & Time Commands
- `time` - Show current time (HH:MM:SS AM/PM)
- `date` - Show current date with day name

## Mathematical Operations
- `calc <operation> <num1> <num2>` - Mathematical calculations
  - Operations: `add`, `sub`, `mul`, `div`
  - Example: `calc add 10 5` → Result: 15.00

## Entertainment & Fun Features
- `joke` - Tell a random joke from curated collection
- `quote` - Share motivational quotes
- `fact` - Display interesting facts and trivia

## File Management Commands

### Basic File Operations
- `list files` - Show files in current directory
- `create file <filename>` - Create new empty file
- `delete file <filename>` - Delete a file

### Advanced File Operations
- `read file <filename>` - Display file content
- `file stats <filename>` - Show file statistics (size, permissions, modified time)
- `search files <pattern> <directory>` - Search text in files
- `create dir <dirname>` - Create new directory
- `tree` - Show directory tree structure (Linux only)

### File Backup & Advanced
- `backup <filename>` - Create timestamped backup of file
- `qr <text>` - Generate QR code for text/URL

## AI/NLP Features

### Voice & Speech
- `voice` - Start speech recognition mode
- `speak <text>` - Text-to-speech output

### Local AI Assistant
- `ai <message>` - Chat with local AI assistant (llama.cpp)
- `rag <question>` - Query knowledge base with RAG system
- `detectlang <text>` - Detect language of text

### Intent Recognition
- `addintent <name> <aliases>` - Add new command intent with aliases
- `trainintent` - Train intent recognition model

## Automation & System Control

### Task Scheduling
- `automation` - Show system dashboard
- `schedule <expression> <message> <seconds> <repeats>` - Schedule automated task
- `tasks` - List all scheduled tasks
- `removetask <id>` - Remove scheduled task

### Clipboard Management
- `clipboard` - View clipboard content
- `copy <text>` - Copy text to clipboard

### Window & Process Management
- `windows` - List all open windows
- `ports` - Show listening ports
- `killport <port>` - Kill process on specific port

### Network & Services
- `wifi <on|off|scan>` - Control Wi-Fi connectivity
- `services` - List system services

### Advanced Development Tools

#### Git Assistant
- `gitstatus <path>` - Check Git repository status
- `git smart commit <repo_path> <message>` - Smart commit with change analysis
- `git sync <repo_path>` - Sync repository (pull + push)

#### Project Management
- `proj new <type> <name>` - Create new project templates
  - Types: `c`, `cpp`, `python`, `web`
- `proj run <path>` - Run project at specified path

#### HTTP & API Testing
- `http <method> <url> [json_data]` - Make HTTP requests
  - Methods: `GET`, `POST`, `PUT`, `DELETE`
- `pretty json <json>` - Pretty print JSON strings

#### Port & Process Management
- `ports` - Show listening ports
- `killport <port>` - Kill process on specific port
- `killprocess <name>` - Kill process by name
- `portinfo <port>` - Show detailed port usage info

#### Log Management
- `tail <file> [filter]` - Tail log file with optional filter
- `logmonitor <file>` - Monitor log file changes in real-time

#### Snippets & Automation
- `snippet add <name> <command>` - Add command snippet
- `snippet run <name>` - Run command snippet
- `snippets` - List all available snippets

#### Code Quality Tools
- `codereview <filename> <language>` - Start code review for file
- `codedocs <project_path>` - Generate API documentation
- `codemetrics <filename>` - Show code metrics analysis
- `codeformat <filename>` - Auto-format source code
- `unittest <test_command>` - Run unit tests
- `perftest <iterations>` - Run performance benchmarking

#### Additional Developer Tools
- `docker` - Show Docker containers and status

### Media & Entertainment
- `media <play|pause|next>` - Control media playback
- `crypto <coin>` - Get cryptocurrency price

### Notifications
- `notify <title> <message>` - Send system notification

## Advanced Features

### Virtual Assistant
- `assistant` - Enter virtual assistant conversation mode

### Translation & Screenshots
- `translate <language> <text>` - Translate text using Google Translate
- `screenshot` - Take screenshot and save with timestamp

### Advanced Calculator
- `calc++` - Enter advanced calculator mode with expressions

### Currency Conversion
- `convert <amount> <from_currency> <to_currency>` - Currency conversion

### System Optimization
- `optimize` - Run system cleanup and optimization

### Monitoring
- `monitor` - Real-time system resource monitoring

## Miscellaneous Commands
- `clear` - Clear terminal screen
- `help` - Show complete command list
- `exit` or `quit` - Exit Jarvis Assistant

## Usage Examples

### Basic Examples:
```bash
jarvis> time
Current Time: 19:15:30 PM

jarvis> weather london
Opening weather information for: london

jarvis> joke
Why don't scientists trust atoms? Because they make up everything!
```

### Advanced Examples:
```bash
jarvis> schedule notify "Reminder" "Meeting in 5 minutes" 300 1
✅ Task 1 scheduled: Meeting in 5 minutes (every 300 seconds, 1 repeats)

jarvis> automation
📊 Jarvis Dashboard
═══════════════════════════════════════
🔄 Tasks scheduled: 1
💻 Memory usage: ~1.00 MB
⌚ Uptime: 120 seconds
📅 Next task in: 180 seconds
═══════════════════════════════════════

jarvis> wifi scan
📡 Scanning for networks...
```

## Installation & Setup

### Prerequisites:
- GCC compiler
- Vosk speech recognition models (for voice commands)
- Llama.cpp compatible models (for AI chat)
- Documents for RAG system (in documents/ folder)

### Compilation:
**Windows:**
```bash
.\compile_jarvis.bat
```

**Linux/Mac:**
```bash
./compile_jarvis.sh
```

### Running:
**Windows:**
```bash
.\jarvis.exe
```

**Linux/Mac:**
```bash
./jarvis
```

## Technical Notes

- Cross-platform compatible (Windows/Linux)
- Uses ANSI color codes for better UI
- Automatic logging to `jarvis.log`
- Real-time task scheduling system
- Platform-specific implementations for system calls

This comprehensive guide covers all 75+ commands available in Jarvis Assistant v2.0 with advanced AI and developer productivity capabilities.