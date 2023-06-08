#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

bool check_overlap(uint32_t buf_size, uint32_t in, uint32_t out, uint8_t len);
void test_check_overlap(void);
uint32_t buf_copy(uint8_t *buf, uint32_t buf_size, uint8_t *src, uint8_t len, uint32_t in);
void test_buf_copy(void);
uint8_t checksum(const uint8_t *buf, uint32_t buf_size, uint32_t out);

// int main()
// {
//     uint8_t idx;
//     uint8_t buf[4] = {0x12, 0x34, 0x56, 0x78};
//     for (int i = 0; i < 4; i++) {
//         printf("buf + %d = %p, *(buf + %d) = %02x\n", i, buf + i, i, *(buf + i));
//     }
// }

int main()
{
    uint32_t val = 0x12345678;
    uint8_t buf[4];
    for (int i = 0; i < 4; i++)
    {
        buf[i] = *((uint8_t*)&val + i);
    }
    
    for (int i = 0; i < 4; i++) {
        printf("buf[%d] = %02x \n", i, buf[i]);
    }
}

bool 
check_overlap(uint32_t buf_size, uint32_t in, uint32_t out, uint8_t len) 
{
    uint32_t diff = in - out;

    if (in >= out) {
        if (diff + len >= buf_size)
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

void
test_buf_copy(void)
{

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