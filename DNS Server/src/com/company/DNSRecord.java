package com.company;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.Calendar;
import java.util.HashMap;

public class DNSRecord
{
    public  byte [] answer;
    byte [] typeAndClass=new byte[4];
    byte [] timeToLive=new byte[4];
    byte [] dataLength=new byte[4];
    byte[] ipAdress;
    public  byte [] restOfMessage;
    public  Calendar time;
    DNSRecord()
    {
        Calendar calendar = Calendar.getInstance();
        time=calendar;

    }

     DNSRecord decodeRecord(InputStream input, DNSMessage message) throws IOException
    {
        int count=0;
    while(true)
        {
        byte[] compressonChecker = input.readNBytes(2);


//                System.out.println(Integer.toString(compressonChecker[i]));
            if (compressonChecker[0] == -64)
            {
                System.out.println("Answer is Compressed");
            } else
            {

                byte[] rest = input.readNBytes(9);
                byte[] allByteArray = new byte[rest.length + compressonChecker.length];

                ByteBuffer buff = ByteBuffer.wrap(allByteArray);
                buff.put(compressonChecker);
                buff.put(rest);
                message.record.restOfMessage = buff.array();
                return message.record;
            }
        message.record.answer = compressonChecker;
        message.record.typeAndClass = input.readNBytes(4);
        message.record.timeToLive = input.readNBytes(4);
        message.record.dataLength = input.readNBytes(2);
        int ipSize = message.record.dataLength[1] | message.record.dataLength[0] << 8;
//            System.out.println(ipSize);
        message.record.ipAdress = input.readNBytes(ipSize);
        int timetoLIVE = (((timeToLive[0] & 0xFF) << 24) | ((timeToLive[1] & 0xFF) << 16) | ((timeToLive[2] & 0xFF) << 8) | ((timeToLive[3] & 0xFF)));
        System.out.println(timetoLIVE);
        time = Calendar.getInstance();
        time.add(Calendar.SECOND, timetoLIVE);
        System.out.println(time.getTime());

//            message.record.restOfMessage=input.readNBytes(11);
        }
//            return message.record;
    }
    void writeBytes(ByteArrayOutputStream out)
    {
        if (answer!=null)
        {
            for (int i = 0; i < answer.length; i++)
            {
                out.write(answer[i]);
            }

            for (int i = 0; i < typeAndClass.length; i++)
            {
                out.write(typeAndClass[i]);
            }
            for (int i = 0; i < timeToLive.length; i++)
                out.write(timeToLive[i]);

            for (int i = 0; i < dataLength.length; i++)
                out.write(dataLength[i]);

            for (int i = 0; i < ipAdress.length; i++)
                out.write(ipAdress[i]);
        }
        for (int i=0;i<restOfMessage.length;i++)
            out.write(restOfMessage[i]);
    }
    boolean timestampValid()
    {
        Calendar calendar = Calendar.getInstance();

        if (time.compareTo(calendar)==1)
        {
            return false;
        }
        return true;
    }
}
