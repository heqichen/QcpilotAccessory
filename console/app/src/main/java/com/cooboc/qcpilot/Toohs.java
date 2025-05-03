package com.cooboc.qcpilot;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.util.Log;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.nio.charset.StandardCharsets;

public class Toohs {

    private  InetAddress group_;
    private MulticastSocket socket_;

    public Toohs() {

    }
    public void init() {
        Log.e("QC", "init the shott");
        try {
            this.group_ = InetAddress.getByName("239.238.237.236");
            this.socket_ = new MulticastSocket(1900);
            this.socket_.setLoopbackMode(false);
            this.socket_.joinGroup(this.group_);

            Log.e("QC", "join group OK");
            int beforeTimeout = this.socket_.getSoTimeout();
            this.socket_.setSoTimeout(500);
            int afterTimeout = this.socket_.getSoTimeout();
            Log.e("QC", "timeout: " + String.valueOf(beforeTimeout) + " " +String.valueOf(afterTimeout));
        } catch (Exception e) {
            this.group_ = null;
            this.socket_ = null;
            Log.e("QC", "join group failed", e);
        }
    }

    public byte[] recv() {
        byte[] buf = new byte[1024];
        Log.d("QC", "start receive");
        if ((this.group_ == null) || (this.socket_ == null)) {
            Log.e("QC", "init socket failed, cannot receive");
        } else {

            DatagramPacket packet = new DatagramPacket(buf, buf.length);
            try {
                Log.e("QC", "before receive");
                this.socket_.receive(packet);
                Log.e("QC", "after receive: " + String.valueOf(packet.getLength()));
            } catch (Exception e) {
                Log.e("QC", "Read socket error", e);
            }
        }
        return buf;
    }



    public void destroy () {
        if ((this.socket_ != null) && (this.group_ != null)) {
            try {
                this.socket_.leaveGroup(this.group_);
            } catch (Exception e){}
        }

    }
}
