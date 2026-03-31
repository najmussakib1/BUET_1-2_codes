import javafx.fxml.FXML;

import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.Node;
public class MainController {
    @FXML
    private void handleButtonClick(ActionEvent event) {
        System.out.println("Button was clicked! Switching to second scene...");
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("second.fxml"));
            Scene scene = new Scene(loader.load(), 400, 300);
            Stage stage = (Stage)((Node)event.getSource()).getScene().getWindow();

        stage.setScene(scene);
        stage.show();
        } catch (IOException e) {
            e.printStackTrace();

        }
    }
}