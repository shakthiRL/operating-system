#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

// Structure to represent a disk block
typedef struct DiskBlock {
    int blockNumber;
    struct DiskBlock* next;
} DiskBlock;

// Structure to represent a file
typedef struct File {
    int fileId;
    DiskBlock* firstBlock;
    DiskBlock* lastBlock;
} File;

// Function to allocate a new disk block
DiskBlock* allocateBlock(int blockNumber) {
    DiskBlock* newBlock = (DiskBlock*)malloc(sizeof(DiskBlock));
    newBlock->blockNumber = blockNumber;
    newBlock->next = NULL;
    return newBlock;
}

// Function to add a block to the end of the file
void addBlockToFile(File* file, int blockNumber) {
    DiskBlock* newBlock = allocateBlock(blockNumber);
    if (file->firstBlock == NULL) {
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }
}

// Function to deallocate blocks of a file
void deallocateBlocks(File* file) {
    DiskBlock* currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        DiskBlock* nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

int main() {
    File file;
    file.fileId = 1;
    file.firstBlock = NULL;
    file.lastBlock = NULL;

    // Simulate file allocation
    printf("Allocating blocks to file...\n");
    for (int i = 0; i < 5; i++) {
        addBlockToFile(&file, i);
    }

    // Print allocated blocks
    printf("Allocated blocks for file %d: ", file.fileId);
    DiskBlock* currentBlock = file.firstBlock;
    while (currentBlock != NULL) {
        printf("%d ", currentBlock->blockNumber);
        currentBlock = currentBlock->next;
    }
    printf("\n");

    // Simulate file deallocation
    printf("Deallocating blocks of file...\n");
    deallocateBlocks(&file);
    printf("Blocks deallocated.\n");

    return 0;
}
