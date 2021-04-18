package com.chakans.algorithm.gcd;

public class GreatestCommonDivisor {

    public static void main(String[] args) {
        int u = 3052;
        int v = 10;

        System.out.println("--- 나머지 연산을 이용하는 방법 ---");
        System.out.println("Modulus: " + gcd_modulus(u, v));
        System.out.println("--- --------- ---");
        System.out.println("--- 재귀 호출을 이용하는 방법 ---");
        System.out.println("Recursion: " + gcd_recursion(u, v));
        System.out.println("--- --------- ---");
    }

    /**
     * 나머지 연산을 이용하는 방법 ( 가장 빠르게 나옴 )
     *
     * @param u
     * @param v
     * @return
     */
    private static int gcd_modulus(int u, int v) {
        int tmp;
        while (v > 0) {
            tmp = u % v;
            u = v;
            v = tmp;
        }
        return u;
    }

    /**
     * 재귀 호출을 이용하는 방법 ( 나름 괜찮은 속도가 나오고 구조적으로 깔끔함 )
     *
     * @param u
     * @param v
     * @return
     */
    private static int gcd_recursion(int u, int v) {
        if (v == 0) {
            return u;
        } else {
            return gcd_recursion(v, u % v);
        }
    }

}
