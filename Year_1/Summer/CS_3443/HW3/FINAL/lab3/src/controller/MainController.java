/**
 * @author Julianus
 */
package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import model.Cast;
import model.DisneyMovies;
import model.Movies;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

public class MainController {
	@FXML
	private TextField textbox;
	@FXML
	private TextArea retVal;
	
	String text = "";
	
	@FXML
	private void handleButton(ActionEvent event) throws IOException {
		
		retVal.clear();
		
		DisneyMovies Dmovies = new DisneyMovies("Disney Movies 2019");
		Dmovies.loadMovies("data/movies.csv");
		Dmovies.loadCast("data/characters.csv");
		ArrayList<Movies> searchRes =  Dmovies.searchMovies(textbox.getText());
		if (searchRes.isEmpty()) {
			retVal.setText("There is no data containing your search, try again.");
		}
		else {
			
			searchRes.forEach( (movie) -> { text+=movie.toString(); } );
			retVal.setText(text);
		}
	}
	
}
