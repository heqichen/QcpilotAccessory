package com.cooboc.qcpilot;

public class Facade {
    private int c = 0;

    public int fun() {
        this.c+=5;
        return this.c;
    }
}
