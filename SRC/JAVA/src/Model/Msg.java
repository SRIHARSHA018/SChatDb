package Model;

import java.sql.Timestamp;


public class Msg {
     public int id;
    public String message;
    public int senderid;
     public int receiver_id;
     public int status;
    public Timestamp timestamp;

    public Msg(int aInt, String string, int aInt0, int aInt1, int aInt2, Timestamp timestamp) {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    public Msg() {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public void setSenderid(int senderid) {
        this.senderid = senderid;
    }

    public void setReceiver_id(int receiver_id) {
        this.receiver_id = receiver_id;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public void setTimestamp(Timestamp timestamp) {
        this.timestamp = timestamp;
    }

    public int getId() {
        return id;
    }

    public String getMessage() {
        return message;
    }

    public int getSenderid() {
        return senderid;
    }

    public int getReceiver_id() {
        return receiver_id;
    }

    public int getStatus() {
        return status;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }
    
    
}
