package multithread;

public class ThreadGenerator implements Runnable {
    private Thread thread;
    private void startThread() { this.thread = new Thread(this); }
    private void setThreadName(String name) { this.thread.setName(name); }
    private Thread getThread() { return this.thread; }

    public ThreadGenerator(String name) {
        this.startThread();
        this.setThreadName(name);
    }

    public void start() {
        try {
            System.out.println("Thread started");
            this.getThread().start();
        }
        catch (Exception e) {
            System.out.println("Thread failed to start");
        }
    }

    public void run() {
        try {
            /* Intentionally changed format to make more readable
             * Previous didn't have a space and was poorly formatted
             */
            System.out.println("Thread running - " + Thread.currentThread().getName());
            for (int i = 0; i < 4; i++) {
                System.out.println(Integer.toString(i) + " - " + Thread.currentThread().getName());
                Thread.sleep(1000);
            }

        }
        catch (Exception e) {
            System.out.println("Thread failed to run");
        }
    }
    
}
