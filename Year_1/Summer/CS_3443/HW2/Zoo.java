/**
 * This file sets up zones which contain animals.
 * It has a name of the zoo, and a list of zones.
 * Main functions are the getters and setters for all the variables, the function to add a zone to the zoo, the toString function, and the constructor.
 * Other functions are loadZones, loadAnimals, relocate, and save.
 * It also has variables to save the file names it loaded zones and animals from
 * 
 * I kept many of my comments which I would otherwise delete to show some of my work and problem solving process
 * 
 * @author Julianus
 * UTSA CS 3443 - Lab 1
 * Summer 2022
 */
// import java.io.File;
import java.util.ArrayList; // imports the arraylist class so we can replace arrays with more dynamic arraylists
import java.io.*;  
import java.util.Scanner; 

public class Zoo {
    private String name; // variable is private so only the getters and setters can be used outside of the class
    public String getName() {return name;} // getter for the name
    public void setName(String name) {this.name = name;} // inline function to set the name, setter
    
    private ArrayList<Zone> zones = new ArrayList<Zone>(); // this is the arraylist of zones in the zoo
    public ArrayList<Zone> getZones() {return zones;} // getter for the zones arraylist

    public Zoo(String name) { // constructor for the zoo
        setName(name); // uses the setter to set the name
    }

    public String toString() { // toString function for the zoo, this will be used for representing the class in a string
        String s = "Welcome to the " + getName() + "!\n=============================\n\n"; // Welcome to the ___ !
        // for (int i = 0; i < getZones().length; i++) {
        for (int i = 0; i < getZones().size(); i++) { // loops through the zones, adding them to the string. Only goes until the last added zone
            s += getZones().get(i) + "\n";
        }
        return s;
    }
    public void addZone(Zone z){ // adds a zone to the zoo's list of zones
        getZones().add(z); // adds the zone to the list of zones
    }
    public void removeZone(Zone z){ // removes a zone from the zoo's list of zones
        getZones().remove(z); // removes the zone from the list of zones
    }
    
    // old attempt
    // private File zoneFile = null; // this is the file for the zones, which is a csv
    // public File getZoneFile() {return zoneFile;} // getter for the zone file
    // public void setZoneFile(File zoneFile) {this.zoneFile = zoneFile;} // inline function to set the zone file, setter

    private String zoneFile = null; // this is the file for the zones, which is a csv
    public String getZoneFile() {return zoneFile;} // getter for the zone file
    public void setZoneFile(String zoneFile) {this.zoneFile = zoneFile;} // inline function to set the zone file, setter

    public void loadZones(String fileName) throws IOException {
        File f = new File(fileName); // creates a file object from the filename
        // setZoneFile(f);
        setZoneFile(fileName); // uses the setter to set the zone file
        Scanner scan = new Scanner(f);
        // scan.useDelimiter(",");
        while (scan.hasNext()) { // while there is still a line to read
            
            // String name = scan.next();
            // String requiredSafetyRating = scan.next();
            // Zone z = new Zone(name, requiredSafetyRating);

            String line = scan.nextLine(); // load the entire line into a string
            String[] tokens = line.split(","); // split the line into tokens seperated by commas
            Zone z = new Zone(tokens[0], tokens[1], tokens[2].charAt(0)); // create a new zone with the proper values
            addZone(z);
        }
        scan.close();
    }

    // old attempt
    // private File animalFile = null; // this is the file for the animal file, which is a csv
    // public File getAnimalFile() {return animalFile;} // getter for the animal file
    // public void setAnimalFile(File animalFile) {this.animalFile = animalFile;} // inline function to set the animal file, setter

    private String animalFile = null; // this is the file for the animal file, which is a csv
    public String getAnimalFile() {return animalFile;} // getter for the animal file
    public void setAnimalFile(String animalFile) {this.animalFile = animalFile;} // inline function to set the animal file, setter

