package com.company;


import java.awt.dnd.DnDConstants;
import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.BitSet;


public class Main
{
    private static int serverPort = 8053;
    private static int askingPort = 53;

    public static void main(String[] args) throws Exception
    {


        //Test cases for yahoo.com
        String hexrequest = "b42e0100000100000000000003777777057961686f6f03636f6d0000010001";
        String hexresponse = "b42e8180000100030000000003777777057961686f6f03636f6d0000010001c00c000500010000000300140b6e65772d66702d73686564037767310162c010c02b0001000100000003000462890ba4c02b0001000100000003000462890ba3";
        byte[] yahoo = hexStringtoByteArray.hexStringToByteArrays(hexrequest);


        //for printing out test cases in ints
//        for (int i = 0; i < yahoo.length; i++)
//        {
//            System.out.println(yahoo[i] + "\n");
//        }





//        response.question.writeBytes(outStream,request);

//        for (int i=0;i<head.header.length;i++)
//        {
//            if (head.header[i]==yahoo[i])
//            {
//                System.out.println("GME IS GOING TO THE MOON \n");
//            }
//            else
//            {
//                System.out.println(i);
//            }
//        }

        DatagramSocket serverSocket = new DatagramSocket(serverPort);
        DNSCACHE cache=new DNSCACHE();


        System.out.println("DNS Server started");
        while (true)
        {
            //for answer
            byte [] answer=null;
            ByteArrayOutputStream output=new ByteArrayOutputStream();

            byte[] receiveData = new byte[512];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
//            for (int i=0;i<receiveData.length;i++)
//                System.out.println(Integer.toHexString(receiveData[i]));
            serverSocket.receive(receivePacket);
            receiveData = receivePacket.getData();
            System.out.println("Request received from client");
            DNSMessage request=new DNSMessage();
            request.decodeMessage(receiveData);


            InetAddress IPAddress = receivePacket.getAddress();
            int clientPort = receivePacket.getPort();
            if (cache.responseRecord.containsKey(request.question.toString()))
            {
                System.out.println("Searching cache...");
                DNSMessage cacheRespond=new DNSMessage();
                cacheRespond.head=request.head.buildResponseHeader(request);
                cacheRespond.question=request.question;
                cacheRespond.record= cache.responseRecord.get(request.question.toString());
                cacheRespond.writeBytes(output);



//                InetAddress address = InetAddress.getByName("8.8.8.8");
//                answer= output.toByteArray();
//                DatagramPacket clientPacket = new DatagramPacket(answer, answer.length, address, askingPort);
//                serverSocket.send(clientPacket);

            } else
            {


                DatagramSocket googleSocket = new DatagramSocket(askingPort);
                InetAddress address = InetAddress.getByName("8.8.8.8");
                byte[] datafromGoogle = new byte[512];


                // send packet
                DatagramPacket sendPacket = new DatagramPacket(receiveData, receiveData.length, address, askingPort);

                googleSocket.send(sendPacket);
                System.out.println("Data sent...");


                DatagramPacket googleReceive = new DatagramPacket(datafromGoogle, datafromGoogle.length);
                // received packet
                googleSocket.receive(googleReceive);
                datafromGoogle = googleReceive.getData();
//                for (int i=0;i<datafromGoogle.length;i++)
//                    System.out.println(Integer.toHexString(datafromGoogle[i]));
                DNSMessage googleMSG = new DNSMessage();
                googleMSG.decodeMessage(datafromGoogle);

                cache.responseRecord.put(googleMSG.question.toString(), googleMSG.record);

                googleMSG.writeBytes(output);


                System.out.println("......added to Cache");

                googleSocket.close();
                System.out.println("Google Connection closed");


            }
            cache.killOld();
            answer= output.toByteArray();
            DatagramPacket clientPacket = new DatagramPacket(answer, answer.length, IPAddress, clientPort);
            serverSocket.send(clientPacket);



        }
//            System.out.println("Clent sent " );
//            System.out.println("Searching cache...");






        }
}
