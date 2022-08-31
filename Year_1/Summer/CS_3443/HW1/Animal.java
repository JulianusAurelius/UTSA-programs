/**
 * File for individual animals in the zoo
 * It has the name and type of the animal, and whether the animal is a carnivore or vegetarian.
 * Main functions are the getters and setters for all the variables, the toString function, and the constructor.
 * 
 * @author Julianus
 * UTSA CS 3443 - Lab 1
 * Summer 2022
 */

public class Animal {
    private String name; // variable is private so only the getters and setters can be used outside of the class
    public String getName() {return name;} // getter for the name
    public void setName(String name) {this.name = name;} // inline function to set the name, setter
    private String type; // This is what kind of animal it is (Tiger, Elephant, etc.)
    public String getType() {return type;} 
    public void setType(String type) {this.type = type;}
    private boolean Carnivorous; // boolean for whether or not the animal is carnivorous
    public boolean getCarnivorous() {return Carnivorous;}
    public void setCarnivorous(boolean Carnivorous) {this.Carnivorous = Carnivorous;}


    public Animal(String type, String name, boolean Carnivorous) { // constructor for the animal
        setName(name); // uses the setter to set the name
        setType(type); // uses the setter to set the type
        setCarnivorous(Carnivorous); // uses the setter to set whether or not the animal is carnivorous
    }
    public String toString() { // toString function for the animal, this will be used for representing the class in a string
        return getType() + " - " + getName() + " (" + (getCarnivorous() ? "Carnivore" : "Vegetarian") + ")"; // _(type)_ - _(name)_ (_(carnivorous)_) // uses a ternary operator to add Carnivore or Vegetarian to the string
    }
}