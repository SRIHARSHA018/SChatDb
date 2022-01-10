package Server;



import Model.Groups;
import Model.User;
import Model.Message;
import Model.Msg;
import java.lang.reflect.Array;
import java.sql.PreparedStatement;
import java.sql.ResultSet;  
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;  

public class Server1 {
   private static final String DATABASE_URL = "jdbc:postgresql://localhost:5432/Schat";
    private static final String DATABASE_USERNAME = "postgres";
    private static final String DATABASE_PASSWORD = "root";
    private static final String LOGIN_SELECT = "SELECT id FROM public.users WHERE username = ? and password = ?";
     private static final String SELECT_QUERY = "SELECT id,username,firstname,lastname, status, contactno FROM users WHERE username = ?";
     private static final String ALL_DATA = "SELECT id,username FROM users WHERE username != ?";
    private static final String INSERT_QUERY = "INSERT INTO users (username, password,firstname,lastname, contactno) VALUES (?, ?, ?, ?, ?)";
   private static final String GROUP_NAMES = "select id,group_name from public.groups where id in (select distinct p.group_id\n" +
"from public.\"Participants\" as p join public.\"users\" as u \n" +
"   on p.user_id = ? );";
   
   private static final String INSERT_GROUP ="INSERT INTO public.groups(\n" +
"		group_name, description, participants)\n" +
"	VALUES (?, ?, ?);";
  private static final String INSERT_PARTICIPANTS = "insert into public.\"Participants\"(user_id, group_id)\n" +
"SELECT cast (regexp_split_to_table(Participants, E',' ) as integer ) as users ,\n" +
"id FROM public.\"groups\"";
          
   private static final String DELETE_PAR = "DELETE FROM public.\"Participants\";";
 ArrayList<Object> data = new ArrayList();
 
 private static final String ALL_MESSAGES ="SELECT m1.message, m1.group_id, m1.status, m1.timestamp, m1.sender_id,u1.username\n" +
"	FROM public.group_messages m1 inner join public.users  u1 on m1.sender_id = u1.id and group_id = ?;";
  
  private static final String INSERT_MSGS ="INSERT INTO public.group_messages(\n" +
"	 message, group_id,sender_id,timestamp)\n" +
"	VALUES (?, ?, ?,?);";
   private static final String IND_MESSAGES ="SELECT m1.id, m1.message, m1.sender_id, m1.reciever_id, m1.timestamp,u1.username\n" +
"	FROM public.messages m1 inner join users u1 on m1.sender_id = u1.id and sender_id = ?;";
  
  private static final String INSERT__IND_MSGS ="INSERT INTO public.messages(\n" +
"	 message, sender_id, reciever_id, timestamp)\n" +
"	VALUES (?, ?, ?, ?);";
    public User get(String userName) throws SQLException {
       
       try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);

