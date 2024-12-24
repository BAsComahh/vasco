#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PrimeFactorizer.h"


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void arrExpand(int** arr) { // 数组大小+10
    int i = 0;
    while (arr[i]) {
        i++;
    }
    i += 10;
    *arr = realloc(*arr, i* sizeof(int));
}

void arrCpy(int* arrO, int** arrD, int size) {
    for(int i = 0; i < size; i++) {
        *arrD[i] = arrO[i];
    }
}

// 找出num的所有因数
int* getFactors(int num) { 
    int* factors = (int*)malloc(100*sizeof(int));
    memset(factors, 0, 100 * sizeof(int)); 
    int capacity = 100;
    int count = 0;

    for (int i = 2; i <= num; i++) { // i = 2起步将因数1排除
        if (count == capacity) {
            capacity *= 2;
            factors = (int*)realloc(factors,capacity*sizeof(int));
        }
        if (num % i == 0) {
            factors[count] = i;
            count++;
        }
    }
    if (count == 0) {
        return NULL;
    }
    return factors;
}

// 找出num的所有因数为互素的情况
int updateCoprimeFactors(int num, int* coprimeFactors, int size) { 
    int ans = 0;
    int factor = 0;
    int* factors = getFactors(num);

    if (factors == NULL) {    // 没有更多因数 -- 结束
        if (size >= 2) {
            return 1;
        }
        else {     // 互素因数数量小于2则不计入
            return 0;
        }
    }

    int j = 0;
    while (factor = factors[j]) {
        int flag = 1;
        if (size % 10 == 0) {   // 数组满了
            arrExpand(&coprimeFactors);
        }
        for (int i = 0; i < size; i++) {    // 检查该因数是否与已有因数互素
            if (gcd(factor,coprimeFactors[i]) != 1) {
                flag = 0;
                break;
            }
        }
        if (flag) { // 若全互素，num除以该因数，递归检查是否还有因数
            int* new_coprimeFactors = malloc((size+1)*sizeof(int));
            memset(new_coprimeFactors,0,(size+1)*sizeof(int));
            arrCpy(coprimeFactors,&new_coprimeFactors,size);
            new_coprimeFactors[size] = factor;
            ans += updateCoprimeFactors(num/factor,new_coprimeFactors,size+1);
            free(new_coprimeFactors);
        }   
        j++;
    }
    
    free(factors);
    return ans;
}

int primeFactorize(int num) {
    int ans = 0;
    int* factors = getFactors(num);
    int factor = 0;
    int* coprimeFactors = (int*)malloc(10*sizeof(int)); // 数组默认大小10个int

    if (num == 1) { // 默认输出
        return 1;
    }

    int i = 0;
    while(factor = factors[i]){ // 计算每个因数有几种互素的结果
        coprimeFactors[0] = factor;
        ans += updateCoprimeFactors(num/factor,coprimeFactors,1);
        i++;
    }

    free(coprimeFactors);
    free(factors);
    return ans+1;
}