    public void loadAnimals(String fileName) throws IOException {
        File f = new File(fileName); // creates a file object from the filename
        // setAnimalFile(f);
        setAnimalFile(fileName); // uses the setter to set the animal file
        Scanner scan = new Scanner(f);
        // scan.useDelimiter(",");
        while (scan.hasNext()) {
            // String name = scan.next();
            // String zone = scan.next();
            // // boolean Carnivorous = scan.nextBoolean();
            // String Carn_str = scan.next();
            
            String line = scan.nextLine(); // load the entire line into a string
            String[] tokens = line.split(","); // split the line into tokens seperated by commas

            boolean Carnivorous;
            if (tokens[2].equals("TRUE")) { // if it's true, set our variable manually
                Carnivorous = true;
            } else {
                Carnivorous = false;
            }
            // tear apart the tokens and save them into relevant variables for future use or to match types to init a new animal
            char zoneCode = tokens[3].charAt(0);
            String zone = tokens[1];
            Animal a = new Animal(zone, tokens[0], Carnivorous, zoneCode);
            // Animal a = new Animal(zone, name, Carnivorous, zoneCode);
            // find the zone that matches the zone
            for (int i = 0; i < getZones().size(); i++) {
                // if (getZones().get(i).getName().equals(zone)) {
                if (getZones().get(i).getZoneCode() == zoneCode) { // if the *zone code* matches the zone code of the animal
                    getZones().get(i).addAnimal(a);
                    break;
                }
            }
        }
        scan.close();
    }

    public void relocate(String name, String zoneCode) { // function to relocate an animal to a new zone
        // find the animal that matches the animal's name
        // System.out.println("Relocating " + name + " to " + zoneCode);
        Animal a = null;
        boolean found = false; // this helps us end the outer loop instead of continuing to loop through the list of animals
        for (int i = 0; i < getZones().size(); i++) { // loops through the zones
            for (int j = 0; j < getZones().get(i).getAnimals().size(); j++) { // loops through the animals in the current zone
                // System.out.println(getZones().get(i).getAnimals().get(j).getName());
                if (getZones().get(i).getAnimals().get(j).getName().equals(name)) { // if the animal's name matches the name we are looking for
                    // System.out.println("Found animal");
                    a = getZones().get(i).getAnimals().get(j); // set the animal to the current animal
                    getZones().get(i).removeAnimal(a); // remove the animal from the current zone
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        // Convert zoneCode string to char
        char zone = zoneCode.charAt(0);
        a.setZoneCode(zone); // set the animal's zone code to the zone code, as a note, if the animal is never found, this will throw an error
        // find the zone that matches the zonecode
        for (int i = 0; i < getZones().size(); i++) {
            if (getZones().get(i).getZoneCode() == zone) { // if the *zone code* matches the zone code of the animal
                getZones().get(i).addAnimal(a);
                break;
            }
        }
    }

    public void save() { // function to save the current state of the zoo back into the files previously used
        // This method saves the current zones and animals back into their respective files
        try {
            // zones, in format "[Name],[Required Safety Rating],[Zone Code]"
            PrintWriter writer = new PrintWriter(getZoneFile()); // create a new print writer object, with the zone filename as the argument
            for (int i = 0; i < getZones().size(); i++) {
                writer.println(getZones().get(i).getName() + "," + getZones().get(i).getRequiredSafetyRating() + "," + getZones().get(i).getZoneCode());
                // saves data back into the zone csv file in the proper format
            }
            writer.close();

            // animals, in format "[Name],[Zone],[Carnivorous],[Zone Code]"
            writer = new PrintWriter(getAnimalFile()); // create a new print writer object, with the animal filename as the argument
            for (int i = 0; i < getZones().size(); i++) {
                for (int j = 0; j < getZones().get(i).getAnimals().size(); j++) {
                    // saves data back into the animal csv file in the proper format
                    if (getZones().get(i).getAnimals().get(j).getCarnivorous()) { // need to check if the animal is carnivorous or not so we can manually save TRUE|FALSE
                        writer.println(getZones().get(i).getAnimals().get(j).getName() + "," + getZones().get(i).getName() + "," + "TRUE" + "," + getZones().get(i).getAnimals().get(j).getZoneCode());
                    } else {
                        writer.println(getZones().get(i).getAnimals().get(j).getName() + "," + getZones().get(i).getName() + "," + "FALSE" + "," + getZones().get(i).getAnimals().get(j).getZoneCode());
                    }
                }
            }
            writer.close();
        } catch (IOException e) { // if one of the files is not found, throw an error
            System.out.println("Error saving data");
        }
    }
}