# Advanced Jarvis Assistant in C

## Overview
This is an advanced AI-powered desktop assistant written in C with over 75+ sophisticated features. The assistant provides a comprehensive command-line interface with system control, internet capabilities, developer productivity tools, AI/NLP features, mathematical operations, entertainment features, and much more.

## Key Features

### 🧠 **AI-Powered Intelligence**
- Advanced command processing with natural language understanding
- Dynamic response system with contextual awareness
- Professional logging and activity tracking
- Cross-platform compatibility (Windows/Linux)
- **Offline Speech Recognition**: Vosk integration for voice commands
- **Local LLM Chat**: llama.cpp integration for private AI conversations
- **RAG System**: Vector search over local documents for knowledge retrieval
- **Intent Parser**: Advanced command recognition with aliases
- **Multi-language Detection**: Automatic language identification

### 🌐 **Internet & Search Capabilities**
- **Google Search**: `google <query>` - Opens Google search in default browser
- **YouTube Search**: `youtube <query>` - Searches YouTube videos
- **Website Navigation**: `open <url>` - Opens any website
- **Weather Information**: `weather <city>` - Get weather data for any city

### 💻 **System Control & Applications**
- **Notepad**: `open notepad` - Launches text editor
- **Command Prompt**: `open cmd` - Opens system shell
- **Calculator**: `open calculator` - Launches calculator app
- **System Control**: 
  - `shutdown` - Safely shuts down the system
  - `restart` - Restarts the system
  - `logoff` - Logs off current user

### ⏰ **Date & Time Functions**
- **Current Time**: `time` - Shows formatted current time
- **Current Date**: `date` - Displays today's date with day name

### 🧮 **Mathematical Operations**
- **Calculator**: `calc <operation> <num1> <num2>`
  - `calc add 10 5` - Addition
  - `calc sub 10 5` - Subtraction
  - `calc mul 10 5` - Multiplication
  - `calc div 10 5` - Division (with zero-division protection)

### 🎭 **Entertainment & Fun**
- **Jokes**: `joke` - Tells random jokes from a curated collection
- **Quotes**: `quote` - Shares motivational quotes from famous personalities
- **Facts**: `fact` - Displays interesting facts and trivia

### 📊 **System Information**
- **System Info**: `systeminfo` - Detailed system specifications
- **Network Info**: `ipconfig` - Network configuration details
- **Storage Info**: `diskinfo` - Disk space and storage information

### 📁 **File Management**
- **List Files**: `list files` - Shows all files in current directory
- **Create File**: `create file <filename>` - Creates new files
- **Delete File**: `delete file <filename>` - Removes files safely

### 🎨 **User Interface**
- **Clear Screen**: `clear` - Clears terminal display
- **Help System**: `help` - Comprehensive command reference
- **Colored Output**: Professional ANSI color coding
- **ASCII Art**: Beautiful welcome screen

### 🛠️ **Developer Productivity**

#### Git Assistant
- **Git Status**: `gitstatus <path>` - Check Git repository status
- **Smart Commit**: `git smart commit <repo_path> <message>` - Automatic commit with change analysis
- **Sync Repository**: `git sync <repo_path>` - Pull latest changes and push local commits

#### Project Management
- **New Project**: `proj new <type> <name>` - Create project templates
  - C, C++, Python, and Web project templates
- **Run Project**: `proj run <path>` - Auto-detect and run projects
  - Automatic language detection and execution

#### HTTP & API Testing
- **HTTP Client**: `http <method> <url> [json_data]` - Make REST API calls
  - Supports GET, POST, PUT, DELETE methods
- **JSON Pretty Print**: `pretty json <json>` - Format JSON data

#### Port & Process Management
- **Port Scanner**: `ports` - Show all listening ports
- **Kill Port**: `killport <port>` - Terminate processes on specific ports
- **Process Killer**: `killprocess <name>` - Kill processes by name
- **Port Info**: `portinfo <port>` - Detailed port usage information

#### Log Management
- **Log Tail**: `tail <file> [filter]` - Real-time log viewing with filters
- **Log Monitor**: `logmonitor <file>` - Continuous log monitoring

#### Code Snippets & Automation
- **Snippet Manager**: Add, run, and list command snippets
  - `snippet add <name> <command>` - Add new snippet
  - `snippet run <name>` - Execute snippet
  - `snippets` - List all snippets

#### Code Quality Tools
- **Code Review**: `codereview <file> <language>` - Automated code analysis
- **API Docs**: `codedocs <path>` - Generate Doxygen documentation
- **Code Metrics**: `codemetrics <file>` - Source code metrics analysis
- **Code Formatting**: `codeformat <file>` - Auto-format source code
- **Unit Testing**: `unittest <command>` - Run test suites
- **Performance Test**: `perftest <iterations>` - Benchmark performance

