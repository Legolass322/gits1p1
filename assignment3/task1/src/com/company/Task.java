//package com.company;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Task {
    public static void main(String[] args) throws IOException {
        int hours, minutes;
        int hAngle, mAngle;

//        Scanner in = new Scanner(new File("C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment3\\input.txt"));
        Scanner in = new Scanner(new File("input.txt"));

        in.useDelimiter(":");

        hours = in.nextInt();
        minutes = in.nextInt();

        in.close();

        FileWriter out = new FileWriter("output.txt");
//        FileWriter out = new FileWriter("C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment3\\output.txt");

        if (!isCorrectFormat(hours, minutes)) {
            out.write("Wrong format");
            out.close();
            System.exit(0);
        }

        hAngle = (hours % 12) * (360 / 12);
        mAngle = (minutes % 60) * (360 / 60);

        out.write(new String(String.valueOf(Math.min(360 - Math.abs(hAngle - mAngle), Math.abs(hAngle - mAngle)))) );
        out.close();
    }

    private static boolean isCorrectFormat(int hours, int minutes) {
        return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
    }
}