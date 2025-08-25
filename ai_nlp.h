/*
 * AI/NLP Core Header for Jarvis Assistant
 * Includes definitions for AI features:
 *   - Vosk speech-to-text
 *   - Local LLM with llama.cpp
 *   - RAG with vector search
 *   - Intent parsing
 *   - Multi-language detection
 */

#ifndef AI_NLP_H
#define AI_NLP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
    #include <mmsystem.h>
    #pragma comment(lib, "winmm.lib")
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <portaudio.h>
#endif

/* ---------- Configuration Constants ---------- */
#define MAX_SPEECH_TEXT 1024
#define MAX_LLM_RESPONSE 4096
#define MAX_INTENT_LENGTH 256
#define MAX_ALIAS_LENGTH 50
#define MAX_LANG_CODE 10

/* ---------- Vosk Speech-to-Text Configuration ---------- */
#define VOSK_MODEL_DIR "models/vosk"
#define SAMPLE_RATE 16000
#define FRAMES_PER_BUFFER 1024
#define SILENCE_THRESHOLD 500

typedef struct {
    char* model_path;
    void* model;
    void* recognizer;
    bool initialized;
} VoskEngine;

/* ---------- LLM Configuration ---------- */
#define LLM_MODEL_PATH "models/llama/ggml-model.bin"
#define LLM_CONTEXT_SIZE 2048
#define LLM_TEMP 0.7f
#define LLM_TOP_P 0.9f

typedef struct {
    char* model_path;
    void* model;
    void* context;
    bool initialized;
} LLMEngine;

/* ---------- RAG Configuration ---------- */
#define VECTOR_DIMENSION 384
#define MAX_DOCUMENTS 1000
#define MAX_QUERY_LENGTH 256

typedef struct {
    char* document_path;
    float* vector;
    float similarity;
} DocumentVector;

typedef struct {
    DocumentVector* documents;
    int count;
    bool initialized;
} RAGSystem;

/* ---------- Intent Parser Configuration ---------- */
#define MAX_INTENTS 50
#define MAX_ALIASES_PER_INTENT 10

typedef struct {
    char intent_name[MAX_INTENT_LENGTH];
    char aliases[MAX_ALIASES_PER_INTENT][MAX_ALIAS_LENGTH];
    int alias_count;
} Intent;

typedef struct {
    Intent intents[MAX_INTENTS];
    int intent_count;
} IntentParser;

/* ---------- Language Detection Configuration ---------- */
typedef struct {
    char language_code[MAX_LANG_CODE];
    float confidence;
} LanguageDetection;

/* ---------- Function Declarations ---------- */

// Speech-to-Text Functions
bool vosk_init();
void vosk_cleanup();
char* vosk_transcribe_audio(const short* audio_data, int sample_count);
bool capture_audio(short* buffer, int max_samples);
void start_speech_recognition();

// LLM Functions
bool llm_init();
void llm_cleanup();
char* llm_generate_response(const char* prompt, const char* context);
char* llm_chat(const char* message);

// RAG Functions
bool rag_init(const char* documents_dir);
void rag_cleanup();
char* rag_query(const char* question);
bool add_document_to_index(const char* file_path);
float* generate_document_embedding(const char* text);

// Intent Parser Functions
bool intent_parser_init();
void intent_parser_cleanup();
char* parse_intent(const char* text);
bool add_intent(const char* intent_name, const char* aliases[], int alias_count);
bool train_intent_parser();

// Language Detection
char* detect_language(const char* text);
bool is_language_supported(const char* language_code);

// Utility Functions
float cosine_similarity(const float* vec1, const float* vec2, int dim);
void normalize_vector(float* vector, int dim);
char* preprocess_text(const char* text);
void print_ai_help();

// String utility function
static inline char* str_to_lower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

#endif /* AI_NLP_H */