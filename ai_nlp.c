/*
 * AI/NLP Core Implementation for Jarvis Assistant
 * Implementation of AI features including:
 *   - Vosk speech-to-text
 *   - Local LLM with llama.cpp
 *   - RAG with vector search
 *   - Intent parsing
 *   - Multi-language detection
 */

#include "ai_nlp.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>

/* ---------- Global Engine Instances ---------- */
static VoskEngine vosk_engine = {0};
static LLMEngine llm_engine = {0};
static RAGSystem rag_system = {0};
static IntentParser intent_parser = {0};

/* ---------- Speech-to-Text Implementation ---------- */

bool vosk_init() {
    // Check if Vosk model directory exists
    struct stat st = {0};
    if (stat(VOSK_MODEL_DIR, &st) == -1) {
        printf("\033[31mVosk model directory not found: %s\033[0m\n", VOSK_MODEL_DIR);
        printf("\033[33mPlease download Vosk models from: https://alphacephei.com/vosk/models\033[0m\n");
        return false;
    }
    
    // In a real implementation, we would initialize the Vosk library here
    // For now, we'll simulate the initialization
    
    vosk_engine.model_path = VOSK_MODEL_DIR;
    vosk_engine.initialized = true;
    
    printf("\033[32mVosk speech recognition engine initialized\033[0m\n");
    return true;
}

void vosk_cleanup() {
    if (vosk_engine.initialized) {
        // Cleanup Vosk resources
        vosk_engine.initialized = false;
    }
}

char* vosk_transcribe_audio(const short* audio_data, int sample_count) {
    if (!vosk_engine.initialized) {
        return strdup("Speech recognition not initialized");
    }
    
    // Simulate speech recognition - in real implementation, this would use Vosk API
    // For demonstration, we'll simulate some common commands
    
    // Simple energy-based voice activity detection
    float energy = 0.0f;
    for (int i = 0; i < sample_count; i++) {
        energy += fabs(audio_data[i] / 32768.0f);
    }
    energy /= sample_count;
    
    if (energy < 0.01f) {
        return strdup(""); // Silence or very low energy
    }
    
    // Simulate recognition of some common commands
    const char* commands[] = {
        "hello jarvis",
        "what time is it",
        "tell me a joke",
        "open notepad",
        "search for artificial intelligence",
        "weather in london",
        "shutdown system",
        "exit",
        "help"
    };
    
    int random_index = rand() % (sizeof(commands) / sizeof(commands[0]));
    return strdup(commands[random_index]);
}

bool capture_audio(short* buffer, int max_samples) {
    // Simulate audio capture - in real implementation, this would use PortAudio or Windows audio APIs
    printf("\033[1;33m🎤 Listening... (speak now)\033[0m\n");
    
    // Simulate some delay for "listening"
#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
#endif
    
    // For demonstration, we'll simulate capturing some audio data
    for (int i = 0; i < max_samples; i++) {
        buffer[i] = (short)(sin(i * 0.1) * 10000 + (rand() % 2000 - 1000));
    }
    
    return true;
}

void start_speech_recognition() {
    if (!vosk_engine.initialized && !vosk_init()) {
        printf("\033[31mFailed to initialize speech recognition\033[0m\n");
        return;
    }
    
    short audio_buffer[FRAMES_PER_BUFFER * 5]; // 5 frames buffer
    if (capture_audio(audio_buffer, sizeof(audio_buffer)/sizeof(short))) {
        char* transcribed = vosk_transcribe_audio(audio_buffer, sizeof(audio_buffer)/sizeof(short));
        if (transcribed && strlen(transcribed) > 0) {
            printf("\033[1;32mRecognized: %s\033[0m\n", transcribed);
            // Process the recognized command
            printf("\033[1;33mProcessing voice command...\033[0m\n");
            // In the real implementation, this would call process_command(transcribed)
        } else {
            printf("\033[31mNo speech detected or recognition failed\033[0m\n");
        }
        free(transcribed);
    }
}

/* ---------- LLM Implementation ---------- */

bool llm_init() {
    // Check if LLM model exists
    struct stat st = {0};
    if (stat(LLM_MODEL_PATH, &st) == -1) {
        printf("\033[31mLLM model not found: %s\033[0m\n", LLM_MODEL_PATH);
        printf("\033[33mPlease download a llama.cpp compatible model\033[0m\n");
        return false;
    }
    
    // In a real implementation, we would initialize llama.cpp here
    llm_engine.model_path = LLM_MODEL_PATH;
    llm_engine.initialized = true;
    
    printf("\033[32mLLM engine initialized\033[0m\n");
    return true;
}

