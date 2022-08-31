import static org.junit.Assert.*;

import org.junit.Test;

public class FibonacciRecursiveTest {
	
	/* For extra credit */
	@Test
	public void fibonacciRecursiveTest() {
		Fib fibSequencer = new Fib();

		int result = fibSequencer.fib_recursive(9);
		assertEquals(21, result);
		
		int result1 = fibSequencer.fib_recursive(10);
		assertEquals(34, result1);

        int result2 = fibSequencer.fib_recursive(11);
        assertEquals(55, result2);
        assertEquals(result+result1, result2);
	}

}