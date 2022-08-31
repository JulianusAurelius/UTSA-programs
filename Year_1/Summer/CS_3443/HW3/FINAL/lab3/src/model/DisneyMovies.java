/*
 * @author Julianus
 */
package model;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.File; 

public class DisneyMovies {
    private String name;
    public String getName() {return this.name;}
    public void setName(String name) {this.name = name;}

    private ArrayList<Movies> movies;
    public ArrayList<Movies> getMovies() {return this.movies;}
    public void setMovies(ArrayList<Movies> movies) {this.movies = movies;}
    public void addMovie(Movies movie) {movies.add(movie);}
    public int getMoviesSize() {return movies.size();}
    public Movies getMovie(int index) {return movies.get(index);}

    public DisneyMovies(String name) {
        setMovies(new ArrayList<Movies>());
        setName(name);
    }

    public void loadMovies(String filename) throws IOException {
        File file = new File(filename);
        try {
            Scanner input = new Scanner(file);
            while (input.hasNextLine()) {
                String data = input.nextLine();
                String[] vals = data.split(",");
                String title = vals[0];
                String uniqueID = vals[1];
                String genre = vals[2];
                addMovie(new Movies(title, uniqueID, genre));
            }
            input.close();
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void loadCast(String filename) throws IOException {
        File file = new File(filename);
        try {
            Scanner input = new Scanner(file);
            while (input.hasNextLine()) {
                String data = input.nextLine();
                String[] vals = data.split(",");
                String c_name = vals[0];
                String r_name = vals[1];
                String role = vals[2];
                String uniqueID = vals[3];
                String nationality = vals[4];
                Cast curr_cast = new Cast(c_name, r_name, role, nationality);
                
                for (int i=0; i<getMoviesSize(); i++) {
                    if(getMovie(i).getUniqueID().equalsIgnoreCase(uniqueID)) {
                        getMovie(i).addCast(curr_cast);
                        break;
                    }
                }
            }
            input.close();
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public ArrayList<Movies> searchMovies(String substring) {
        ArrayList<Movies> results = new ArrayList<Movies>();
        for (int i=0; i<getMoviesSize(); i++) {
            if(getMovie(i).getName().contains(substring)) {
                results.add(getMovie(i));
            }
        }
        return results;
    }
}