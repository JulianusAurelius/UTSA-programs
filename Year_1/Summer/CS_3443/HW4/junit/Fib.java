public class Fib {
    public int fib(int n) {
        if (n <= 0) {
            System.out.println("0");
            return 0;
        } else {
            int num1 = 0;
            int num2 = 1;
            System.out.print(num1);
            for (int i = 2; i <= n; i++) {
                int temp = num1;
                num1 = num2;
                num2 = temp + num2;
                System.out.print(", " + num1);
            }
            System.out.println();
            return num2;
        }
    }

    /* For extra credit */
    public int fib_recursive(int n) {
        if (n <= 0) {
            System.out.println("0");
            return 0;
        } else if (n == 1) {
            System.out.println("1");
            return 1;
        } else {
            int num1 = 0;
            int num2 = 1;
            System.out.print(num1);
            for (int i = 2; i <= n; i++) {
                int temp = num1;
                num1 = num2;
                num2 = temp + num2;
                System.out.print(", " + num1);
            }
            System.out.println();
            return num2;
        }
    }
}