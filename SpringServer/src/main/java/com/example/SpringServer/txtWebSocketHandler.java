package com.example.SpringServer;

import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.util.HashMap;

public class txtWebSocketHandler extends TextWebSocketHandler
{
    HashMap<String,Room> rooms=new HashMap<>();
    Room room=null;
    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception
    {
        String [] theMessage =message.getPayload().split(" ");
        String firstWord=theMessage[0];
        String theRest=new String();
        for (int i=1;i<theMessage.length;i++)
        {
            theRest+=theMessage[i];
        }
        if (rooms.get(firstWord)==null&&room==null)
        {
            System.out.println("Creating New Room");
             room=new Room(firstWord,session);

        }
        else if (room==null)
        {
            room=rooms.get(firstWord);
            room.addUser(theRest,session);


        }else
        {
            room.chatty(theRest,firstWord);

        }
    }
}
