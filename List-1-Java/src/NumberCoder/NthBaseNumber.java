package NumberCoder;

import org.jetbrains.annotations.Contract;

import java.util.LinkedList;
import java.util.Objects;

public class NthBaseNumber {
    private LinkedList<Integer> _number = new LinkedList<>();
    private int _base = 10;

    public int getBase() { return _base; }

    public NthBaseNumber(int base) {
        _base = base;
    }

    public NthBaseNumber(long number, int base) {
        _base = base;
        _number = Convert(number, _base);
    }

    public NthBaseNumber(NthBaseNumber rhs) {
        if (this == rhs) {
            return;
        }

        _number = new LinkedList<>(rhs._number);
        _base = rhs._base;
    }

    public NthBaseNumber Add(NthBaseNumber rhs) {
        var carry = 0;
        final var result = new NthBaseNumber(getBase());
        final var len = Math.max(_number.size(), rhs._number.size());

        for (var digIdx = 0; digIdx < len; digIdx++) {
            var digLhs = tryGetNumberInList(_number, digIdx);
            var digRhs = tryGetNumberInList(rhs._number, digIdx);

            var sum = digLhs + digRhs + carry;
            if (sum >= _base) {
                carry = 1;
                sum -= _base;
            }

            result._number.addLast(sum);
        }

        return result;
    }

    public NthBaseNumber Subtract(NthBaseNumber rhs) {
        return Add(NthBaseNumber.Negative(rhs));
    }

    public NthBaseNumber Multiply(NthBaseNumber rhs) {
        var signLeft = _number.getLast();
        var signRight = rhs._number.getLast();

        if (signLeft == _base - 1 && signRight == 0) {
            return rhs.Multiply(this);
        }

        if (signLeft == _base - 1 && signRight == _base - 1) {
            var negLeft = Negative(this);
            var negRight = Negative(rhs);
            return negRight.Multiply(negLeft);
        }

        var result = new NthBaseNumber(0, getBase());
        var preZeros = 0;

        _number.addLast(0);
        _number.addLast(0);

        for (var digRhs : rhs._number) {
            var carry = 0;
            var partResult = new NthBaseNumber(getBase());

            for (int i = 0; i < preZeros; i++) {
                partResult._number.addFirst(0);
            }
            ++preZeros;

            for (var digLhs : _number) {
                var partResultInt = digLhs * digRhs + carry;

                carry = partResultInt / getBase();
                partResult._number.addLast(partResultInt % getBase());
            }

            result = result.Add(partResult);
        }

        if (rhs._number.getLast() >= (getBase() - 1) / 2) {
            var negative = Negative(new NthBaseNumber(this));
            for (int i = 0; i < preZeros; i++) {
                negative._number.addFirst(0);
            }

            result = result.Add(negative);
        }

        shrinkList(result._number);
        return result;
    }

    public static LinkedList<Integer> Convert(long number, int base) {
        var list = new LinkedList<Integer>();

        var isNegative = number < 0;
        number = Math.abs(number);

        while (number > 0) {
            var mod = number % base;
            number /= base;
            list.addLast((int)mod);
        }

        list.addLast(0);

        if (!isNegative) {
            shrinkList(list);
            return list;
        }

        list.replaceAll(digit -> (base - 1) - digit);

        var carry = 1;
        for (int digitIdx = 0; digitIdx < list.size(); digitIdx++) {
            var digit = list.get(digitIdx) + carry;

            if (digit >= base) {
                digit -= base;
            } else {
                carry = 0;
            }

            list.set(digitIdx, digit);

            if (carry == 0) {
                break;
            }
        }

        shrinkList(list);
        return list;
    }

    boolean equals(NthBaseNumber rhs) {
        if (_number.size() != rhs._number.size()) {
            return false;
        }

        var signLhs = _number.getLast();
        var signRhs = rhs._number.getLast();

        if (!Objects.equals(signLhs, signRhs)) {
            return false;
        }

        for (int idx = 0; idx < _number.size(); idx++) {
            var left = _number.get(idx);
            var right = rhs._number.get(idx);

            if (!Objects.equals(left, right)) {
                return false;
            }
        }

        return true;
    }

    boolean isLess(NthBaseNumber rhs) {
        var signLhs = _number.getLast();
        var signRight = rhs._number.getLast();

        if (!signLhs.equals(signRight)) {
            return signLhs > signRight;
        }

        if (_number.size() != rhs._number.size()) {
            return _number.size() < rhs._number.size();
        }

        var left = _number.getFirst();
        var right = _number.getFirst();
        for (int idx = 0; idx < _number.size(); idx++) {
            left = _number.get(idx);
            right = rhs._number.get(idx);

            if (Objects.equals(left, _number.getLast())) {
                return false;
            }
        }

        return left < right;
    }

    @Override
    @Contract(value = "null -> false", pure = true)
    public boolean equals(Object rhs) {
        var bRhs = (NthBaseNumber)rhs;
        if (_number.size() != bRhs._number.size()) {
            return false;
        }

        var signLhs = _number.getLast();
        var signRhs = bRhs._number.getLast();

        if (!Objects.equals(signLhs, signRhs)) {
            return false;
        }

        for (int idx = 0; idx < _number.size(); idx++) {
            var left = _number.get(idx);
            var right = bRhs._number.get(idx);

            if (!Objects.equals(left, right)) {
                return false;
            }
        }

        return true;
    }

    public static NthBaseNumber Negative(NthBaseNumber nthBaseNumber) {
        var negative = new NthBaseNumber(nthBaseNumber);
        final var base = negative.getBase();

        negative._number.replaceAll(digit -> (base - 1) - digit);

        var carry = 1;
        for (int digitIdx = 0; digitIdx < negative._number.size(); digitIdx++) {
            var digit = negative._number.get(digitIdx) + carry;

            if (digit >= base) {
                digit -= base;
            } else {
                carry = 0;
            }

            negative._number.set(digitIdx, digit);

            if (carry == 0) {
                break;
            }
        }

        shrinkList(negative._number);
        return negative;
    }

    private int tryGetNumberInList(LinkedList<Integer> list, int idx) {
        int item;
        try {
            item = list.get(idx);
        } catch (IndexOutOfBoundsException err) {
            item = list.getLast();
        }

        return item;
    }

    private static void shrinkList(LinkedList<Integer> list) {
        var stopSign = list.getLast();

        for (int digIdx = list.size() - 1; digIdx >= 0; digIdx--) {
            if (!list.get(digIdx).equals(stopSign)) {
                break;
            }

            list.removeLast();
        }

        list.addLast(stopSign);
    }

    @Override
    public String toString() {
        return _number.toString();
    }

    @Override
    public int hashCode() {
        var sum = 0;
        int i = 0;
        for (; i < _number.size(); i++) {
            sum += _number.get(i) * (int) Math.pow(_base, i);
        }

        if (_number.getLast() == getBase() - 9) {
            sum -= (int) Math.pow(_base, i);
        }

        return sum;
    }
}

