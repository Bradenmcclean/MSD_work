package com.example.chatphoneapp;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.google.gson.Gson;
import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketAdapter;
import com.neovisionaries.ws.client.WebSocketFactory;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
public class ChatRoom extends AppCompatActivity implements MyRecyclerViewAdapter.ItemClickListener {
    MyRecyclerViewAdapter adapter;
    private  ArrayList<String> talkingPoints = new ArrayList<>();
    private   String ipAdress = "ws://10.0.2.2:8080";
    private WebSocket webSocketBoi;
    private String userName;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_room);
        Intent intent = getIntent();
        String roomName = intent.getStringExtra(MainActivity.ROOM);
        String username = intent.getStringExtra(MainActivity.USERNAME);
        userName= username;
        TextView textView = findViewById(R.id.chatRoom);
        textView.setText(roomName);
        RecyclerView recyclerView = findViewById(R.id.rvAnimals);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        adapter = new MyRecyclerViewAdapter(this, talkingPoints);
        adapter.setClickListener(this);
        recyclerView.setAdapter(adapter);
        WebSocketFactory factory = new WebSocketFactory();
        try
        {
            WebSocket ws = factory.createSocket(ipAdress);
            webSocketBoi = ws;
            ws.connectAsynchronously();
            ws.addListener(new WebSocketAdapter() {
                @Override
                public void onConnected(WebSocket ws, Map<String, List<String>> headers ) throws Exception
                {
                    ws.sendText("join " + roomName);
//                    System.out.println("here too");
                }
            });
            ws.addListener(new WebSocketAdapter() {
                @Override
                public void onTextMessage(WebSocket websocket, String message) throws Exception
                {
                    Gson gson = new Gson();
                    Message messageObj= gson.fromJson(message, Message.class);
                    System.out.println(messageObj.user);
                    System.out.println(messageObj.message);
                    talkingPoints.add(messageObj.user + ": " + messageObj.message);
                    adapter.notifyDataSetChanged();
//                    System.out.println("Yhere");
                }
            });
            ws.addListener(new WebSocketAdapter()
            {
                @Override
                public void onTextMessage(WebSocket websocket, String message) throws Exception
                {
                    System.out.println(message);
                }
            });
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }
    @Override
    public void onItemClick(View view, int position)
    {
        Toast.makeText(this, "You clicked " + adapter.getItem(position) + " on row number " + position, Toast.LENGTH_SHORT).show();
    }
    public void sendMessage(View view)
    {
        TextView textview = findViewById(R.id.newMessage);
        String message = textview.getText().toString();
        webSocketBoi.sendText(userName + " " + message);
    }
}