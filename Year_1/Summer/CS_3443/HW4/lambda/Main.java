public class Main { 
    public static void main(String[] args) { 
     // TODO Auto-generated method stub 
    String arr[] = {"3", "7637412332637467323", "98756", "23" };  
    SortNumbers obj = new SortNumbers(); 

    obj.sortLargeNumbers(arr); 

    for (String s : arr)  
        System.out.println(s + " ");  
    } 
}
