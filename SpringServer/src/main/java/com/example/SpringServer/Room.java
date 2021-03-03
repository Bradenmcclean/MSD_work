package com.example.SpringServer;

import com.fasterxml.jackson.databind.util.JSONPObject;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketMessage;
import org.springframework.web.socket.WebSocketSession;

import java.io.IOException;
import java.net.Socket;
import java.net.http.WebSocket;
import java.util.ArrayList;
import java.util.HashMap;

public class Room
{
    HashMap<String, WebSocketSession> usersSockets = new HashMap<>();
    public ArrayList<String> users = new ArrayList<>();
    SimpMessagingTemplate simpMessage;

    Room(String user, WebSocketSession ws)
    {
        usersSockets.put(user, ws);
        users.add(user);
    }

    public void addUser(String user, WebSocketSession ws)
    {
        usersSockets.put(user, ws);
        users.add(user);
    }
    public synchronized void chatty(String message,String user) throws IOException
    {
        TextMessage text=new TextMessage(message);

        for (int i=0;i<users.size();i++)
        {
            usersSockets.get(users.get(i)).sendMessage(text);
            System.out.println(users.get(i));
        }

    }

}