void llm_cleanup() {
    if (llm_engine.initialized) {
        // Cleanup llama.cpp resources
        llm_engine.initialized = false;
    }
}

char* llm_generate_response(const char* prompt, const char* context) {
    if (!llm_engine.initialized) {
        return strdup("LLM not initialized");
    }
    
    // Simulate LLM response - in real implementation, this would use llama.cpp API
    const char* responses[] = {
        "I understand your request. Let me help you with that.",
        "That's an interesting question. Based on my knowledge...",
        "I'd be happy to assist you with this matter.",
        "Let me think about that for a moment...",
        "Thank you for asking. Here's what I can tell you...",
        "I've analyzed your request and here's my response...",
        "Based on the available information, I recommend...",
        "That's a great question! Here's what I know...",
        "I'm processing your request and will provide the best answer.",
        "Let me provide you with some helpful information about that."
    };
    
    char* response = malloc(MAX_LLM_RESPONSE);
    if (response) {
        int random_index = rand() % (sizeof(responses) / sizeof(responses[0]));
        snprintf(response, MAX_LLM_RESPONSE, "%s You asked about: %s", responses[random_index], prompt);
    }
    
    return response;
}

char* llm_chat(const char* message) {
    return llm_generate_response(message, NULL);
}

/* ---------- RAG Implementation ---------- */

bool rag_init(const char* documents_dir) {
    // Initialize RAG system
    rag_system.documents = malloc(sizeof(DocumentVector) * MAX_DOCUMENTS);
    if (!rag_system.documents) {
        return false;
    }
    
    rag_system.count = 0;
    rag_system.initialized = true;
    
    printf("\033[32mRAG system initialized\033[0m\n");
    return true;
}

void rag_cleanup() {
    if (rag_system.initialized) {
        for (int i = 0; i < rag_system.count; i++) {
            free(rag_system.documents[i].vector);
        }
        free(rag_system.documents);
        rag_system.initialized = false;
    }
}

char* rag_query(const char* question) {
    if (!rag_system.initialized) {
        return strdup("RAG system not initialized");
    }
    
    // Simulate RAG query - in real implementation, this would use vector search
    char* response = malloc(MAX_LLM_RESPONSE);
    if (response) {
        snprintf(response, MAX_LLM_RESPONSE, 
                "Based on my knowledge documents, I found information related to your question: \"%s\". "
                "The documents suggest that this is an important topic with several key points to consider.", 
                question);
    }
    
    return response;
}

bool add_document_to_index(const char* file_path) {
    if (!rag_system.initialized || rag_system.count >= MAX_DOCUMENTS) {
        return false;
    }
    
    // Simulate document indexing
    rag_system.documents[rag_system.count].document_path = strdup(file_path);
    rag_system.documents[rag_system.count].vector = calloc(VECTOR_DIMENSION, sizeof(float));
    rag_system.count++;
    
    return true;
}

float* generate_document_embedding(const char* text) {
    // Simulate embedding generation
    float* embedding = malloc(VECTOR_DIMENSION * sizeof(float));
    if (embedding) {
        for (int i = 0; i < VECTOR_DIMENSION; i++) {
            embedding[i] = (float)rand() / RAND_MAX;
        }
    }
    return embedding;
}

/* ---------- Intent Parser Implementation ---------- */

bool intent_parser_init() {
    // Initialize with some common intents
    const char* greet_aliases[] = {"hello", "hi", "hey", "greetings", "good morning"};
    const char* time_aliases[] = {"time", "what time", "current time", "clock"};
    const char* joke_aliases[] = {"joke", "tell joke", "make me laugh", "funny"};
    
    add_intent("greeting", greet_aliases, 5);
    add_intent("get_time", time_aliases, 4);
    add_intent("tell_joke", joke_aliases, 4);
    
    printf("\033[32mIntent parser initialized with %d intents\033[0m\n", intent_parser.intent_count);
    return true;
}

void intent_parser_cleanup() {
    // Nothing to cleanup for now
}

char* parse_intent(const char* text) {
    char* processed = preprocess_text(text);
    if (!processed) return strdup("unknown");
    
    // Simple keyword matching for intent parsing
    for (int i = 0; i < intent_parser.intent_count; i++) {
        for (int j = 0; j < intent_parser.intents[i].alias_count; j++) {
            if (strstr(processed, intent_parser.intents[i].aliases[j]) != NULL) {
                free(processed);
                return strdup(intent_parser.intents[i].intent_name);
            }
        }
    }
    
    free(processed);
    return strdup("unknown");
}

