
import java.util.Arrays;

public class SortNumbers {
    // public SortNumbers() {
    // }

    public void sortLargeNumbers(String[] arr) {
        for (int i=0; i<arr.length; i++) {
            Arrays.sort(arr, (left,right) -> {
                if(left.length() != right.length()) {
                    return left.length() - right.length();
                } else {
                    /* My first thought was to do a try/catch block
                     * and covert the string to an int. But after
                     * reviewing the notes, I saw the professor
                     * solved it much more succinctly.
                     * Don't reinvent the wheel
                     */
                    return right.compareTo(left);
                }
		    });
        }
    }
}
