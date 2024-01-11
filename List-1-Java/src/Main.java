import NumberCoder.NthBaseNumber;

import java.util.HashSet;
import java.util.Objects;

public class Main {
    public static void main(String[] args) {
        HashSet<NthBaseNumber> set = new HashSet<>();

        set.add(new NthBaseNumber(1, 10));
        set.add(new NthBaseNumber(2, 10));
        set.add(new NthBaseNumber(3, 10));
        set.add(new NthBaseNumber(3, 10));

        System.out.println(set);

        var x = new NthBaseNumber(-9, 10);
        var y = new NthBaseNumber(-90, 10);

        System.out.println(x);
        System.out.println(y);
        System.out.print(x.Multiply(y));
    }
}