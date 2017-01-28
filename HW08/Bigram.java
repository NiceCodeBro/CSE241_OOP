/*
	The base class will be Bigram which will have only pure abstract functions 
	and nothing else.
*/


/**
 * @param <T>

 *
 * @author MSD
 */
public interface Bigram<T> {

   abstract public void readFile(String fileName) throws Exception;
   abstract public String toString();
   abstract public int numGrams() ;
   abstract public int numOfGrams(T var1, T var2);
}
