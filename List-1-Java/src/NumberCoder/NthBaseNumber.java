package NumberCoder;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class NthBaseNumber {
    private final static int NATURAL_SYSTEM = 10;

    private List<Byte> _number;
    private NumberCoder _numberCoder;

    public NthBaseNumber(long init, NumberCoder nc) {
        _numberCoder = nc != null ? nc : new UBaseCoder(NATURAL_SYSTEM);
        _number = _numberCoder.codeNumber(init);
    }

    public NthBaseNumber(List<Byte> init, boolean isReversed, NumberCoder nc) {
        _numberCoder = nc != null ? nc : new UBaseCoder(NATURAL_SYSTEM);
        if (!isReversed) {
            Collections.reverse(init);
        }
        _number = new ArrayList<>(init);
    }

    public NthBaseNumber(NthBaseNumber other) {
        _numberCoder = other._numberCoder;
        _number = new ArrayList<>(other._number);
    }

    public NthBaseNumber(NthBaseNumber other, boolean isReversed) {
        _numberCoder = other._numberCoder;
        _number = new ArrayList<>(other._number);
        if (!isReversed) {
            Collections.reverse(_number);
        }
    }

    public NthBaseNumber negate() {
        System.out.println(_number);
        List<Byte> negated = negate(_number, _numberCoder.getBase());
        return new NthBaseNumber(negated, false, _numberCoder);
    }

    public boolean isNegative() {
        return isNegative(this);
    }

    public NthBaseNumber add(NthBaseNumber other) {
        int thisBase = _numberCoder.getBase();
        int otherBase = other._numberCoder.getBase();

        if (thisBase != otherBase) {
            other.changeBase(_numberCoder);
        }

        equalizeLength(_number, other._number, (byte) thisBase);

        int carry = 0;

        for (int i = 0; i < _number.size(); i++) {
            byte num1 = _number.get(i);
            byte num2 = other._number.get(i);

            num1 += num2 + carry;

            if (num1 >= thisBase) {
                carry = 1;
                num1 -= thisBase;
            } else {
                carry = 0;
            }

            _number.set(i, num1);
        }

        shrinkLength(_number, (byte) thisBase);
        shrinkLength(other._number, (byte) otherBase);

        return this;
    }

    public NthBaseNumber subtract(NthBaseNumber other) {
        return add(other.negate());
    }

    public NthBaseNumber multiply(NthBaseNumber other) {
        int thisBase = _numberCoder.getBase();
        int otherBase = other._numberCoder.getBase();

        if (thisBase != otherBase) {
            other.changeBase(_numberCoder);
        }

        int additionalZeros = 0;
        NthBaseNumber multiple = new NthBaseNumber(0, _numberCoder);
        NthBaseNumber sum = new NthBaseNumber(0, _numberCoder);

        for (byte factorNum2 : other._number) {
            int carry = 0;
            multiple = new NthBaseNumber(0, _numberCoder);
            for (byte factorNum1 : _number) {
                int smallSum = factorNum1 * factorNum2 + carry;

                if (smallSum > thisBase) {
                    carry = smallSum / thisBase;
                    smallSum %= thisBase;
                } else {
                    carry = 0;
                }

                multiple._number.add((byte) smallSum);
            }

            pushCarryOver(multiple, carry);
            sum.add(multiple);
            additionalZeros++;
        }

        _number = sum._number;
        return this;
    }

    public Tuple<NthBaseNumber, NthBaseNumber> slowDivision(NthBaseNumber lhs, NthBaseNumber rhs) {
        NthBaseNumber mem = new NthBaseNumber(0, lhs._numberCoder);
        mem._number = new ArrayList<>();

        NthBaseNumber result = new NthBaseNumber(0, lhs._numberCoder);
        result._number = new ArrayList<>();
        List<Byte> resultNum = result._number;

        Runnable divide = () -> {
            NthBaseNumber partQuot = new NthBaseNumber(0, lhs._numberCoder);
            NthBaseNumber remainder = new NthBaseNumber(0, lhs._numberCoder);

            for (int i = 0; i < lhs._numberCoder.getBase(); i++) {
                NthBaseNumber factor = new NthBaseNumber(i, lhs._numberCoder);
                NthBaseNumber part = rhs.multiply(factor);

                shrinkLength(mem._number, mem._numberCoder.getBase());
                if (mem.lessThan(part)) {
                    partQuot = new NthBaseNumber(--i, lhs._numberCoder);
                    break;
                }
            }

            remainder = mem.subtract(rhs.multiply(partQuot));

            mem._number.clear();
            mem._number.add((byte) 0);
            mem._number.addAll(0, remainder._number.subList(0, 1));

            resultNum.addAll(0, partQuot._number);
        };

        List<Byte> lhsNumbers = lhs._number;
        Collections.reverse(lhsNumbers);
        for (Byte item : lhsNumbers) {
            mem._number.add(0, item);
            divide.run();
        }

        NthBaseNumber modulo = mem;
        return new Tuple<>(result, modulo);
    }

    public class Tuple<X, Y> {
        public final X first;
        public final Y second;

        public Tuple(X first, Y second) {
            this.first = first;
            this.second = second;
        }
    }

    public NthBaseNumber increment() {
        NthBaseNumber inc = new NthBaseNumber(1, _numberCoder);
        add(inc);
        return this;
    }

    public NthBaseNumber clone() {
        return new NthBaseNumber(this);
    }

    public boolean equals(NthBaseNumber other) {
        if (_number.size() != other._number.size()) {
            return false;
        }

        for (int i = 0; i < _number.size(); i++) {
            if (!other._number.get(i).equals(_number.get(i))) {
                return false;
            }
        }

        return true;
    }

    public boolean lessThan(NthBaseNumber other) {
        boolean thisSign = getSignBit(_number.get(_number.size() - 1), _numberCoder.getBase()) > 0;
        boolean otherSign = getSignBit(other._number.get(other._number.size() - 1), other._numberCoder.getBase()) > 0;
        boolean areBothNegative = isNegative() && other.isNegative();

        if (thisSign != otherSign) {
            return thisSign;
        }

        if (_number.size() < other._number.size()) {
            return !areBothNegative;
        }

        if (_number.size() > other._number.size()) {
            return areBothNegative;
        }

        for (int i = _number.size() - 1; i >= 0; i--) {
            if (_number.get(i) < other._number.get(i)) {
                return true;
            } else if (_number.get(i) > other._number.get(i)) {
                return false;
            }
        }

        return false;
    }

    public boolean greaterThan(NthBaseNumber other) {
        return other.lessThan(this);
    }

    public boolean lessThanOrEqualTo(NthBaseNumber other) {
        return !greaterThan(other);
    }

    public boolean greaterThanOrEqualTo(NthBaseNumber other) {
        return !lessThan(other);
    }

    @Override
    public String toString() {
        List<Byte> reversedNumber = new ArrayList<>(_number);
        Collections.reverse(reversedNumber);

        StringBuilder result = new StringBuilder();

        for (byte frag : reversedNumber) {
            if (frag > 9) {
                result.append((char) (frag + 55));
            } else {
                result.append((int) frag);
            }
        }

        Collections.reverse(reversedNumber);
        return result.toString();
    }

    private void changeBase(NumberCoder newNc) {
        long numberCache = _numberCoder.decodeNumber(_number);
        _number.clear();

        _numberCoder = newNc;

        _number = _numberCoder.codeNumber(numberCache);
    }

    private boolean isNegative(NthBaseNumber what) {
        byte signBit = what._number.get(what._number.size() - 1);
        int base = what._numberCoder.getBase();
        return getSignBit(signBit, (byte) base) > 0;
    }

    public static List<Byte> negate(List<Byte> numToNegate, byte base) {
        List<Byte> negative = new ArrayList<Byte>();

        for (int i = 0; i < numToNegate.size(); i++) {
            negative.add((byte) (base - 1));
        }

        int carry = 1;
        equalizeLength(numToNegate, negative, base);

        for (int i = 0; i < negative.size(); i++) {
            negative.set(i, (byte) (negative.get(i) - numToNegate.get(i)));
        }

        for (byte mag : negative) {
            mag += (byte) carry;
            if (mag >= base) {
                mag -= base;
                carry = 1;
            }
            else {
                carry = 0;
            }
        }

        shrinkLength(negative, base);
        return negative;
    }

    public static void equalizeLength(List<Byte> lhs, List<Byte> rhs, byte base) {
        int lenDiff = Math.abs(lhs.size() - rhs.size()) + 1;

        if (lhs.size() < rhs.size()) {
            for (int i = 0; i < lenDiff; i++) {
                lhs.add(NthBaseNumber.getSignBit(lhs.get(lhs.size() - 1), base));
            }
            rhs.add(NthBaseNumber.getSignBit(rhs.get(rhs.size() - 1), base));
        } else {
            for (int i = 0; i < lenDiff; i++) {
                if (!rhs.isEmpty())
                    rhs.add(NthBaseNumber.getSignBit(rhs.get(rhs.size() - 1), base));
            }
            lhs.add(NthBaseNumber.getSignBit(lhs.get(lhs.size() - 1), base));
        }
    }

    public static void shrinkLength(List<Byte> rhs, byte base) {
        int what = base / 2;

        java.util.function.Predicate<Byte> biggerEqual = i -> i >= what;

        java.util.function.Consumer<List<Byte>> shrink = vec -> {
            int posToDel = 1;

            if (biggerEqual.test(vec.getLast())) {
                while (vec.get(vec.size() - posToDel) >= base / 2) {
                    posToDel++;
                }
            } else {
                while (vec.get(vec.size() - posToDel) == 0 && vec.size() - posToDel > 0) {
                    posToDel++;
                }
            }

            posToDel -= 2;

            for (int i = 0; i < posToDel; i++) {
                vec.remove(vec.size() - 1);
            }
        };

        shrink.accept(rhs);
    }

    public static void pushCarryOver(NthBaseNumber where, int carry) {
        List<Byte> number = where._number;

        List<Byte> codedCarry = where._numberCoder.codeNumber(carry);

        if (codedCarry.get(codedCarry.size() - 1) == 0) {
            codedCarry.remove(codedCarry.size() - 1);
        }

        number.addAll(codedCarry);
    }

    public static byte getSignBit(byte sign, byte base) {
        return sign >= (base / 2) ? sign : 0;
    }
}

