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

        equalizeLength(_number, other._number, thisBase);

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

        shrinkLength(_number, thisBase);
        shrinkLength(other._number, otherBase);

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
            return thisSign && !otherSign;
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
        return getSignBit(signBit, base) > 0;
    }
}

