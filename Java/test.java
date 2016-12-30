import java.math.BigDecimal;
import java.math.MathContext;

/**
 * Created by aa on 24/12/16.
 */
public class test {
    public static void main(String[] args) {
        BigDecimal base = BigDecimal.valueOf(2147483645.4141948);
        BigDecimal product = base.pow(987654321);

        System.out.println("product = " + product.toPlainString());
    }

}
