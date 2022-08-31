/**
 * This file sets up zones which contain animals.
 * It has a name of the zoo, and a list of zones.
 * Main functions are the getters and setters for all the variables, the function to add a zone to the zoo, the toString function, and the constructor.
 * 
 * @author Julianus
 * UTSA CS 3443 - Lab 1
 * Summer 2022
 */

public class Zoo {
    private String name; // variable is private so only the getters and setters can be used outside of the class
    public String getName() {return name;} // getter for the name
    public void setName(String name) {this.name = name;} // inline function to set the name, setter
    private Zone[] zones; // private array of zones
    public Zone[] getZones() {return zones;} // getter for the zones
    public void setZones(int numZones) {this.zones = new Zone[numZones];} // inline function to set the zones, setter

    private int lastIndex = 0; // this is used to track the last object in the zones array, the setter and getters are private as they are only meant for internal use
    private int getLastIndex() {return lastIndex;}
    private void incrementLastIndex() {this.lastIndex++;}

    public Zoo(String name, int numZones) { // constructor for the zoo
        setName(name); // uses the setter to set the name
        setZones(numZones); // uses the setter to set the zones
    }
    public String toString() { // toString function for the zoo, this will be used for representing the class in a string
        String s = "Welcome to the \"" + getName() + "\"!\n----------------------------------\n"; // Welcome to the ___ !
        // for (int i = 0; i < getZones().length; i++) {
        for (int i = 0; i < getLastIndex(); i++) { // loops through the zones, adding them to the string. Only goes until the last added zone
            s += getZones()[i] + "\n";
        }
        return s;
    }
    public void addZone(Zone z){ // adds a zone to the zoo's list of zones
        // getZones()[getZones().length] = z;
        getZones()[getLastIndex()] = z; // adds a zone to the list's last empty index
        incrementLastIndex(); // after filling in the last empty index, increments the last index to point to the next empty index
    }
}