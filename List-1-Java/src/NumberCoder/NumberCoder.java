package NumberCoder;

import java.util.List;

public interface NumberCoder {
    List<Byte> codeNumber(long numberToCode);
    long decodeNumber(List<Byte> numberToDecode);
    int getBase();
}