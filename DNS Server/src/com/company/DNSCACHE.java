package com.company;

import java.util.HashMap;
import java.util.Map;

public class DNSCACHE
{
    public  HashMap<String , DNSRecord> responseRecord=new HashMap<>();
    void killOld()
    {
        for (Map.Entry<String, DNSRecord> set :
                responseRecord.entrySet())
        {

                if (set.getValue().timestampValid())
                {
                    responseRecord.remove(set.getKey());
                }


        }
    }
}
