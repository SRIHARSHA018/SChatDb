package Server;

import Controller.Controller;
import Model.Message;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.io.OutputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;

public class Server {
    private static ArrayList<ClientHandler> clients = new ArrayList<ClientHandler>();
       
         OutputStream outputStream;
	static ObjectOutputStream objectOutputStream;
    
    public  static void main(String[] args) {
       //   OutputStream outputStream;
	//ObjectOutputStream objectOutputStream;
        ServerSocket serverSocket;
        Socket socket;
        try {
            serverSocket = new ServerSocket(8889);
            while(true) {
                 
                System.out.println("Waiting for clients...");
                socket = serverSocket.accept();
                System.out.println("Connected");
          //      outputStream = socket.getOutputStream();
		//objectOutputStream = new ObjectOutputStream(outputStream);
                
                ClientHandler clientThread = new ClientHandler(socket, clients);
                clients.add(clientThread);
                clientThread.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
  
}