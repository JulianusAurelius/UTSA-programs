/**
 * This is a file for individual zones in the zoo, which usually contain similar types of animals.
 * It has a name of the zone, and a list of animals.
 * Main functions are the getters and setters for all the variables, the function to add an animal to the zone, the toString function, and the constructor.
 * 
 * @author Julianus
 * UTSA CS 3443 - Lab 1
 * Summer 2022
 */

public class Zone {
    private String name; // variable is private so only the getters and setters can be used outside of the class
    public String getName() {return name;} // getter for the name
    public void setName(String name) {this.name = name;} // inline function to set the name, setter
    private Animal[] animals; // private array of animals
    public Animal[] getAnimals() {return animals;} // getter for the animals
    public void setAnimals(int numAnimals) {this.animals = new Animal[numAnimals];} // inline function to set the animals, setter

    private int lastIndex = 0; // this is used to track the last object in the animals array, the setter and getters are private as they are only meant for internal use
    private int getLastIndex() {return lastIndex;}
    private void incrementLastIndex() {this.lastIndex++;}

    public Zone(String name, int numAnimals) { // constructor for the zone
        setName(name); // uses the setter to set the name
        setAnimals(numAnimals); // uses the setter to set the animals
    }
    public String toString() { // toString function for the zone, this will be used for representing the class in a string
        String s = getName() + " Zone :\n----------------\n"; // ___ Zone :
        // for (int i = 0; i < getAnimals().length; i++) {
        for (int i = 0; i < getLastIndex(); i++) { // loops through the animals, adding them to the string. Only goes until the last added animal
            s += " >>  " + getAnimals()[i] + "\n";
        }
        return s;
    }
    public void addAnimal(Animal a){ // adds an animal to the zone's list of animals
        // getAnimals()[getAnimals().length] = a;
        getAnimals()[getLastIndex()] = a; // adds an animal to the list's last empty index
        incrementLastIndex(); // after filling in the last empty index, increments the last index to point to the next empty index
    }
}