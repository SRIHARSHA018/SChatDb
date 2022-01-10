package Model;
import java.io.Serializable;
import java.sql.Timestamp;  
public class Message implements Serializable{
    
    public int id;
    public String message;
    public int groupId;
    public int status;
    public Timestamp timestamp;
    public String senderid;
     public int sender_id;
      public int receiver_id;

    public void setSender_id(int sender_id) {
        this.sender_id = sender_id;
    }

    public void setReceiver_id(int receiver_id) {
        this.receiver_id = receiver_id;
    }

    public int getSender_id() {
        return sender_id;
    }

    public int getReceiver_id() {
        return receiver_id;
    }
     public String username;

    public Message(String message, int groupid, int status, Timestamp timestamp, String senderid,String username) {
        this.message = message;
        this.groupId = groupid;
        this.status = status;
        this.timestamp = timestamp;
        this.senderid = senderid;
        this.username = username;
    }
     public Message(int id,String message, int sender_id, int receiver_id, Timestamp timestamp, String username) {
       this.id = id;
         this.message = message;
        this.sender_id = sender_id;
        this.receiver_id = receiver_id;
        this.timestamp = timestamp;
        this.username = username;
    }
    
     public Message(String message, int groupid, String senderid,String username) {
        this.message = message;
        this.groupId = groupid;
        this.senderid = senderid;
        this.username = username;
    }

    public Message() {
         }

 

    public void setUsername(String username) {
        this.username = username;
    }

    public String getUsername() {
        return username;
    }
    public int getId() {
        return id;
    }

    public String getMessage() {
        return message;
    }

    public int getGroupId() {
        return groupId;
    }

    public int getStatus() {
        return status;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }

    public String getSenderid() {
        return senderid;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public void setGroupId(int groupId) {
        this.groupId = groupId;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public void setTimestamp(Timestamp timestamp) {
        this.timestamp = timestamp;
    }

    public void setSenderid(String senderid) {
        this.senderid = senderid;
    }

   

  
  

}
