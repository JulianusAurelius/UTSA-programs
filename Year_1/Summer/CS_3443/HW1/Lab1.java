/**
 * Lab1 is a Java class containing a main method to run your program when completed.
 * This class will not compile until you have completed the requirements outlined in 
 * the lab description.
 * 
 * @author Professor
 * UTSA CS 3443 - Lab 1
 * Summer 2022
 */
public class Lab1 {

	public static void main( String[] args ) {
		Zoo animalKingdom = new Zoo( "Animal Kingdom Zoo", 10 );
		
		Zone m = new Zone( "Monkey", 10 );
		Zone t = new Zone( "Tiger", 2 );
		Zone l = new Zone( "Lion", 20 );
		Zone e = new Zone("Elephant", 15);
		
		Animal bubbles = new Animal( "Monkey", "Bubbles the Chimp", false );
		Animal grape = new Animal( "Monkey", "Grape Ape", false );
		Animal sher = new Animal( "Tiger", "Shere Khan", true );
		Animal tigger = new Animal( "Tiger", "Tigger", true );
		Animal aslan = new Animal( "Lion", "Aslan", true );
		Animal simba = new Animal( "Lion", "Simba", true );
		Animal christian = new Animal( "Lion", "Christian", true );
		Animal elmar = new Animal( "Elephant", "Elmar", false );

		m.addAnimal( bubbles );
		m.addAnimal( grape );
		t.addAnimal( sher );
		t.addAnimal( tigger );
		l.addAnimal( aslan );
		l.addAnimal( simba );
		l.addAnimal( christian );
		e.addAnimal(elmar);
		
		animalKingdom.addZone( m );
		animalKingdom.addZone( t );
		animalKingdom.addZone( l );
		animalKingdom.addZone( e );
		
		System.out.println(animalKingdom);
	}
}