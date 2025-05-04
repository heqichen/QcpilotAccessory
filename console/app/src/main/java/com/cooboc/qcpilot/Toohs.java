package com.cooboc.qcpilot;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.util.Log;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.nio.charset.StandardCharsets;

public class Toohs {
    private class Worker implements Runnable {

        private byte[] buffer_ = null;

        public Worker() {
            this.buffer_ = new byte[0];
        }

        @Override
        public void run() {
            InetAddress inetGroup;
            MulticastSocket socket;
            Log.e("QC", "init the UDP multicast");
            try {
                inetGroup = InetAddress.getByName("239.238.237.236");
                socket = new MulticastSocket(1900);
                socket.setLoopbackMode(false);
                socket.joinGroup(inetGroup);
                // socket.setSoTimeout(50);
            } catch (Exception e) {
                inetGroup = null;
                socket = null;
                Log.e("QC", "join group failed", e);
            }
            while (true) {
                // receive data
                byte[] buf = new byte[1024];
                if ((inetGroup == null) || (socket == null)) {
                    Log.e("QC", "init socket failed, cannot receive");
                } else {
                    DatagramPacket packet = new DatagramPacket(buf, buf.length);
                    try {
                        socket.receive(packet);
                        synchronized (this) {
                            // copy data
                            this.buffer_ = new byte[packet.getLength()];
                            for (int i=0; i< packet.getLength(); ++i) {
                                this.buffer_[i] = buf[i];
                            }
                        }
                    } catch (Exception e) {
                        Log.e("QC", "Read socket error", e);
                    }
                }
            }
        }

        public byte[] getPacket() {
            byte[] ret = null;
            synchronized(this) {
                ret = this.buffer_;
            }
            return ret;

        }
    }

    private Worker worker_;
    public Toohs() {
        this.worker_ = new Worker();
    }

    public void init() {

        Thread t = new Thread(this.worker_);
        t.start();
    }

    public byte[] recv() {
        return this.worker_.getPacket();
    }


    public void destroy() {


    }
}
