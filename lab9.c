#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order; 
    struct RecordType* next; // Pointer to the next record in the chain
};

// HashType with a pointer to the first element (head) of the list
struct HashType {
    struct RecordType* head;
};

// Function prototypes
void insertRecord(struct HashType* hashTable, int hashSz, struct RecordType newRecord);
void displayRecordsInHash(struct HashType* hashTable, int hashSz);
int hash(int x, int hashSz);

// Compute the hash function
int hash(int x, int hashSz) {
    return x % hashSz; // Simple modulo-based hash function
}

// Insert a new record into the hash table
void insertRecord(struct HashType* hashTable, int hashSz, struct RecordType newRecord) {
    int index = hash(newRecord.id, hashSz);
    struct RecordType* newNode = (struct RecordType*) malloc(sizeof(struct RecordType));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    *newNode = newRecord;
    newNode->next = hashTable[index].head;
    hashTable[index].head = newNode;
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType* hashTable, int hashSz) {
    for (int i = 0; i < hashSz; ++i) {
        struct RecordType* current = hashTable[i].head;
        if (current != NULL) {
            printf("Index %d -> ", i);
            while (current != NULL) {
                printf("id: %d, name: %c, order: %d -> ", current->id, current->name, current->order);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    if (inFile == NULL) {
        printf("Failed to open file\n");
        return 0;
    }
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
    if (*ppData == NULL) {
        printf("Cannot allocate memory\n");
        exit(-1);
    }
    for (int i = 0; i < dataSz; ++i) {
        fscanf(inFile, "%d %c %d", &((*ppData)[i].id), &((*ppData)[i].name), &((*ppData)[i].order));
        (*ppData)[i].next = NULL;
    }
    fclose(inFile);
    return dataSz;
}

// Print the records
void printRecords(struct RecordType pData[], int dataSz) {
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;
    int hashTableSize = 10; // Assuming a hash table size of 10 for demonstration

    // Parse data from "input_lab_9.txt"
    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType* hashTable = malloc(sizeof(struct HashType) * hashTableSize);
    if (hashTable == NULL) {
        printf("Memory allocation failed for hash table\n");
        exit(-1);
    }
    for (int i = 0; i < hashTableSize; i++) {
        hashTable[i].head = NULL;
    }

    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, hashTableSize, pRecords[i]);
    }

    displayRecordsInHash(hashTable, hashTableSize);

    // Cleanup
    free(hashTable);
    free(pRecords);

    return 0;
}

