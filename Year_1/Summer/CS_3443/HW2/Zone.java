/**
 * This is a file for individual zones in the zoo, which usually contain similar types of animals.
 * It has a name of the zone, and a list of animals. It also has a zoneCode, which is the zone code of the zone,
 * and a requiredSafetyRating
 * Main functions are the getters and setters for all the variables, the function to add an animal to the zone, the toString function, and the constructor.
 * 
 * @author Julianus
 * UTSA CS 3443 - Lab 1
 * Summer 2022
 */
import java.util.ArrayList;


public class Zone {
    private String name; // variable is private so only the getters and setters can be used outside of the class
    public String getName() {return name;} // getter for the name
    public void setName(String name) {this.name = name;} // inline function to set the name, setter
    
    private char zoneCode; // private variable for the zone code, which is a single character
    public char getZoneCode() {return zoneCode;} // getter for the zone code
    public void setZoneCode(char zoneCode) {this.zoneCode = zoneCode;} // inline function to set the zone code, setter

    private ArrayList<Animal> animals = new ArrayList<Animal>(); // this is the arraylist of animals in the zone
    public ArrayList<Animal> getAnimals() {return animals;} // getter for the animals arraylist

    private String requiredSafetyRating; // this is the required safety rating for the zone, which is a string
    public String getRequiredSafetyRating() {return requiredSafetyRating;} // getter for the required safety rating
    public void setRequiredSafetyRating(String requiredSafetyRating) {this.requiredSafetyRating = requiredSafetyRating;} // inline function to set the required safety rating, setter

    public Zone(String name, String requiredSafetyRating, char zoneCode) { // constructor for the zone
        setName(name); // uses the setter to set the name
        setRequiredSafetyRating(requiredSafetyRating); // uses the setter to set the required safety rating
        setZoneCode(zoneCode); // uses the setter to set the zone code
    }
    public String toString() { // toString function for the zone, this will be used for representing the class in a string
        String s = getZoneCode() + ": " + getName() + " Zone (" + getRequiredSafetyRating() + " risk) :\n----------------\n"; // ___ Zone :
        // for (int i = 0; i < getAnimals().length; i++) {
        for (int i = 0; i < getAnimals().size(); i++) { // loops through the animals, adding them to the string. Only goes until the last added animal
            s += " >>  " + getAnimals().get(i) + "\n";
        }
        return s;
    }
    public void addAnimal(Animal a){ // adds an animal to the zone's list of animals, this is similar to the setter
        getAnimals().add(a); // adds the animal to the list of animals
    }
    public void removeAnimal(Animal a){ // removes an animal from the zone's list of animals, this is similar to the setter
        getAnimals().remove(a); // removes the animal from the list of animals
    }
}