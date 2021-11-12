/*
Online Judge problem 1566 - John

The problem description is identical to a game of nim with misere rules.
*/

#include <cstdio>
#include <cstdint>

void solve(){
    int32_t heaps;
    int32_t heap_size;
    int32_t bitwise_xor = 0;
    bool two_or_more_count = 0;
    scanf("%d\n", &heaps);
    for (int i=0; i < heaps; i++){
        scanf("%d", &heap_size);
        bitwise_xor = bitwise_xor ^ heap_size;
        if (heap_size >= 2){
            two_or_more_count++;
        }
        if (i < heaps - 1){
            scanf(" ");
        }
    }
    scanf("\n");
    if (two_or_more_count > 0){
        if (bitwise_xor > 0){
            printf("John\n");
        } else {
            printf("Brother\n");
        }
    } else {
        if (bitwise_xor == 0){
            printf("John\n");
        } else {
            printf("Brother\n");
        }
    }
}


int main(){
    int32_t test_cases;
    scanf("%d\n", &test_cases);
    for (int i = 0; i < test_cases; i++){
        solve();
    }
    return 0;
}
