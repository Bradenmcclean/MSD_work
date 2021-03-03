package com.company;

import java.awt.*;
import java.io.*;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Objects;

public class DNSQuestion
{
    public  byte [] type;
    public  byte [] classType;
    public  HashMap<Integer,String> questionsLocation=new HashMap<>();

   DNSQuestion()
   {

   }
    @Override
    public boolean equals(Object ob) {

        if (ob == this)
            return true;

        if (ob == null || ob.getClass() != getClass()) {
            return false;
        }

        DNSQuestion p = (DNSQuestion) ob;
        return p.toString().equals(this.toString());
    }

    @Override
    public int hashCode() {
        return Objects.hash(type.toString(), classType.toString(),questionsLocation.toString());
    }

    @Override
    public String toString() {
       String typeString = null;
        for (int i=0;i<type.length;i++)
        {
            typeString+=(type[i]+" ");
        }
        String classtypeString = null;
        for (int i=0;i<classType.length;i++)
        {
            classtypeString+=(classType[i]+" ");
        }
        String questionLocations=questionsLocation.toString();
        return "{" + classtypeString + ", " + typeString + questionLocations +"}";
    }

    DNSQuestion(byte [] type,byte [] classType,HashMap<Integer,String> questionsLocation)
    {
        this.type=type;
        this.classType=classType;
        this.questionsLocation=questionsLocation;
    }
     DNSQuestion decodeQuestion(InputStream input, DNSMessage message) throws IOException
    {
        int numbertoRead=0;
        int locationNumber=0;
//        reader.readNBytes(Message.DNSHeader.header.length);

        numbertoRead=input.readNBytes(1)[0];
        locationNumber=message.head.header.length;
        while (numbertoRead!=0)
        {
            String url="";
//            System.out.println(Integer.toString((int)numbertoRead));
            url+=numbertoRead+" ";
            int oldNumber=numbertoRead;
            byte [] newLine=input.readNBytes(numbertoRead);
            numbertoRead=(int)input.readNBytes(1)[0];

            for (int i=0;i<newLine.length;i++)
            {

               url=url+Integer.toString((int)newLine[i])+" ";

            }
//            System.out.println(url+ " "+locationNumber);
            message.question.questionsLocation.put(locationNumber,url);
            locationNumber+=oldNumber+1;



        }
        message.question.type=input.readNBytes(2);
        message.question.classType=input.readNBytes(2);
//        System.out.println(message.question.type[0]);
//        System.out.println(message.question.type[1]);
//        System.out.println(message.question.classType[0]);
//        System.out.println(message.question.classType[1]);
//        System.out.println("end of Question");
        return message.question;
    }
    void writeBytes(ByteArrayOutputStream stream, DNSMessage request,HashMap<String,Integer> compresionChecker) throws IOException
    {
        int bitLocation=12;
        while(!(request.question.questionsLocation.isEmpty()))
        {

            String wholeQuestion = request.question.questionsLocation.get(bitLocation);
            request.question.questionsLocation.remove(bitLocation);
            String [] questions=wholeQuestion.split(" ");
            compresionChecker.put(wholeQuestion,bitLocation);
            for (int i=0;i<questions.length;i++)
            {
                bitLocation+=1;
                int insert=Integer.parseInt(questions[i]);
//                System.out.println(insert);
                stream.write(insert);
            }
//            System.out.println(bitLocation);
        }
        stream.write(0);
        stream.write(type);
        stream.write(classType);




    }

}


