#!/bin/bash
JAVAFX_PATH="/Users/sakib/Downloads/javafx-sdk-25.0.2/lib"

echo "Compiling..."
javac --module-path "$JAVAFX_PATH" --add-modules javafx.controls,javafx.fxml TicTacToeApp.java TicTacToeController.java

if [ $? -eq 0 ]; then
    echo "Running..."
    java --module-path "$JAVAFX_PATH" --add-modules javafx.controls,javafx.fxml TicTacToeApp
else
    echo "Compilation failed."
fi
