package Controller;

import Model.User;
import javafx.stage.Window;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import java.io.IOException;
import java.util.ArrayList;
import javafx.animation.FadeTransition;
import javafx.collections.ObservableList;
import javafx.scene.control.ToggleGroup;
import javafx.util.Duration;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.util.ResourceBundle;
import java.net.URL;    
import Server.Server1;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;



public class Controller {

    static int flag;
    @FXML
    public Pane pnSignIn;
    @FXML
    public Pane pnSignUp;
    @FXML
    public Button btnSignUp;
    @FXML
    public Button getStarted;
    @FXML
    public ImageView btnBack;
    @FXML
    public TextField regLastName;
    @FXML
    public TextField regPass;
    @FXML
    public TextField regFirstName;
    @FXML
    public TextField reguserName;
    @FXML
    public TextField regPhoneNo;
    @FXML
    public RadioButton male;
    @FXML
    public RadioButton female;
    @FXML
    public Label controlRegLabel;
    @FXML
    public Label success;
    @FXML
    public Label goBack;
    @FXML
    public TextField userName;
     @FXML
    public TextField clientName;
    @FXML
    public TextField passWord;
     @FXML
     public Button submitButton;
      @FXML
     private Button regButton;
    @FXML
    public Label loginNotifier;
    @FXML
    public Label nameExists;
    @FXML
    public Label checkEmail;
    
    public static String username, password, gender;
    public static ArrayList<User> loggedInUser = new ArrayList<>();
    public static ArrayList<User> users = new ArrayList<User>();
    @FXML
    private ToggleGroup Gender;
    @FXML
    private Label wrongLogIn;
    
    ObservableList<User> listU;
    
    int index = -1;
    Connection Con = null;
    ResultSet rs = null;
    PreparedStatement pstmt = null;

      
    @FXML
    public void registration(ActionEvent event) throws SQLException {
       Window owner = regButton.getScene().getWindow();
       
        if (reguserName.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!",
                "Please enter your name");
            return;
        }
         if (regFirstName.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!",
                "Please enter Name");
            return;
        }

        if (regPass.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!",
                "Please enter password");
            return;
        }
        if (regLastName.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!",
                "Please enter a email");
            return;
        }
     
        String gender;
        String userName = reguserName.getText();
        String firstname = regFirstName.getText();
        String Lastname = regLastName.getText();
        String password = regPass.getText();
        String contactno = regPhoneNo.getText();
        
        Server1 insert = new Server1();
        insert.insertRecord(userName,password,firstname,Lastname,contactno);
        goBack.setOpacity(1);
        success.setOpacity(1);
        makeDefault();
        if (controlRegLabel.getOpacity() == 1) {
            controlRegLabel.setOpacity(0);
        }
        if (nameExists.getOpacity() == 1) {
            nameExists.setOpacity(0);
        }
    }

    private void setOpacity(Label a, Label b, Label c, Label d) {
        if(a.getOpacity() == 1 || b.getOpacity() == 1 || c.getOpacity() == 1 || d.getOpacity() == 1) {
            a.setOpacity(0);
            b.setOpacity(0);
            c.setOpacity(0);
            d.setOpacity(0);
        }
    }


    private void setOpacity(Label controlRegLabel, Label checkEmail, Label nameExists) {
        controlRegLabel.setOpacity(0);
        checkEmail.setOpacity(0);
        nameExists.setOpacity(0);
    }

    private boolean checkUser(String username) {
        for(User user : listU) {
            if(user.userName.equalsIgnoreCase(username)) {
                return false;
            }
        }
        return true;
    }


    private void makeDefault() {
        regFirstName.setText("");
        regPass.setText("");
        regLastName.setText("");
        reguserName.setText("");
        regPhoneNo.setText("");
       
        setOpacity(controlRegLabel, checkEmail, nameExists);
    }


    @FXML
    public void login() throws SQLException {
        Window owner = submitButton.getScene().getWindow();
        if (userName.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!",
                "Please enter your email id");
            return;
        }
        if (passWord.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!",
                "Please enter a password");
            return;
        }
        username = userName.getText();
        password = passWord.getText();
        
        Server1 jdbcDao = new Server1();
        flag = jdbcDao.validate(username, password);
        
        
         if (flag ==0 ) {
            infoBox("Please enter correct Email and Password", null, "Failed");
        } else {
             
             changeWindow();
        }
       
    }

    public void changeWindow() {
        try {
            Stage stage = (Stage) userName.getScene().getWindow();
            
            Parent root = FXMLLoader.load(this.getClass().getResource("/Client/Room.fxml"));
            stage.setScene(new Scene(root, 680, 562));
            stage.setTitle("ChatRoom");
            stage.setOnCloseRequest(event -> {
                System.exit(0);
            });
            stage.setResizable(false);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void handleButtonAction(ActionEvent event) {
        if (event.getSource().equals(btnSignUp)) {
            new FadeTransition(Duration.millis(3000),pnSignUp).play();
            pnSignUp.toFront();
        }
        if (event.getSource().equals(getStarted)) {
            new FadeTransition(Duration.millis(3000),pnSignIn).play();
            pnSignIn.toFront();
        }
        loginNotifier.setOpacity(0);
        userName.setText("");
        passWord.setText("");
    }

    @FXML
    private void handleMouseEvent(MouseEvent event) {
        if (event.getSource() == btnBack) {
            new FadeTransition(Duration.millis(3000),pnSignIn).play();
            pnSignIn.toFront();
        }
        regFirstName.setText("");
        regPass.setText("");
        regLastName.setText("");
    }

    public static void infoBox(String infoMessage, String headerText, String title) {
        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setContentText(infoMessage);
        alert.setTitle(title);
        alert.setHeaderText(headerText);
        alert.showAndWait();
    }

    private static void showAlert(Alert.AlertType alertType, Window owner, String title, String message) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.initOwner(owner);
        alert.show();
    }
}