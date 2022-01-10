package Controller;

import Model.User;
import Server.Server1;
import javafx.event.ActionEvent;
import java.io.IOException;
import java.lang.reflect.Array;
import java.net.URL;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;

import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import javafx.stage.Window;

    
public class CreateGroup implements Initializable {
    @FXML
     public Button createGroup;
    @FXML
    public TextField GroupName;
    @FXML
    public TextField GroupDesc;
    @FXML
    public ListView ListViewGroup;
    
     ObservableList selectedItems = FXCollections.observableArrayList();
     ArrayList<String> groupMembers = new ArrayList<>();
     CheckBox checkbox = new CheckBox();
     private ActionEvent event; 
     ArrayList ids = new ArrayList();
     ArrayList names = new ArrayList();
     
      public void initialize(URL location, ResourceBundle resources) {
          int index;
           Server1 Userdata = new Server1();
           ArrayList user = new ArrayList();
          
        try {
            user =Userdata.getAllUsers(Controller.username);
        } catch (SQLException ex) {
            Logger.getLogger(CreateGroup.class.getName()).log(Level.SEVERE, null, ex);
        }
            ObservableList contacts = FXCollections.observableArrayList(user);
             int i = 0;
       
      while(i<contacts.size()){
                index = contacts.get(i).toString().indexOf(".");
                ListViewGroup.getItems().add(i, contacts.get(i).toString().substring(index+2));
                ids.add(contacts.get(i).toString().substring(0, index));
                 names.add(contacts.get(i).toString().substring(index+2));
             i++;
        }
    
         ListViewGroup.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
           ListViewGroup.setOnMouseClicked(new EventHandler<Event>() {

                    @Override
                    public void handle(Event event) {
                        selectedItems =  ListViewGroup.getSelectionModel().getSelectedIndices();
                        // for(String id : contacts){
                        
                            System.out.println(selectedItems);
                    }
         });
         System.out.println(ids);
    }
        public void handleBack(ActionEvent event){
         try {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            
            Parent root1 = FXMLLoader.load(getClass().getResource("/Client/Room.fxml"));
            stage.setScene(new Scene(root1, 680, 562));
             stage.setTitle("ChatRoom");
            //stage.setOnCloseRequest( event->{
            //   System.exit(0);
            //});
            stage.setResizable(false);
            stage.show();
           
        } catch (IOException e) {
            e.printStackTrace();
        } 
        }
     public void handleCreateGroup() throws SQLException{
         	Window owner = createGroup.getScene().getWindow();
                if(GroupName.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!", 
                    "Please enter your Group name");
            return;
        }
    	
    	  
      StringBuilder buffer = new StringBuilder();
        int k; 
        int j =0;
        String CurrentID = Integer.toString(Controller.flag);
        while(j<selectedItems.size()){
          k = Integer.parseInt(selectedItems.get(j).toString());
            buffer.append(ids.get(k).toString()+",");
            j++;
          
        }
        buffer.append(CurrentID);
       // int l =buffer.lastIndexOf(",");
        String participants = buffer.toString();
        System.out.println(participants);
    	String Groupname = GroupName.getText();
    	String Groupdesc = GroupDesc.getText();
        
         Server1 insertgroup = new Server1();
        
    	insertgroup.insertGroup(Groupname, Groupdesc, participants);
         
       
    	showAlert(Alert.AlertType.CONFIRMATION, owner, "Created Successful!", 
                "Welcome Group " + GroupName.getText());
        
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


