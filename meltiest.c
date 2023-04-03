#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DDR_SIZE (1 * 1024 * 1024) // DDR大小为1GB
#define BLOCK_SIZE (64 * 1024) // 每个块的大小为64KB
#define NUM_BLOCKS (DDR_SIZE / BLOCK_SIZE) // 块的数量

int main()
{
    char *ddr = (char *)malloc(DDR_SIZE); // 分配DDR内存
    if (ddr == NULL) {
        printf("Failed to allocate DDR memory.\n");
        return -1;
    }

    // 初始化DDR内存
    printf("test init...\r\n");
    printf("size:%d\r\n",DDR_SIZE);
    srand(time(NULL));
    for (int i = 0; i < DDR_SIZE; i++) {
        ddr[i] = rand() % 256;
    }

    // 测试读取DDR带宽
    printf("rd test...\r\n");
    clock_t start = clock();
    for (int i = 0; i < NUM_BLOCKS; i++) {
        char *block = ddr + i * BLOCK_SIZE;
        for (int j = 0; j < BLOCK_SIZE; j++) {
            char c = block[j];
        }
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    double bandwidth = DDR_SIZE / time / 1024 / 1024;
    printf("Read bandwidth: %.2f MB/s\n", bandwidth);

    // 测试写入DDR带宽
    printf("\r\nwr test...\r\n");
    start = clock();
    for (int i = 0; i < NUM_BLOCKS; i++) {
        char *block = ddr + i * BLOCK_SIZE;
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = rand() % 256;
        }
    }
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    bandwidth = DDR_SIZE / time / 1024 / 1024;
    printf("Write bandwidth: %.2f MB/s\n", bandwidth);

    free(ddr); // 释放DDR内存

    return 0;
}

