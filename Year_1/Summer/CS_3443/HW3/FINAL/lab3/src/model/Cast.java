/*
 * @author Julianus
 */
package model;

public class Cast {
        private String c_name;
        public String getCName() {return this.c_name;}
        public void setCName(String c_name) {this.c_name = c_name;}

        private String r_name;
        public String getRName() {return this.r_name;}
        public void setRName(String r_name) {this.r_name = r_name;}

        private String role;
        public String getRole() {return this.role;}
        public void setRole(String role) {this.role = role;}
                
        private String nationality;
        public String getNationality() {return this.nationality;}
        public void setNationality(String nationality) {this.nationality = nationality;}

        public Cast(String c_name, String r_name, String role, String nationality) {
                setCName(c_name);
                setRName(r_name);
                setRole(role);
                setNationality(nationality);
	}

	public String toString() {
                return "- " + getCName() + " " + getRole() + ", " + getRName() + " (" + getNationality() + ")\n";
	}
}
