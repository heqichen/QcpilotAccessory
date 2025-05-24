package com.cooboc.qcpilot;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;

import android.util.Log;

public class Facade {
    private Toohs toohs;
    private ArrayList<Integer> keyboardEvents;

    public Facade() {
        toohs = new Toohs();
        toohs.init();
        keyboardEvents = new ArrayList<>();
        keyboardEvents.clear();
    }

    // keyAction 1 is down, 0 is up
    public synchronized  void insertKeyboardEvent(int keyCode, int keyAction){
        keyboardEvents.add(keyCode);
        keyboardEvents.add(keyAction);
    }
    public synchronized  int[] fetchKeyboardEvents() {
        int[] ret = new int[keyboardEvents.size()];
        for (int i = 0; i<keyboardEvents.size(); ++i ) {
            ret[i] = keyboardEvents.get(i);
        }
        keyboardEvents.clear();
        return ret;
    }

    public byte[] fetchPacket() {
        return toohs.fetchPacket();
    }

    private void mock() {

        try {
            //here you must put your computer's IP address.
            InetAddress serverAddr = InetAddress.getByName("10.1.99.69");
            Log.d("QC", "C: Connecting...");
            //create a socket to make the connection with the server
            Socket socket = new Socket(serverAddr, 1900);

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
