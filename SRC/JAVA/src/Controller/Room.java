package Controller;

import javafx.embed.swing.SwingFXUtils;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.ScrollPane;
import javafx.event.Event;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Circle;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.fxml.Initializable;
import javafx.collections.ObservableList;
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.Socket;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.animation.FadeTransition;
import javafx.scene.text.TextFlow;
import javafx.util.Duration;
import Model.User;
import Server.Server1;
import Server.Server;
import java.sql.SQLException;
import static Controller.Controller.users;
import Model.Groups;
import Model.Message;
import Model.Msg;
import java.sql.Timestamp;
import java.time.Instant;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.FXCollections;
import javafx.concurrent.Task;
import javafx.concurrent.WorkerStateEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;
public class Room extends Thread implements Initializable {
    public Label clientName;
    public Button chatBtn;
    @FXML
    public Pane chat;
    public TextField msgField;
    public TextArea msgRoom;
    public Label online;
    public Label userName;
    public Label Lastname;
    public Label FullName;
    public Label phoneNo;
    public Label status;
    public Pane profile;
    public Button profileBtn;
    public Button groupBtn;
    public Button btnClose;
    private TextFlow emojiList;
    public TextField fileChoosePath;
    public ImageView proImage;
    public Circle showProPic;
    public VBox OnlineUsers;
    public VBox chatBox;
    public ListView<HBox> ChatPane;
    public ScrollPane scrollPane;
    public ListView ListView;
    public ListView GroupsListView;
    public Pane ContactsPane;
    public Pane GroupsPane;
    private FileChooser fileChooser;
    private File filePath;
    public boolean toggleChat = false, toggleProfile = false;
    public boolean toggleContacts = false, toggleGroups = false;
    private OutputStream outputStream;
    private static ObjectOutputStream objectOutputStream;
    BufferedReader reader;
    PrintWriter writer;
    Socket socket;
    ObservableList selectedItems = FXCollections.observableArrayList();
     ArrayList<User> user = new ArrayList();
     Server1 Userdata = new Server1();
     boolean dataExists = false;
     ArrayList ids = new ArrayList();
     ArrayList individualids = new ArrayList();
     ArrayList names = new ArrayList();
     int SelectedGroupID ,SelectedUserID;
     ArrayList<Message> messageSaveList = new ArrayList();
     ArrayList<Msg> messageSaveList1 = new ArrayList();
     boolean flagContacts=true,flagGroups=false;
        
      
      public void connectSocket() {
        try {
            socket = new Socket("localhost", 8889);
         //   outputStream = socket.getOutputStream();
	   // objectOutputStream = new ObjectOutputStream(outputStream);
          //  objectOutputStream.flush();
            System.out.println("Socket is connected with server!");
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            writer = new PrintWriter(socket.getOutputStream(), true);
            this.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 @Override
  public void run() {
       
        try {
                while(true){
                String msg = reader.readLine();
                if(msg!= null){
                String[] tokens = msg.split(" ");
                String cmd = tokens[0];
                System.out.println(cmd);
                StringBuilder fulmsg = new StringBuilder();
                for(int i = 1; i < tokens.length; i++) {
                    fulmsg.append(tokens[i]);
                }
                System.out.println(fulmsg);
                
                if (cmd.equalsIgnoreCase(Controller.username + ":")) {
                    continue;
                } else if(fulmsg.toString().equalsIgnoreCase("bye")) {
                    break;
                }
              //  msgRoom.appendText(msg + "\n");
                }
            }
            
          
            
        } catch (Exception e) {
            e.printStackTrace();
        }
        finally{
        try{
         reader.close();
            writer.close();
           socket.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }}
    }


      public void handleProfileBtn(ActionEvent event) throws SQLException {
        if (event.getSource().equals(profileBtn) && !toggleProfile) {
            
            new FadeTransition(Duration.millis(3000),profile).play();
            profile.toFront();
            chat.toBack();
            chatBox.setVisible(false);
            toggleProfile = true;
            toggleChat = false;
            profileBtn.setText("Back");
            setProfile();
        } else if (event.getSource().equals(profileBtn) && toggleProfile) {
            new FadeTransition(Duration.millis(3000),chat).play();
            chat.toFront();
            chatBox.setVisible(true);
            toggleProfile = false;
            toggleChat = false;
            profileBtn.setText("Profile");
        }
    }

    public void setProfile() throws SQLException {
        Server1 Userdata = new Server1();
        User users =Userdata.get(Controller.username);
   
                FullName.setText(users.fullname);
                FullName.setOpacity(1);
                Lastname.setText(users.lastname);
                Lastname.setOpacity(1);
                phoneNo.setText(users.contactno);
                status.setText(users.status);
        //    }
      //  }
    }
   
     public void AddGroups(ActionEvent event) throws SQLException{

          try {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            
            Parent root1 = FXMLLoader.load(getClass().getResource("/Client/CreateGroup.fxml"));
            stage.setScene(new Scene(root1, 479, 580));
             stage.setTitle("Group");
          
            stage.setResizable(false);
            stage.show();
           
        } catch (IOException e) {
            e.printStackTrace();
        }    
    }
    
   
       public void handleGroupsButton(ActionEvent event) throws SQLException, IOException {
        if (event.getSource().equals(groupBtn) && !toggleGroups) {
                
            new FadeTransition(Duration.millis(3000),GroupsPane).play();
            GroupsPane.toFront();
            ContactsPane.toBack();
            toggleGroups = true;
            toggleContacts = false;
            flagGroups =true;
            flagContacts =false;
            groupBtn.setText("Contacts");
            ChatPane.getItems().clear();
            if(! dataExists){
            handleGroups(event);
            }
        } else if (event.getSource().equals(groupBtn) && toggleGroups) {
            new FadeTransition(Duration.millis(3000),ContactsPane).play();
            ContactsPane.toFront();
            flagGroups =false;
            flagContacts =true;
            toggleGroups = false;
            toggleContacts = false;
            groupBtn.setText("Groups");
            ChatPane.getItems().clear();
        }
    }

      public void handleGroups(ActionEvent event) throws SQLException, IOException {
          int index;
          GroupsListView.getItems().clear();
        ArrayList<Groups> group = new ArrayList();
        int id = Controller.flag;
         group =Userdata.getGroups(id);
        ObservableList<Groups> groups = FXCollections.observableArrayList(group);
        int i = 0;
          while(i<groups.size()){ 
        
         GroupsListView.getItems().add(groups.get(i).getGroupname());
         ids.add(groups.get(i).getId());
         i++;
       }
       GroupsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
       GroupsListView.setOnMouseClicked(new EventHandler<Event>() {
            
        @Override
        public void handle(Event event) {
        ChatPane.getItems().clear();
        
        int  index = GroupsListView.getSelectionModel().getSelectedIndex();
        SelectedGroupID = (int) ids.get(index);
         ArrayList<Message> Messages = new ArrayList();
       
            try {
                Messages   =Userdata.getAllMessages(SelectedGroupID);
                for(int i = 0; i < Messages.size(); i++) {
                            addPreviousChat(Messages.get(i));
                    }
                    Messages.clear();

            } catch (SQLException ex) {
                Logger.getLogger(Room.class.getName()).log(Level.SEVERE, null, ex);
            }
      } }); 
    }
    
    public void handleSendEvent(MouseEvent event) throws SQLException, IOException {
        send();
         for(User user : users) {
            System.out.println(user.fullname);
        }
        
    }
    public void send() throws IOException, SQLException {
       
       String msg = msgField.getText();
         Timestamp t = new Timestamp(System.currentTimeMillis());
        String sender_id = Integer.toString(Controller.flag);
        if(flagGroups){
             Message messageObject;
                messageObject = new Message();
		messageObject.setMessage(msg);
		messageObject.setUsername(Controller.username);
		messageObject.setSenderid(sender_id);
                messageObject.setGroupId(SelectedGroupID);
                messageObject.setTimestamp(t);
             
              msgField.setText("");
     
        Server1 insertgroup = new Server1();
    	insertgroup.insertMsgs(msg, SelectedGroupID, sender_id,t);
         addToChat(messageObject);
        }
        else{
         Message messageObject;
                messageObject = new Message();
		messageObject.setMessage(msg);
		messageObject.setUsername(Controller.username);
		messageObject.setSender_id(Controller.flag);
                messageObject.setGroupId(SelectedUserID);
                messageObject.setTimestamp(t);
             
              msgField.setText("");
     
        Server1 insertIndividual = new Server1();
    	insertIndividual.insertIndividualMsgs(msg, SelectedUserID, Controller.flag,t);
        addToChat(messageObject);
        }
        if(msg.equalsIgnoreCase("BYE") || (msg.equalsIgnoreCase("logout"))) {
            System.exit(0);
        }
    }
    public boolean saveControl = false;
    public void chooseImageButton(ActionEvent event) {
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        fileChooser = new FileChooser();
        fileChooser.setTitle("Open Image");
        this.filePath = fileChooser.showOpenDialog(stage);
        fileChoosePath.setText(filePath.getPath());
        saveControl = true;
    }
    public void sendMessageByKey(KeyEvent event) throws IOException, SQLException {
        if (event.getCode().toString().equals("ENTER")) {
            send();
        }
    }

    public void saveImage() {
        if (saveControl) {
            try {
                BufferedImage bufferedImage = ImageIO.read(filePath);
                Image image = SwingFXUtils.toFXImage(bufferedImage, null);
                proImage.setImage(image);
                showProPic.setFill(new ImagePattern(image));
                saveControl = false;
                fileChoosePath.setText("");
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        }
    }
    public void emojiAction(ActionEvent event) {
        if(emojiList.isVisible()){

            emojiList.setVisible(false);
        }else {
            emojiList.setVisible(true);
        }
    } 
    protected void addPreviousChat(Message messageObj) {
		messageSaveList.add(messageObj);	
        if (messageObj.getUsername().equals(Controller.username)) {
            Label messageLabel = new Label();
            messageLabel.setText(messageObj.getMessage());
            messageLabel.setTextFill(Color.WHITE);
            
            Label userLabel = new Label();
            userLabel.setText(messageObj.getUsername());
            userLabel.setStyle("-fx-font-weight: bold;");
            userLabel.setTextFill(Color.WHITE);
            
            VBox vBox = new VBox(2);
            CornerRadii cornerRadi = new CornerRadii(5f);
            BackgroundFill backgroundFill = new BackgroundFill(Color.rgb(64, 128, 128), cornerRadi, null);
            vBox.setBackground(new Background(backgroundFill));
           // vBox.setPadding(new Insets(5f));
            vBox.getChildren().addAll(userLabel, messageLabel);
            
            Label dateLabel = new Label();
            dateLabel.setText(messageObj.getTimestamp().toString());
            dateLabel.setStyle("-fx-font-size: 10;");
            dateLabel.setTextFill(Color.GRAY);
            dateLabel.setAlignment(Pos.CENTER);
            dateLabel.setMaxHeight(Double.MAX_VALUE);

            HBox x = new HBox(2);
            x.setMaxWidth(ChatPane.getWidth() - 20);
            x.setAlignment(Pos.TOP_RIGHT);
            x.getChildren().addAll(dateLabel, vBox);
            
            ChatPane.getItems().add(x);
        } else {
        	
            Label messageLabel = new Label();
            messageLabel.setText(messageObj.getMessage());
            messageLabel.setTextFill(Color.BLACK);
            
            Label userLabel = new Label();
            userLabel.setText(messageObj.getUsername());
            userLabel.setStyle("-fx-font-weight: bold;");
            userLabel.setTextFill(Color.BLACK);
            
            VBox vBox = new VBox(2);
            CornerRadii cornerRadi = new CornerRadii(5f);
            BackgroundFill backgroundFill = new BackgroundFill(Color.rgb(218, 218, 218), cornerRadi, null);
            vBox.setBackground(new Background(backgroundFill));
           // vBox.setPadding(new Insets(5f));
            vBox.getChildren().addAll(userLabel, messageLabel);
            
            Label dateLabel = new Label();
            dateLabel.setText(messageObj.getTimestamp().toString());
            dateLabel.setStyle("-fx-font-size: 10;");
            dateLabel.setTextFill(Color.GRAY);
            dateLabel.setAlignment(Pos.CENTER);
            dateLabel.setMaxHeight(Double.MAX_VALUE);
            
            HBox x = new HBox(2);
            x.setMaxWidth(ChatPane.getWidth() - 20);
            x.setAlignment(Pos.TOP_LEFT);
            x.getChildren().addAll(vBox, dateLabel);
            
            ChatPane.getItems().add(x);
        }
	}
    @Override
    public void initialize(URL location, ResourceBundle resources) {
       
        showProPic.setStroke(Color.valueOf("#90a4ae"));
        Image image; 
       image = new Image("icons/user.png", false);
        showProPic.setFill(new ImagePattern(image));
        clientName.setText(Controller.username);
            this.connectSocket();  
         ListView.getItems().clear();
        try {
            user =Userdata.getAll(Controller.username);
        } catch (SQLException ex) {
            Logger.getLogger(Room.class.getName()).log(Level.SEVERE, null, ex);
        }
        int index;
       System.out.println(user);
        ObservableList<User> contacts = FXCollections.observableArrayList(user);
        int i = 0;
        System.out.println(contacts);
        while(i<contacts.size()){
           ListView.getItems().add(contacts.get(i).getUserName());
         individualids.add(contacts.get(i).getId());
         i++; 
     }
   
         ListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
         ListView.setOnMouseClicked(new EventHandler<Event>() {
            
        @Override
        public void handle(Event event) {
        ChatPane.getItems().clear();
        
        int  index = ListView.getSelectionModel().getSelectedIndex();
        SelectedUserID = (int) individualids.get(index);
         ArrayList<Message> Messages = new ArrayList();
       
            try {
                Messages   =Userdata.getIndividualMessages(SelectedUserID);
                for(int i = 0; i < Messages.size(); i++) {
                            addPreviousChat(Messages.get(i));
                    }
                    Messages.clear();

            } catch (SQLException ex) {
                Logger.getLogger(Room.class.getName()).log(Level.SEVERE, null, ex);
            }
      } }); 
       
         /* for(Node text : emojiList.getChildren()){
            text.setOnMouseClicked(event -> {
                msgField.setText(msgField.getText()+" "+((Text)text).getText());
                emojiList.setVisible(false);
            });
          }*/
    }
public synchronized void addToChat(Message messageObj) {
		
		messageSaveList.add(messageObj);
	  if (messageObj.getUsername().equals(Controller.username)) {
               Label messageLabel = new Label();
                messageLabel.setText(messageObj.getMessage());
                messageLabel.setTextFill(Color.WHITE);
                
                Label userLabel = new Label();
                userLabel.setText(messageObj.getUsername());
                userLabel.setStyle("-fx-font-weight: bold;");
                userLabel.setTextFill(Color.WHITE);
                
                VBox vBox = new VBox(2);
                CornerRadii cornerRadi = new CornerRadii(5f);
                BackgroundFill backgroundFill = new BackgroundFill(Color.rgb(64, 128, 128), cornerRadi, null);
                vBox.setBackground(new Background(backgroundFill));
              //  vBox.setPadding(new Insets(5f));
                vBox.getChildren().addAll(userLabel, messageLabel);
                
                Label dateLabel = new Label();
                dateLabel.setText(messageObj.getTimestamp().toString());
                dateLabel.setStyle("-fx-font-size: 10;");
                dateLabel.setTextFill(Color.GRAY);
                dateLabel.setAlignment(Pos.CENTER);
                dateLabel.setMaxHeight(Double.MAX_VALUE);

                HBox x = new HBox(2);
                x.setMaxWidth(ChatPane.getWidth() - 20);
                x.setAlignment(Pos.TOP_RIGHT);
                x.getChildren().addAll(dateLabel, vBox);

            
        	ChatPane.getItems().add(x);
}else{
                Label messageLabel = new Label();
                messageLabel.setText(messageObj.getMessage());
                messageLabel.setTextFill(Color.BLACK);
                
                Label userLabel = new Label();
                userLabel.setText(messageObj.getUsername());
                userLabel.setStyle("-fx-font-weight: bold;");
                userLabel.setTextFill(Color.BLACK);
                
                VBox vBox = new VBox(2);
                CornerRadii cornerRadi = new CornerRadii(5f);
                BackgroundFill backgroundFill = new BackgroundFill(Color.rgb(218, 218, 218), cornerRadi, null);
                vBox.setBackground(new Background(backgroundFill));
               // vBox.setPadding(new Insets(5f));
                vBox.getChildren().addAll(userLabel, messageLabel);
                
                
                Label dateLabel = new Label();
                dateLabel.setText(messageObj.getTimestamp().toString());
                dateLabel.setStyle("-fx-font-size: 10;");
                dateLabel.setTextFill(Color.GRAY);
                dateLabel.setAlignment(Pos.CENTER);
                dateLabel.setMaxHeight(Double.MAX_VALUE);
                
                HBox x = new HBox(2);
                x.setMaxWidth(ChatPane.getWidth() - 20);
                x.setAlignment(Pos.TOP_LEFT);
                x.getChildren().addAll(vBox, dateLabel);

               
       
            ChatPane.getItems().add(x);
          }
}
	
	
}
