package Model;

public class User {
    public int id;
    public String userName;
    public String password;
    public String fullname;
    public String lastname;
    public String status;
    public String contactno;

   public User(String userName,String password, String fullname,  String lastname, String status, String contactno) {
        
        this.userName = userName;
        this.password = password;
        this.fullname = fullname;
        this.lastname = lastname;
        this.status = status;
        this.contactno = contactno;
    }

 public User(String userName, String fullname,  String lastname, String status, String contactno) {
        this.id = id;
        this.userName = userName;
        this.fullname = fullname;
        this.lastname = lastname;
        this.status = status;
        this.contactno = contactno;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }
   public User(int id,String userName) {
        
        this.userName = userName;
        this.id = id;
        
    }
    public User(String userName) {
       this.userName = userName;
    }

    public String getUserName() {
        return userName;
    }

    public String getPassword() {
        return password;
    }

    public String getFullname() {
        return fullname;
    }

    public String getLastname() {
        return lastname;
    }

    public String getStatus() {
        return status;
    }

    public String getContactno() {
        return contactno;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setFullname(String fullname) {
        this.fullname = fullname;
    }

    public void setLastname(String lastname) {
        this.lastname = lastname;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public void setContactno(String contactno) {
        this.contactno = contactno;
    }
  

  
  
}
