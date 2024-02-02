package NumberCoder;

import org.jetbrains.annotations.Contract;

public class NthBaseRational {
    private final NthBaseNumber _numerator;
    private final NthBaseNumber _denominator;

    public NthBaseRational(NthBaseNumber numerator, NthBaseNumber denominator) {
        _numerator = new NthBaseNumber(numerator);
        _denominator = new NthBaseNumber(denominator);
    }

    public NthBaseRational Add(NthBaseRational rhs) {
        var numeratorLhs = this._numerator.Multiply(rhs._denominator);
        var numeratorRhs = rhs._numerator.Multiply(this._denominator);

        var numerator = numeratorLhs.Add(numeratorRhs);
        var denominator = this._denominator.Multiply(rhs._denominator);

        return new NthBaseRational(numerator, denominator);
    }

    public NthBaseRational Subtract(NthBaseRational rhs) {
        var numeratorLhs = this._numerator.Multiply(rhs._denominator);
        var numeratorRhs = rhs._numerator.Multiply(this._denominator);

        var numerator = numeratorLhs.Subtract(numeratorRhs);
        var denominator = this._denominator.Multiply(rhs._denominator);

        return new NthBaseRational(numerator, denominator);
    }

    public NthBaseRational Multiply(NthBaseRational rhs) {
        var numerator = this._numerator.Multiply(rhs._denominator);
        var denominator = this._denominator.Multiply(rhs._denominator);

        return new NthBaseRational(numerator, denominator);
    }

    @Override
    @Contract(value = "null -> false", pure = true)
    public boolean equals(Object rhs) {
        var _rhs = (NthBaseRational) rhs;

        var numeratorLhs = this._numerator.Multiply(_rhs._denominator);
        var numeratorRhs = _rhs._numerator.Multiply(this._denominator);

        return numeratorLhs.equals(numeratorRhs);
    }

    @Override
    public int hashCode() {
        return _numerator.hashCode() + _denominator.hashCode();
    }
}
