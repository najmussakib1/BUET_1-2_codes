import javafx.animation.FadeTransition;
import javafx.animation.PauseTransition;
import javafx.animation.ScaleTransition;
import javafx.animation.SequentialTransition;
import javafx.animation.TranslateTransition;
import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.util.Duration;

public class NajmusIntroApp extends Application {

    @Override
    public void start(Stage primaryStage) {
        // Root container with CSS class
        StackPane root = new StackPane();
        root.getStyleClass().add("root");

        // Profile Card Container
        VBox profileCard = new VBox();
        profileCard.getStyleClass().add("profile-card");
        profileCard.setAlignment(Pos.CENTER);
        
        // --- Content Elements ---
        
        // Name
        Label nameLabel = new Label("Najmus Sakib");
        nameLabel.getStyleClass().add("name-label");
        
        // Title
        Label titleLabel = new Label("Software Engineer");
        titleLabel.getStyleClass().add("title-label");
        
        // University
        Label uniLabel = new Label("BUE CSE - Most Reputed University");
        uniLabel.getStyleClass().add("detail-label");
        
        // Skill
        Label skillLabel = new Label("Highly Skilled Professional");
        skillLabel.getStyleClass().add("skill-label");
        
        // Button
        Button contactBtn = new Button("View Portfolio");
        contactBtn.getStyleClass().add("action-button");
        
        // Add elements to card (initially invisible for animation)
        profileCard.getChildren().addAll(nameLabel, titleLabel, uniLabel, skillLabel, contactBtn);
        profileCard.getChildren().forEach(node -> node.setOpacity(0)); // Start invisible

        // Add card to root
        root.getChildren().add(profileCard);

        // Scene setup
        Scene scene = new Scene(root, 800, 600);
        scene.getStylesheets().add(getClass().getResource("styles.css").toExternalForm());
        
        primaryStage.setTitle("Najmus Sakib - Intro");
        primaryStage.setScene(scene);
        primaryStage.show();
        
        // --- Animations ---
        
        // 1. Fade in the card background
        FadeTransition cardFade = new FadeTransition(Duration.seconds(1), profileCard);
        cardFade.setFromValue(0);
        cardFade.setToValue(1);
        
        // 2. Animate elements sequentially
        SequentialTransition seq = new SequentialTransition();
        seq.getChildren().add(cardFade);
        
        // Helper to create entry animation for nodes
        seq.getChildren().add(createEntryAnimation(nameLabel));
        seq.getChildren().add(createEntryAnimation(titleLabel));
        seq.getChildren().add(createEntryAnimation(uniLabel));
        seq.getChildren().add(createEntryAnimation(skillLabel));
        seq.getChildren().add(createEntryAnimation(contactBtn));
        
        // Start animations after a short delay
        PauseTransition delay = new PauseTransition(Duration.seconds(0.5));
        delay.setOnFinished(e -> seq.play());
        delay.play();
        
        // Button Hover Animation
        setupButtonAnimation(contactBtn);
    }

    private SequentialTransition createEntryAnimation(javafx.scene.Node node) {
        // Fade in
        FadeTransition fade = new FadeTransition(Duration.seconds(0.6), node);
        fade.setFromValue(0);
        fade.setToValue(1);
        
        // Slide up
        TranslateTransition translate = new TranslateTransition(Duration.seconds(0.6), node);
        translate.setFromY(20);
        translate.setToY(0);
        
        // Combine (Parallel)
        javafx.animation.ParallelTransition parallel = new javafx.animation.ParallelTransition(fade, translate);
        
        // Add a slight pause before next item
        return new SequentialTransition(parallel, new PauseTransition(Duration.seconds(0.1)));
    }
    
    private void setupButtonAnimation(Button btn) {
        ScaleTransition scaleIn = new ScaleTransition(Duration.seconds(0.2), btn);
        scaleIn.setToX(1.1);
        scaleIn.setToY(1.1);
        
        ScaleTransition scaleOut = new ScaleTransition(Duration.seconds(0.2), btn);
        scaleOut.setToX(1.0);
        scaleOut.setToY(1.0);
        
        btn.setOnMouseEntered(e -> scaleIn.play());
        btn.setOnMouseExited(e -> scaleOut.play());
    }

    public static void main(String[] args) {
        launch(args);
    }
}
