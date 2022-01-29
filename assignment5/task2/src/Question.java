import org.w3c.dom.Element;

import java.util.List;

public class Question {
    protected String questiontext;
    protected String difficulty;

    public Question() {}

    public Question(Element element) {}
    public static void reorderQuestions(List<Question> questions) {}
    public static String print(List<Question> questions) { return null; }
    public static String printWithAnswers(List<Question> questions) { return null; }

    protected String toPrintable() { return null; }
    protected String toPrintableWithAnswers() { return null; }
}

class MultipleChoiceQuestion extends Question {
    public MultipleChoiceQuestion(Element element) {

    }
}

class TrueFalseQuestion extends Question {
    private String answer;
    public TrueFalseQuestion(Element element) {
        answer = element.getAttribute("answer");
        difficulty = element.getAttribute("difficulty");
        questiontext = element.getAttribute("questiontext");
    }

    @Override
    protected String toPrintable() {
        return this.difficulty + ") " + this.questiontext + "\nAnswer: true false (circle hte right answer)";
    }

    @Override
    protected String toPrintableWithAnswers() {
        return this.difficulty + ") " + this.questiontext + "\nAnswer: " + this.answer;
    }
}

class EssayQuestion extends Question {
    public EssayQuestion(Element element) {

    }
}

class ShortQuestion extends Question {
    public ShortQuestion(Element element) {

    }
}