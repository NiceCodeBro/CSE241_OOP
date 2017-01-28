/*
	this header for throw exception
*/
/**
 * @author MSD
 */
public class myException extends Exception {
    protected String error;
    public myException(String errorMssg){    this.error = errorMssg;    }
    public String toString(){   return this.error;   }
}
