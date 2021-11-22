import java.io.*;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class task {
    public static void main(String[] args) throws IOException {
//        String inputPath = "C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment4\\input.txt";
//        String outputPath = "C:\\Users\\79120\\Desktop\\ITP\\gits1p1\\assignment4\\output.txt";
        String inputPath = "input.txt";
        String outputPath = "output.txt";

        File inputFile = new File(inputPath);
        if (!inputFile.isFile()) exitWithMessage(outputPath, "Exception, file not found!");
        if (inputFile.length() == 0) exitWithMessage(outputPath, "Exception, file is empty!");
        if (inputFile.length() > 300) exitWithMessage(outputPath, "Exception, input exceeds text max size!");

        Scanner scan = new Scanner(inputFile);
        String input = scan.nextLine();
        int max_width = 0;

        try { max_width = scan.nextInt(); }
        catch (NoSuchElementException e) { exitWithMessage(outputPath, "Exception, intended line width is not specified!"); }
        if (max_width <= 0) exitWithMessage(outputPath, "Exception, line width cannot be negative or zero!");

        Scanner worder = new Scanner(input);
        worder.useDelimiter(" ");
        int[] wordsperline = new int[256];
        int[] extraSymbols = new int[256];
        int currentWidth = max_width;
        int currentLine = 0;
        char incorrect = 0;
        while (worder.hasNext()) {
            String word = worder.next();
            if (word.length() == 0) exitWithMessage(outputPath, "Exception, input contains an empty word!");
            for (int i = 0; i < word.length(); i++) {
                if (!isCorrectSymbol(word.charAt(i))) incorrect = word.charAt(i);
            }
            if (incorrect != 0) exitWithMessage(outputPath, "Exception, input contains forbidden symbol '" + incorrect + "'!");
            if (word.length() > 20) exitWithMessage(outputPath, "Exception, '" + word + "' exceeds the limit of 20 symbols!");
            if (word.length() > max_width) exitWithMessage(outputPath, "Exception, '" + word + "' exceeds "+String.valueOf(max_width)+" symbols!");
        }

        worder = new Scanner(input);
        worder.useDelimiter(" ");
        String word = worder.next();
        wordsperline[0] = 1;
        currentWidth -= word.length();
        int sum = word.length();
        while(worder.hasNext()) {
            word = worder.next();
            if (word.length() + 1 <= currentWidth) {
                wordsperline[currentLine]++;
                currentWidth -= word.length() + 1;
                sum += word.length();
            }
            else {
                extraSymbols[currentLine] = max_width - sum;
                currentLine++;
                currentWidth = max_width - word.length();
                wordsperline[currentLine]++;
                sum = word.length();
            }

        }

        FileWriter outputWriter = new FileWriter(outputPath);
        worder = new Scanner(input);
        worder.useDelimiter(" ");
        int line = 0;
        int remainder = 0;
        int minSymbols = 0;
        int currentSymbols = 0;
        while (wordsperline[line] > 0) {
            if (wordsperline[line] == 1) {
                outputWriter.write(worder.next());
            } else if (wordsperline[line + 1] > 0) {
                currentSymbols = extraSymbols[line];
                minSymbols = currentSymbols / (wordsperline[line] - 1);
                remainder = currentSymbols % (wordsperline[line] - 1);
                for (int i = 0; i < wordsperline[line] - 1; i++) {
                    outputWriter.write(worder.next());
                    int t = remainder > 0 ? 1: 0;
                    for (int space = 0; space < minSymbols + t; space++) outputWriter.write(" ");
                    if (remainder > 0) remainder--;
                }
                outputWriter.write(worder.next());
            } else {
                outputWriter.write(worder.next());
                for (int i = 1; i < wordsperline[line]; i++) {
                    outputWriter.write(' ' + worder.next());
                }
            }
            outputWriter.write('\n');
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

    private static boolean isCorrectSymbol(char c) {
        return (c >= 97 && c <= 122) || (c >= 65 && c <= 90) || ".,!?-:;()'\"".indexOf(c) >= 0;
    }
}
