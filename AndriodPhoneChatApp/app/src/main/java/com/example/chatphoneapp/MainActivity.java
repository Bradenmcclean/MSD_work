package com.example.chatphoneapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    public static final String ROOM = "com.example.chatphoneapp.ROOM";
    public static final String USERNAME = "com.example.chatphoneapp.USERNAME";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void sendMessage(View view)
    {
        Intent intent = new Intent(this, ChatRoom.class);
        EditText editText = (EditText) findViewById(R.id.Room);
        EditText editText2 = (EditText) findViewById(R.id.Username);
        String room = editText.getText().toString();
        String username = editText.getText().toString();
        intent.putExtra(ROOM,room);
        intent.putExtra(USERNAME,username);
        startActivity(intent);
    }
}