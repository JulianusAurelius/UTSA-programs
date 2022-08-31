/*
 * @author Julianus
 */
package model;

import java.util.ArrayList;

public class Movies {
        private String name;
        public String getName() {return this.name;}
        public void setName(String name) {this.name = name;}
	
        private String uniqueID;
        public String getUniqueID() {return this.uniqueID;}
        public void setUniqueID(String uniqueID) {this.uniqueID = uniqueID;}

        private String genre;
        public String getGenre() {return this.genre;}
        public void setGenre(String genre) {this.genre = genre;}

        private ArrayList<Cast> cast;
        public ArrayList<Cast> getCast() {return this.cast;}
        public void setCast(ArrayList<Cast> cast) {this.cast = cast;}
        public int getCastSize() {return cast.size();}
        public void addCast(Cast cast) {this.cast.add(cast);}
                
        public Movies(String name, String uniqueID, String genre) {
                setCast(new ArrayList<Cast>());
                setName(name);
                setUniqueID(uniqueID);
                setGenre(genre);
	}
	
	public String toString() {
                return getName() + " " + getUniqueID() + ", Genre: " + getGenre() + ", Cast: " + getCastSize() + "\n" + getCast();
	}
}
