import NumberCoder.NthBaseNumber;
import NumberCoder.UBaseCoder;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        UBaseCoder code = new UBaseCoder(10);
        NthBaseNumber num = new NthBaseNumber(10, code);
        NthBaseNumber num2 = new NthBaseNumber(20, code);

        System.out.println(num.add(num2).toString());
    }
}