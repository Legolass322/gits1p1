//package com.company;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class Task {
    public static void main(String[] args) throws IOException {
        ArrayList<Box> boxes = new ArrayList<>();
        int maxLength = 0;

        // Reading
        char[] cb = new char[1024];
//        FileReader fileIn = new FileReader("C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment3\\input.txt");
        FileReader fileIn = new FileReader("input.txt");
        int read = fileIn.read(cb);
        String input = new String(cb).substring(0, read);
        fileIn.close();
        
        // Parsing
        input = input.replace("] [", ",");
        input = input.substring(1, input.length() - 1);
        Scanner in = new Scanner(input);

        in.useDelimiter(",");
        while(in.hasNext()) {
            boxes.add(new Box(in.next()));
        }
        in.close();

        // Algorithm
        for (int i = 0; i < 3; i++) {
            Collections.sort(boxes, new Sortbycol(i));

            ArrayList<Box> tempBoxes = new ArrayList<>();
            ArrayList<Integer> tempInt = new ArrayList<>();

            tempBoxes.add(new Box(0, 0, 0));
            tempBoxes.get(0).clone(boxes.get(0));
            tempInt.add(1);

            for (int ibox = 1; ibox < boxes.size(); ibox++) {
                Box currentBox = boxes.get(ibox);
                boolean flag = true;

                for (int tmpCounter = 0; tmpCounter < tempBoxes.size(); tmpCounter++) {
                    if (Box.compare(currentBox, tempBoxes.get(tmpCounter)) == 1) {
                        flag = false;
                        tempBoxes.get(tmpCounter).clone(currentBox);
                        tempInt.set(tmpCounter, tempInt.get(tmpCounter) + 1);
                    }
                }
                if (flag) {
                    tempBoxes.add(new Box(0, 0, 0));
                    tempBoxes.get(tempBoxes.size() - 1).clone(currentBox);
                    tempInt.add(1);
                }
            }
            maxLength = Math.max(maxLength, Collections.max(tempInt));
        }

        // Output
//        System.out.println(maxLength);
//        FileWriter fileout = new FileWriter("C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment3\\output.txt");
        FileWriter fileout = new FileWriter("output.txt");
        fileout.write(new String(String.valueOf(maxLength)));
        fileout.close();
    }
}

class Box {
    private int[] size;
    public Box(int a, int b, int c) {
        this.size = new int[]{a, b, c};
        Arrays.sort(this.size);
    }

    public Box(String str) {
        Scanner scan = new Scanner(str);
        this.size = new int[]{scan.nextInt(), scan.nextInt(), scan.nextInt()};
        Arrays.sort(this.size);
    }

    public static int compare(Box b1, Box b2) {
        if (b1.size[0] > b2.size[0] && b1.size[1] > b2.size[1] && b1.size[2] > b2.size[2])
            return 1;
        if (b1.size[0] < b2.size[0] && b1.size[1] < b2.size[1] && b1.size[2] < b2.size[2])
            return -1;
        return 0;
    }

    public static int compare(String strB1, String strB2) {
        return Box.compare(new Box(strB1), new Box(strB2));
    }

    public int getSide(int i) {
        return this.size[i];
    }

    public void clone(Box box) {
        for (int i = 0; i < 3; i++) this.size[i] = box.getSide(i);
    }

    @Override
    public String toString() {
        return String.format("%d %d %d", this.size[0], this.size[1], this.size[2]);
    }
}

class Sortbycol implements Comparator<Box> {
    private int col;
    public Sortbycol(int col) {
        this.col = col;
    }
    public int compare(Box a, Box b) {
        return a.getSide(col) - b.getSide(col);
    }
}