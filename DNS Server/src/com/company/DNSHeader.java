package com.company;

import java.io.*;
import java.nio.ByteBuffer;

public class DNSHeader
{
    public  byte [] header=new byte[12];
    public  byte [] ID =new byte[2];
    public  byte [] QRtoRD =new byte[1];
    public  byte [] RAtoRcode =new byte[1];
    public  byte [] QDCount =new byte[2];
    public  byte [] ANCount =new byte[2];
    public  byte [] NSCount =new byte[2];
    public  byte [] ARCount =new byte[2];
    /*
    read the header from an input stream
    (we'll use a ByteArrayInputStream
    but we will only use the basic read methods of input stream to read 1 byte,
    or to fill in a byte array, so we'll be generic).
    */


    byte[] decodeHeader(InputStream stream) throws Exception
    {
        try
        {


            ID =stream.readNBytes(2);
////            for (int i=0;i<ID.length;i++)
//            {
//                System.out.println(ID[i]);
//            }

            /*
            This section is to catch request errors that i cant deal with
            TURN OFF SECTION WHEN LOOKING AT PHYSICAL TEST
             */
            QRtoRD=stream.readNBytes(1);
//            if (QRtoRD[0]!=1)
//            {
//                System.out.println(QRtoRD[0]);
//                throw new Exception("QRtoRD Error in Request");
//            }
            RAtoRcode=stream.readNBytes(1);
//            if (RAtoRcode[0]!=0)
//            {
//                System.out.println(RAtoRcode[0]);
//                throw new Exception("RAtoRcode Error in Request");
//            }


            //CAN ADD ERROR RESPONESE TO LAST 4 Bits Later
//            RAtoRcode[0]= (byte) 0x80;


            //ASK TA ABOUT THIS!!!!!!!!!!
//            if (QRtoRA[0]!=0x81)
//            {
//                System.out.println(QRtoRA[0]);
//                throw new Exception("QRtoRA Error in Request");
//            }
            QDCount =stream.readNBytes(2);
            ANCount =stream.readNBytes(2);
            NSCount =stream.readNBytes(2);
            ARCount =stream.readNBytes(2);
            //combinding the arrays to make a header
            byte[] allByteArray = new byte[ID.length + QRtoRD.length + RAtoRcode.length+ QDCount.length + ANCount.length+ NSCount.length + ARCount.length];

            ByteBuffer buff = ByteBuffer.wrap(allByteArray);
            buff.put(ID);
            buff.put(QRtoRD);
            buff.put(RAtoRcode);
            buff.put(QDCount);
            buff.put(ANCount);
            buff.put(NSCount);
            buff.put(ARCount);

            header= buff.array();

        } catch (IOException e)
        {
            e.printStackTrace();
        }
//        String headerString="";
//        for (int i=0;i<header.length;i++)
//        {
//            headerString+=(header[i]+" ");
//        }
//        System.out.println(headerString);
        return header;

    }
     DNSHeader buildResponseHeader( DNSMessage response)
    {
        /*
            need to add some logic to the QRtoRD and RA to RCODE for error handling
            changes the request header
         */

        response.head.QRtoRD[0]= (byte) 0x81;
        response.head.RAtoRcode[0]= (byte) 0x80;
//        System.out.println(response.record.answer[0]);
        if(response.record.answer!=null)
        {

            response.head.ANCount[1] = (byte) 0x1;
        }
        byte[] allByteArray = new byte[ ID.length+response.head.QRtoRD.length + response.head.RAtoRcode.length+ QDCount.length + ANCount.length+ NSCount.length + ARCount.length];

        ByteBuffer buff = ByteBuffer.wrap(allByteArray);
        buff.put(ID);
        buff.put(response.head.QRtoRD);
        buff.put(response.head.RAtoRcode);
        buff.put(QDCount);
        buff.put(ANCount);
        buff.put(NSCount);
        buff.put(ARCount);

        response.head.header= buff.array();


        return response.head;
    }
    void writeBytes(ByteArrayOutputStream out) throws IOException
    {
        for (int i=0;i<header.length;i++)
        out.write(header[i]);

    }

    String toStrings()
    {
        String headerString="";
        System.out.println("hi");
        for (int i=0;i<header.length;i++)
        {
           headerString+=(header[i]+" ");
        }
        return headerString;
    }

}