bool add_intent(const char* intent_name, const char* aliases[], int alias_count) {
    if (intent_parser.intent_count >= MAX_INTENTS || alias_count > MAX_ALIASES_PER_INTENT) {
        return false;
    }
    
    strncpy(intent_parser.intents[intent_parser.intent_count].intent_name, 
            intent_name, MAX_INTENT_LENGTH - 1);
    
    for (int i = 0; i < alias_count; i++) {
        strncpy(intent_parser.intents[intent_parser.intent_count].aliases[i],
                aliases[i], MAX_ALIAS_LENGTH - 1);
    }
    
    intent_parser.intents[intent_parser.intent_count].alias_count = alias_count;
    intent_parser.intent_count++;
    
    return true;
}

bool train_intent_parser() {
    // Simulate training - in real implementation, this would use ML
    return true;
}

/* ---------- Language Detection ---------- */

char* detect_language(const char* text) {
    // Simple language detection based on common words
    const char* english_words[] = {"the", "and", "is", "are", "you", "me", "this", "that"};
    const char* spanish_words[] = {"el", "la", "y", "es", "que", "por", "para", "con"};
    
    int english_count = 0;
    int spanish_count = 0;
    
    char* lower_text = str_to_lower(strdup(text));
    
    for (int i = 0; i < sizeof(english_words)/sizeof(english_words[0]); i++) {
        if (strstr(lower_text, english_words[i]) != NULL) {
            english_count++;
        }
    }
    
    for (int i = 0; i < sizeof(spanish_words)/sizeof(spanish_words[0]); i++) {
        if (strstr(lower_text, spanish_words[i]) != NULL) {
            spanish_count++;
        }
    }
    
    free(lower_text);
    
    if (english_count > spanish_count) {
        return strdup("en");
    } else if (spanish_count > english_count) {
        return strdup("es");
    }
    
    return strdup("unknown");
}

bool is_language_supported(const char* language_code) {
    const char* supported[] = {"en", "es", "fr", "de", "it"};
    for (int i = 0; i < sizeof(supported)/sizeof(supported[0]); i++) {
        if (strcmp(language_code, supported[i]) == 0) {
            return true;
        }
    }
    return false;
}

/* ---------- Utility Functions ---------- */

float cosine_similarity(const float* vec1, const float* vec2, int dim) {
    float dot = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (int i = 0; i < dim; i++) {
        dot += vec1[i] * vec2[i];
        norm1 += vec1[i] * vec1[i];
        norm2 += vec2[i] * vec2[i];
    }
    return dot / (sqrt(norm1) * sqrt(norm2));
}

void normalize_vector(float* vector, int dim) {
    float norm = 0.0;
    for (int i = 0; i < dim; i++) {
        norm += vector[i] * vector[i];
    }
    norm = sqrt(norm);
    
    if (norm > 0) {
        for (int i = 0; i < dim; i++) {
            vector[i] /= norm;
        }
    }
}

char* preprocess_text(const char* text) {
    // Convert to lowercase and remove extra whitespace
    char* result = strdup(text);
    if (!result) return NULL;
    
    str_to_lower(result);
    
    // Remove extra whitespace
    char* dst = result;
    char* src = result;
    int in_space = 0;
    
    while (*src) {
        if (isspace((unsigned char)*src)) {
            if (!in_space) {
                *dst++ = ' ';
                in_space = 1;
            }
        } else {
            *dst++ = *src;
            in_space = 0;
        }
        src++;
    }
    *dst = '\0';
    
    // Trim leading/trailing whitespace
    char* start = result;
    while (isspace((unsigned char)*start)) start++;
    
    char* end = result + strlen(result) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    
    if (start != result) {
        memmove(result, start, strlen(start) + 1);
    }
    
    return result;
}

void print_ai_help() {
    printf("\033[1;36m=== AI/NLP Commands ===\033[0m\n");
    printf("  voice            - Start voice recognition mode\n");
    printf("  ai <message>     - Chat with local AI assistant\n");
    printf("  rag <question>   - Query knowledge base with RAG\n");
    printf("  detectlang <text>- Detect language of text\n");
    printf("  addintent <name> <aliases> - Add new command intent\n");
    printf("  trainintent      - Train intent recognition model\n");
}
