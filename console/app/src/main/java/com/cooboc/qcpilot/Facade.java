package com.cooboc.qcpilot;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

import android.util.Log;

public class Facade {
    private Toohs toohs;
    private int c = 0;

    public Facade() {
        toohs = new Toohs();
        toohs.init();
    }

    public byte[] fun() {
        return toohs.recv();
    }

    public long getLastReceivedElapsedMillis() {
        return toohs.getLastReceivedElapsedMillis();
    }

    private void mock() {

        try {
            //here you must put your computer's IP address.
            InetAddress serverAddr = InetAddress.getByName("10.1.99.69");
            Log.d("QC", "C: Connecting...");
            //create a socket to make the connection with the server
            Socket socket = new Socket(serverAddr, 1900);


//            PrintWriter mBufferOut;
//            //sends the message to the server
//            mBufferOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
//            BufferedReader mBufferIn;
//            //receives the message which the server sends back
//            mBufferIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//

            byte[] buff = new byte[1024];
            int byteLen = -1;
            do {
                byteLen = socket.getInputStream().read(buff);
                Log.e("QC", "S: Received Message: '" + String.valueOf(byteLen) + "'");
            } while (byteLen >= 0);


            Log.e("QC", "receive end");
            socket.close();

        } catch (Exception e) {
            Log.e("TCP", "TCP Error", e);
        }

    }
}
