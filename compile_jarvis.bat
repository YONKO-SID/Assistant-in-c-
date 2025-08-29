@echo off
REM Compilation script for Jarvis Assistant with AI/NLP features

echo Compiling Jarvis Assistant with AI/NLP features...

REM Create model directories
mkdir models\vosk 2>nul
mkdir models\llama 2>nul
mkdir documents 2>nul

echo Model directories created:
echo   models\vosk\ - Place Vosk speech recognition models here
echo   models\llama\ - Place llama.cpp compatible models here
echo   documents\ - Place documents for RAG system here

REM Compile the program
echo Compiling...
gcc -std=c11 -O2 -o jarvis.exe jarvis.c ai_nlp.c automation.c -lm -liphlpapi -lws2_32

if %errorlevel% equ 0 (
    echo Compilation successful! Run jarvis.exe to start Jarvis Assistant
) else (
    echo Compilation failed. Please check for errors.
)