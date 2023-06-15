#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

bool check_overlap(uint32_t buf_size, uint32_t in, uint32_t out, uint8_t len);
void test_check_overlap(void);
void easy_code_test_check_overlap(void);
void chatgpt_test_check_overlap(void);

uint32_t buf_copy(uint8_t *buf, uint32_t buf_size, uint8_t *src, uint8_t len, uint32_t in);
void test_buf_copy(void);
uint8_t checksum(const uint8_t *buf, uint32_t buf_size, uint32_t out);

typedef struct entry1
{
    uint8_t len;
    uint32_t timestamp;
    uint32_t id;
    uint32_t params[3];
} entry1_t;

typedef struct entry2
{
    uint32_t timestamp;
    uint32_t id;
    uint32_t params[3];
    uint8_t len;
} entry2_t;


int main()
{
<<<<<<< HEAD
    // int8_t flag = 1;
    // uint8_t idx;
    // for(int i = 0; i < 7; i++)
    // {
    //     idx = flag & (-flag);
    //     printf("flag, idx: %d %d\n", flag, idx);
    //     flag = flag << 1;
    // }

    uint8_t *buf;
    uint32_t malloc_size;
    buf = (uint8_t*)malloc(1000);
    for (int i = 0; i < 5; i++) {
        printf("buf[%u] =  %02x\n", buf - i, (uint8_t)((uint8_t*)(buf-i)));
=======
    int8_t flag = 1;
    uint8_t idx;
    for(int i = 0; i < 100; i++)
    {
        idx = flag & (-flag);
        printf("flag, idx: %d %d\n", flag, idx);
        flag = flag << 1;
>>>>>>> workflows i < 10
    }
    //printf("malloc_size = %u \n", (uint32_t)((uint16_t*)(buf - 4)));
}

bool 
check_overlap(uint32_t buf_size, uint32_t in, uint32_t out, uint8_t len) 
{
    uint32_t diff;
    assert(in < buf_size);
    assert(out < buf_size);

    if (in >= out) {
        diff = in - out;
        if (diff >= buf_size - len)
            return true;
    } else {
        if (out - in <= len)
            return true;
    }
    return false;
}

void
test_check_overlap(void)
{
    bool rc;

    /* rc = 0 */
    rc = check_overlap(10, 5, 8, 2);
    assert(rc == 0);

    /* rc = 1 */
    rc = check_overlap(10, 5, 8, 3);
    assert(rc == 1);

    /* rc = 1 */
    rc = check_overlap(10, 5, 8, 4);
    assert(rc == 1);

    /* rc = 0 */
    rc = check_overlap(10, 8, 1, 2);
    assert(rc == 0);

    /* rc = 1 */
    rc = check_overlap(10, 8, 1, 3);
    assert(rc == 1);

    /* rc = 1 */
    rc = check_overlap(10, 8, 1, 4);
    assert(rc == 1);

    /* rc = 0 */
    rc = check_overlap(10, 7, 9, 1);
    assert(rc == 0);

    /* rc = 1 */
    rc = check_overlap(10, 7, 9, 2);
    assert(rc == 1);

    /* rc = 1 */
    rc = check_overlap(10, 7, 9, 3);
    assert(rc == 1);

    printf("check_overlap pass");
}

uint32_t 
buf_copy(uint8_t *buf, uint32_t buf_size, uint8_t *src, uint8_t len, uint32_t in) 
{
    if ((in + len) < buf_size) {
        memcpy(buf + in, src, len);

    } else {
        uint32_t first_chunk_len = buf_size - in;

        if (len == first_chunk_len) {
            memcpy(buf + in, src, first_chunk_len);
        } else {
            memcpy(buf + in, src, first_chunk_len);
            memcpy(buf, src + first_chunk_len, len - first_chunk_len);
        }
        
    }
    // 返回更新后的写索引
    return (in + len) % buf_size;
}


uint8_t 
checksum(const uint8_t *buf, uint32_t buf_size, uint32_t out) {
    uint8_t length = buf[out] + 1;  
    uint32_t sum = 0;

    for (uint32_t i = 0; i < length; i++) {
        sum += buf[(out + i) % buf_size];  // 计算校验和
    }

    return sum;
}

void
easy_code_test_check_overlap(void) 
{
    assert(!check_overlap(10, 0, 0, 1));
    assert(!check_overlap(10, 0, 0, 5));
    // assert(!check_overlap(10, 0, 0, 10));
    assert(!check_overlap(10, 5, 5, 1));
    assert(!check_overlap(10, 5, 5, 5));
    assert(!check_overlap(10, 5, 5, 10));
    assert(!check_overlap(10, 9, 0, 1));
    assert(!check_overlap(10, 9, 0, 5));
    assert(!check_overlap(10, 9, 0, 10));
    assert(!check_overlap(10, 9, 1, 1));
    assert(!check_overlap(10, 9, 1, 5));
    assert(!check_overlap(10, 9, 1, 10));
    assert(!check_overlap(10, 9, 5, 1));
    assert(!check_overlap(10, 9, 5, 5));
    assert(!check_overlap(10, 9, 5, 10));
    assert(!check_overlap(10, 9, 9, 1));
    assert(!check_overlap(10, 9, 9, 5));
    assert(!check_overlap(10, 9, 9, 10));

    assert(check_overlap(10, 0, 1, 1));
    assert(check_overlap(10, 0, 1, 5));
    assert(check_overlap(10, 0, 1, 10));
    assert(check_overlap(10, 0, 5, 1));
    assert(check_overlap(10, 0, 5, 5));
    assert(check_overlap(10, 0, 5, 10));
    assert(check_overlap(10, 0, 9, 1));
    assert(check_overlap(10, 0, 9, 5));
    assert(check_overlap(10, 0, 9, 10));
    assert(check_overlap(10, 1, 0, 1));
    assert(check_overlap(10, 1, 0, 5));
    assert(check_overlap(10, 1, 0, 10));
    assert(check_overlap(10, 1, 1, 1));
    assert(check_overlap(10, 1, 1, 5));
    assert(check_overlap(10, 1, 1, 10));
    assert(check_overlap(10, 1, 5, 1));
    assert(check_overlap(10, 1, 5, 5));
    assert(check_overlap(10, 1, 5, 10));
    assert(check_overlap(10, 1, 9, 1));
    assert(check_overlap(10, 1, 9, 5));
    assert(check_overlap(10, 1, 9, 10));
    assert(check_overlap(10, 5, 0, 1));
    assert(check_overlap(10, 5, 0, 5));
    assert(check_overlap(10, 5, 0, 10));
    assert(check_overlap(10, 5, 1, 1));
    assert(check_overlap(10, 5, 1, 5));
    assert(check_overlap(10, 5, 1, 10));
    assert(check_overlap(10, 5, 5, 1));
    assert(check_overlap(10, 5, 5, 5));
    assert(check_overlap(10, 5, 5, 10));
    assert(check_overlap(10, 5, 9, 1));

    assert(check_overlap(10, 5,5, 5));
    assert(check_overlap(10, 5, 5, 10));
    assert(check_overlap(10, 5, 9, 1));
    assert(check_overlap(10, 5, 9, 5));
    assert(check_overlap(10, 5, 9, 10));
    assert(check_overlap(10, 9, 0, 1));
    assert(check_overlap(10, 9, 0, 5));
    assert(check_overlap(10, 9, 0, 10));
    assert(check_overlap(10, 9, 1, 1));
    assert(check_overlap(10, 9, 1, 5));
    assert(check_overlap(10, 9, 1, 10));
    assert(check_overlap(10, 9, 5, 1));
    assert(check_overlap(10, 9, 5, 5));
    assert(check_overlap(10, 9, 5, 10));
    assert(check_overlap(10, 9, 9, 1));
    assert(check_overlap(10, 9, 9, 5));
    assert(check_overlap(10, 9, 9, 10));

}

void
chatgpt_test_check_overlap(void)
{
    // 测试 in > out，且没有重叠
    assert(check_overlap(100, 10, 0, 5) == false);
    
    // 测试 in > out，有部分重叠
    // assert(check_overlap(100, 10, 0, 15) == true);
    
    // 测试 in > out，完全重叠
    assert(check_overlap(100, 10, 0, 100) == true);
    
    // 测试 out > in，且没有重叠
    assert(check_overlap(100, 0, 10, 5) == false);
    
    // 测试 out > in，有部分重叠
    assert(check_overlap(100, 0, 10, 15) == true);
    
    // 测试 out > in，完全重叠
    assert(check_overlap(100, 0, 10, 100) == true);
    
    // 测试 in == out
    assert(check_overlap(100, 10, 10, 5) == false);
    
    // 测试边界情况，buf_size 为 0
    // assert(check_overlap(0, 10, 0, 5) == false);
    
    // 测试边界情况，len 为 0
    assert(check_overlap(100, 10, 0, 0) == false);
    
    // 测试边界情况，buf_size 为最大值
    assert(check_overlap(UINT32_MAX, UINT32_MAX - 10, 0, 15) == true);

    assert(check_overlap(10, 8, 11, 2) == true);
}

static uint32_t ble_timestamp_get(uint8_t *buf, uint32_t start, uint32_t buf_size)
{
    uint32_t time = 0;
    uint32_t remaining;
    uint8_t *p = (uint8_t*)&time;
    if (start >= buf_size) {
        start -= buf_size;
    }

    remaining = buf_size - start;
    if(remaining >= 4) {
        return (*((uint32_t*)(buf+start)));
    } else {
        memcpy(p, buf+start, remaining);
        p += remaining;
        memcpy(p, buf, 4-remaining);
        return time;
    }
}