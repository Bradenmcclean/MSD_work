package com.company;

import java.io.*;
import java.util.HashMap;

public class DNSMessage
{
    public  DNSHeader head;
    public  DNSQuestion question=new DNSQuestion();
    public  DNSRecord record=new DNSRecord();


    DNSMessage decodeMessage(byte[] bytes) throws Exception
    {
        InputStream input=new ByteArrayInputStream(bytes);
        head= new DNSHeader();
        head.decodeHeader(input);
        question.decodeQuestion(input,this);
        record.decodeRecord(input,this);
        return this;

    };
    void writeBytes(ByteArrayOutputStream out) throws IOException
    {
        head.buildResponseHeader(this);
        head.writeBytes(out);
        HashMap<String,Integer> compresionChecker=new HashMap<String,Integer>();
        question.writeBytes(out,this,compresionChecker);
        record.writeBytes(out);

    }



}
