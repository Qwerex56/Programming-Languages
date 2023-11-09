package NumberCoder;

import java.util.ArrayList;
import java.util.List;

public class UBaseCoder implements NumberCoder {
    private final int base;

    public UBaseCoder(int base) {
        this.base = base;
    }

    @Override
    public List<Byte> codeNumber(long number) {
        boolean isNegative = false;
        List<Byte> numberInBase = new ArrayList<>();

        if (number < 0) {
            isNegative = true;
            number *= -1;
        }

        while (number > 0) {
            byte remainder = (byte) (number % base);
            number /= base;

            numberInBase.add(remainder);
        }

        // Add additional bit for sign
        numberInBase.add((byte) 0);

        if (isNegative) {
            convertToNeg(numberInBase);
        }

        return numberInBase;
    }

    @Override
    public long decodeNumber(List<Byte> codedNumber) {
        long accumulator = 0;
        int factor = 0;

        for (Byte frag : codedNumber) {
            accumulator += (long) (frag * Math.pow(base, factor));
            factor += 1;
        }

        if (codedNumber.get(codedNumber.size() - 1) >= base / 2) {
            System.out.println(codedNumber.get(codedNumber.size() - 1));
            accumulator -= (long) Math.pow(base, factor);
        }

        return accumulator;
    }

    @Override
    public byte getBase() {
        return (byte) base;
    }

    private void convertToNeg(List<Byte> number) {
        List<Byte> convertedNumber = new ArrayList<>();
        for (byte mag : number) {
            convertedNumber.add((byte) (base - 1 - mag));
        }

        int carry = 1;

        for (int i = 0; i < convertedNumber.size(); i++) {
            convertedNumber.set(i, (byte) (convertedNumber.get(i) + carry));
            if (convertedNumber.get(i) >= base) {
                convertedNumber.set(i, (byte) (convertedNumber.get(i) - base));
                carry = 1;
            } else {
                carry = 0;
            }
        }

        number.clear();
        number.addAll(convertedNumber);
    }
}
