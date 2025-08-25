#!/bin/bash
# Compilation script for Jarvis Assistant with AI/NLP features

echo "Compiling Jarvis Assistant with AI/NLP features..."

# Create model directories
mkdir -p models/vosk
mkdir -p models/llama
mkdir -p documents

echo "Model directories created:"
echo "  models/vosk/ - Place Vosk speech recognition models here"
echo "  models/llama/ - Place llama.cpp compatible models here"
echo "  documents/ - Place documents for RAG system here"

# Compile the program
echo "Compiling..."
gcc -std=c11 -O2 -o jarvis jarvis.c ai_nlp.c automation.c -lm

if [ $? -eq 0 ]; then
    echo "Compilation successful! Run ./jarvis to start Jarvis Assistant"
else
    echo "Compilation failed. Please check for errors."
fi