            PreparedStatement preparedStatement = connection.prepareStatement(SELECT_QUERY)) {
           preparedStatement.setString(1, userName);
             ResultSet rst = preparedStatement.executeQuery();
       while(rst.next()){
          
                  return new User(
                            rst.getString(1),
                            rst.getString(2),
                            rst.getString(3),
                            rst.getString(4),
                            rst.getString(5),
                           rst.getString(6)
                    );
       }
        }
       return null;
       }
       
       
    public int validate(String userName, String password) throws SQLException {
         int id = 0;
        try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);

            PreparedStatement preparedStatement = connection.prepareStatement(LOGIN_SELECT)) {
            preparedStatement.setString(1, userName);
            preparedStatement.setString(2, password);
             
            System.out.println(preparedStatement);
           
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                id = resultSet.getInt(1);
                
            }
        } catch (SQLException e) {  
            printSQLException(e);
        }
         return id;
    }

    public static void printSQLException(SQLException ex) {
        for (Throwable e: ex) {
            if (e instanceof SQLException) {
                e.printStackTrace(System.err);
                System.err.println("SQLState: " + ((SQLException) e).getSQLState());
                System.err.println("Error Code: " + ((SQLException) e).getErrorCode());
                System.err.println("Message: " + e.getMessage());
                Throwable t = ex.getCause();
                while (t != null) {
                    System.out.println("Cause: " + t);
                    t = t.getCause();
                }
            }
        }
    }
    public void insertRecord(String username,String password, String firstname, String lastname,String contactno ) throws SQLException {

       
        try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);

            // Step 2:Create a statement using connection object
            PreparedStatement preparedStatement = connection.prepareStatement(INSERT_QUERY)) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            preparedStatement.setString(3, firstname);
            preparedStatement.setString(4, lastname);
            preparedStatement.setString(5, contactno);
            

            System.out.println(preparedStatement);
            // Step 3: Execute the query or update query
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            // print SQL exception information
            printSQLException(e);
        }
    }
  
    public ArrayList<User> getAll(String userName) throws SQLException {
         ArrayList<User> contacts = new ArrayList();
       try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);

            PreparedStatement preparedStatement = connection.prepareStatement(ALL_DATA)) {
            preparedStatement.setString(1, userName);
             ResultSet rst = preparedStatement.executeQuery();
        while(rst.next()){
           User user = new User(
                        
                        rst.getInt(1),
                      rst.getString(2)     
                );
            contacts.add(user);
          }

        return contacts;
       
        }
    }
        public ArrayList<Groups> getGroups(int id) throws SQLException {
         ArrayList<Groups> contacts = new ArrayList();
       try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);

            PreparedStatement preparedStatement = connection.prepareStatement(GROUP_NAMES)) {
            preparedStatement.setInt(1, id);
             System.out.println(preparedStatement);
             ResultSet rst = preparedStatement.executeQuery();
             
       while(rst.next()){
            
              Groups group = new Groups(
                        
                        rst.getInt(1),
                      rst.getString(2)
                        
                );

            contacts.add(group);
          }

        return contacts;
        }
 
    }
          public void insertGroup(String groupname,String description, String participants) throws SQLException {

       
        try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);

            // Step 2:Create a statement using connection object
            PreparedStatement preparedStatement = connection.prepareStatement(INSERT_GROUP)) {
            preparedStatement.setString(1, groupname);
            preparedStatement.setString(2, description);
            preparedStatement.setString(3, participants);

            preparedStatement.executeUpdate();
            insertPartcipants();
        } catch (SQLException e) {
            // print SQL exception information
            printSQLException(e);
        }
    }
           public void insertPartcipants() throws SQLException {

       
        try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);
               
            PreparedStatement preparedStatement = connection.prepareStatement(DELETE_PAR)) {
            preparedStatement.executeUpdate();
        
        } catch (SQLException e) {
            // print SQL exception information
            printSQLException(e);
        }
        try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);
               
             PreparedStatement preparedStatement1 = connection.prepareStatement(INSERT_PARTICIPANTS)){
            preparedStatement1.executeUpdate();
        
        } catch (SQLException e) {
            // print SQL exception information
            printSQLException(e);
        }
         
    }
    
        
      
           
     public ArrayList<Message> getAllMessages(int groupid) throws SQLException
    {
        ArrayList<Message> messages = new ArrayList();

     try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);
               
            PreparedStatement preparedStatement = connection.prepareStatement(ALL_MESSAGES)) {
         System.out.println(groupid);
          preparedStatement.setInt(1, groupid);
       System.out.println(preparedStatement);
            preparedStatement.executeQuery();

        ResultSet resultSet1 = preparedStatement.executeQuery();
          while(resultSet1.next()){
            
              Message message = new Message(
                        resultSet1.getString(1),
                        resultSet1.getInt(2),
                        resultSet1.getInt(3),
                        resultSet1.getTimestamp(4),
                        resultSet1.getString(5),
                        resultSet1.getString(6)
                );

            messages.add(message);
          }

        return messages;
        
    }        
           
}
       public void insertMsgs(String message,int group_id, String sender,Timestamp timestamp) throws SQLException {
          
       int sender_id = Integer.parseInt(sender);
        try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);
         
               
            // Step 2:Create a statement using connection object
            PreparedStatement preparedStatement = connection.prepareStatement(INSERT_MSGS)) {
            preparedStatement.setString(1, message);
            preparedStatement.setInt(2, group_id);
            preparedStatement.setInt(3,sender_id);
            preparedStatement.setTimestamp(4,timestamp);
            preparedStatement.executeUpdate();
            
        } catch (SQLException e) {
            // print SQL exception information
            printSQLException(e);
        }
    }
       
       public void insertIndividualMsgs(String message,int receiver_id, int sender,Timestamp timestamp) throws SQLException {
          
       //int sender_id = Integer.parseInt(sender);
        try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);
         
               
            // Step 2:Create a statement using connection object
            PreparedStatement preparedStatement = connection.prepareStatement(INSERT__IND_MSGS)) {
            preparedStatement.setString(1, message);
            preparedStatement.setInt(2, receiver_id);
            preparedStatement.setInt(3,sender);
            preparedStatement.setTimestamp(4,timestamp);
            preparedStatement.executeUpdate();
            
        } catch (SQLException e) {
            // print SQL exception information
            printSQLException(e);
        }
    }
     public ArrayList<Message> getIndividualMessages(int sender_id) throws SQLException
             
    {
       //  int sender_id = Integer.parseInt(sender);
        ArrayList<Message> messages = new ArrayList();

     try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);
               
            PreparedStatement preparedStatement = connection.prepareStatement(IND_MESSAGES)) {
         System.out.println(sender_id);
          preparedStatement.setInt(1, sender_id);
       System.out.println(preparedStatement);
            preparedStatement.executeQuery();

        ResultSet resultSet1 = preparedStatement.executeQuery();
          while(resultSet1.next()){
            
              Message message = new Message(
                      resultSet1.getInt(1),
                        resultSet1.getString(2),
                        resultSet1.getInt(3),
                        resultSet1.getInt(4),
                        resultSet1.getTimestamp(5),
                      resultSet1.getString(6)
                       
                );

            messages.add(message);
          }

        return messages;
        
    }        
    }
     public ArrayList getAllUsers(String userName) throws SQLException {
         ArrayList contacts = new ArrayList();
       try (Connection connection = DriverManager
            .getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);

            PreparedStatement preparedStatement = connection.prepareStatement(ALL_DATA)) {
            preparedStatement.setString(1, userName);
             ResultSet rst = preparedStatement.executeQuery();
        while(rst.next()){
            
               contacts.add(rst.getString(1)+ ".." +rst.getString(2));
               
       
       }
        return contacts;
       
        }
    }
           
}
  