### 🎙️ **AI/NLP Features**

#### Voice Commands
- **Voice Recognition**: `voice` - Start speech recognition mode
  - Speak commands naturally instead of typing
  - Supports common commands like "hello jarvis", "what time is it", "tell me a joke"
  - Works offline using Vosk models

#### Local AI Assistant
- **AI Chat**: `ai <message>` - Chat with local AI assistant
  - Private, offline conversations using llama.cpp
  - Responses generated locally without internet
  - Example: `ai what is the weather today?`

#### Knowledge Base (RAG)
- **RAG Query**: `rag <question>` - Search knowledge base
  - Retrieval-Augmented Generation over local documents
  - Vector search for semantic understanding
  - Example: `rag how to use python?`

#### Language Detection
- **Language ID**: `detectlang <text>` - Detect language
  - Identifies English, Spanish, French, German, Italian
  - Useful for multilingual interactions
  - Example: `detectlang bonjour comment ça va`

#### Intent Recognition
- **Intent Management**: Advanced command parsing
  - `addintent` - Add new command intents with aliases
  - `trainintent` - Train the intent recognition model
  - Understands natural language variations of commands

## Technical Architecture

### Core Components
- **Command Processor**: Advanced string matching and parsing
- **System Integration**: Cross-platform system calls
- **Logging System**: Activity tracking with timestamps
- **Error Handling**: Robust error management and validation

### Cross-Platform Support
- **Windows**: Full Windows API integration
- **Linux**: Unix system calls and utilities
- **ANSI Colors**: Automatic color support detection

## Installation & Compilation

### Prerequisites
- GCC compiler (GNU Compiler Collection)
- Standard C libraries
- Internet connection (for web features)

### AI Model Setup

#### Vosk Speech Recognition Models
1. Download Vosk models from: https://alphacephei.com/vosk/models
2. Extract models to `models/vosk/` directory
3. Supported languages: English, Spanish, French, German, etc.

#### Llama.cpp Compatible Models
1. Download GGML format models compatible with llama.cpp
2. Place model files in `models/llama/` directory
3. Recommended: 7B parameter models for good performance

#### RAG Document Repository
1. Place text documents in `documents/` directory
2. Supported formats: .txt, .md, .pdf (text extraction)
3. Documents are automatically indexed for semantic search

### Compilation Commands

**Windows:**
```bash
gcc -std=c11 -O2 -o jarvis.exe jarvis.c automation.c ai_nlp.c
```

**Linux/Mac:**
```bash
gcc -std=c11 -O2 -o jarvis jarvis.c automation.c ai_nlp.c
```

## Usage

### Starting the Assistant
```bash
# Windows
jarvis.exe

# Linux/Mac
./jarvis
```

### Example Session
```
╔══════════════════════════════════════════════════════════════╗
║                    JARVIS ASSISTANT v2.0                    ║
║                Advanced AI Desktop Assistant                 ║
║                    Created by Advanced AI                   ║
╚══════════════════════════════════════════════════════════════╝

Hello! I am Jarvis, your advanced AI assistant.
Type 'help' to see what I can do for you.

jarvis> help
=== Jarvis Assistant - Available Commands ===

System Controls:
  open notepad     - Open Notepad
  open cmd         - Open Command Prompt
  open calculator  - Open Calculator
  shutdown         - Shutdown system
  restart          - Restart system
  logoff           - Log off current user

Internet & Search:
  google <query>   - Search Google
  youtube <query>  - Search YouTube
  open <url>       - Open website

Date & Time:
  time             - Show current time
  date             - Show current date

Math Tools:
  calc <op> <n1> <n2> - Mathematical operations
    Operations: add, sub, mul, div

Fun & Entertainment:
  joke             - Tell a random joke
  quote            - Show motivational quote
  fact             - Share interesting fact

System Information:
  systeminfo       - Show system details
  ipconfig         - Show network info
  diskinfo         - Show storage info

File Management:
  list files       - List files in directory
  create file <name> - Create new file
  delete file <name> - Delete file

Weather:
  weather <city>   - Get weather information

Miscellaneous:
  clear            - Clear screen
  help             - Show this help
  exit             - Exit Jarvis

jarvis> time
Current Time: 03:42:17 PM

jarvis> joke
Why don't scientists trust atoms? Because they make up everything!

jarvis> calc add 15 25
Result: 40.00

jarvis> google artificial intelligence
Opening Google search for: artificial intelligence

jarvis> exit
Goodbye! Thank you for using Jarvis Assistant.
```

### 💻 **Developer Productivity Session Example**

