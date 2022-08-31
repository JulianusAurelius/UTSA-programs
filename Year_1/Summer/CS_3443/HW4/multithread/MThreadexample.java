package multithread;

public class MThreadexample { 

    public static void main(String[] args) { 
     // TODO Auto-generated method stub 
    ThreadGenerator thread1 = new ThreadGenerator("thread1"); 
    thread1.start(); 
    ThreadGenerator thread2 = new ThreadGenerator("thread2"); 
    thread2.start(); 
    } 
}