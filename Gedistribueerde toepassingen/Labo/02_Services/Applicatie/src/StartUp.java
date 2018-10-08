
import be.tiwi.woordenboek.data.ArrayOfDictionaryWord;
import be.tiwi.woordenboek.data.DictService;
import be.tiwi.woordenboek.data.DictionaryWord;
import be.tiwi.woordenboek.gui.WoordenboekFrame;
import java.util.List;
import java.util.Scanner;

public class StartUp {

    public static void main(String[] args) {
        WoordenboekFrame f = new WoordenboekFrame();
        f.show();
    }

    void consoleApplicatie() {
        Scanner s = new Scanner(System.in);
        System.out.println("Geef tekst:");
        String zin = "web servizes are kool";
        DictService service = new DictService();

        for (String woord : zin.split(" ")) {
            System.out.print(woord + " - > ");
            ArrayOfDictionaryWord a = service.getDictServiceSoap().match(woord, "lev");
            List<DictionaryWord> d = a.getDictionaryWord();
            d.forEach((w) -> {
                System.out.print(w.getWord() + " ");
            });
            System.out.println();
        }
    }
}