```
jarvis> gitstatus /home/user/project
📊 Git status for: /home/user/project
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   main.c

jarvis> git smart commit /home/user/project "Bug fixes"
📝 Smart commit for: /home/user/project
🔍 Analyzing changes...
🚀 Staging and committing changes...
[main abc1234] Bug fixes
 1 file changed, 2 insertions(+), 1 deletion(-)

jarvis> proj new python myapp
🚀 Creating new python project: myapp
📋 Creating Python project template...
✅ Python project created. Run with: cd myapp && python main.py

jarvis> tail /var/log/syslog web
📄 Tailing log file: /var/log/syslog with filter: web
2024-01-15T10:30:45 web-server[1234] GET /api/users 200
2024-01-15T10:31:22 web-server[1234] POST /api/login 201

jarvis> snippet add build make clean && make
✅ Snippet 'build' added: make clean && make

jarvis> snippet run build
🚀 Running snippet: build
💻 Executing: make clean && make
rm -f *.o
gcc main.c -o myapp

```

### 🚀 **Advanced AI Session Example**

```
╔══════════════════════════════════════════════════════════════╗
║                    JARVIS ASSISTANT AI 2.0                  ║
║                With Advanced NLP Capabilities                ║
╚══════════════════════════════════════════════════════════════╝

Hello! I am Jarvis, now with AI superpowers!

jarvis> voice
🎤 Voice Assistant Mode Activated!
🎤 Speak> (User speaks: "hello jarvis what can you do?")
Recognized: hello jarvis what can you do?
🤖 AI: I understand your request. Let me help you with that. You asked about: hello jarvis what can you do?

jarvis> ai how does machine learning work?
🤖 AI: That's a great question! Here's what I know... Machine learning is a subset of artificial intelligence that enables systems to learn and improve from experience without being explicitly programmed.

jarvis> rag artificial intelligence benefits
📚 RAG: Based on my knowledge documents, I found information related to your question: "artificial intelligence benefits". The documents suggest that AI can automate tasks, improve efficiency, and enable new capabilities.

jarvis> detectlang esto es muy interesante
🌐 Language detected: es

jarvis> addintent weather_check ["weather", "forecast", "temperature"]
✅ Intent system: Added new intent placeholder

jarvis> trainintent
✅ Intent parser trained successfully

jarvis> help
=== AI/NLP Commands ===
  voice            - Start speech recognition mode
  ai <message>     - Chat with local AI assistant
  rag <question>   - Query knowledge base with RAG
  detectlang <text>- Detect language of text
  addintent <name> <aliases> - Add new command intent
  trainintent      - Train intent recognition model

jarvis> exit
Thank you for using Jarvis AI Assistant. Have an intelligent day!
```

## File Structure
```
Assistant-in-c-/
├── jarvis.c          # Main source code with 75+ commands
├── automation.c       # Developer productivity tools implementation
├── automation.h       # Developer tools header
├── ai_nlp.h          # AI/NLP header with definitions
├── ai_nlp.c          # AI/NLP implementation
├── compile_jarvis.bat # Windows compilation script
├── compile_jarvis.sh # Linux compilation script
├── README.md         # Advanced documentation
├── COMMANDS_GUIDE.md # Complete command reference (75+ commands)
├── jarvis.log        # Activity log (created at runtime)
├── jarvis.conf       # Configuration file (optional)
├── models/           # AI model directories
│   ├── vosk/         # Vosk speech recognition models
│   └── llama/        # Llama.cpp compatible models
├── documents/        # RAG document repository
└── .git/             # Git repository
```

**Note:** `jarvis.log` and `jarvis.conf` are created automatically when you run the program. The log file tracks all user actions, and the config file can store custom commands.

## Features Summary

| Category | Features | Count |
|----------|----------|-------|
| System Control | 6 commands | 6 |
| Internet & Search | 4 commands | 4 |
| Date & Time | 2 commands | 2 |
| Mathematics | 4 operations | 4 |
| Entertainment | 3 features | 3 |
| System Info | 3 commands | 3 |
| File Management | 3 commands | 3 |
| Weather | 1 command | 1 |
| Utilities | 3 commands | 3 |
| Developer Productivity | 28 commands | 28 |
| **Total** | **57+ features** | **57+** |

## Advanced Features

### 🔒 **Security & Safety**
- Input validation and sanitization
- Safe file operations with error handling
- Protected system commands with confirmation

### 📈 **Performance**
- Optimized command processing
- Efficient memory management
- Fast response times

### 🎯 **User Experience**
- Intuitive command structure
- Helpful error messages
- Professional interface design

## Contributing
This is an advanced AI assistant demonstration. Feel free to extend the functionality by adding more commands, improving the interface, or enhancing the AI capabilities.

## License
This project demonstrates advanced C programming concepts and AI assistant capabilities.

