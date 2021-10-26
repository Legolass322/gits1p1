package com.company;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Task {
    public static void main(String[] args) throws FileNotFoundException {
        int hours, minutes;
        int hAngle, mAngle;

        Scanner in = new Scanner(new File("C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment3\\input.txt"));
//        Scanner in = new Scanner(new File("input.txt"));
        in.useDelimiter(":");

        hours = in.nextInt();
        minutes = in.nextInt();

        if (!isCorrectFormat(hours, minutes)) {
            System.out.println("Wrong format");
            System.exit(0);
        }

        hAngle = (hours % 12) * (360 / 12);
        mAngle = (minutes % 60) * (360 / 60);

        System.out.println(Math.abs(hAngle - mAngle) % 180);
    }

    private static boolean isCorrectFormat(int hours, int minutes) {
        return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
    }
}