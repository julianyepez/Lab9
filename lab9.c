#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType *next; // For chaining in the hash table
};

// HashType
struct HashType {
    struct RecordType *head; // Pointer to the head of the chain
};

// Compute the hash function
int hash(int x, int hashSz) {
    return x % hashSz; // Simple modulo hash function
}

// Initialize hash table
struct HashType* initHashTable(int size) {
    struct HashType *hashTable = malloc(sizeof(struct HashType) * size);
    if (hashTable == NULL) {
        printf("Cannot allocate hash table\n");
        exit(-1);
    }
    for (int i = 0; i < size; i++) {
        hashTable[i].head = NULL;
    }
    return hashTable;
}

// Insert record into hash table
void insertRecord(struct HashType *hashTable, int hashSz, struct RecordType record) {
    int index = hash(record.id, hashSz);
    struct RecordType *newNode = malloc(sizeof(struct RecordType));
    if (newNode == NULL) {
        printf("Cannot allocate new node\n");
        exit(-1);
    }
    *newNode = record; // Copy the record data into the node
    newNode->next = hashTable[index].head;
    hashTable[index].head = newNode;
}

// Parse input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d ", &pRecord->id, &pRecord->name, &pRecord->order);
            pRecord->next = NULL; // Initialize next pointer to NULL
        }
        fclose(inFile);
    }
    return dataSz;
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType *pHashArray, int hashSz) {
    printf("Displaying Hash Table:\n");
    for (int i = 0; i < hashSz; ++i) {
        struct RecordType *current = pHashArray[i].head;
        if (current != NULL) {
            printf("index %d -> ", i);
            while (current != NULL) {
                printf("%d, %c, %d -> ", current->id, current->name, current->order);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;
    int hashTableSize = 10; // Define the size of the hash table

    recordSz = parseData("input.txt", &pRecords);

    struct HashType *hashTable = initHashTable(hashTableSize);
    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, hashTableSize, pRecords[i]);
    }

    displayRecordsInHash(hashTable, hashTableSize);

    return 0;
}
