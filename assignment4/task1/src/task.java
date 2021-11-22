import java.io.*;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.Pattern;

public class task {
    public static void main(String[] args) throws IOException {
        String inputPath = "C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment4\\input.txt";
        String outputPath = "C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment4\\output.txt";

        File inputFile = new File(inputPath);
        if (!inputFile.isFile()) exitWithMessage(outputPath, "No such file");
        if (inputFile.length() == 0) exitWithMessage(outputPath, "file is empty");
        if (inputFile.length() > 300) exitWithMessage(outputPath, "file is long");

        Scanner scan = new Scanner(inputFile);
        String input = scan.nextLine();
        int max_width = 0;

        try { max_width = scan.nextInt(); }
        catch (NoSuchElementException e) { exitWithMessage(outputPath, "no width"); }
        if (max_width <= 0) exitWithMessage(outputPath, "improper int");

        Scanner worder = new Scanner(input);
        worder.useDelimiter(" ");
        int[] wordsperline = new int[256];
        int[] extraSymbols = new int[256];
        int currentWidth = max_width;
        int currentLine = 0;
        while (worder.hasNext()) {
            String word = worder.next();
            if (word.length() == 0) exitWithMessage(outputPath, "empty word");
            Pattern pat = Pattern.compile("^[a-zA-Z[.,!?\\-:;()'\"]]");
            if (!pat.matcher(word).matches()) exitWithMessage(outputPath, "forbidden symbol");
            if (word.length() > 20) exitWithMessage(outputPath, "20");
            if (word.length() > max_width) exitWithMessage(outputPath, "maxWidth");

            if (word.length() <= currentWidth) wordsperline[currentLine]++;
            else {
                extraSymbols[currentLine] = currentWidth;
                currentLine++;
                currentWidth = max_width;
            }
            currentWidth -= word.length() + 1;
        }


        FileWriter outputWriter = new FileWriter(outputPath);
        worder = new Scanner(input);
        worder.useDelimiter(" ");
        int line = 0;
        int remainder = 0;
        int currentSymbols = 0;
        while (wordsperline[line] > 0) {
            if (wordsperline[line] == 1) {
                outputWriter.write(worder.next());
            } else {
                currentSymbols = extraSymbols[line];
                remainder = currentSymbols % (wordsperline[line] - 1);
                for (int i = 0; i < wordsperline[line]; i++) {
                    
                }
            }
            line++;
        }
        outputWriter.close();
        System.out.println(input);
        System.out.println(max_width);
    }

    private static void exitWithMessage(String output, String message) throws IOException {
        FileWriter outputWriter = new FileWriter(output);
        outputWriter.write(message);
        outputWriter.close();
        System.exit(0);
    }
}
