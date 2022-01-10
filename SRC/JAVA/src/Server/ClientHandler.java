package Server;

import Controller.Controller;
import Controller.Room;
import Model.Message;
import Model.User;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;

public class ClientHandler extends Thread {

    private ArrayList<ClientHandler> clients;
    private Socket socket;
    private BufferedReader reader;
    private PrintWriter writer;
    private InputStream inputStream;
    private ObjectInputStream objectInputStream;
   
   Room r = new Room();
    public ClientHandler(Socket socket, ArrayList<ClientHandler> clients) throws IOException {
        this.socket = socket;
        this.clients = clients;
        this.reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            this.writer = new PrintWriter(socket.getOutputStream(), true);
           //   inputStream = socket.getInputStream();
	    //objectInputStream = new ObjectInputStream(inputStream);
            
    }

    @Override
    public void run() {
        try {
    
            String msg;
            while ((msg = reader.readLine()) != null) {
                if (msg.equalsIgnoreCase( "exit")) {
                    break;
                } 
                 for (ClientHandler cl : clients) {
                     cl.writer.println(msg);
           /*    Message messageObj = (Message) objectInputStream.readObject();
				System.out.println(messageObj.getMessage());
				r.addToChat(messageObj);*/
               
                } 
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            try {
                reader.close();
                writer.close();
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }
}