import org.w3c.dom.Element;

class NoSuchQuestionType extends Exception { }

public class QuestionFactory {
    public QuestionFactory() {

    }

    public Question createQuestion(String questiontype, Element element) {
        if (questiontype == "multichoice") return new MultipleChoiceQuestion(element);
        if (questiontype == "truefalse") return new TrueFalseQuestion(element);
        if (questiontype == "essay") return new EssayQuestion(element);
        if (questiontype == "short") return new ShortQuestion(element);
        return null;
    }
}
