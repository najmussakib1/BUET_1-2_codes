import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.Node;

public class TicTacToeController {

    @FXML
    private Label statusLabel;

    @FXML
    private GridPane gameGrid;

    private boolean isPlayerX = true; // True for X, False for O
    private boolean gameEnded = false;
    private int movesCount = 0;

    @FXML
    public void initialize() {
        resetGame();
    }

    @FXML
    public void handleButtonClick(ActionEvent event) {
        if (gameEnded) return;

        Button clickedButton = (Button) event.getSource();

        if (!clickedButton.getText().isEmpty()) return;

        if (isPlayerX) {
            clickedButton.setText("X");
            clickedButton.setStyle("-fx-text-fill: #1877f2; -fx-font-size: 36px; -fx-font-weight: bold;");
        } else {
            clickedButton.setText("O");
            clickedButton.setStyle("-fx-text-fill: #42b72a; -fx-font-size: 36px; -fx-font-weight: bold;");
        }

        movesCount++;

        if (checkWin()) {
            statusLabel.setText("Player " + (isPlayerX ? "X" : "O") + " Wins!");
            gameEnded = true;
        } else if (movesCount == 9) {
            statusLabel.setText("It's a Draw!");
            gameEnded = true;
        } else {
            isPlayerX = !isPlayerX;
            statusLabel.setText("Player " + (isPlayerX ? "X" : "O") + "'s Turn");
        }
    }

    private boolean checkWin() {
        String[][] board = new String[3][3];
        int row = 0;
        int col = 0;

        // Populate the board array from the GridPane children
        // Note: GridPane children order is not guaranteed, so we must rely on constraints
        for (Node node : gameGrid.getChildren()) {
            if (node instanceof Button) {
                Integer r = GridPane.getRowIndex(node);
                Integer c = GridPane.getColumnIndex(node);
                // Handle nulls as 0 (default)
                if (r == null) r = 0;
                if (c == null) c = 0;
                
                Button btn = (Button) node;
                board[r][c] = btn.getText();
            }
        }

        // Check Rows
        for (int i = 0; i < 3; i++) {
            if (!board[i][0].isEmpty() && board[i][0].equals(board[i][1]) && board[i][0].equals(board[i][2])) {
                return true;
            }
        }

        // Check Columns
        for (int i = 0; i < 3; i++) {
            if (!board[0][i].isEmpty() && board[0][i].equals(board[1][i]) && board[0][i].equals(board[2][i])) {
                return true;
            }
        }

        // Check Diagonals
        if (!board[0][0].isEmpty() && board[0][0].equals(board[1][1]) && board[0][0].equals(board[2][2])) {
            return true;
        }
        if (!board[0][2].isEmpty() && board[0][2].equals(board[1][1]) && board[0][2].equals(board[2][0])) {
            return true;
        }

        return false;
    }

    @FXML
    public void handleReset(ActionEvent event) {
        resetGame();
    }

    private void resetGame() {
        isPlayerX = true;
        gameEnded = false;
        movesCount = 0;
        statusLabel.setText("Player X's Turn");

        for (Node node : gameGrid.getChildren()) {
            if (node instanceof Button) {
                ((Button) node).setText("");
            }
        }
    }
}
