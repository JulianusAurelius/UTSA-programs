import static org.junit.Assert.*;

import org.junit.Test;

public class FibonacciTest {

	@Test
	public void fibonacciTest() {
		Fib fibSequencer = new Fib();

		int result = fibSequencer.fib(9);
		assertEquals(21, result);
		
		int result1 = fibSequencer.fib(10);
		assertEquals(34, result1);

        int result2 = fibSequencer.fib(11);
        assertEquals(55, result2);
        assertEquals(result+result1, result2);
	}

}