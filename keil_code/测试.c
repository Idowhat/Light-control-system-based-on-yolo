#include "stdio.h"

char Trigger_sta[3] ;
#define TEXT_LENTH sizeof(Trigger_sta) /* 数组长度 */
/*SIZE表示半字长(2字节), 大小必须是2的整数倍, 如果不是的话, 强制对齐到2的整数倍 */
#define SIZE TEXT_LENTH / 2 + ((TEXT_LENTH % 2) ? 1 : 0)
int main() {
    printf("SIZE: %d\n", SIZE);
	printf("TEXT_LENTH: %d\n", TEXT_LENTH);
    return 0;
}