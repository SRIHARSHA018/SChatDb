/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Model;

import java.sql.Timestamp;  

/**
 *
 * @author ravip
 */
public class Groups {
    public int id;

   
      public String groupname;
    public String description ;
    public String  participants;
    public int status;
    public Timestamp timestamp;

    public Groups( int id,String groupname, String description, String participants, int status, Timestamp timestamp) {
     this.id =id;
     this.groupname = groupname;
     this.description = description;
     this.participants = participants;
     this.status = status;
     this.timestamp = timestamp;
    }

    public Groups(int id, String groupname) {
     this.id =id;
     this.groupname = groupname;  
    }
    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }
    public String getGroupname() {
        return groupname;
    }

    public String getDescription() {
        return description;
    }

    public String getParticipants() {
        return participants;
    }

    public int getStatus() {
        return status;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }

    public void setGroupname(String groupname) {
        this.groupname = groupname;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setParticipants(String participants) {
        this.participants = participants;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public void setTimestamp(Timestamp timestamp) {
        this.timestamp = timestamp;
    }
   
}
