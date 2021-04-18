package com.chakans.algorithm.prime;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Prime {

    public static void main(String[] args) {
        int non_prime = 111;
        int prime = 31;
        int max = 9999;

        System.out.println("--- 기본 소수 구하기 ---");
        System.out.println("Prime : " + is_prime(non_prime));
        System.out.println("--- --------- ---");
        System.out.println("--- SQRT 사용한 소수 구하기 ---");
        System.out.println("Prime ( SQRT ): " + is_prime_sqrt(prime));
        System.out.println("--- --------- ---");
        System.out.println("--- MAX 값보다 작은 소수를 모두 구하기 ( 에라토스테네스의 체 ) ---");
        System.out.println("Prime Numbers: " + eratosthenes_sieve(max));
        System.out.println("--- --------- ---");
    }

    /**
     * 소수 구하기 ( 작은 소수나 소수가 아닌 수에 대해서는 빠름 )
     *
     * @param n
     * @return
     */
    private static boolean is_prime(int n) {
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * 소수 구하기 (SQRT 사용) ( 수의 크기와 관계없이 고른 속력을 보임 )
     *
     * @param n
     * @return
     */
    private static boolean is_prime_sqrt(int n) {
        int sqrt = (int) Math.round(Math.sqrt(n));
        for (int i = 2; i <= sqrt; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * MAX 값보다 작은 소수를 모두 구하기 ( 에라토스테네스의 체 )
     *
     * @param MAX
     * @return
     */
    private static List<Integer> eratosthenes_sieve(int MAX) {
        List<Integer> prim_numbers = new ArrayList<>();
        // max만큼 할당
        int[] numbers = new int[MAX + 1];
        // 0으로 초기화
        Arrays.fill(numbers, 0);

        for (int i = 2; i <= MAX; i++) {
            if (numbers[i] == 1) {
                continue;
            }
            int j = i;
            while ((j += i) <= MAX) {
                numbers[j] = 1;
            }
        }

        for (int i = 2; i <= MAX; i++) {
            if (numbers[i] == 0) {
                prim_numbers.add(i);
            }
        }

        return prim_numbers;
    }

}
